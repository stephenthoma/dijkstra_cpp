/**
* Name: edge.h
* Desc: Contains the definition of an Edge class
**/

#ifndef EDGE_HEADER
#define EDGE_HEADER

using namespace std;

class Node;

class Edge
{
public:

	Edge(Node * newStartNode, Node * newEndNode, int newCost);

	Node * getStartNode();

	Node * getEndNode();

	Node * getOtherNode(Node * node);

	int getCost();

private:
	Node * startNode;
	Node * endNode;
	int cost;
};

#endif