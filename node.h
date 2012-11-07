/**
 * Name: node.h
 * Desc: Contains the definition of a Node class
**/

#ifndef NODE_HEADER
#define NODE_HEADER

#include <vector>
using namespace std;

#include "constants.h"
#include "edge.h"

class Node
{
public:

	Node(const char * newName);

	~Node();

	int getCost();

	void setCost(int newCost);

	vector<Edge *> * getConnections();

	void addConnection(Edge * newEdge);

	void computeCost(Edge * edgeToMe);

	void setEdgeToMe(Edge * edgeToMe);

	Edge * getEdgeToMe();

	const char * getName();

private:
	int cost; // Cost to get to this node
	vector<Edge *> connections; // List of connections leading from this node
	const char * name; // String representing name identifier of node
	Edge * edgeToMe; // The road taken to get to me
};

#endif