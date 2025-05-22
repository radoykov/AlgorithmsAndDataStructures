all: main.exe

main.exe : main.c hashMap.o
	gcc main.c hashMap.o -o main.exe

hashMap.o: hashMap.c hashMap.h
	gcc -c hashMap.c -o hashMap.o

clean:
	del *.exe *.o