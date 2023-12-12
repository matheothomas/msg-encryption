# msg-encryption

This is a project made in C to try and understand the basics of asymmetric encryption.

## Roadmap
- [x] Use RSA algorithm.
- [ ] Create a messaging client with local sockets.
- [ ] Create a program to bruteforce the keys.

## Principle
For each user, a **private** and a **public** key is generated using the RSA principle. 
- The public key is shared with the other user, and will use it to encrypt every message sent.
- The other user will be able to decrypt the message encrypted with its public key using the associated private key.


## Disclaimer
This code should not be used for **security purposes** and is only made to demonstrate how asymmetric encryption works.

## Installation
Clone the repository and compile the code with :
```bash
git clone https://github.com/matheothomas/msg-encryption
cd msg-encryption/src
make
```

Execute the program with
```bash
./main
```

### Credits

The mathematic implementation of the RSA algorithm was highly inspired from [this repository](https://github.com/andrewkiluk/RSA-Library).
