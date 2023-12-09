/* name : rsa.h
 * author : matheo thomas
 * date : 08-12-23
 */

#ifndef rsa_h 
#define rsa_h


/* Functions definitions */

// generates a public/private key pair using the RSA algorithm.
RSA *genKeyPair();

// encrypts a message given a keypair (not secure yet, gives both public and private key)
void encryptMsg(RSA* keypair);

// decrypts a message given a keypair (not secure yet, gives both public and private key)
void decryptMsg(RSA *keypair);


#endif

