#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int puerto = 7202;

int es_primo(unsigned int num, int r, int r1){
   for(int i = r; i < r1; i++){
      if(num % i == 0){
           return 0;
      }
   }
   return 1;
}

int main(int argc, char *argv[]){
   unsigned int num;
   int s, res, clilen, rango_1, rango_2;
   int primo;
   struct sockaddr_in server_addr, msg_to_client_addr;
   
   s = socket(AF_INET, SOCK_DGRAM, 0);
   
   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(puerto);
   bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
   clilen = sizeof(msg_to_client_addr);

   recvfrom(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
   recvfrom(s, (char *)&rango_1, sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
   recvfrom(s, (char *)&rango_2, sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);

   printf("%u\n",num );
   res=es_primo(num, rango_1, rango_2);
   //printf("%d\n",res );
   sendto(s, (char *)&res, sizeof(int), 0, (struct sockaddr *)&msg_to_client_addr, clilen);
}