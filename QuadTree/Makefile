all: main.exe

main.exe: main.c dynarr.o quadTree.o
	gcc main.c dynarr.o quadTree.o -o main.exe

quadTree.o: quadTree.c quadTree.h
	gcc -c quadTree.c -o quadTree.o

dynarr.o: dynarr.c dynarr.h
	gcc -c dynarr.c -o dynarr.o

clean:
	del *.o *.exe