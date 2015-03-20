#pragma once

template <typename container_type>
class Enumerator
{
public:
	typedef typename container_type::const_iterator Iterator;
public:
	Enumerator(const container_type &container)
		: it(container.cbegin())
		, c(container)
	{

	}
	bool hasMore() { return it != c.cend(); }
	Iterator next() { return it++; }
private:
	Iterator it;
	container_type &c;
};