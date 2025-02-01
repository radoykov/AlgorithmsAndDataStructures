all: main.exe

main.exe: helpSanta.o main.c
	gcc main.c helpSanta.o -o main.exe

helpSanta.o: helpSanta.c helpSanta.h
	gcc -c helpSanta.c -o helpSanta.o

clean: 
	del *.exe *.o