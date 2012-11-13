solver: solver.cpp possiblemove.o edge.o node.o
	g++ -g -Wall -o solver node.o edge.o possiblemove.o solver.cpp

possiblemove.o: possiblemove.cpp
	g++ -g -Wall -c possiblemove.cpp -o possiblemove.o

edge.o: edge.cpp
	g++ -g -Wall -c edge.cpp -o edge.o

node.o: node.cpp
	g++ -g -Wall -c node.cpp -o node.o

clean:
	rm *.o
	rm solver

