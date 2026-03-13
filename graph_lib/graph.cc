#include "graph.h"

Graph::Graph(std::ifstream& file) {
  size_ = get_dimension(file);
  if (size_ == 0) {
    throw std::runtime_error("Invalid matrix size");
  }

  matrix_ =
      std::vector<std::vector<size_t>>(size_, std::vector<size_t>(size_, 0));

  if (!load_graph_to_matrix(file)) {
    throw std::runtime_error("Failed to load matrix data");
  }
}

Graph Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file");
  }
  return Graph(file);
}

size_t Graph::get_dimension(std::ifstream& file) {
  size_t s = 0;  // size
  bool result = true;

  char c;
  while (file.get(c) && std::isspace(static_cast<unsigned char>(c))) {
  }

  while (file && c != '\n' && std::isdigit(static_cast<unsigned char>(c)) &&
         result) {
    if (s > (std::numeric_limits<size_t>::max() - (c - '0')) / 10) {
      result = false;
    }
    s = s * 10 + (c - '0');
    file.get(c);
  }
  while (file && c != '\n') {
    if (!std::isspace(static_cast<unsigned char>(c))) {
      result = false;
    }
    file.get(c);
  }

  return result ? s : 0;
}

size_t Graph::get_number_from_file_line(std::ifstream& file) {
  size_t num = 0;
  bool success = false;

  char c;
  while (file.get(c) && std::isspace(static_cast<unsigned char>(c))) {
  }

  while (file && std::isdigit(static_cast<unsigned char>(c))) {
    num = num * 10 + (c - '0');
    file.get(c);
    success = true;
  }

  if (file && !std::isspace(static_cast<unsigned char>(c))) {
    success = false;
    num = std::numeric_limits<size_t>::max();
  }

  if (!file && !success) {
    num = std::numeric_limits<size_t>::max();
  }
  return num;
}

bool Graph::load_graph_to_matrix(std::ifstream& file) {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t num = get_number_from_file_line(file);

      if (num != std::numeric_limits<size_t>::max()) {
        matrix_[i][j] = num;
      } else {
        return false;
      }
    }
  }
  return true;
}

void Graph::ExportGraphToDot(const std::string& filename) const {
  std::ofstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }
  write_graph_to_file(file);
}

void Graph::write_graph_to_file(std::ofstream& file) const {
  file << "digraph s21 {\n";

  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (matrix_[i][j] != 0) {
        file << "    " << i << " -> " << j << " [label=\"" << matrix_[i][j]
             << "\"];\n";
      }
    }
  }

  file << "}\n";
}

size_t Graph::get_edge(size_t ver1, size_t ver2) const {
  if (ver1 < size_ && ver2 < size_) {
    return matrix_[ver1][ver2];
  }
  throw std::runtime_error("Vertex out of range");
}