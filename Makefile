all:calculadora.o main.o
	gcc calculadora.o main.o -o calculadora -g -Wall
calculadora.o:
	gcc calculadora.c -c -Wall -g
main.o:
	gcc main.c -c -g -Wall
clean:
	rm -rf *.o calculadora
run:
	./calculadora
