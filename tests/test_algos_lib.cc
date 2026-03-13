#include "test_algos_lib.h"

TEST_F(GraphAlgosTest, DepthFirstSearch) {
  Graph g = Graph::LoadGraphFromFile("test_dfs_bfs.txt");
  std::vector<size_t> result = GraphAlgorithms::DepthFirstSearch(g, 1);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 1);

  std::vector<size_t> sorted = result;
  std::sort(sorted.begin(), sorted.end());
  for (size_t i = 1; i <= 5; ++i) {
    EXPECT_TRUE(std::find(result.begin(), result.end(), i) != result.end());
  }
}

TEST_F(GraphAlgosTest, BreadthFirstSearch) {
  Graph g = Graph::LoadGraphFromFile("test_dfs_bfs.txt");
  std::vector<size_t> result = GraphAlgorithms::BreadthFirstSearch(g, 1);

  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 1);

  bool valid =
      (result[1] == 2 && result[2] == 5) || (result[1] == 5 && result[2] == 2);
  EXPECT_TRUE(valid);
}

TEST_F(GraphAlgosTest, ShortestPathBetweenVertices) {
  Graph g = Graph::LoadGraphFromFile("test_shortest.txt");

  size_t distance = GraphAlgorithms::GetShortestPathBetweenVertices(g, 1, 4);
  EXPECT_EQ(distance, 3U);

  distance = GraphAlgorithms::GetShortestPathBetweenVertices(g, 1, 3);
  EXPECT_EQ(distance, 5U);

  distance = GraphAlgorithms::GetShortestPathBetweenVertices(g, 3, 4);
  EXPECT_EQ(distance, 4U);
}

TEST_F(GraphAlgosTest, ShortestPathsBetweenAllVertices) {
  Graph g = Graph::LoadGraphFromFile("test_shortest.txt");
  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(g);

  EXPECT_EQ(result.size(), 4U);
  EXPECT_EQ(result[0].size(), 4U);

  EXPECT_EQ(result[0][1], 2U);
  EXPECT_EQ(result[0][2], 5U);
  EXPECT_EQ(result[0][3], 3U);
  EXPECT_EQ(result[1][3], 1U);
  EXPECT_EQ(result[2][3], 4U);
}

TEST_F(GraphAlgosTest, LeastSpanningTree) {
  Graph g = Graph::LoadGraphFromFile("test_mst.txt");
  auto result = GraphAlgorithms::GetLeastSpanningTree(g);

  EXPECT_EQ(result.size(), 5U);
  EXPECT_EQ(result[0].size(), 5U);

  size_t total_weight = 0;
  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = i + 1; j < 5; ++j) {
      total_weight += result[i][j];
    }
  }
  EXPECT_EQ(total_weight, 16U);

  EXPECT_NE(result[0][1], 0U);
  EXPECT_NE(result[1][2], 0U);
  EXPECT_NE(result[1][4], 0U);
  EXPECT_NE(result[0][3], 0U);
}

TEST_F(GraphAlgosTest, SimulatedAnnealing) {
  Graph g = Graph::LoadGraphFromFile("test_tsp.txt");
  TsmResult result = GraphAlgorithms::SimulatedAnnealing(g);

  EXPECT_EQ(result.vertices.size(), 4U);
  EXPECT_GT(result.distance, 0U);

  std::set<size_t> unique_vertices(result.vertices.begin(),
                                   result.vertices.end());
  EXPECT_EQ(unique_vertices.size(), 4U);

  for (size_t i = 0; i < 3; ++i) {
    size_t v1 = result.vertices[i];
    size_t v2 = result.vertices[i + 1];
    EXPECT_GT(g.get_edge(v1 - 1, v2 - 1), 0U);
  }
  EXPECT_GT(g.get_edge(result.vertices[0] - 1, result.vertices[3] - 1), 0U);
}

TEST_F(GraphAlgosTest, SolveTravelingSalesmanProblem) {
  Graph g = Graph::LoadGraphFromFile("test_tsp.txt");
  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(g, true);

  EXPECT_EQ(result.vertices.size(), 4U);
  EXPECT_GT(result.distance, 0U);

  std::set<size_t> unique_vertices(result.vertices.begin(),
                                   result.vertices.end());
  EXPECT_EQ(unique_vertices.size(), 4U);

  for (size_t i = 0; i < 3; ++i) {
    size_t v1 = result.vertices[i];
    size_t v2 = result.vertices[i + 1];
    EXPECT_GT(g.get_edge(v1 - 1, v2 - 1), 0U);
  }
  EXPECT_GT(g.get_edge(result.vertices[0] - 1, result.vertices[3] - 1), 0U);
}

TEST_F(GraphAlgosTest, SimulatedAnnealingWithNB) {
  Graph g = Graph::LoadGraphFromFile("test_tsp.txt");
  TsmResult result = GraphAlgorithms::SimulatedAnnealing(g, true);

  EXPECT_EQ(result.vertices.size(), 4U);
  EXPECT_GT(result.distance, 0U);

  std::set<size_t> unique_vertices(result.vertices.begin(),
                                   result.vertices.end());
  EXPECT_EQ(unique_vertices.size(), 4U);

  for (size_t i = 0; i < 3; ++i) {
    size_t v1 = result.vertices[i];
    size_t v2 = result.vertices[i + 1];
    EXPECT_GT(g.get_edge(v1 - 1, v2 - 1), 0U);
  }
  EXPECT_GT(g.get_edge(result.vertices[0] - 1, result.vertices[3] - 1), 0U);
}

TEST_F(GraphAlgosTest, ClosestNeibourgh) {
  Graph g = Graph::LoadGraphFromFile("test_tsp.txt");
  TsmResult result = GraphAlgorithms::ClosestNeibourgh(g);

  EXPECT_EQ(result.vertices.size(), 4U);
  EXPECT_GT(result.distance, 0U);

  std::set<size_t> unique_vertices(result.vertices.begin(),
                                   result.vertices.end());
  EXPECT_EQ(unique_vertices.size(), 4U);

  for (size_t i = 0; i < 3; ++i) {
    size_t v1 = result.vertices[i];
    size_t v2 = result.vertices[i + 1];
    EXPECT_GT(g.get_edge(v1 - 1, v2 - 1), 0U);
  }
  EXPECT_GT(g.get_edge(result.vertices[0] - 1, result.vertices[3] - 1), 0U);
}

TEST_F(GraphAlgosTest, ClosestNeibourghINF) {
  Graph g = Graph::LoadGraphFromFile("test_disconnected.txt");
  TsmResult result = GraphAlgorithms::ClosestNeibourgh(g);

  EXPECT_EQ(result.vertices.size(), 5U);
  EXPECT_EQ(result.distance, INF);
}

TEST_F(GraphAlgosTest, SimulatedAnnealingINF) {
  Graph g = Graph::LoadGraphFromFile("test_disconnected.txt");
  TsmResult result = GraphAlgorithms::SimulatedAnnealing(g);

  EXPECT_EQ(result.vertices.size(), 5U);
  EXPECT_EQ(result.distance, INF);
}

TEST_F(GraphAlgosTest, SolveTravelingSalesmanProblemINF) {
  Graph g = Graph::LoadGraphFromFile("test_disconnected.txt");
  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(g);

  EXPECT_EQ(result.vertices.size(), 5U);
  EXPECT_EQ(result.distance, INF);
}