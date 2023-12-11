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
#include "rsa.h"


int main(void){
	pubKey *pub = (pubKey *)malloc(sizeof(pubKey));
	priKey *pri = (priKey *)malloc(sizeof(priKey));
	genKeys(pub, pri);
	printf("%lld\n%lld\n%lld\n%lld\n", pub->mod, pub->exp, pri->mod, pri->exp);

	
	char msg[] = "Coucou ceci est un test de l'algorithme de RSA !";
	for(int i = 0; i < strlen(msg); i++){
		printf("%c", (long long)msg[i]);
	}
	printf("\n");
	long long *encrypted = encrypt(msg, sizeof(msg), pub);

	for(int i = 0; i < strlen(msg); i++){
		printf("%lld\n", (long long)encrypted[i]);
	}

	char *decrypted = decrypt(encrypted, 8*sizeof(msg), pri);
	for(int i = 0; i < strlen(msg); i++){
		printf("%c", (long long)decrypted[i]);
	}
	printf("\n");


	free(pub);
	free(pri);
	return 0;
}

