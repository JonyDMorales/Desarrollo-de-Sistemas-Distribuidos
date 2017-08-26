#include "SocketMulticast.h"
#include "PaqueteDatagrama.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstdio>
#include <signal.h>

void tratar_alarma(int sig);

SocketMulticast::SocketMulticast(int port) {
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
        printf("ERROR EN LA CREACION DEL SOCKET!!!\n");
    else {
        bzero((char*) &direccionLocal, sizeof(direccionLocal));
        direccionLocal.sin_family = AF_INET;
        direccionLocal.sin_addr.s_addr = INADDR_ANY;
        direccionLocal.sin_port = htons(port);
        bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
        bzero((char*) &direccionForanea, sizeof(direccionForanea));
        direccionForanea.sin_family = AF_INET;
    }
}

SocketMulticast::~SocketMulticast() {
    close(s);
}

int SocketMulticast::recibe(PaqueteDatagrama &p, char *ipE) {
    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(ipE);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &multicast, sizeof(struct ip_mreq));

    unsigned int length = sizeof(direccionForanea);
    int bytes = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &length);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));

    setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void*) &multicast, sizeof(struct ip_mreq));

    return bytes;
}

int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char TTL){
    setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void*) &TTL, sizeof(TTL));
    direccionForanea.sin_port = htons(p.obtienePuerto());
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    gettimeofday(&tiempoInicial, NULL);
    return sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}

int SocketMulticast::recibeTimeout(PaqueteDatagrama &p, char *ipE) {
    int bytes;
    struct timeval tiempoDif;

    struct sigaction act;
    sigset_t mask;
    act.sa_handler =  tratar_alarma; /*funcion a ejecutar */
    act.sa_flags = 0; /* Ninguna accion especifica */
    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    sigaction(SIGALRM, &act, NULL);

    struct itimerval intervalo;
    intervalo.it_interval.tv_sec = 0;
    intervalo.it_interval.tv_usec = 0;
    intervalo.it_value.tv_sec = tiempo.tv_sec ;
    intervalo.it_value.tv_usec = tiempo.tv_usec ;

    if (timeout) {
        if (tiempo.tv_sec != 0)
            alarm(tiempo.tv_sec);
        else
            ualarm(tiempo.tv_usec,0);
    }

    bytes = recibe(p, ipE);

    setitimer(ITIMER_REAL, &intervalo, NULL);
    gettimeofday(&tiempoFinal, NULL);

    unsetTimeout();
    return bytes;
}

void tratar_alarma(int sig) {
    //printf("Alarma activada \n");
}

void SocketMulticast::setTimeout(time_t segundos, suseconds_t microsegundos) {
    if (segundos != 0 || microsegundos != 0) {
        if (segundos != 0)
            tiempo.tv_sec = segundos;
        if (microsegundos != 0)
            tiempo.tv_usec = microsegundos;
        timeout = 1;
    } else {
        timeout = 0;
    }
}

void SocketMulticast::unsetTimeout(){
    if (timeout)
        alarm(0);
}

void SocketMulticast::setBroadcast() {
    int yes = 1;
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
}

void SocketMulticast::unsetBroadcast() {
    int no = 0;
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &no, sizeof(int));
}
