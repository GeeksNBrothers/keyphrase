#CC = gcc
CFLAGS = -Wall -std=c99
BIN_DIR = ${DESTDIR}/usr/bin

all: keyphrase tests 

keyphrase: keyphrase.c funcs.h funcs.c
	$(CC) $(CFLAGS) -o keyphrase keyphrase.c funcs.c

tests: tests.c funcs.h funcs.c
	$(CC) $(CFLAGS) -o tests tests.c funcs.c

install: keyphrase 
	mkdir -p ${BIN_DIR}
	install -c -s -m 755 -o root -g root keyphrase $(BIN_DIR)

clean:
	rm -f keyphrase tests *~ *.o core
