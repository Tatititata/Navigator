#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Graph {
 public:
  Graph() = delete;
  Graph(const Graph&) = delete;
  Graph& operator=(const Graph&) = delete;
  Graph(Graph&&) = default;
  Graph& operator=(Graph&&) = default;

  static Graph LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename) const;

  ~Graph() = default;

  size_t size() const { return size_; }

  size_t get_edge(size_t ver1, size_t ver2) const;

 private:
  explicit Graph(std::ifstream& file);

  size_t get_dimension(std::ifstream& file);
  static size_t get_number_from_file_line(std::ifstream& file);
  bool load_graph_to_matrix(std::ifstream& file);
  void write_graph_to_file(std::ofstream& file) const;

  std::vector<std::vector<size_t>> matrix_;
  size_t size_;
};

#endif