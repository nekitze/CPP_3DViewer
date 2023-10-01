#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_H_

#include <cmath>
#include <string>
#include <vector>

#include "affine.h"
#include "parser.h"

namespace s21 {

/**
 * @brief Interface for observer
 */
class IObserver {
 public:
  virtual void update_gl() = 0;
};

/**
 * @brief Interface for observable
 */
class IObservable {
 public:
  virtual void addObserver(IObserver* o) = 0;

  virtual void notify() = 0;
};

class Model : public IObservable {
 public:
  /**
   * @brief Destructor and constructor
   *
   */
  ~Model() = default;
  Model(const Model&) = delete;
  void operator=(const Model&) = delete;

  /**
   * @brief calles parser to set points and lines from file
   *
   * @param file_name
   */
  void set_model(std::string file_name);
  /**
   * @brief returns pointer to the only one model object
   *
   * @return Model* model
   */
  static Model* get_model();

  /**
   * @brief rotates the model by an angle around an axis
   *
   * @param axis
   * @param angle
   */
  void affine_rotate(int axis, double angle);
  /**
   * @brief scale model
   *
   * @param size
   */
  void affine_scale(double size);
  /**
   * @brief shifts the model by an shift around an axis
   *
   * @param axis
   * @param shift
   */
  void affine_shift(int axis, double shift);

  /**
   * @brief lines getter
   *
   * @return std::vector<int>
   */
  std::vector<int> get_connections();
  /**
   * @brief points getters
   *
   * @return std::vector<double>
   */
  std::vector<double> get_points();

  /**
   * @brief lines setter
   *
   * @param other
   */
  void set_connections(const std::vector<int>& other);
  /**
   * @brief points setter
   *
   * @param other
   */
  void set_points(const std::vector<double>& other);

  /**
   * @brief returns relative shift angle
   *
   * @param axis
   * @param value
   * @return double
   */
  double GetPositionValue(int axis, double value);
  /**
   * @brief returns relative rotation angle
   *
   * @param axis
   * @param value
   * @return double
   */
  double GetRotationValue(int axis, double value);
  /**
   * @brief returns relative scale
   *
   * @param value
   * @return double
   */
  double GetScaleValue(double value);

  /**
   * @brief addObserver
   * @param subscriber
   */
  void addObserver(IObserver* o) override { observers.push_back(o); }

  /**
   * @brief notify observers
   */
  void notify() override {
    for (auto o : observers) o->update_gl();
  }

 private:
  Model() = default;

  static Model* pointer_;
  Parser pars_;

  double previous_rot[3]{};
  double previous_shift[3]{};
  double previous_scale{};

  std::vector<IObserver*> observers;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_H_
