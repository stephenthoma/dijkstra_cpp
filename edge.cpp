#include "edge.h"

Edge::Edge(Node * newStartNode, Node * newEndNode, int newCost)
{
	endNode = newEndNode;
	startNode = newStartNode;
	cost = newCost;
}

Node * Edge::getStartNode()
{
	return startNode;
}

Node * Edge::getEndNode()
{
	return endNode;
}

Node * Edge::getOtherNode(Node * node)
{
	if (node == startNode)
		return endNode;
	else
		return startNode;
}

int Edge::getCost()
{
	return cost;
}