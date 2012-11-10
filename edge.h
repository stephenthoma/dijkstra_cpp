/**
* Name: edge.h
* Desc: Contains the definition of an Edge class
**/

#ifndef EDGE_HEADER
#define EDGE_HEADER

using namespace std;

class Node;

/**
* Name: Edge
* Desc: A connecting component between two nodes representing a path.
**/
class Edge
{
public:

	/**
	* Name: Edge(Node * newStartNode, Node * newEndNode, int newCost)
	* Desc: Creates a new edge.
	* Para: newStartNode, The starting point to associate with this edge.
	*		newEndNode, The end point to associate with this edge.
	*		newCost, The cost of traveling across the edge.
	**/
	Edge(Node * newStartNode, Node * newEndNode, int newCost);

	/**
	* Name: getStartNode()
	* Desc: Returns the starting node of the edge.
	**/
	Node * getStartNode();

	/**
	* Name: getEndNode()
	* Desc: Returns the ending node of the edge.
	**/
	Node * getEndNode();

	/**
	* Name: getOtherNode(Node * node)
	* Desc: Get the node on the other side of the edge
	* Para: node, The node on the starting side
	**/
	Node * getOtherNode(Node * node);

	/**
	* Name: getCost()
	* Desc: Returns the cost of traveling from the edge's start node to its end node.
	**/
	int getCost();

private:
	Node * startNode; // The starting node of an edge
	Node * endNode; // The ending node of an edge
	int cost; // The cost of traveling from an edge's start node to its end node
};

#endif