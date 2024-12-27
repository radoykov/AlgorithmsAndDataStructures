all: main.exe

main.exe: main.c game.o
	gcc main.c game.o -o main.exe

game.o: game.c game.h
	gcc -c game.c -o game.o

clean: 
	del *.o *.exe