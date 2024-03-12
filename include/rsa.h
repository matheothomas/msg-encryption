/* name : rsa.h
 * author : matheo thomas
 * date : 11-12-23
 */

#ifndef rsa_h 
#define rsa_h

/* Struct definitions */
typedef struct pubKey {
	long long mod;
	long long exp;
} pubKey;

typedef struct priKey {
	long long mod;
	long long exp;
} priKey;


/* Functions definitions */

bool isPrime(int n);


int genPrime();


long long gcd(long long a, long long b);


long long extEuclid(long long a, long long b);


void genKeys(pubKey *pub, priKey *pri);


long long modMult(long long a, long long b, long long mod);


long long rsaModExp(long long b, long long e, long long m);


long long *rsaEncrypt(char *msg, unsigned long msgSize, pubKey *pub);


char *rsaDecrypt(long long *msg, unsigned long msgSize, priKey *pri);


#endif

