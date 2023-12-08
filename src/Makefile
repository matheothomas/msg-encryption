CC=gcc
OPT=-Wall -Wextra -Wno-deprecated
OPTSSL=-lcrypto

main: rsa.o
	${CC} ${OPT} rsa.o -o main ${OPTSSL}
rsa.o: rsa.c
	${CC} ${OPT} rsa.c -c

clean:
	rm -f *.o *.gch

