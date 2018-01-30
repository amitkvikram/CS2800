all: topologicalSort

topologicalSort:topologicalSort.o dll.o stack.o
	g++ topologicalSort.o dll.o stack.o -o topologicalSort

topologicalSort.o: topologicalSort.cpp
	g++ -c topologicalSort.cpp

dll.o: dll.cpp
	g++ -c dll.cpp

stack.o: stack.cpp
	g++ -c stack.cpp

clean:
	rm *.o
