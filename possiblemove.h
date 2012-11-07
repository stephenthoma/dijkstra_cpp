/**
* Name: possiblemove.h
* Desc: Contains the definition of a record of a move that can be taken
**/

#ifndef POSSIBLE_MOVES_HEADER
#define POSSIBLE_MOVES_HEADER

using namespace std;

#include "edge.h"
#include "node.h"

class PossibleMove
{
public:
	PossibleMove(Node * newStartNode, Edge * newEdge);

	Node * getStartNode();

	Edge * getStartEdge();

	int getCost() const;

private:
	Node * startNode;
	Edge * edge;
	int cost;
};

#endif