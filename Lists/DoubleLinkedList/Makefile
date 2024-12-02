all: test.exe

doubleLinkedList.o: doubleLinkedList.h doubleLinkedList.c
	gcc -c doubleLinkedList.c -o doubleLinkedList.o

test.exe: doubleLinkedList.o test.c
	gcc test.c doubleLinkedList.o -o test.exe

clean:
	del *.o *.exe