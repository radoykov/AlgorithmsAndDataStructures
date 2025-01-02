all: main.exe

main.exe: main.c vector.o
	gcc main.c vector.o -o main.exe

vector.o: vector.c vector.h
	gcc -c vector.c -o vector.o

clean:
	del *.exe *.o