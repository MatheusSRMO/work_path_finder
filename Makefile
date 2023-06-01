CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g
LDFLAGS = -lm -lpthread -lrt
LIBS = -led -lsearch -lcheck

DEPS = horario.h
OBJ = horario.o main.o

LIBED_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/ed/*.c)) 
LIBSEARCH_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/search/*.c)) 

all: main stack_test

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $< 

libed.a: $(LIBED_DEPS)
	ar -crs libed.a $(LIBED_DEPS)

libsearch.a: $(LIBSEARCH_DEPS)
	ar -crs libsearch.a $(LIBSEARCH_DEPS)

stack_test: ./src/ed/stack_test.c ./src/ed/stack.c
	$(CC) $(CFLAGS) -o stack_test ./src/ed/stack_test.c ./src/ed/stack.c
	./stack_test
	rm -f stack_test

main: main.c libed.a libsearch.a 
	$(CC) $(CFLAGS) -o main main.c -I src/search -I src/ed -L . $(LIBS) $(LDFLAGS)

clean:
	rm -f main stack_test libed.a libsearch.a $(LIBSEARCH_DEPS) $(LIBED_DEPS)

run:
	./main

.PHONY: all clean run stack_test
