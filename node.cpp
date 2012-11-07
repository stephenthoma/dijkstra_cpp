#include "node.h"

Node::Node(const char * newName)
{
	name = newName;
	cost = UNDEFINED;
	edgeToMe = NULL;
}

Node::~Node()
{
	delete [] name;
}

int Node::getCost()
{
	return cost;
}

void Node::setCost(int newCost)
{
	cost = newCost;
}

vector<Edge *> * Node::getConnections()
{
	return &connections;
}

void Node::addConnection(Edge * newEdge)
{
	return connections.push_back(newEdge);
}

void Node::computeCost(Edge * edgeToMe)
{
	Node * nodeThatGotToMe = edgeToMe->getOtherNode(this);
	cost = edgeToMe->getCost() + nodeThatGotToMe->getCost();
}

void Node::setEdgeToMe(Edge * newEdgeToMe)
{
	edgeToMe = newEdgeToMe;
}

Edge * Node::getEdgeToMe()
{
	return edgeToMe;
}

const char * Node::getName()
{
	return name;
}