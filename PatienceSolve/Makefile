all: main.exe

main.exe: solitaire.o stack.o main.c
	gcc main.c solitaire.o stack.o -o main.exe

solitaire.o: solitaire.c solitaire.h
	gcc -c solitaire.c -o solitaire.o

stack.o: stack.c stack.h
	gcc -c stack.c -o stack.o

clean:
	del *.o *.exe