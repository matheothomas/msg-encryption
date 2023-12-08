/* name : rsa.c
 * author : matheo thomas
 * date : 08-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void genKeyPair(RSA *keypair){
	keypair = RSA_generate_key(2048, 65537, NULL, NULL);
	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	size_t pri_len = BIO_pending(pri);
	size_t pub_len = BIO_pending(pub);

	char *pri_key = malloc(pri_len +1);
	char *pub_key = malloc(pub_len +1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';
	printf("\n%s\n%s\n", pri_key, pub_key);

}


void encryptMsg(RSA *keypair){
	char *msg[2048/8];
	printf("Message to encrypt : ");
	fgets(msg, 2048/8, stdin);
	msg[strlen(msg)-1] = '\0';


	char *encrypt = malloc(RSA_size(keypair));
	int encrypt_len;
	char *err = malloc(130);
	if((encrypt_len = RSA_public_encrypt(strlen(msg)+1, (unsigned char*)msg, (unsigned char *)encrypt, keypair, RSA_PKCS1_OAEP_PADDING)) == -1){
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), err);
		fprintf(stderr, "Error encrypting message : %s\n", err);
	}
}

void decryptMsg(RSA *keypair){
	char *encrypt = malloc(RSA_size(keypair));
	int encrypt_len;
	char *err = malloc(130);
	char *decrypt = malloc(RSA_size(keypair));
	if(RSA_private_decrypt(encrypt_len, (unsigned char *)encrypt, (unsigned char *)decrypt, keypair, RSA_PKCS1_OAEP_PADDING) == -1){
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), err);
		fprintf(stderr, "Error decrypting message : %s\n", err);
	} else {
		printf("Decrypted message : %s\n", decrypt);
	}
}


int main(void){

	RSA *keypair = NULL;
	genKeyPair(keypair);

	//encryptMsg(keypair);

	//decryptMsg(keypair);




	return 0;
}

