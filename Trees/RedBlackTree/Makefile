all: main.exe

main.exe : main.c redBlackTree.exe
	gcc main.c redBlackTree.exe -o main.exe

redBlackTree.exe: redBlackTree.h redBlackTree.c
	gcc -c redBlackTree.c -o redBlackTree.exe

clean:
	del *.o *.exe