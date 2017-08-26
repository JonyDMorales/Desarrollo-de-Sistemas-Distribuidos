#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int puerto = 7200;

int main(int argc, char *argv[]) {
   unsigned int primo = atoi(argv[1]);
   int s, clilen_1, clilen_2, clilen_3, clilen_4, num_1 = 0 , num_2 = 0, num_3 = 0, num_4 = 0;
   struct sockaddr_in server_addr, addr_1, addr_2, addr_3, addr_4 ;
   
   s = socket(AF_INET, SOCK_DGRAM, 0);
   
   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(puerto);
   bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));

   clilen_1 = sizeof(addr_1);
   clilen_2 = sizeof(addr_2);
   clilen_3 = sizeof(addr_3);
   clilen_4 = sizeof(addr_4);
   printf("El numero que quieres saber si es primo es %u:\n", primo);

   //while(1) {
      //scanf("%u", &primo);
      
      recvfrom(s, (char *) &num_1, sizeof(int), 0, (struct sockaddr *) &addr_1, &clilen_1);
      printf("Cliente 1 conectado: %d\n", num_1);

      recvfrom(s, (char *) &num_2, sizeof(int), 0, (struct sockaddr *)&addr_2, &clilen_2);
      printf("Cliente 2 conectado: %d\n", num_2);

      recvfrom(s, (char *) &num_3, sizeof(int), 0, (struct sockaddr *)&addr_3, &clilen_3);
      printf("Cliente 3 conectado: %d\n", num_2);

      recvfrom(s, (char *) &num_4, sizeof(int), 0, (struct sockaddr *)&addr_4, &clilen_4);
      printf("Cliente 4 conectado: %d\n", num_4);


      /* envía la petición al cliente. La estructura msg_to_client_addr contiene la dirección socket del cliente */
      sendto(s, (char *) &primo, sizeof(unsigned int), 0, (struct sockaddr *)&addr_1, clilen_1);
      sendto(s, (char *) &primo, sizeof(unsigned int), 0, (struct sockaddr *)&addr_2, clilen_2);
      sendto(s, (char *) &primo, sizeof(unsigned int), 0, (struct sockaddr *)&addr_3, clilen_3);
      sendto(s, (char *) &primo, sizeof(unsigned int), 0, (struct sockaddr *)&addr_4, clilen_4);

      recvfrom(s, (char *) &num_1, sizeof(int), 0, (struct sockaddr *)&addr_1, &clilen_1);
      recvfrom(s, (char *) &num_2, sizeof(int), 0, (struct sockaddr *)&addr_2, &clilen_2);
      recvfrom(s, (char *) &num_3, sizeof(int), 0, (struct sockaddr *)&addr_3, &clilen_3);
      recvfrom(s, (char *) &num_4, sizeof(int), 0, (struct sockaddr *)&addr_4, &clilen_4);

      if (num_1*num_2*num_3*num_4 == 0)
         printf("\nEl numero no es primo :(\n");
      else
         printf("\nEl numero es primo B)\n");
   //}
}