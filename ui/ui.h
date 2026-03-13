#ifndef _UI_H_
#define _UI_H_
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

class UI {
 public:
  static size_t request_vertex(const std::string& prompt, size_t max);
  static size_t request_number();
  static constexpr size_t INF = std::numeric_limits<size_t>::max();
  static constexpr const char* RED = "\033[1;31m";
  static constexpr const char* RESET = "\033[0m";

  static void clear_screen();
  static void press_enter();
  static void print_request_file_name_menu();
  static void print_request_algo_menu();
  static void print_request_vertex_number(const std::string& str, size_t size);
  static void print_start_menu();
  static void print_get_number_menu();
  static void print_matrix(const std::vector<std::vector<size_t>>& matrix);
};
#endif