#include <vector>
#include <gtest/gtest.h>

#include "euler.hpp"
#include "topologicalSort.hpp"
#include "bipartite.hpp"
#include "graphfundsgrading.hpp"

namespace{

	/*
	- Euler 
		* use an enumerated type for has a circuit, has a walk, has neither
		* if it's one of the yes cases, std::vector<std::pair<unsigned, unsigned>> of the circuit/path
	*/


TEST(RequiredEuler, NotEulerianK4)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 4, journey), neither);
}

TEST(RequiredEuler, NotEulerClassic)
{	// a representation of the classic Bridges of Konigsberg problem.
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {0,1}, {0,2}, {0,3}, {0,3}, {1,2}, {2,3} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 4, journey), neither);
}



TEST(RequiredEuler, HasAnEulerianWalk)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {0,3}, {0,5}, {0,7}, {1,3}, {1,5}, {1,7}, {2,4}, {2,6}, {3,4}, {3,5}, {4,5}, {6,7} };
	// one such journey, in the desired representation, is as follows:
	// { {7,6}, {6,2}, {2,4}, {4,3}, {3,5}, {5,0}, {0,7}, {7,1}, {1,0}, {0,3}, {3,1}, {1,5}, {5,4} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 8, journey), walk);
	EXPECT_EQ(journey.size(), GRAPH.size());
	EXPECT_TRUE(confirmEdgesInGraph(GRAPH, journey));
	EXPECT_TRUE(confirmIsWalk(journey));
}

TEST(RequiredEuler, HasAnEulerianCircuit)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {0,7}, {1,7}, {1,3}, {1,6}, {2,3}, {2,4}, {2,6}, {2,7}, {3,5}, {3,4}, {4,5}, {4,6}, {6,7} };
	// one such journey, in the desired representation, is as follows:
	// { {0,7}, {7,1}, {1,6}, {6,4}, {4,3}, {3,2}, {2,7}, {7,6}, {6,2}, {2,4}, {4,5}, {5,3}, {3,1}, {1,0} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 8, journey), circuit);
	EXPECT_EQ(journey.size(), GRAPH.size());
	EXPECT_TRUE(confirmEdgesInGraph(GRAPH, journey));
	EXPECT_TRUE(confirmIsCycle(journey));
}

TEST(NotRequiredEuler, NotEulerianK4){
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = {{0,1},{1,4},{1,2},{2,5},{4,5},{2,3},{5,6},{2,5},{3,6},{6,7} };
	// one such journey, in the desired representation, is as follows:
	// { {0,7}, {7,1}, {1,6}, {6,4}, {4,3}, {3,2}, {2,7}, {7,6}, {6,2}, {2,4}, {4,5}, {5,3}, {3,1}, {1,0} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 8, journey), neither);
}

TEST(NotRequiredEuler, HasAnEulerianWalk)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1},{1,2},{2,3},{3,4},{4,5} };
	// one such journey, in the desired representation, is as follows:
	// { {7,6}, {6,2}, {2,4}, {4,3}, {3,5}, {5,0}, {0,7}, {7,1}, {1,0}, {0,3}, {3,1}, {1,5}, {5,4} };
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 6, journey), walk);
	EXPECT_EQ(journey.size(), GRAPH.size());
	EXPECT_TRUE(confirmEdgesInGraph(GRAPH, journey));
	EXPECT_TRUE(confirmIsWalk(journey));
}

TEST(NotRequiredEuler1, HasAnEulerianWalk){
	const std::vector<std::pair<unsigned, unsigned> > GRAPH ={{1,0},{0,2},{2,1},{0,3},{3,4}};
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 5, journey), walk);
	EXPECT_EQ(journey.size(), GRAPH.size());
	EXPECT_TRUE(confirmEdgesInGraph(GRAPH, journey));
	EXPECT_TRUE(confirmIsWalk(journey));
}

TEST(NotRequiredEuler2, HasAnEulerianCircuit){
	const std::vector<std::pair<unsigned, unsigned> > GRAPH ={{1,0},{0,2},{2,1},{0,3},{3,4},{4,0}};
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 5, journey), circuit);
	EXPECT_EQ(journey.size(), GRAPH.size());
	EXPECT_TRUE(confirmEdgesInGraph(GRAPH, journey));
	EXPECT_TRUE(confirmIsWalk(journey));
}

TEST(NotRequiredEuler3, NotEulerian){
	const std::vector<std::pair<unsigned, unsigned> > GRAPH ={{1,0},{0,2},{2,1},{0,3},{1,3}, {3,4}};
	std::vector<std::pair<unsigned, unsigned>>  journey;
	EXPECT_EQ(checkForEuler(GRAPH, 5, journey), neither);
}


/*
 	Test cases and verification functions for Topological Sort

	Expected behavior of Topological Sort:
		* has a cycle?  Throw a NoTopologicalOrderException
		* else provide a vector in Topological order

 */



TEST(RequiredTopologicalSort, GraphWithCycleThrowsAnException)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {1,2}, {2,0} };
    EXPECT_THROW( topologicalSort(GRAPH, 3) , NoTopologicalSortException);   
}


TEST(RequiredTopologicalSort, SimpleTopologicalOrder)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {0,3} };
	std::vector<unsigned> ord = topologicalSort(GRAPH, 6);
	// one possible ord, in the desired format: 	 ord = {0, 1, 2, 3, 4, 5};

    EXPECT_TRUE( validTopologicalSort(GRAPH, 6, ord) );   
}

TEST(NotRequiredTopologicalSort, SimpleTopologicalOrder){
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {1,0}, {2,0},{3,1},{3,2}};
	std::vector<unsigned> ord = topologicalSort(GRAPH, 4);
	// one possible ord, in the desired format: 	 ord = {0, 1, 2, 3, 4, 5};

    EXPECT_TRUE( validTopologicalSort(GRAPH, 4, ord) ); 
}


	/* 

	- bipartite checking
		* bipartite?  Tell me that it is.
		* not bipartite?  provide an odd length cycle

	*/

TEST(RequiredBipartiteChecking, IsBipartiteOne)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {1,2}, {2,3}, {0,3} };
	std::vector<std::pair<unsigned, unsigned>> evidence; // will not be in use this test case
	EXPECT_TRUE( isBipartite(GRAPH, 4, evidence));
}



TEST(RequiredBipartiteChecking, IsBipartiteTwo)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {1,2}, {2,3}, {0,4}, {4,5}, {5,6}, {0,7}, {7,8} };
	std::vector<std::pair<unsigned, unsigned>> evidence; // will not be in use this test case
	EXPECT_TRUE( isBipartite(GRAPH, 9, evidence));
}


TEST(RequiredBipartiteChecking, ThisIsNotBipartite)
{
	const std::vector<std::pair<unsigned, unsigned> > GRAPH = { {0,1}, {1,2}, {2,3}, {0,3}, {2,4}, {4,5}, {5,6}, {6,7}, {2,7} };
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_FALSE( isBipartite(GRAPH, 8, evidence));

	// one possible evidence, in the desired format, is as follows
	// { {2,4}, {4,5}, {5,6}, {6,7}, {7,2} };

	// Note:  in the above graph, the evidence should be either { {2,4}, {4,5}, {5,6}, {6,7}, {7,2} } or { {2,7}, {7,6}, {6,5}, {5,4}, {4,2} }.
	// Even though the edges are not presented in that fashion in the input, the verification mechanism expects them in that order. 
	EXPECT_TRUE(evidence.size() > 0 and confirmIsCycle(evidence));
	EXPECT_EQ(evidence.size() % 2, 1);
	EXPECT_TRUE(evidence.size() > 0 and confirmEdgesInGraph(GRAPH, evidence));

}
TEST(NotRequiredBipartiteChecking, ThisIsNotBipartite){
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0,1}, {1,3}, {3,2}, {2,0}, {0,3}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_FALSE( isBipartite(GRAPH, 4, evidence));

	EXPECT_TRUE(evidence.size() > 0 and confirmIsCycle(evidence));
	EXPECT_EQ(evidence.size() % 2, 1);
	EXPECT_TRUE(evidence.size() > 0 and confirmEdgesInGraph(GRAPH, evidence));
}

TEST(NotRequiredBipartiteChecking1, ThisIsNotBipartite){
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0, 1}, {1,2}, {2,5}, {5,6}, {6,3}, {3,5}, {3,4}, {4,0}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_FALSE( isBipartite(GRAPH, 7, evidence));

	EXPECT_TRUE(evidence.size() > 0 and confirmIsCycle(evidence));
	EXPECT_EQ(evidence.size() % 2, 1);
	EXPECT_TRUE(evidence.size() > 0 and confirmEdgesInGraph(GRAPH, evidence));
}

TEST(NotRequiredBipartiteChecking2, IsBipartiteTwo){
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0, 1}, {1,2}, {2,5}, {5,7}, {7,6}, {6,3}, {3,5}, {3,4}, {0,4}, {1,3}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_TRUE( isBipartite(GRAPH, 8, evidence));
}

TEST(NotRequiredBipartiteChecking3, IsBipartiteTwo){
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0, 1}, {1,2},{1,4},{2,3},{4,3},{5,0}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_TRUE( isBipartite(GRAPH, 8, evidence));
}

TEST(NotRequiredBipartiteChecking4, ThisIsNotBipartite){
	// has odd cycle from 0-1-2-3-5-6-10-12-14-0
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0,1},{1,2},{2,3},{3,4},{3,5},{5,6},{6,7},{7,8},{0,14},{8,9},{9,6},{6,10},{10,11},{10,12},{12,13},{12,14}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_FALSE( isBipartite(GRAPH, 15, evidence));

	EXPECT_TRUE(evidence.size() > 0 and confirmIsCycle(evidence));
	EXPECT_EQ(evidence.size() % 2, 1);
	EXPECT_TRUE(evidence.size() > 0 and confirmEdgesInGraph(GRAPH, evidence));
}
TEST(NotRequiredBipartiteChecking5, IsBipartiteOne){
	const std::vector<std::pair<unsigned, unsigned>> GRAPH = {{0,1},{1,2},{2,3},{3,4},{3,5},{5,6},{6,7},{7,8},{8,9},{9,6},{6,10},{10,11},{10,12},{12,13},{12,14}};
	std::vector<std::pair<unsigned, unsigned>> evidence; // this will be in use this test case
	EXPECT_TRUE( isBipartite(GRAPH, 15, evidence));
}



} // end namespace that includes the test cases



