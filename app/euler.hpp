#ifndef __EULER_PROJECT_HPP
#define __EULER_PROJECT_HPP

#include <vector>

enum EulerPossibility { circuit, walk, neither };

// input:  graph as an edge list, n as number of vertices in the graph (graph.size() is number of edges)
// journey is an EMPTY vector, which will be used to return the circuit or walk, if the graph has one.
// unlike topological sort and bipartite checking, you ARE NOT guaranteed that this is a simple graph.
// Note that the graph is undirected.  All edges listed are <a,b> where a <= b.  
// Return whether this graph has an Eulerian circuit, Eulerian walk, or neither.

EulerPossibility checkForEuler(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n,  std::vector<std::pair<unsigned, unsigned>> & journey);


#endif