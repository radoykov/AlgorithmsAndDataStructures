all: listTraversal.exe

listTraversal.exe : queue.o listTraversal.c
	gcc listTraversal.c queue.o -o listTraversal.exe

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o

clean:
	del *.exe *.o