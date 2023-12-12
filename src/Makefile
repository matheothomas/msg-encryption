CC=gcc
OPT=-Wall -Wextra -Wno-deprecated
OPTSSL=-lcrypto

main: main.o rsa.o network.o
	${CC} ${OPT} main.o rsa.o network.o -o main ${OPTSSL}
main.o: main.c
	${CC} ${OPT} main.c -c
rsa.o: rsa.c
	${CC} ${OPT} rsa.c -c
network.o: network.c
	${CC} ${OPT} network.c -c

clean:
	rm -f *.o *.gch

