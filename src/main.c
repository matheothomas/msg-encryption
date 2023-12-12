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
			netParams p = mainNetworkServ();
		} else if(strcmp(argv[1], "client") == 0){
			if(argc >= 3){
				char *IPADDR = argv[2];
				netParams p = mainNetworkClient(IPADDR);
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

