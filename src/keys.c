/* name : keys.c
 * author : matheo thomas
 * date : 05-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <stdbool.h>

void generateKey(){
	const int kBits = 1024;
	const int kExp = 3;
	int keylen;
	char *pem_key;

	RSA *rsa = RSA_generate_key(kBits, kExp, 0, 0);

	BIO *bio = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

	keylen = BIO_pending(bio);
	pem_key = calloc(keylen+1, 1);
	BIO_read(bio, pem_key, keylen);

	printf("%s\n", pem_key);

	BIO_free_all(bio);
	RSA_free(rsa);
	free(pem_key);

}

/*
bool generateKey(){
	int ret = 0;
	RSA *r = NULL;
	BIGNUM *bne = NULL;
	BIO *bpPublic = NULL;
	BIO *bpPrivate = NULL;
	int bits = 2048;
	unsigned long e = RSA_F4;

	bne = BN_new();
	ret = BN_set_word(bne,e);
	if(ret != 1){
		goto free_all;
	}

	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if(ret != 1){
		goto free_all;
	}

	bpPublic = BIO_new_file("public.pem", "w+");
	ret = PEM_write_bio_RSAPublicKey(bpPublic, r);
	if(ret != 1){
		goto free_all;
	}

	bpPrivate = BIO_new_file("private.pem", "w+");
	ret = PEM_write_bio_RSAPrivateKey(bpPrivate, r, NULL, NULL, 0, NULL, NULL);

free_all:

	BIO_free_all(bpPublic);
	BIO_free_all(bpPrivate);
	RSA_free(r);
	BN_free(bne);

	return (ret == 1);

}
*/

int main(void){
	generateKey();

	return 0;
}

