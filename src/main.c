/* name : main.c
 * author : matheo thomas
 * date : 11-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <math.h>
#include <complex.h>
#include <time.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "rsa.h"
#include "network.h"



int main(int argc, char *argv[]){

	if(argc >= 2){
		if(strcmp(argv[1], "server") == 0){
			pubKey *pub = (pubKey *)malloc(sizeof(pubKey));
			priKey *pri = (priKey *)malloc(sizeof(priKey));
			genKeys(pub, pri);
			printf("Server keys : %lld\n              %lld\n              %lld\n              %lld\n\n", pub->mod, pub->exp, pri->mod, pri->exp);

			netParams p = mainNetworkServ();

			sleep(1);
			/* Public key exchange */
			char buffer[1024] = { 0 };
			char *s = (char *)malloc(255*sizeof(char));
			snprintf(s, 255, "%lld", pub->mod);

			send(p.new_socket, s, strlen(s), 0);
			p.valread = read(p.new_socket, buffer, 1024-1);
			//printf("buffer : %s\n", buffer);
			char *ptr;
			long long res = strtol(buffer, &ptr, 10);
			printf("res : %lld\n", res);
			sleep(1);

			fflush(stdin);
			fflush(stdout);

			/* Message exchange */
			char s1[255];
			printf("Enter message : ");
			scanf("%s", s1);
			//s[strlen(s)] = '\n';
			printf("s1 : %s\n", s1);
			sleep(1);

			char *toSend = (char *)malloc(255*sizeof(char));
			snprintf(toSend, 255, "%s", s1);
			printf("toSend : %s\n", toSend);
			sleep(1);
			memset(buffer, 0, sizeof(buffer));

			send(p.new_socket, toSend, strlen(toSend), 0);
			sleep(1);

			p.valread = read(p.new_socket, buffer, 1024-1);

			printf("buffer : %s\n", buffer);



		} else if(strcmp(argv[1], "client") == 0){
			if(argc >= 3){
				char *IPADDR = argv[2];
				pubKey *pub = (pubKey *)malloc(sizeof(pubKey));
				priKey *pri = (priKey *)malloc(sizeof(priKey));
				genKeys(pub, pri);
				printf("Client keys : %lld\n              %lld\n              %lld\n              %lld\n\n", pub->mod, pub->exp, pri->mod, pri->exp);

				netParams p = mainNetworkClient(IPADDR);

				sleep(1);
				/* public key exchange */
				char buffer[1024];
				char *s = (char *)malloc(255*sizeof(char));
				snprintf(s, 255, "%lld", pub->mod);

				send(p.client_fd, s, strlen(s), 0);
				p.valread = read(p.client_fd, buffer, 1024-1);
				//printf("buffer : %s\n", buffer);
				char *ptr;
				long long res = strtol(buffer, &ptr, 10);
				printf("res : %lld\n", res);
				sleep(1);

				fflush(stdin);
				fflush(stdout);

				/* Message exchange */
				char s1[255];
				printf("Enter message : ");
				scanf("%s", s1);
				//s[strlen(s)] = '\n';
				printf("s1 : %s\n", s1);
				fflush(stdin);
				sleep(1);

				char *toSend = (char *)malloc(255*sizeof(char));
				snprintf(toSend, 255, "%s", s1);
				printf("toSend : %s\n", toSend);
				sleep(1);
				memset(buffer, 0, sizeof(buffer));

				send(p.new_socket, toSend, strlen(toSend), 0);
				sleep(1);

				p.valread = read(p.new_socket, buffer, 1024-1);

				printf("buffer : %s\n", buffer);

				/*
				   printf("Enter message : ");
				   scanf("%s", s);
				   send(p.client_fd, s, strlen(s), 0);
				   p.valread = read(p.client_fd, buffer, 1024-1);

				   printf("%s\n", buffer);
				   */


			} else {
				fprintf(stderr, "Not enough parameters.\n");
			}
		} else {
			fprintf(stderr, "Wrong parameter.\n");
		}
	} else {
		fprintf(stderr, "Not enough parameters.\n");
	}




	/*
	   pubKey *pub = (pubKey *)malloc(sizeof(pubKey));
	   priKey *pri = (priKey *)malloc(sizeof(priKey));
	   genKeys(pub, pri);
	   printf("%lld\n%lld\n%lld\n%lld\n", pub->mod, pub->exp, pri->mod, pri->exp);


	   char msg[] = "Coucou ceci est un test de l'algorithme de RSA !";
	   for(int i = 0; i < strlen(msg); i++){
	   printf("%c", (long long)msg[i]);
	   }
	   printf("\n");
	   long long *encrypted = rsaEncrypt(msg, sizeof(msg), pub);

	   for(int i = 0; i < strlen(msg); i++){
	   printf("%lld\n", (long long)encrypted[i]);
	   }

	   char *decrypted = rsaDecrypt(encrypted, 8*sizeof(msg), pri);
	   for(int i = 0; i < strlen(msg); i++){
	   printf("%c", (long long)decrypted[i]);
	   }
	   printf("\n");


	   free(pub);
	   free(pri);
	   */

	return 0;
}

