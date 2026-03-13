#ifndef GRAPH_ALGOS_TEST_H_
#define GRAPH_ALGOS_TEST_H_

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../algos_lib/graph_algos.h"
#include "../graph_lib/graph.h"

class GraphAlgosTest : public ::testing::Test {
 protected:
  void SetUp() override { createTestGraphs(); }

  void TearDown() override { cleanupTestFiles(); }

  void createTestGraphs() {
    std::ofstream file1("test_dfs_bfs.txt");
    file1 << "5\n";
    file1 << "0 1 0 0 1\n";
    file1 << "1 0 1 0 0\n";
    file1 << "0 1 0 1 0\n";
    file1 << "0 0 1 0 1\n";
    file1 << "1 0 0 1 0\n";
    file1.close();

    std::ofstream file2("test_shortest.txt");
    file2 << "4\n";
    file2 << "0 2 6 0\n";
    file2 << "2 0 3 1\n";
    file2 << "6 3 0 4\n";
    file2 << "0 1 4 0\n";
    file2.close();

    std::ofstream file3("test_tsp.txt");
    file3 << "4\n";
    file3 << "0 10 15 20\n";
    file3 << "10 0 35 25\n";
    file3 << "15 35 0 30\n";
    file3 << "20 25 30 0\n";
    file3.close();

    std::ofstream file4("test_mst.txt");
    file4 << "5\n";
    file4 << "0 2 0 6 0\n";
    file4 << "2 0 3 8 5\n";
    file4 << "0 3 0 0 7\n";
    file4 << "6 8 0 0 9\n";
    file4 << "0 5 7 9 0\n";
    file4.close();

    std::ofstream file5("test_disconnected.txt");
    file5 << "5\n";
    file5 << "0 2 0 6 0\n";
    file5 << "2 0 3 8 0\n";
    file5 << "0 3 0 0 0\n";
    file5 << "6 8 0 0 0\n";
    file5 << "0 0 0 0 1\n";
    file5.close();
  }

  void cleanupTestFiles() {
    std::filesystem::remove("test_dfs_bfs.txt");
    std::filesystem::remove("test_shortest.txt");
    std::filesystem::remove("test_tsp.txt");
    std::filesystem::remove("test_mst.txt");
    std::filesystem::remove("test_disconnected.txt");
  }
};

#endif  // GRAPH_ALGOS_TEST_H_