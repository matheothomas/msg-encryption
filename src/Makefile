CC=gcc
OPT=-Wall -Wextra -Wno-deprecated
OPTSSL=-lcrypto

main: main.o rsa.o
	${CC} ${OPT} main.o rsa.o -o main ${OPTSSL}
main.o: main.c
	${CC} ${OPT} main.c -c
rsa.o: rsa.c
	${CC} ${OPT} rsa.c -c

clean:
	rm -f *.o *.gch

