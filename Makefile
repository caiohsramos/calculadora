all:calculadora.o main.o
	gcc calculadora.o main.o -o calculadora -g -Wall -ansi -pedantic
calculadora.o:
	gcc calculadora.c -c -Wall -g -ansi -pedantic
main.o:
	gcc main.c -g -c -Wall -ansi -pedantic
clean:
	rm -rf *.o calculadora
run:
	./calculadora
