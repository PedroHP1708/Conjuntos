all: set.o avl.o lista.o main.o
	gcc set.o avl.o lista.o main.o -o prog -std=c99 -Wall

lista.o:
	gcc -c lista.c -o lista.o

set.o:
	gcc -c set.c -o set.o

avl.o:
	gcc -c avl.c -o avl.o
	
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o prog

zip:
	zip programa.zip *

run:
	./prog