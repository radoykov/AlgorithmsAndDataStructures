all: main.exe

xorlist.o: xorlist.h xorlist.c
	gcc -c xorlist.c -o xorlist.o

main.exe: xorlist.o main.c
	gcc main.c xorlist.o -o main.exe

clean:
	del *.o *.exe