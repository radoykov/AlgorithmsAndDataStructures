all: concat.exe

dLinkedList.o: dLinkedList.h dLinkedList.c
	gcc -c dLinkedList.c -o dLinkedList.o

concat.exe: dLinkedList.o concat.c
	gcc concat.c dLinkedList.o -o concat.exe

clean:
	del *.o *.exe