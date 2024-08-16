#include "euler.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

bool dfs(unsigned start, std::vector<std::pair<unsigned,unsigned>> &eulerPath, std::vector<std::pair<unsigned,unsigned>> &currPath,
 std::unordered_map<unsigned, std::vector<unsigned>> &adjList,
		 unsigned edges, unsigned totalEdges, unsigned n, std::unordered_map<unsigned, std::unordered_set<unsigned>> &visitedEdges);

EulerPossibility checkForEuler(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n,  std::vector<std::pair<unsigned, unsigned>> & journey){
	std::unordered_map<unsigned, std::vector<unsigned>> adjList;
	for(auto& [from, to] : graph){
		adjList[from].push_back(to);
		adjList[to].push_back(from);
	}
	unsigned start = 0; // starting node
	for(unsigned i = 0; i<graph.size(); i++){
		if(adjList[i].size() % 2 == 1){ // vertex with odd num edges will be the start point
			start = i;
			break;
		}
	}

	// begin dfs starting from start covering all edges if possible
	std::vector<std::pair<unsigned, unsigned>> eulerPath, currPath;
	std::unordered_map<unsigned, std::unordered_set<unsigned>> visitedEdges;

	bool isEulerGraph = dfs(start, eulerPath, currPath, adjList, 0, graph.size(), n, visitedEdges);
	journey = eulerPath;

	if(isEulerGraph){ // check if is a walk or circuit path
		if(eulerPath[0].first == eulerPath[eulerPath.size()-1].second) return circuit;
		return walk;
	}
	return neither;
}

bool dfs(unsigned start, std::vector<std::pair<unsigned,unsigned>> &eulerPath, std::vector<std::pair<unsigned,unsigned>> &currPath,
 std::unordered_map<unsigned, std::vector<unsigned>> &adjList,
		 unsigned edges, unsigned totalEdges, unsigned n, std::unordered_map<unsigned, std::unordered_set<unsigned>> &visitedEdges){
	if(edges == totalEdges) {
		eulerPath = currPath;
		return true;
	}
	if(start >= n) return false;

	std::unordered_set<unsigned> nodes = visitedEdges[start];
	for(auto& neighbor : adjList[start]){
		if(nodes.find(neighbor) == nodes.end()){ // edge wasnt previously passed through
			visitedEdges[start].insert(neighbor);
			visitedEdges[neighbor].insert(start);
			currPath.push_back({start, neighbor});

			bool res = dfs(neighbor, eulerPath, currPath, adjList, edges+1, totalEdges, n, visitedEdges);
			
			if(res) return true;
			currPath.pop_back();
			visitedEdges[start].erase(neighbor);
			visitedEdges[neighbor].erase(start);
		}
	}
	return false;
}