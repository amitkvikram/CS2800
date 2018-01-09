all: edgeType run

edgeType: edgeType.o dll.o dll.h
	gcc -g -Wall edgeType.o  dll.o dll.h -std=c11 -o edgeType

edgeType.o: edgeType.c
	gcc -g -c edgeType.c

dll.o: dll.c
	gcc -g -c dll.c

run:edgeType
	valgrind ./edgeType

clean:
	rm edgeType *.o
