#ifndef SOCKET_MULTICAST_H
#define SOCKET_MULTICAST_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "PaqueteDatagrama.h"
#include <netinet/in.h>

class SocketMulticast {
public:
    SocketMulticast(int);
    ~SocketMulticast();
    int recibe(PaqueteDatagrama &p, char *ipE);
    int envia(PaqueteDatagrama &p, unsigned char TTL);
    int recibeTimeout(PaqueteDatagrama &p, char *ipE);
    void setTimeout(time_t segundos, suseconds_t microsegundos);
    void unsetTimeout();
    void setBroadcast();
    void unsetBroadcast();
private:
    struct timeval tiempo;
    struct timeval tiempoInicial;
    struct timeval tiempoFinal;
    bool timeout;
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    int s;

};

#endif
