#ifndef CPP4_3DVIEWER_V2_0_SRC_AFFINE_H_
#define CPP4_3DVIEWER_V2_0_SRC_AFFINE_H_

#include <cmath>
#include <vector>

namespace s21 {

/**
 * @brief interface for affins transformation
 *
 */
class Affine {
 public:
  virtual void execute(std::vector<double> &points, int axis, double value) = 0;
  virtual ~Affine() {}
};

/**
 * @brief class for rotation
 *
 */
class AffineRotation : public Affine {
 public:
  void execute(std::vector<double> &points, int axis, double value) override;
};

/**
 * @brief class for scale
 *
 */
class AffineScale : public Affine {
 public:
  void execute(std::vector<double> &points, int axis, double value) override;
};

/**
 * @brief class for moving of model
 *
 */
class AffineShift : public Affine {
 public:
  void execute(std::vector<double> &points, int axis, double value) override;
};

/**
 * @brief class that is used for implementing strategy patters, stores the
 * pointer to the affine class inheritor
 *
 */
class Context {
 public:
  Context(Affine *other);
  void execute(std::vector<double> &points, int axis, double value);

 private:
  Affine *affine;
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_AFFINE_H_
