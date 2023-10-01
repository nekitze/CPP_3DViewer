#include "parser.h"

namespace s21 {

std::vector<int> Parser::get_connections() { return connections_; }

std::vector<double> Parser::get_points() { return points_; }

void Parser::set_connections(const std::vector<int> &other) {
  connections_ = other;
}

void Parser::set_points(const std::vector<double> &other) { points_ = other; }

void Parser::get_data(std::string filename) {
  std::ifstream fin(filename);
  if (fin.is_open()) {
    points_.clear();
    connections_.clear();
    std::string buffer_line;
    while (std::getline(fin, buffer_line)) {
      auto it = buffer_line.begin();
      if (buffer_line.size() > 2 && *it == 'v' && *(it + 1) == ' ') {
        for (int i = 0; i < 3; i++) {
          insert_points(it, buffer_line);
          max_min_check(i);
        }
      }
      if (buffer_line.size() > 2 && *it == 'f' && *(it + 1) == ' ') {
        it += 2;
        std::vector<int> values;
        while (*it != '\n' && *it != '\0' && *it != '\r' &&
               it != buffer_line.end()) {
          insert_connections(it, values, buffer_line);
        }
        values_for_result(values);
      }
    }
    fin.close();
  }
  normalization(0.9);
  centering();
}

void Parser::normalization(double size_value) {
  double scale = size_value * (size_value) / find_max_length();
  for (auto it = points_.begin(); it != points_.end(); ++it) {
    *it *= scale;
  }
  for (int i = 0; i < 3; i++) {
    max[i] *= scale;
    min[i] *= scale;
  }
}

double Parser::find_max_length() {
  double result = -1E28;
  for (int i = 0; i < 3; i++) {
    if (max[i] - min[i] > result) result = max[i] - min[i];
  }
  return result;
}

void Parser::centering() {
  std::vector<double> center(3);
  for (int i = 0; i < 3; i++) center[i] = min[i] + (max[i] - min[i]) / 2;
  for (int i = 0; i < (int)points_.size(); i += 3) {
    for (int j = 0; j < 3; j++) points_[i + j] -= center[j];
  }
}

void Parser::max_min_check(int axis) {
  if (max.empty()) {
    max = {0, 0, 0};
    min = {0, 0, 0};
  }

  if (points_.size() < 4) {
    max[axis] = points_.back();
    min[axis] = points_.back();
  } else {
    max[axis] = (max[axis] < points_.back()) ? points_.back() : max[axis];
    min[axis] = (min[axis] > points_.back()) ? points_.back() : min[axis];
  }
}

void Parser::insert_points(std::string::iterator &it,
                           std::string &buffer_line) {
  it += 2;
  std::string buffer;
  while (*it == ' ') ++it;
  while (*it != ' ' && *it != '\r' && *it != '\n' && *it != '\0' &&
         it != buffer_line.end()) {
    if ((*it >= '0' && *it <= '9') || *it == '.' || *it == '-')
      buffer.push_back(*it);
    ++it;
  }
  if (buffer.size()) points_.push_back(std::stod(buffer));
  --it;
}

void Parser::insert_connections(std::string::iterator &it,
                                std::vector<int> &values,
                                std::string &buffer_line) {
  std::string buffer;
  while (*it == ' ') ++it;
  while (*it >= '0' && *it <= '9') {
    buffer.push_back(*it);
    ++it;
  }
  if (buffer.size()) values.push_back(std::stoi(buffer) - 1);
  if (*it == '/') {
    while (*it != ' ' && *it != '\r' && *it != '\n' && *it != '\0' &&
           it != buffer_line.end()) {
      ++it;
    }
  }
}

void Parser::values_for_result(std::vector<int> &values) {
  for (auto it = values.begin(); it != values.end(); ++it) {
    connections_.push_back(*it);
    if (it != values.begin()) connections_.push_back(*it);
  }
  connections_.push_back(values[0]);
}

}  // namespace s21
