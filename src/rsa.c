/* name : rsa.c
 * author : matheo thomas
 * date : 11-12-23
 */

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "rsa.h"


bool isPrime(int n){
	bool res = true;
	for(int i = 2; i <= n/2; i++){
		if (n % i == 0){
			res = false;
			break;
		}
	}
	return res;
}
int genPrime(){
	srand(time(0));
	int n = 10000 + rand()%10000;
	while(isPrime(n) != true){
		n++;
	}
	return n;
}

long long gcd(long long a, long long b){
	long long c;
	while(a != 0){
		c = a;
		a = b%a;
		b = c;
	}
	return b;
}

long long extEuclid(long long a, long long b){
	long long x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
	while(a != 0){
		q = gcd/a;
		r = gcd%a;
		m = x-u*q;
		n = y-v*q;
		gcd = a;
		a = r;
		x = u;
		y = v;
		u = m;
		v = n;
	}
	return y;
}

void genKeys(pubKey *pub, priKey *pri){
	long long p = genPrime();
	long long q = genPrime();
	long long e = (2 << 16)+1;
	long long max = p*q;
	long long phiMax = (p-1)*(q-1);

	while(!(p && q) || (p == q) || (gcd(phiMax, e) != 1)){
		p = genPrime();
		q = genPrime();
		max = p*q;
		phiMax = (p-1)*(q-1);
	}

	long long d = extEuclid(phiMax, e);
	while(d < 0){
		d += phiMax;
	}

	pub->mod = max;
	pub->exp = e;
	pri->mod = max;
	pri->exp = d;
}

long long modMult(long long a, long long b, long long mod){
	if(a == 0){
		return 0;
	}
	long long product = a*b;
	if(product / a == b){
		return product % mod;
	}
	if(a & 1){
		product = modMult((a >> 1), b, mod);
		if((product << 1) > product){
			return (((product << 1) %mod) +b) %mod;
		}
	}

	product = modMult((a >> 1), b, mod);
	if((product << 1) > product){
		return (product << 1) %mod;
	}
	long long sum = 0;
	while(b > 0){
		if(b & 1){
			sum = (sum+a)%mod;
		}
		a = (2*a)%mod;
		b >>= 1;
	}
	return sum;
}

long long rsaModExp(long long b, long long e, long long m){
	long long p = 1;
	if(b < 0 || e < 0 || m <= 0){
		return -1;
	}
	b %= m;
	while(e > 0){
		if(e & 1){
			p = modMult(p, b, m);
		}
		b = modMult(b, b, m);
		e >>= 1;
	}
	return p;
}


long long *encrypt(char *msg, unsigned long msgSize, pubKey *pub){
	long long *encrypted = malloc(sizeof(long long)*msgSize);
	if(encrypted == NULL){
		fprintf(stderr, "malloc failed\n");
		return NULL;
	}

	for(long long i = 0; i < msgSize; i++){
		if((encrypted[i] = rsaModExp(msg[i], pub->exp, pub->mod)) == -1){
			return NULL;
		}
	}
	return encrypted;
}


char *decrypt(long long *msg, unsigned long msgSize, priKey *pri){
	if(msgSize % sizeof(long long) != 0){
		fprintf(stderr, "error\n");
		return NULL;
	}

	char *decrypted = malloc(msgSize/sizeof(long long));
	char *temp = malloc(msgSize);
	if((decrypted == NULL) || (temp == NULL)){
		fprintf(stderr, "error\n");
		return NULL;
	}

	for(long long i = 0; i < msgSize/8; i++){
		if((temp[i] = rsaModExp(msg[i], pri->exp, pri->mod)) == -1){
			free(temp);
			return NULL;
		}
	}
	for(long long i = 0; i < msgSize/8; i++){
		decrypted[i] = temp[i];
	}
	free(temp);
	return decrypted;
}

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

