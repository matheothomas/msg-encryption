/* name : rsa.c
 * author : matheo thomas
 * date : 08-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/err.h>


void genKeyPair(RSA *keypair){
	keypair = RSA_generate_key(2048, 3, NULL, NULL);
	
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

	RSA *keypair;
	genKeyPair(keypair);




	return 0;
}

