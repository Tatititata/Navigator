#include "graph_algos.h"

std::vector<size_t> GraphAlgorithms::DepthFirstSearch(const Graph& g,
                                                      size_t vertex) {
  size_t size = g.size();
  if (vertex == 0 || vertex > size) {
    throw std::out_of_range("Start vertex is out of range");
  }
  --vertex;
  Stack s;
  std::vector<char> visited(size, 0);
  std::vector<size_t> result;
  s.push(vertex);
  while (!s.empty()) {
    size_t curr = s.pop();
    if (!visited[curr]) {
      visited[curr] = 1;
      result.push_back(curr + 1);
      for (size_t i = 0; i < size; ++i) {
        if (!visited[i] && g.get_edge(curr, i)) {
          s.push(i);
        }
      }
    }
  }
  return result;
}

std::vector<size_t> GraphAlgorithms::BreadthFirstSearch(const Graph& g,
                                                        size_t vertex) {
  size_t size = g.size();
  if (vertex < 1 || vertex > size) {
    throw std::out_of_range("Start vertex is out of range");
  }
  --vertex;
  Queue q;
  std::vector<char> visited(size, 0);
  std::vector<size_t> result;
  q.push(vertex);
  while (!q.empty()) {
    size_t curr = q.pop();
    if (!visited[curr]) {
      visited[curr] = 1;
      result.push_back(curr + 1);
      for (size_t i = 0; i < size; ++i) {
        if (!visited[i] && g.get_edge(curr, i)) {
          q.push(i);
        }
      }
    }
  }
  return result;
}

size_t GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& g,
                                                       size_t v1, size_t v2) {
  size_t size = g.size();
  if (v1 < 1 || v1 > size || v2 < 1 || v2 > size) {
    throw std::out_of_range("Vertex is out of range");
  }
  --v1;
  --v2;
  std::vector<char> visited(size, 0);
  std::vector<size_t> distance(size, std::numeric_limits<size_t>::max());
  MinHeap q;
  distance[v1] = 0;

  q.push({0, v1, 0});  // {distance, vertex, dummy - not used here}
  while (!q.empty()) {
    auto [dist, vertex, dummy] = q.pop();
    if (vertex == v2) {
      return distance[v2];
    }
    if (!visited[vertex]) {
      visited[vertex] = 1;
      size_t actual_distance = distance[vertex];
      for (size_t i = 0; i < size; ++i) {
        if (!visited[i]) {
          size_t d = g.get_edge(vertex, i);
          if (d) {
            d += actual_distance;
            if (d < distance[i]) {
              q.push({d, i, 0});
              distance[i] = d;
            }
          }
        }
      }
    }
  }
  return distance[v2];
}

std::vector<std::vector<size_t>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph& g) {
  size_t size = g.size();
  std::vector<std::vector<size_t>> matrix(size, std::vector<size_t>(size, INF));
  for (size_t i = 0; i < size; ++i) {
    matrix[i][i] = 0;
    for (size_t j = i + 1; j < size; ++j) {
      size_t edge = g.get_edge(i, j);
      if (edge != 0) {
        matrix[i][j] = matrix[j][i] = edge;
      }
    }
  }
  for (size_t k = 0; k < size; ++k) {
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        size_t a = matrix[i][k];
        size_t b = matrix[k][j];
        if (a != INF && b != INF) {
          size_t res = a + b;
          if (res > a && res > b) {
            matrix[i][j] = res < matrix[i][j] ? res : matrix[i][j];
          }
        }
      }
    }
  }
  return matrix;
}

std::vector<std::vector<size_t>> GraphAlgorithms::GetLeastSpanningTree(
    const Graph& g) {
  size_t size = g.size();
  std::vector<std::vector<size_t>> matrix(size, std::vector<size_t>(size, 0));
  std::vector<char> visited(size, 0);
  MinHeap q;
  q.push({0, 0, 0});  // distance, vertex, parent
  while (!q.empty()) {
    auto [dist, vert, parent] = q.pop();
    if (!visited[vert]) {
      visited[vert] = 1;
      matrix[vert][parent] = matrix[parent][vert] = dist;
      for (size_t i = 0; i < size; ++i) {
        if (!(i == vert || i == parent)) {
          size_t edge = g.get_edge(i, vert);
          if (edge) q.push({edge, i, vert});
        }
      }
    }
  }
  if (std::any_of(visited.begin(), visited.end(),
                  [](char v) { return v == 0; })) {
    return {};
  }
  return matrix;
}

TsmResult GraphAlgorithms::SimulatedAnnealing(const Graph& g, bool with_nb) {
  Annealing ann(g, with_nb);
  return ann.solve_salesman_problem(with_nb);
}

GraphAlgorithms::Annealing::Annealing(const Graph& g, bool with_nb)
    : g_(g), size_(g.size()), path_(size_) {
  if (!with_nb) {
    for (size_t i = 0; i < size_; ++i) {
      path_[i] = i;
    }
    std::shuffle(path_.begin(), path_.end(), GraphAlgorithms::generator_());
  }
}

TsmResult GraphAlgorithms::Annealing::solve_salesman_problem(bool with_nb) {
  double temp = TEMPERATURE;
  TsmResult res;
  if (with_nb) {
    res = GraphAlgorithms::ClosestNeibourgh(g_);
    if (res.distance == INF) return res;
    for (size_t i = 0; i < size_; ++i) path_[i] = res.vertices[i] -= 1;
  } else {
    res.vertices = path_;
    res.distance = get_distance_();
  }
  auto old_path = path_;
  auto distance = res.distance;
  auto old_distance = distance;

  for (size_t e = 0; e < EPISODES && size_ != 1; ++e) {
    path_ = old_path;
    change_path_();
    distance = get_distance_();
    if (distance < res.distance) {
      res.vertices = path_;
      res.distance = distance;
      old_path = path_;
      old_distance = distance;
    } else {
      if (distance < old_distance) {
        old_path = path_;
        old_distance = distance;
      }
      if (distance > old_distance) {
        double delta = distance - old_distance;
        double probability = std::exp(-delta / temp);
        if (GraphAlgorithms::real_random_0_1() < probability) {
          old_path = path_;
          old_distance = distance;
        }
      }
    }
    temp *= ALPHA;
  }
  for (size_t i = 0; i < size_; ++i) res.vertices[i] += 1;
  return res;
}

size_t GraphAlgorithms::Annealing::get_distance_() const {
  size_t distance = 0;
  for (size_t i = 1; i < size_; ++i) {
    size_t edge = g_.get_edge(path_[i - 1], path_[i]);
    if (!edge) {
      edge = INF;
    }
    distance = GraphAlgorithms::safe_add_edge(distance, edge);
  }
  size_t edge = g_.get_edge(path_[0], path_[size_ - 1]);
  if (!edge) {
    edge = INF;
  }
  distance = GraphAlgorithms::safe_add_edge(distance, edge);
  return distance;
}

void GraphAlgorithms::Annealing::change_path_() {
  size_t left = random_vertex_(size_ - 1);
  size_t right = random_vertex_(size_ - 1);
  while (left == right) right = random_vertex_(size_ - 1);
  if (GraphAlgorithms::int_random_0_1()) {
    std::swap(path_[left], path_[right]);
  } else {
    if (right < left) {
      std::swap(left, right);
    }
    while (left < right) {
      std::swap(path_[left], path_[right]);
      left++;
      right--;
    }
  }
}

TsmResult GraphAlgorithms::ClosestNeibourgh(const Graph& g) {
  Neibourgh nb(g);
  return nb.solve_salesman_problem();
}

GraphAlgorithms::Neibourgh::Neibourgh(const Graph& g)
    : g_(g), size_(g.size()), path_(size_), visited_(size_) {}

TsmResult GraphAlgorithms::Neibourgh::solve_salesman_problem() {
  TsmResult res{path_, INF};
  for (size_t v = 0; v < size_; ++v) {
    memset(visited_.data(), 0, size_ * sizeof(char));
    memset(path_.data(), 0, size_ * sizeof(size_t));
    size_t curr = v;
    size_t count = 0;
    size_t distance = 0;
    while (count < size_ - 1) {
      path_[count] = curr;
      visited_[curr] = 1;
      auto [vertex, edge] = get_next_(curr);
      distance = safe_add_edge(distance, edge);
      curr = vertex;
      ++count;
    }
    path_[count] = curr;
    size_t edge = g_.get_edge(path_[0], path_[size_ - 1]);
    if (!edge) edge = INF;
    distance = safe_add_edge(distance, edge);

    if (distance < res.distance) {
      res.distance = distance;

      for (size_t i = 0; i < size_; ++i) {
        res.vertices[i] = path_[i] + 1;
      }
    }
  }
  return res;
}

std::pair<size_t, size_t> GraphAlgorithms::Neibourgh::get_next_(
    size_t curr) const {
  size_t distance = INF;
  size_t next = INF;

  for (size_t i = 0; i < size_; ++i) {
    if (i != curr && !visited_[i]) {
      size_t edge = g_.get_edge(curr, i);
      if (!edge) {
        edge = INF;
      }
      if (distance >= edge) {
        distance = edge;
        next = i;
      }
    }
  }
  return {next, distance};
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph& g,
                                                         bool with_nb) {
  Ant ant(g);
  return ant.solve_salesman_problem(with_nb);
}

GraphAlgorithms::Ant::Ant(const Graph& g)
    : g_(g),
      size_(g.size()),
      path_(size_, 0),
      visited_(size_, 0),
      probabilities_(size_, 0.0),
      full_graph_(size_ * size_, INF),
      pheromones_(size_ * size_, START_FERROMONE),
      length_{},
      pher_for_episode_(size_ * size_, 0)

{
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = i + 1; j < size_; ++j) {
      size_t edge = g.get_edge(i, j);
      if (edge) {
        full_graph_[i * size_ + j] = full_graph_[j * size_ + i] = edge;
      }
    }
  }
}

TsmResult GraphAlgorithms::Ant::solve_salesman_problem(bool with_nb) {
  TsmResult res;
  if (with_nb) {
    res = GraphAlgorithms::ClosestNeibourgh(g_);
    if (res.distance == INF) {
      return res;
    }
    for (size_t i = 0; i < size_ - 1; ++i) {
      size_t a = res.vertices[i] - 1;
      size_t b = res.vertices[i + 1] - 1;
      pheromones_[a * size_ + b] += START_FERROMONE;
      pheromones_[b * size_ + a] += START_FERROMONE;
    }
  }

  for (size_t ep = 0; ep < EPISODES; ++ep) {
    std::memset(pher_for_episode_.data(), 0,
                pher_for_episode_.size() * sizeof(double));
    for (size_t vertex = 0; vertex < size_; ++vertex) {
      run(vertex);
      fill_pher_for_episode();
    }
    for (size_t i = 0; i < size_ * size_; ++i) {
      pheromones_[i] = RHO * pheromones_[i] + pher_for_episode_[i];
    }
  }
  fill_best_path();
  res.distance = get_best_length();
  res.vertices = get_best_path();
  return res;
}

void GraphAlgorithms::Ant::run(size_t v) {
  std::memset(visited_.data(), 0, size_ * sizeof(char));
  length_ = 0;
  size_t count = 0;
  while (count < size_ - 1) {
    visited_[v] = 1;
    path_[count] = v;
    std::memset(probabilities_.data(), 0, size_ * sizeof(double));
    double denominator = 0;
    for (size_t i = 0; i < size_; ++i) {
      if (!visited_[i]) {
        double p = pow(pheromones_[v * size_ + i], ALPHA) *
                   pow(1.0 / (double)full_graph_[v * size_ + i], BETA);
        probabilities_[i] = p;
        denominator += p;
      }
    }
    double random_value = real_random_0_1() * denominator;
    bool found = false;
    double probability = 0;
    for (size_t i = 0; i < size_ && !found; ++i) {
      if (!visited_[i]) {
        probability += probabilities_[i];
        if (random_value < probability) {
          v = i;
          found = true;
        }
      }
    }
    add_length(count, v);
    ++count;
  }
  path_[count] = v;
  add_length(0, path_[size_ - 1]);
}

void GraphAlgorithms::Ant::add_length(size_t count, size_t v) {
  size_t edge = full_graph_[path_[count] * size_ + v];
  length_ = safe_add_edge(length_, edge);
}

void GraphAlgorithms::Ant::fill_best_path() {
  std::memset(path_.data(), 0, size_ * sizeof(size_t));
  std::memset(visited_.data(), 0, size_ * sizeof(char));
  length_ = 0;
  size_t v = 0;
  size_t count = 0;
  while (count < size_) {
    visited_[v] = 1;
    path_[count] = v;
    double max = 0;
    size_t idx = 0;
    for (size_t i = 0; i < size_; ++i) {
      if (pheromones_[v * size_ + i] > max && !visited_[i]) {
        max = pheromones_[v * size_ + i];
        idx = i;
      }
    }
    add_length(count, idx);
    v = idx;
    ++count;
  }
  for (size_t i = 0; i < size_; ++i) ++path_[i];
}

void GraphAlgorithms::Ant::fill_pher_for_episode() {
  double fer = L / (double)length_;
  for (size_t i = 1; i < size_; ++i) {
    pher_for_episode_[path_[i - 1] * size_ + path_[i]] += fer;
    pher_for_episode_[path_[i] * size_ + path_[i - 1]] += fer;
  }
  pher_for_episode_[path_[0] * size_ + path_[size_ - 1]] += fer;
  pher_for_episode_[path_[size_ - 1] * size_ + path_[0]] += fer;
}

size_t GraphAlgorithms::safe_add_edge(size_t curr, size_t edge) {
  if (edge < INF && INF - curr >= edge) return curr + edge;
  return INF;
}

double GraphAlgorithms::real_random_0_1() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(generator_());
}

std::mt19937& GraphAlgorithms::generator_() {
  static std::mt19937 rng(std::random_device{}());
  return rng;
}

int GraphAlgorithms::int_random_0_1() {
  static std::uniform_int_distribution<int> dist(0, 1);
  return dist(generator_());
}

size_t GraphAlgorithms::Annealing::random_vertex_(size_t max) {
  std::uniform_int_distribution<size_t> dist(0, max);
  return dist(generator_());
}