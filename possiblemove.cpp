#include "possiblemove.h"

PossibleMove::PossibleMove(Node * newStartNode, Edge * newEdge)
{
	startNode = newStartNode;
	edge = newEdge;
	cost = newEdge->getCost() + startNode->getCost();
}

Node * PossibleMove::getStartNode()
{
	return startNode;
}

Edge * PossibleMove::getStartEdge()
{
	return edge;
}

int PossibleMove::getCost() const
{
	return cost;
}