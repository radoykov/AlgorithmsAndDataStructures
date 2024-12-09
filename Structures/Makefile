all: main.exe

main.exe: main.c queue.o set.o stack.o vector.o
	gcc main.c queue.o set.o stack.o vector.o -o main.exe

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o

set.o: set.c set.h
	gcc -c set.c -o set.o

stack.o: stack.c stack.h
	gcc -c stack.c -o stack.o

vector.o: vector.c vector.h
	gcc -c vector.c -o vector.o

clean:
	del *.o *.exe