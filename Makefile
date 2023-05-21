all:
	gcc -Wall -g -o main *.c -Wno-format
clean:
	rm -f main