all: main.exe

skiplist.o: skiplist.h skiplist.c
	gcc -c skiplist.c -o skiplist.o

main.exe: skiplist.o main.c
	gcc main.c skiplist.o -o main.exe

clean:
	del *.o *.exe