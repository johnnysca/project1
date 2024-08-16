#ifndef __BIPARTITE_CHECKING
#define __BIPARTITE_CHECKING

#include <vector>

// evidence is initially empty
// graph is undirected and simple.
bool isBipartite(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n, std::vector< std::pair<unsigned, unsigned> > & evidence);


#endif
