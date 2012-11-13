/**
 * Name: possiblemove.h
 * Desc: Contains the definition of a record of a move that can be taken
 * Auth: Stephen Thoma, 2012
**/

#ifndef POSSIBLE_MOVES_HEADER
#define POSSIBLE_MOVES_HEADER

using namespace std;

#include "edge.h"
#include "node.h"

/**
 * Name: PossibleMove
 * Desc: A move that could be taken, within the graph, from one node to another.
**/
class PossibleMove
{
public:

	/**
	 * Name: PossibleMove(Node * newStartNode, Edge * newEdge)
	 * Desc: A record of a move that could be taken.
	 * Para: newStartNode, The possible move's starting node.
	 *		newEdge, The possible move's chosen edge.
	**/
	PossibleMove(Node * newStartNode, Edge * newEdge);

	/**
	 * Name: getStartNode()
	 * Desc: Returns the starting node of the possible move.
	**/
	Node * getStartNode();

	/**
	 * Name: getStartEdge()
	 * Desc: Returns the starting edge of the possible move.
	**/
	Edge * getStartEdge();

	/**
	 * Name: getCost()
	 * Desc: Returns the cost of the possible move.
	**/
	int getCost() const;

private:
	Node * startNode; // The potential starting place
	Edge * edge; // The edge that would be taken
	int cost; // The cost of the edge and the starting node
};

#endif