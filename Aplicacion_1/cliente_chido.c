#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
   struct sockaddr_in msg_to_server_addr1,msg_to_server_addr2,msg_to_server_addr3,msg_to_server_addr4, client_addr;
   int s, res1,res2,res3,res4;
   unsigned int num=atoi(argv[1]);
   s = socket(AF_INET, SOCK_DGRAM, 0);
   /* rellena la dirección del servidor */
   bzero((char *)&msg_to_server_addr1, sizeof(msg_to_server_addr1));
   msg_to_server_addr1.sin_family = AF_INET;
   msg_to_server_addr1.sin_addr.s_addr = inet_addr("192.168.0.105");
   msg_to_server_addr1.sin_port = htons(7202);

   bzero((char *)&msg_to_server_addr2, sizeof(msg_to_server_addr2));
   msg_to_server_addr2.sin_family = AF_INET;
   msg_to_server_addr2.sin_addr.s_addr = inet_addr("192.168.0.113");
   msg_to_server_addr2.sin_port = htons(7201);

   bzero((char *)&msg_to_server_addr3, sizeof(msg_to_server_addr3));
   msg_to_server_addr3.sin_family = AF_INET;
   msg_to_server_addr3.sin_addr.s_addr = inet_addr("192.168.0.108");
   msg_to_server_addr3.sin_port = htons(7200);

   bzero((char *)&msg_to_server_addr4, sizeof(msg_to_server_addr4));
   msg_to_server_addr4.sin_family = AF_INET;
   msg_to_server_addr4.sin_addr.s_addr = inet_addr("127.0.0.1");
   msg_to_server_addr4.sin_port = htons(7203);


   bzero((char *)&client_addr, sizeof(client_addr));
   client_addr.sin_family = AF_INET;
   client_addr.sin_addr.s_addr = INADDR_ANY;
   
   /*Se calculan los rangos*/
   int rango_0 = 2;
   int rango_1 = num * 0.19;
   int rango_2 = num * 0.22;
   int rango_3 = num * 0.258;
   int rango_4 = num * 0.329;
   

   printf("Rango 1: %d\n", rango_1);
   printf("Rango 2: %d\n", rango_2);
   printf("Rango 3: %d\n", rango_3);
   printf("Rango 4: %d\n", rango_4);

   /*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
   client_addr.sin_port = htons(0);
   bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
   
   /*Servidor 1*/
   sendto(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr1, sizeof(msg_to_server_addr1));
   sendto(s, (char *)&rango_1, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr1, sizeof(msg_to_server_addr1));
   sendto(s, (char *)&rango_2, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr1, sizeof(msg_to_server_addr1));

   /*Servidor 2*/
   sendto(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr2, sizeof(msg_to_server_addr2));
   sendto(s, (char *)&rango_2, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr2, sizeof(msg_to_server_addr2));
   sendto(s, (char *)&rango_3, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr2, sizeof(msg_to_server_addr2));

   /*Servidor 3*/
   sendto(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr3, sizeof(msg_to_server_addr3));
   sendto(s, (char *)&rango_3, sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr3, sizeof(msg_to_server_addr3));
   //sendto(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr3, sizeof(msg_to_server_addr3));

   /*Servidor 4*/
   sendto(s, (char *)&num, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr4, sizeof(msg_to_server_addr4));
   sendto(s, (char *)&rango_0, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr4, sizeof(msg_to_server_addr4));
   sendto(s, (char *)&rango_1, sizeof(unsigned int), 0, (struct sockaddr *) &msg_to_server_addr4, sizeof(msg_to_server_addr4));

   /*Se recibe respuesta*/
   recvfrom(s, (char *)&res1, sizeof(int), 0, NULL, NULL);
   printf("Respuesta 1: %d\n",res1);
   recvfrom(s, (char *)&res2, sizeof(int), 0, NULL, NULL);
   printf("Respuesta 2: %d\n",res2);
   recvfrom(s, (char *)&res3, sizeof(int), 0, NULL, NULL);
   printf("Respuesta 3: %d\n",res3);
   recvfrom(s, (char *)&res4, sizeof(int), 0, NULL, NULL);
   printf("Respuesta 4: %d\n",res4);

   if(res1*res2*res3*res4==1)
      printf("\nEs primo B)\n");
   else
      printf("\nNo es primo :(\n");

   close(s);
}
