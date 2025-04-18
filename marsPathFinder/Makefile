all: marsPathFinder.o main.c
	gcc main.c marsPathFinder.o -o main.exe

marsPathFinder.o: marsPathFinder.c marsPathFinder.h
	gcc -c marsPathFinder.c -o marsPathFinder.o

clean:
	del *.o *.exe