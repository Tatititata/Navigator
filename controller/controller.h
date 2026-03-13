#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <chrono>
#include <ctime>
#include <functional>
#include <iomanip>

#include "../algos_lib/graph_algos.h"
#include "../graph_lib/graph.h"
#include "../ui/ui.h"

class Controller {
 public:
  static void game_loop();

 private:
  struct TspAlgorithm {
    std::function<TsmResult(const Graph&)> func;
    std::string name;
  };
  static void handle_export(const Graph& g);
  static void handle_tsp(const Graph& g, const TspAlgorithm& algo);
  static void run_algorithm_benchmark(const Graph& g, const TspAlgorithm& algo,
                                      size_t runs);
  static void proceed_algorithms(const Graph& g);
  static void bonus_part(const Graph& g);
  static void handle_traversal(const Graph& g, const char algo_type);
  static void handle_shortest_path(const Graph& g);
  static void handle_matrix_algo(const Graph& g, const char algo_type);

  static const std::vector<TspAlgorithm> kTspAlgorithms;
};

#endif