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

/**
 * Name: Node
 * Desc: A connectable component in a graph representing a location
**/
class Node
{
public:

	/**
	 * Name: Node(const char * newName)
	 * Desc: Creates a new node.
	 * Para: newName, The name to associate with this node.
	**/
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