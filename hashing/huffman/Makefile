all: main.exe

main.exe: main.c pqueue.o
	gcc main.c pqueue.o -o main.exe

pqueue.o: pqueue.h pqueue.c
	gcc -c pqueue.c -o pqueue.o

clean:
	del *.o *.exe