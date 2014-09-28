#CC = gcc
CFLAGS = -Wall -std=c99
BIN_DIR = ${DESTDIR}/usr/bin
ETC_DIR = ${DESDIR}/etc/keyphrase

all: keyphrase tests 

keyphrase: keyphrase.c funcs.h funcs.c
	$(CC) $(CFLAGS) -o keyphrase keyphrase.c funcs.c -D WORDFILE="\"/etc/keyphrase/words.txt\""

portable: keyphrase.c funcs.h funcs.c tests
	mkdir -p portable
	cp words.txt portable
	cp words.txt.gpg portable
	$(CC) $(CFLAGS) -o portable/keyphrase keyphrase.c funcs.c

tests: unit_tests.c funcs.h funcs.c
	$(CC) $(CFLAGS) -o unit_tests unit_tests.c funcs.c

install: keyphrase 
	mkdir -p ${BIN_DIR}
	install -c -s -m 755 -o root -g root keyphrase $(BIN_DIR)
	mkdir -p ${ETC_DIR}
	install -c -m 444 -o root -g root words.txt words.txt.gpg $(ETC_DIR)

clean:
	rm -fr portable
	rm -f keyphrase unit_tests *~ *.o core
