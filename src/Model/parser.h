#ifndef CPP4_3DVIEWER_V2_0_SRC_PARSER_H_
#define CPP4_3DVIEWER_V2_0_SRC_PARSER_H_

#include <fstream>
#include <string>
#include <vector>

namespace s21 {

/**
 * @brief this class is needed for getting lines and points from file
 *
 */
class Parser {
 public:
  /**
   * @brief Constructor and destructor of Parser
   */
  Parser() = default;
  ~Parser() = default;

  /**
   * @brief Get lines and points from file
   *
   * @param filename - path to a obj file
   */
  void get_data(std::string filename);

  /**
   * @brief line vector getter
   *
   * @return std::vector<int> - returns vector of lines
   */
  std::vector<int> get_connections();
  /**
   * @brief point vector getter
   *
   * @return std::vector<double> - returns vector of points
   */
  std::vector<double> get_points();

  /**
   * @brief line vector setter
   *
   * @param other line vector to be installed
   */
  void set_connections(const std::vector<int> &other);
  /**
   * @brief point vector setter
   *
   * @param other point vector to be installed
   */
  void set_points(const std::vector<double> &other);

 private:
  /**
   * @brief parses the string, converts it to double and inserts it into a
   * vector of points
   *
   * @param it iterator to current position of string with points
   * @param buffer_line string with points from file
   */
  void insert_points(std::string::iterator &it, std::string &buffer_line);
  /**
   * @brief parses the string, converts it to int and inserts it into a vector
   * of lines
   *
   * @param it iterator to current position of string with lines
   * @param values values to be inserted into vector of lines
   * @param buffer_line string with lines from file
   */
  void insert_connections(std::string::iterator &it, std::vector<int> &values,
                          std::string &buffer_line);
  /**
   * @brief inserts a vector of the form 1, 2, 3 as 1 2 2 3 3 1 into a line
   * vector
   *
   * @param values values to be inserted into vector of lines
   */
  void values_for_result(std::vector<int> &values);
  /**
   * @brief finds a min and max for axis
   *
   * @param axis the axis for which we are looking for minimum and maximum
   */
  void max_min_check(int axis);
  /**
   * @brief method that normalize the vector of points
   *
   * @param size_value scale for normalization
   */
  void normalization(double size_value);
  /**
   * @brief change the vector of points to fit image into screen
   *
   */
  void centering();
  /**
   * @brief finds the maximum difference in coordinates between the minimum and
   * maximum among all axes
   *
   * @return double
   */
  double find_max_length();

  std::vector<int> connections_{};
  std::vector<double> points_{};
  std::vector<double> min{};
  std::vector<double> max{};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_PARSER_H_
