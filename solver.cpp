#include "constants.h"
#include "node.h"
#include "edge.h"
#include "possiblemove.h"

#include <map>
#include <queue>
#include <vector>
#include <stack>
#include <stdbool.h>

using namespace std;

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};

struct cmp_move : public binary_function<PossibleMove *, PossibleMove *, bool>
{
   bool operator()(PossibleMove const *a, PossibleMove const *b) const
   {
      return a->getCost() > b->getCost();
   }
};

Node * ensureNode(map<const char *, Node *, cmp_str> * graph, const char * name)
{
	Node * retNode;

	if(graph->count(name) == 0) // If the name is not in the graph
	{
		retNode = new Node(name);
		(*graph)[name] = retNode;
	}
	else
	{
		retNode = (*graph)[name];
	}
	return retNode;
}

void getGraphFromFile(map<const char *, Node *, cmp_str> * graph, const char * filename)
{
	FILE * file = fopen(filename, "r");

	char * startNodeName;
	char * endNodeName;
	int cost;
	int status;

	while(true)
	{
		startNodeName = new char[20];
		endNodeName = new char[20];
		status = fscanf(file, "%[^,],%[^,],%d\n", startNodeName, endNodeName, &cost);

		if(status == EOF)
			break;

		Node * startNode = ensureNode(graph, startNodeName);
		Node * endNode = ensureNode(graph, endNodeName);

		Edge * newEdge = new Edge(startNode, endNode, cost);
		startNode->addConnection(newEdge);
	}
}

int main(int argc, const char * argv[])
{
	bool shouldEnqueueConnections;

	if(argc < 4)
	{
		printf("Usage: solver [filename] [start node name] [end node name]\n");
		return 0;
	}

	map<const char *, Node *, cmp_str> graph;
	getGraphFromFile(&graph, argv[1]);
	const char * startNodeName = argv[2];
	const char * endNodeName = argv[3];

	// Set all node costs in graph to infinity
	map<const char *, Node *, cmp_str>::iterator graphItr;
	for(graphItr = graph.begin(); graphItr != graph.end(); graphItr++)
	{
		Node * node = graphItr->second;
		node->setCost(INFINITY);
	}

	// Set starting node cost to zero
	Node * startNode = graph[startNodeName];
	startNode->setCost(0);

	priority_queue<PossibleMove *, vector<PossibleMove *>, cmp_move> possibleMoves;

	// Start main loop for dijkstra's
	Node * currentNode = startNode;
	Node * endNode = graph[endNodeName];
	shouldEnqueueConnections = true;
	while(endNode != currentNode)
	{
		// Enqueue possible moves
		if(shouldEnqueueConnections)
		{
			vector<Edge *> * connections = currentNode->getConnections();
			vector<Edge *>::iterator connectionItr;
			for(connectionItr = connections->begin(); connectionItr != connections->end(); connectionItr++)
			{
				Edge * curEdge = *connectionItr;
				PossibleMove * possibleMove = new PossibleMove(currentNode, curEdge);
				possibleMoves.push(possibleMove);
			}
		}

		// Get the edge and the node on the other side of the edge we are taking
		if(possibleMoves.empty())
		{
			currentNode = NULL;
			break;
		}

		PossibleMove * nextMove = possibleMoves.top();
		possibleMoves.pop();
		Edge * nextEdge = nextMove->getStartEdge();
		Node * nextNode = nextEdge->getOtherNode(currentNode);

		if(nextNode->getCost() == INFINITY)
		{
			// Compute the cost to the next edge
			nextNode->setEdgeToMe(nextEdge);
			nextNode->computeCost(nextEdge);

			// Move to next node
			currentNode = nextNode;

			shouldEnqueueConnections = true;
		}
		else
			shouldEnqueueConnections = false;
	}

	// No path found
	if(currentNode == NULL)
	{
		printf("No path found\n");
	}
	else // Path found
	{
		// Go thorugh linked list back through path
		stack<Node *> traversalStack;
		while(currentNode->getEdgeToMe() != NULL)
		{
			traversalStack.push(currentNode);
			currentNode = currentNode->getEdgeToMe()->getOtherNode(currentNode);
		}

		while(!traversalStack.empty())
		{
			currentNode = traversalStack.top();
			traversalStack.pop();
			printf("%s\n", currentNode->getName());
		}
	}
}