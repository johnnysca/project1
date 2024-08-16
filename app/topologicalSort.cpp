#include "topologicalSort.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>

std::vector<unsigned> topologicalSort(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n)
{
	std::vector<unsigned> topoSort;
	std::unordered_map<unsigned, std::vector<unsigned>> adjList;
	std::unordered_map<unsigned, unsigned> indegree;

	for(auto& [from, to] : graph){
		adjList[from].push_back(to);
		indegree[to]++;
	}
	std::queue<unsigned> nodes; // nodes that have 0 indegree
	for(unsigned i = 0; i<n; i++){ // add all nodes that have indegree of 0
		if(indegree.find(i) == indegree.end()) nodes.push(i);
	}
	std::vector<bool> visited(n, false);
	unsigned nodesSeen = 0;


	while(!nodes.empty()){
		unsigned currNode = nodes.front();
		nodes.pop();
		topoSort.push_back(currNode);
		visited[currNode] = true;
		nodesSeen++;
		for(auto& neighbor : adjList[currNode]){
			if(visited[neighbor]) throw NoTopologicalSortException("Graph has a cycle");
			indegree[neighbor]--;
			if(indegree[neighbor] == 0){
				nodes.push(neighbor);
				indegree.erase(neighbor);
			}
		}
	}
	if(nodesSeen != n)
		throw NoTopologicalSortException("Graph has a cycle");
	return topoSort;
}