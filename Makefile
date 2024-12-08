all: lista.o avl.o main.o
	gcc lista.o avl.o main.o -o prog -std=c99 -Wall

lista.o:
	gcc -c lista.c -o lista.o

avl.o:
	gcc -c avl.c -o avl.o
	
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o prog

zip:
	zip programa.zip *.c *.h Makefile

run:
	./prog