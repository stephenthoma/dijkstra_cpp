/**
 * Name: edge.cpp
 * Desc: Implementation of edge class described in edge.h
 * Auth: Stephen Thoma, 2012
**/

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