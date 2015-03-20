#pragma once
class GraphNode
{
public:
	static const int INVALID_INDEX = -1;
public:
	GraphNode() : mIndex(INVALID_INDEX) {}
	GraphNode(int index) : mIndex(index) {}
	virtual ~GraphNode(void) {}

	void setIndex(int index) { mIndex = index; }
	int getIndex() { return mIndex; }
private:
	int mIndex;
};

