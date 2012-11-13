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

int INFINITY = -1;

/**
 * Name: cmp_str
 * Desc: Compares two strings, returns true or false based on match.
**/
struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};

/**
 * Name: cmp_move
 * Desc: Determines which of two moves has a greater cost.
 * Para: a, The first possible move.
 *		b, The second possible move.
 * Retr: True if the first operand has a higher cost than the second operand.
 *       False otherwise.
 * Auth: Stephen Thoma, 2012
**/
struct cmp_move : public binary_function<PossibleMove *, PossibleMove *, bool>
{
   bool operator()(PossibleMove const *a, PossibleMove const *b) const
   {
      return a->getCost() > b->getCost();
   }
};

/**
 * Name: ensureNode(map<const char *, Node *, cmp_str> * graph, const char * name)
 * Desc: Checks to see if a node exists within the graph.
 * Para: graph, The data structure containing all node information.
 *		name, The name of the node being checked.
**/
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

/**
 * Name: getGraphFromFile(map<const char *, Node *, cmp_str> * graph,
 *       const char * filename)
 * Desc: Retrieves contents of a .csv file containing node information.
 * Para: graph, The data structure containing all node information.
 *		filename, The name of the file to retrieve information from.
**/
int getGraphFromFile(map<const char *, Node *, cmp_str> * graph,
	const char * filename)
{
	FILE * file = fopen(filename, "r");

	if (file == 0)
		return FILE_NOT_FOUND_ERR;

	char * startNodeName;
	char * endNodeName;
	int cost;
	int status;

	while(true)
	{
		startNodeName = new char[20];
		endNodeName = new char[20];
		status = fscanf(file, "%[^,],%[^,],%d\n", startNodeName, endNodeName,
			&cost);

		if(status == EOF)
			break;

		if(status != 3)
			return MALFORMED_FILE_ERR;

		Node * startNode = ensureNode(graph, startNodeName);
		Node * endNode = ensureNode(graph, endNodeName);

		Edge * newEdge = new Edge(startNode, endNode, cost);
		startNode->addConnection(newEdge);
	}

	return SUCCESS;
}

/**
 * Name: main(int argc, const char * argv[])
 * Desc: The main algorithm logic.
 * Para: argc, Number of arguments passed to the program.
 *		argv, Contents of arguments passed to the program.
**/
int main(int argc, const char * argv[])
{
	bool shouldEnqueueConnections;

	if(argc < 4)
	{
		printf("Usage: solver [filename] [start node name] [end node name]\n");
		return 0;
	}

	map<const char *, Node *, cmp_str> graph;
	
	// Load graph specification file
	int fileStatus = getGraphFromFile(&graph, argv[1]);
	if(fileStatus == FILE_NOT_FOUND_ERR)
	{
		printf("File not found.\n");
		return -1;
	}
	else if(fileStatus == MALFORMED_FILE_ERR)
	{
		printf("Improperly formatted file.\n");
		return -1;
	}

	//Set infinity to the maximal possible cost
	INFINITY = graph.size() * graph.size();

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
			for(connectionItr = connections->begin();
			 connectionItr != connections->end(); connectionItr++)
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
		// Go through linked list back through path
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