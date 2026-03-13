#ifndef GRAPH_ALGOS_H_
#define GRAPH_ALGOS_H_
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

// номера вершин начинаются с 1.

#include "../containers/containers.h"
#include "../graph_lib/graph.h"

constexpr size_t INF = std::numeric_limits<size_t>::max();

struct TsmResult {
  std::vector<size_t>
      vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
  size_t distance;  // длина этого маршрута
};

class GraphAlgorithms {
 public:
  GraphAlgorithms() = delete;

  static std::vector<size_t> DepthFirstSearch(const Graph& g, size_t vertex);
  static std::vector<size_t> BreadthFirstSearch(const Graph& g, size_t vertex);
  static size_t GetShortestPathBetweenVertices(const Graph& g, size_t v1,
                                               size_t v2);
  static std::vector<std::vector<size_t>> GetShortestPathsBetweenAllVertices(
      const Graph& g);
  static std::vector<std::vector<size_t>> GetLeastSpanningTree(const Graph& g);
  static TsmResult SolveTravelingSalesmanProblem(const Graph& g,
                                                 bool with_nb = false);
  static TsmResult ClosestNeibourgh(const Graph& g);
  static TsmResult SimulatedAnnealing(const Graph& g, bool with_nb = false);

 private:
  static std::mt19937& generator_();
  static double real_random_0_1();
  static int int_random_0_1();

  class Ant {
   private:
    const Graph& g_;
    size_t size_;
    std::vector<size_t> path_;
    std::vector<char> visited_;
    std::vector<double> probabilities_;
    std::vector<size_t> full_graph_;
    std::vector<double> pheromones_;
    size_t length_;
    std::vector<double> pher_for_episode_;

    void run(size_t v);
    void add_length(size_t count, size_t v);
    void fill_best_path();
    void fill_pher_for_episode();
    size_t get_best_length() const { return length_; };
    std::vector<size_t> get_best_path() { return std::move(path_); };

    static constexpr size_t EPISODES = 1000;
    static constexpr double START_FERROMONE = 0.2;
    static constexpr double ALPHA = 2.0;
    static constexpr double BETA = 2.5;
    static constexpr double RHO = 1.0 - 0.6;
    static constexpr double L = 1.0;

   public:
    explicit Ant(const Graph& g);
    Ant() = delete;
    Ant(const Ant&) = delete;
    Ant& operator=(const Ant&) = delete;
    Ant(Ant&&) = default;
    Ant& operator=(Ant&&) = default;

    TsmResult solve_salesman_problem(bool with_nb = false);
  };

  class Annealing {
   private:
    const Graph& g_;
    size_t size_;
    std::vector<size_t> path_;
    static constexpr double ALPHA = 0.9999;
    static constexpr size_t EPISODES = 200000;
    static constexpr double TEMPERATURE = 10.0;

    size_t get_distance_() const;
    void change_path_();
    static size_t random_vertex_(size_t max);

   public:
    explicit Annealing(const Graph& g, bool with_nb = false);
    Annealing() = delete;
    Annealing(const Annealing&) = delete;
    Annealing& operator=(const Ant&) = delete;
    Annealing(Annealing&&) = default;
    Annealing& operator=(Annealing&&) = default;

    TsmResult solve_salesman_problem(bool with_nb = false);
  };

  class Neibourgh {
   private:
    const Graph& g_;
    size_t size_;
    std::vector<size_t> path_;
    std::vector<char> visited_;

    std::pair<size_t, size_t> get_next_(size_t curr) const;

   public:
    explicit Neibourgh(const Graph& g);
    Neibourgh() = delete;
    Neibourgh(const Neibourgh&) = delete;
    Neibourgh& operator=(const Ant&) = delete;
    Neibourgh(Neibourgh&&) = default;
    Neibourgh& operator=(Neibourgh&&) = default;

    TsmResult solve_salesman_problem();
  };

  static size_t safe_add_edge(size_t curr, size_t edge);
};

#endif
