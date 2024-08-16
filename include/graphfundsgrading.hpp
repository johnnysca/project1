#include <algorithm> 
#include <vector>

/*
 * These are some functions used in grading this project.
 * The implementation is pre-compiled and included.  
 */


#ifndef __GRAPH_FUNDAMENTALS_260P_GRADING
#define __GRAPH_FUNDAMENTALS_260P_GRADING


bool confirmIsWalk(std::vector< std::pair<unsigned, unsigned> > & evidence);

bool confirmIsCycle(std::vector< std::pair<unsigned, unsigned> > & evidence);

bool confirmEdgesInGraph(const std::vector<std::pair<unsigned, unsigned> > & graph, std::vector< std::pair<unsigned, unsigned> > & evidence);

bool validTopologicalSort(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n, const std::vector<unsigned> & topologicalOrder);



#endif
