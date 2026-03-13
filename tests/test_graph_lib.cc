#include "test_graph_lib.h"

TEST_F(GraphTest, LoadValidGraph) {
  EXPECT_NO_THROW({
    Graph g = Graph::LoadGraphFromFile("test_graph1.txt");
    EXPECT_EQ(g.size(), 3);
  });
}

TEST_F(GraphTest, GraphSize) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");
  EXPECT_EQ(g.size(), 3);

  Graph g2 = Graph::LoadGraphFromFile("test_single.txt");
  EXPECT_EQ(g2.size(), 1);

  Graph g3 = Graph::LoadGraphFromFile("test_graph3.txt");
  EXPECT_EQ(g3.size(), 5);
}

TEST_F(GraphTest, GetEdgeValid) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");

  EXPECT_EQ(g.get_edge(0, 1), 2);
  EXPECT_EQ(g.get_edge(0, 2), 5);
  EXPECT_EQ(g.get_edge(1, 0), 2);
  EXPECT_EQ(g.get_edge(1, 2), 3);
  EXPECT_EQ(g.get_edge(2, 0), 5);
  EXPECT_EQ(g.get_edge(2, 1), 3);
  EXPECT_EQ(g.get_edge(0, 0), 0);
}

TEST_F(GraphTest, GraphWithLoops) {
  Graph g = Graph::LoadGraphFromFile("test_graph2.txt");

  EXPECT_EQ(g.size(), 4);
  EXPECT_EQ(g.get_edge(0, 0), 1);
  EXPECT_EQ(g.get_edge(1, 1), 2);
  EXPECT_EQ(g.get_edge(2, 2), 3);
  EXPECT_EQ(g.get_edge(3, 3), 5);
  EXPECT_EQ(g.get_edge(0, 3), 7);
  EXPECT_EQ(g.get_edge(1, 2), 4);
  EXPECT_EQ(g.get_edge(2, 1), 4);
}

TEST_F(GraphTest, GetEdgeInvalidIndices) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");

  EXPECT_THROW(g.get_edge(10, 0), std::runtime_error);
  EXPECT_THROW(g.get_edge(0, 10), std::runtime_error);
  EXPECT_THROW(g.get_edge(10, 10), std::runtime_error);
}

TEST_F(GraphTest, LoadNonExistentFile) {
  EXPECT_THROW(Graph::LoadGraphFromFile("nonexistent.txt"), std::runtime_error);
}

TEST_F(GraphTest, LoadInvalidFileFormat) {
  EXPECT_THROW(Graph::LoadGraphFromFile("test_invalid1.txt"),
               std::runtime_error);
}

TEST_F(GraphTest, LoadInvalidMatrixSize) {
  EXPECT_THROW(Graph::LoadGraphFromFile("test_invalid2.txt"),
               std::runtime_error);
}

TEST_F(GraphTest, LoadInvalidMatrix) {
  EXPECT_THROW(Graph::LoadGraphFromFile("test_invalid3.txt"),
               std::runtime_error);
}

TEST_F(GraphTest, LoadEmptyFile) {
  EXPECT_THROW(Graph::LoadGraphFromFile("test_empty.txt"), std::runtime_error);
}

TEST_F(GraphTest, ExportToDot) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");

  EXPECT_NO_THROW(g.ExportGraphToDot("test_output.dot"));
  EXPECT_TRUE(fileExists("test_output.dot"));

  std::string content = readFile("test_output.dot");
  EXPECT_FALSE(content.empty());
  EXPECT_NE(content.find("digraph s21"), std::string::npos);
  EXPECT_NE(content.find("0 -> 1"), std::string::npos);
  EXPECT_NE(content.find("0 -> 2"), std::string::npos);
  EXPECT_NE(content.find("label=\"2\""), std::string::npos);
  EXPECT_NE(content.find("label=\"5\""), std::string::npos);
}

TEST_F(GraphTest, ExportGraphWithLoops) {
  Graph g = Graph::LoadGraphFromFile("test_graph2.txt");

  EXPECT_NO_THROW(g.ExportGraphToDot("test_output2.dot"));
  EXPECT_TRUE(fileExists("test_output2.dot"));

  std::string content = readFile("test_output2.dot");
  EXPECT_NE(content.find("0 -> 0"), std::string::npos);
  EXPECT_NE(content.find("label=\"1\""), std::string::npos);
}

TEST_F(GraphTest, LargeGraph) {
  Graph g = Graph::LoadGraphFromFile("test_graph3.txt");

  EXPECT_EQ(g.size(), 5);
  EXPECT_EQ(g.get_edge(0, 1), 10);
  EXPECT_EQ(g.get_edge(0, 4), 20);
  EXPECT_EQ(g.get_edge(1, 2), 30);
  EXPECT_EQ(g.get_edge(2, 3), 40);
  EXPECT_EQ(g.get_edge(3, 4), 50);

  EXPECT_EQ(g.get_edge(1, 0), 10);
  EXPECT_EQ(g.get_edge(4, 0), 20);
  EXPECT_EQ(g.get_edge(2, 1), 30);
  EXPECT_EQ(g.get_edge(3, 2), 40);
  EXPECT_EQ(g.get_edge(4, 3), 50);
}

TEST_F(GraphTest, SingleNodeGraph) {
  Graph g = Graph::LoadGraphFromFile("test_single.txt");

  EXPECT_EQ(g.size(), 1);
  EXPECT_EQ(g.get_edge(0, 0), 5);

  EXPECT_NO_THROW(g.ExportGraphToDot("test_output.dot"));
  std::string content = readFile("test_output.dot");
  EXPECT_NE(content.find("0 -> 0"), std::string::npos);
  EXPECT_NE(content.find("label=\"5\""), std::string::npos);
}

TEST_F(GraphTest, ExportToInvalidFile) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");

  EXPECT_THROW(g.ExportGraphToDot("/root/test_output.dot"), std::runtime_error);
}

TEST_F(GraphTest, MoveSemantics) {
  Graph g1 = Graph::LoadGraphFromFile("test_graph1.txt");
  size_t original_size = g1.size();

  Graph g2 = std::move(g1);
  EXPECT_EQ(g2.size(), original_size);

  Graph g3 = Graph::LoadGraphFromFile("test_graph2.txt");
  size_t another_size = g3.size();
  g3 = std::move(g2);
  EXPECT_EQ(g3.size(), original_size);
  EXPECT_NE(another_size, original_size);
}

TEST_F(GraphTest, MatrixContent) {
  Graph g = Graph::LoadGraphFromFile("test_graph1.txt");

  std::vector<std::vector<size_t>> expected = {{0, 2, 5}, {2, 0, 3}, {5, 3, 0}};

  for (size_t i = 0; i < expected.size(); ++i) {
    for (size_t j = 0; j < expected[i].size(); ++j) {
      EXPECT_EQ(g.get_edge(i, j), expected[i][j]);
    }
  }
}
