#include "GraphEdge.h"
#include "GraphNode.h"
#include "SparseGraph.h"

int main(void)
{
	SparseGraph<GraphNode, GraphEdge> sg(true, 10);
	return 0;
}