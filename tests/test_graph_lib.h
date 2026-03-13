#ifndef GRAPH_TEST_H_
#define GRAPH_TEST_H_

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../graph_lib/graph.h"

class GraphTest : public ::testing::Test {
 protected:
  void SetUp() override { createTestFiles(); }

  void TearDown() override { cleanupTestFiles(); }

  void createTestFiles() {
    std::ofstream file1("test_graph1.txt");
    file1 << "3\n";
    file1 << "0 2 5\n";
    file1 << "2 0 3\n";
    file1 << "5 3 0\n";
    file1.close();

    std::ofstream file2("test_graph2.txt");
    file2 << "4\n";
    file2 << "1 0 0 7\n";
    file2 << "0 2 4 0\n";
    file2 << "0 4 3 0\n";
    file2 << "7 0 0 5\n";
    file2.close();

    std::ofstream file3("test_graph3.txt");
    file3 << "5\n";
    file3 << "0 10 0 0 20\n";
    file3 << "10 0 30 0 0\n";
    file3 << "0 30 0 40 0\n";
    file3 << "0 0 40 0 50\n";
    file3 << "20 0 0 50 0\n";
    file3.close();

    std::ofstream file4("test_invalid1.txt");
    file4 << "abc\n";
    file4 << "1 2 3\n";
    file4.close();

    std::ofstream file5("test_invalid2.txt");
    file5 << "3\n";
    file5 << "1 2\n";
    file5 << "2 3\n";
    file5.close();

    std::ofstream file6("test_empty.txt");
    file6.close();

    std::ofstream file7("test_invalid3.txt");
    file7 << "2\n";
    file7 << "2 1\n";
    file7 << "1 4f\n";
    file7.close();

    std::ofstream file8("test_single.txt");
    file8 << "1\n";
    file8 << "5\n";
    file8.close();
  }

  void cleanupTestFiles() {
    std::filesystem::remove("test_graph1.txt");
    std::filesystem::remove("test_graph2.txt");
    std::filesystem::remove("test_graph3.txt");
    std::filesystem::remove("test_invalid1.txt");
    std::filesystem::remove("test_invalid2.txt");
    std::filesystem::remove("test_empty.txt");
    std::filesystem::remove("test_invalid3.txt");
    std::filesystem::remove("test_single.txt");
    std::filesystem::remove("test_output.dot");
    std::filesystem::remove("test_output2.dot");
  }

  bool fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
  }

  std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }
};

#endif  // GRAPH_TEST_H_