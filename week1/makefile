all: edgeType

edgeType: edgeType.o dll.o
	gcc -g -Wall edgeType.o  dll.o -std=c11 -o edgeType

edgeType.o: edgeType.c
	gcc -g -c edgeType.c

dll.o: dll.c
	gcc -g -c dll.c

clean:
	rm edgeType *.o
