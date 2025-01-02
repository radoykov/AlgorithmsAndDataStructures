all: main.exe

main.exe: main.c treeSet.o
	gcc main.c treeSet.o -o main.exe

treeSet.o: treeSet.c treeSet.h
	gcc -c treeSet.c -o treeSet.o

clean:
	del *.exe *.o