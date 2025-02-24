all: main.exe

main.exe: stack.o main.c
	gcc main.c stack.o -o main.exe

stack.o: stack.h stack.c
	gcc -c stack.c -o stack.o
	
clean:
	del *.o *.exe