solver:solver.cpp
	g++ -g -Wall -o solver node.cpp edge.cpp possiblemove.cpp solver.cpp
clean:
	rm solver