all: main.exe

main.exe : main.c avlTree.exe
	gcc main.c avlTree.exe -o main.exe

avlTree.exe: avlTree.h avlTree.c
	gcc -c avlTree.c -o avlTree.exe

clean:
	del *.o *.exe