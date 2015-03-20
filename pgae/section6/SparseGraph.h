#pragma once
#include <vector>
#include <list>
#include "Enumerator.h"
template <typename node_type, typename edge_type>
class SparseGraph
{
public:
	typedef node_type Node;
	typedef edge_type Edge;
	typedef std::vector<node_type> NodeVector;
	typedef std::list<edge_type> EdgeList;
	typedef Enumerator<EdgeList> EdgeEnumerator;
public:
	SparseGraph(bool isDigraph = true, int nodes = 0) 
		: mIsDigraph(isDigraph)
		, mNodes(nodes)
		, mEdgeLists(nodes)
	{
		for (int i = 0; i < nodes; ++i) mNodes[i].setIndex(i);
	}
	EdgeEnumerator getEdgeEnumerator(int index) { return EdgeEnumerator(mEdgeLists[index]); }
private:
	bool mIsDigraph;
	NodeVector mNodes;
	std::vector<EdgeList> mEdgeLists;
};