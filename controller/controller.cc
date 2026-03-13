#include "controller.h"

void Controller::game_loop() {
  std::string input = "0";
  while (input != "q") {
    UI::clear_screen();
    UI::print_start_menu();
    std::getline(std::cin, input);
    if (input == "l") {
      UI::print_request_file_name_menu();
      std::getline(std::cin, input);
      try {
        auto g = Graph::LoadGraphFromFile(input);
        proceed_algorithms(g);
      } catch (const std::exception& e) {
        std::cout << "Can not load graph: " << e.what() << "\n";
        input = "0";
        UI::press_enter();
      }
    }
  }
}

void Controller::handle_traversal(const Graph& g, const char algo_type) {
  size_t start_vertex = UI::request_vertex("start", g.size());
  auto result = algo_type == 'B'
                    ? GraphAlgorithms::BreadthFirstSearch(g, start_vertex)
                    : GraphAlgorithms::DepthFirstSearch(g, start_vertex);
  // std::cout << algo_type << '\n';
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i] << ' ';
  }
  std::cout << '\n';
  if (result.size() < g.size()) {
    std::cout << "Disconnected graph\n";
  }
}
void Controller::handle_shortest_path(const Graph& g) {
  // "Shortest Path Between Vertices"
  size_t start_vertex = UI::request_vertex("start", g.size());
  size_t end_vertex = UI::request_vertex("end", g.size());
  auto result = GraphAlgorithms::GetShortestPathBetweenVertices(g, start_vertex,
                                                                end_vertex);
  std::cout << "Shortest Path Between Vertices\n";
  if (result == INF) {
    std::cout << "No path between vertices.\n";
  } else {
    std::cout << result << '\n';
  }
}

void Controller::handle_matrix_algo(const Graph& g, const char algo_type) {
  auto result = algo_type == 'L'
                    ? GraphAlgorithms::GetLeastSpanningTree(g)
                    : GraphAlgorithms::GetShortestPathsBetweenAllVertices(g);
  UI::print_matrix(result);
}

void Controller::handle_tsp(const Graph& g, const TspAlgorithm& algo) {
  TsmResult result = algo.func(g);
  if (result.distance < INF) {
    std::cout << algo.name << "\nDistance: " << result.distance << "\nPath: ";
    for (size_t v : result.vertices) std::cout << v << ' ';
    std::cout << "\n";
  } else {
    std::cout << "No traveling salesman route exists\n";
  }
}

void Controller::handle_export(const Graph& g) {
  std::string input = "0";
  UI::print_request_file_name_menu();
  std::getline(std::cin, input);
  input += ".dot";
  try {
    g.ExportGraphToDot(input);
    std::cout << "Graph is exported to the file: " << input << "\n";
  } catch (const std::exception& e) {
    std::cout << "Can not export graph to file: " << e.what() << "\n";
    UI::press_enter();
  }
}

void Controller::proceed_algorithms(const Graph& g) {
  std::unordered_map<std::string, std::function<void(const Graph&)>> handlers =
      {{"0", [&](const Graph& g) { handle_export(g); }},
       {"1", [&](const Graph& g) { handle_traversal(g, 'B'); }},
       {"2", [&](const Graph& g) { handle_traversal(g, 'D'); }},
       {"3", [&](const Graph& g) { handle_shortest_path(g); }},
       {"4", [&](const Graph& g) { handle_matrix_algo(g, 'S'); }},
       {"5", [&](const Graph& g) { handle_matrix_algo(g, 'L'); }},
       {"6", [&](const Graph& g) { handle_tsp(g, kTspAlgorithms[0]); }},
       {"7", [&](const Graph& g) { handle_tsp(g, kTspAlgorithms[2]); }},
       {"8", [&](const Graph& g) { handle_tsp(g, kTspAlgorithms[3]); }},
       {"9", [&](const Graph& g) { bonus_part(g); }}};

  UI::clear_screen();
  std::string input = "0";

  while (input != "q") {
    UI::print_request_algo_menu();
    std::getline(std::cin, input);

    auto it = handlers.find(input);
    if (it != handlers.end()) {
      it->second(g);
      UI::press_enter();
    }
  }
}

const std::vector<Controller::TspAlgorithm> Controller::kTspAlgorithms = {
    {[](const Graph& g) {
       return GraphAlgorithms::SolveTravelingSalesmanProblem(g, false);
     },
     "Ant algorithm (without nb)"},
    {[](const Graph& g) {
       return GraphAlgorithms::SolveTravelingSalesmanProblem(g, true);
     },
     "Ant algorithm (with nb)"},
    {[](const Graph& g) { return GraphAlgorithms::ClosestNeibourgh(g); },
     "Closest Neighbour"},
    {[](const Graph& g) {
       return GraphAlgorithms::SimulatedAnnealing(g, false);
     },
     "Simulated Annealing (without nb)"},
    {[](const Graph& g) {
       return GraphAlgorithms::SimulatedAnnealing(g, true);
     },
     "Simulated Annealing (with nb)"}};

void Controller::bonus_part(const Graph& g) {
  size_t number = 0;

  while (number < 1 || number > 1000) {
    UI::print_get_number_menu();
    number = UI::request_number();
  }
  for (const auto& algo : kTspAlgorithms) {
    run_algorithm_benchmark(g, algo, number);
  }
}

void Controller::run_algorithm_benchmark(const Graph& g,
                                         const TspAlgorithm& algo,
                                         size_t runs) {
  double total_time = 0;
  double avg_distance = 0;
  TsmResult result = algo.func(g);
  for (size_t i = 0; i < runs && result.distance != INF; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    result = algo.func(g);
    auto end = std::chrono::high_resolution_clock::now();

    total_time += std::chrono::duration<double>(end - start).count();
    if (result.distance != INF) {
      avg_distance = (avg_distance * i + result.distance) / (i + 1);
    }
  }

  std::cout << std::left << std::setw(40) << algo.name << "| ";
  if (avg_distance > 0) {
    std::cout << std::setw(20)
              << ("Avg distance: " + std::to_string(avg_distance)) << "| "
              << std::setw(25)
              << ("Avg time: " + std::to_string(total_time / runs)) << " sec\n";
  } else {
    std::cout << "No traveling salesman route exists\n";
  }
}
