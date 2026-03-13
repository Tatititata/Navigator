#include "ui.h"

void UI::clear_screen() { std::cout << "\033[2J\033[1;1H" << std::flush; }

void UI::press_enter() {
  std::cout << "Press Enter to continue...";
  std::string dummy;
  std::getline(std::cin, dummy);
  clear_screen();
}

void UI::print_request_file_name_menu() { std::cout << "Enter file name -> "; }

void UI::print_request_algo_menu() {
  std::cout << "\n=== Simple Navigator ===" << '\n';
  std::cout << "\n0. Export graph to *.dot\n\n";
  std::cout << "1. Breadth First Search" << '\n';
  std::cout << "2. Depth First Search" << '\n';
  std::cout << "3. Shortest Path Between Vertices" << '\n';
  std::cout << "4. Shortest Paths Between All Vertices" << '\n';
  std::cout << "5. Get Least Spanning Tree" << '\n';
  std::cout << "\n=== Solve Traveling Salesman Problem ===\n" << '\n';
  std::cout << "6. Ant algorithm" << '\n';
  std::cout << "7. Closest Neibourgh algorithm" << '\n';
  std::cout << "8. Simulated Annealing algorithm" << '\n';

  std::cout << "\n=== Bonus Part ===\n" << '\n';
  std::cout << "9. Speed comparision of 3 TSP algos" << '\n';

  std::cout << "\nTo quit press " << RED << "q" << RESET << " button. " << '\n';
  std::cout << "\nChoose algorithm number -> ";
}

void UI::print_request_vertex_number(const std::string& str, size_t size) {
  std::cout << "\nEnter " << str << " vertex (from 1 to " << size << ") -> ";
}

void UI::print_start_menu() {
  std::cout << "\nTo load a graph from file press " << RED << "l" << RESET
            << " button. ";
  std::cout << "To quit press " << RED << "q" << RESET << " button. ";
}

void UI::print_get_number_menu() {
  std::cout << "\nEnter number of repetitions for comparision -> ";
}

void UI::print_matrix(const std::vector<std::vector<size_t>>& matrix) {
  size_t size = matrix.size();
  if (size < 1) {
    std::cout << "Disconnected graph\n";
    return;
  }
  std::cout << "\n";
  size_t max_width = 0;
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      size_t num = matrix[i][j];

      size_t width = num == INF ? 3 : std::to_string(num).length();
      if (width > max_width) max_width = width;
    }
  }
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (matrix[i][j] == INF) {
        std::cout << "INF ";
      } else {
        std::cout << std::setw(max_width) << matrix[i][j] << " ";
      }
    }
    std::cout << "\n";
  }
}

size_t UI::request_vertex(const std::string& prompt, size_t max) {
  size_t vertex = 0;
  while (vertex < 1 || vertex > max) {
    UI::print_request_vertex_number(prompt, max);
    vertex = request_number();
  }
  return vertex;
}

size_t UI::request_number() {
  size_t number = 0;
  std::string input;
  std::getline(std::cin, input);
  try {
    number = std::stoul(input);
  } catch (...) {
  }
  return number;
}
