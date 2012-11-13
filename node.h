/**
 * Name: node.h
 * Desc: Contains the definition of a Node class
 * Auth: Stephen Thoma, 2012
**/

#ifndef NODE_HEADER
#define NODE_HEADER

#include <vector>
using namespace std;

#include "constants.h"
#include "edge.h"

/**
 * Name: Node
 * Desc: A connectable component in a graph representing a location.
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

	/**
	 * Name: ~Node()
	 * Desc: Delete Node instance.
	**/
	~Node();

	/**
	 * Name: getCost()
	 * Desc: Returns the cost of a node.
	**/
	int getCost();

	/**
	 * Name: setCost()
	 * Desc: Sets the cost of a node.
	 * Para: newCost, The new cost to be assigned.
	**/
	void setCost(int newCost);

	/**
	 * Name: getConnections()
	 * Desc: Retrieves the edges coming from the node.
	**/
	vector<Edge *> * getConnections();

	/**
	 * Name: addConnection(Edge * newEdge)
	 * Desc: Associates an edge with a node.
	 * Para: newEdge, The edge to be associated.
	**/	
	void addConnection(Edge * newEdge);

	/**
	 * Name: computeCost(Edge * edgeToMe)
	 * Desc: Determine cost with the cost of the previous node and the connecting
	 *       edge.
	 * Para: edgeToMe, The edge to be considered.
	**/
	void computeCost(Edge * edgeToMe);

	/**
	 * Name: setEdgeToMe(Edge * edgeToMe)
	 * Desc: Makes the given edge connect to a node.
	 * Para: edgeToMe, The edge to be connected to the node.
	**/
	void setEdgeToMe(Edge * edgeToMe);

	/**
	 * Name: getEdgeToMe()
	 * Desc: Retrieves edges connected to the node.
	**/
	Edge * getEdgeToMe();

	/**
	 * Name: getName()
	 * Desc: Retrieves the Node's name.
	**/
	const char * getName();

private:
	int cost; // Cost to get to this node
	vector<Edge *> connections; // List of connections leading from this node
	const char * name; // String representing name identifier of node
	Edge * edgeToMe; // The road taken to get to me
};

#endif