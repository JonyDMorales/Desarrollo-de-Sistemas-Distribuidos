#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int puerto = 7200;

int es_primo(unsigned int n){
	for(int i = (n/2); i < n ; i++)
		if((n % i) == 0)
			return 0;
return 1;
}

int main(int argc, char *argv[]){
	struct sockaddr_in msg_to_server_addr, client_addr;
   	int s, num;
   	unsigned int p;
   	unsigned char contenido[4];
   	s = socket(AF_INET, SOCK_DGRAM, 0);
   	
   	/* rellena la dirección del servidor */
   	bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   	msg_to_server_addr.sin_family = AF_INET;
   	msg_to_server_addr.sin_addr.s_addr = inet_addr(argv[1]);
   	msg_to_server_addr.sin_port = htons(atoi(argv[2]));
   	memcpy(contenido,&msg_to_server_addr.sin_addr.s_addr,4);

   	/* rellena la direcciòn del cliente*/
   	bzero((char *)&client_addr, sizeof(client_addr));
   	client_addr.sin_family = AF_INET;
   	client_addr.sin_addr.s_addr = INADDR_ANY;
   
   	/*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
   	client_addr.sin_port = htons(0);
   	bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
   	
   	num = 2; /*rellena el mensaje */
   	sendto(s, (char *) &num, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr, sizeof(msg_to_server_addr));

   	/* se bloquea esperando respuesta */
   	recvfrom(s, (char *) &p, sizeof(unsigned int), 0, NULL, NULL);
      printf("El numero que resolveremos es: %u\n", p);
   	num = es_primo(p);
   	
   	sendto(s, (char *) &num, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr, sizeof(msg_to_server_addr));

  	close(s);
return 0;
}