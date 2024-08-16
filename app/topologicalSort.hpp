#ifndef __TOPOLOGICAL_SORT_HPP
#define __TOPOLOGICAL_SORT_HPP

#include <vector>
#include "runtimeexcept.hpp"


class NoTopologicalSortException : public RuntimeException 
{
public:
	NoTopologicalSortException(const std::string & err) : RuntimeException(err) {}
};



// If this graph has a topological order, return any such order.
// If it has no topological orders, throw a NoTopologicalSortException.
std::vector<unsigned> topologicalSort(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n);





#endif
