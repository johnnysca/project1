#include "bipartite.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

bool dfs(unsigned start, std::unordered_map<unsigned, std::vector<unsigned>> &adjList, std::vector<bool> &visited,
		std::vector<int> &parent, int &startOfCycle, int &endOfCycle, std::vector<int> &distances, int &currDist){ 
		// return true iff we find an odd length cycle
	visited[start] = true;
	
	for(auto& neighbor : adjList[start]){
		if(neighbor == parent[start]) continue; // we came from parent so skip
		if(!visited[neighbor]){
			distances[start] = currDist;
			currDist++;
			parent[neighbor] = start;
			if(dfs(neighbor, adjList, visited, parent, startOfCycle, endOfCycle, distances, currDist)) return true;
			currDist = distances[start]; // reset to the current nodes distance
		}
		else{ // node has been visited so its a cycle
			if(((currDist+1) - distances[neighbor]) % 2 == 1){ // calculates nodes involved in cycle
				startOfCycle = neighbor;
				endOfCycle = start;
				return true;
			}
			visited[start] = false;
		}
	}
	return false;
}

bool isBipartite(const std::vector<std::pair<unsigned, unsigned> > & graph, unsigned n, std::vector< std::pair<unsigned, unsigned> > & evidence){
	std::unordered_map<unsigned, std::vector<unsigned>> adjList;
	std::vector<bool> visited(n, false);
	std::vector<int> parent(n, -1); // holds the ith nodes parent 
	int startOfCycle = -1, endOfCycle = -1; // nodes  where the cycle starts and ends

	for(auto& [from, to] : graph){
		adjList[from].push_back(to);
		adjList[to].push_back(from);
	}
	std::vector<int> distances (n, 0); // used to detect if cycle has odd num of nodes
	int currDist = 0;
	for(unsigned start = 0; start < n; start++){
		if(!visited[start] && dfs(start, adjList, visited, parent, startOfCycle, endOfCycle, distances, currDist)){ // return the cycle of odd length
			std::vector<unsigned> path; // path of the cycle 
			
			for(int start = endOfCycle; start != startOfCycle; start = parent[start]){ // backtracks route of cycle
				path.push_back(start);
			}
			path.push_back(startOfCycle);
			evidence.push_back({startOfCycle, path[0]});
			for(unsigned i = 0; i<path.size()-1; i++){
				evidence.push_back({path[i], path[i+1]});
			}
			return false;
		}
	}
	return true; 
}