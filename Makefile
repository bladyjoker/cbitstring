CC=gcc
C_OPTS=-std=c99
WARN_OPTS=-Wall
DBG_OPTS=-ggdb
OPTMZ_OPTS=
DIR_OPTS=-I./ -L./
COMPILE=$(CC) $(DIR_OPTS) $(LNK_OPTS) $(C_OPTS) $(WARN_OPTS) $(DBG_OPTS) $(OPTMZ_OPTS)
AR=ar rcs

all: libbitstring.a libbitstring.so test

libbitstring.a: utils.c bitstring.c
	$(COMPILE) -c utils.c -o utils.o
	$(COMPILE) -c bitstring.c -o bitstring.o
	$(AR) libbitstring.a bitstring.o utils.o

libbitstring.so: utils.c bitstring.c
	$(COMPILE) utils.c bitstring.c -shared -o libbitstring.so

test:
	$(COMPILE) utils.c bitstring.c test_bitstring.c -o test_bitstring
	./test_bitstring

clean:
	rm -f test_bitstring *~ *.o *.a *.so
