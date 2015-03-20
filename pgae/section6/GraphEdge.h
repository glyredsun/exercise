#pragma once
class GraphEdge
{
public:
	GraphEdge(void) {}
	virtual ~GraphEdge(void) {}

	void setFrom(int from) { mFrom = from; }
	int getFrom() { return mFrom; }
	void setTo(int to) { mTo = to; }
	int getTo() { return mTo; }
private:
	int mFrom;
	int mTo;
};

