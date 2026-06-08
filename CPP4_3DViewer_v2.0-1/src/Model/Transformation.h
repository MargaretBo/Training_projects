
#ifndef VIEWER_TRANSFORMATION_H
#define VIEWER_TRANSFORMATION_H

#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {

enum TransformationType {
  kAXISX = 0,
  kAXISY = 1,
  kAXISZ = 2,
  kSHIFTX = 3,
  kSHIFTY = 4,
  kSHIFTZ = 5,
  kSCALING = 6
};
/**
 * @brief This is the strategy for the transformation of the figure.
 *
 */
class TransformationStrategy {
 public:
  virtual void Transform(std::vector<double>& vertices, double number,
                         int numberOfVertices) = 0;
};
/**
 * @brief This class is for rotating the figure about X axis.
 *
 */
class RotationX : public TransformationStrategy {
 public:
  RotationX() {}
  void Transform(std::vector<double>& vertices, double angle,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for rotating the figure about Y axis.
 *
 */
class RotationY : public TransformationStrategy {
 public:
  RotationY() {}
  void Transform(std::vector<double>& vertices, double angle,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for rotating the figure about Z axis.
 *
 */
class RotationZ : public TransformationStrategy {
 public:
  RotationZ() {}
  void Transform(std::vector<double>& vertices, double angle,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for shifting the figure along X axis.
 *
 */
class ShiftX : public TransformationStrategy {
 public:
  ShiftX() {}
  void Transform(std::vector<double>& vertices, double shiftX,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for shifting the figure along Y axis.
 *
 */
class ShiftY : public TransformationStrategy {
 public:
  ShiftY() {}
  void Transform(std::vector<double>& vertices, double shiftY,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for shifting the figure along Z axis.
 *
 */
class ShiftZ : public TransformationStrategy {
 public:
  ShiftZ() {}
  void Transform(std::vector<double>& vertices, double shiftZ,
                 int numberOfVertices) override;
};
/**
 * @brief This class is for scaling the figure.
 *
 */
class Scaling : public TransformationStrategy {
 public:
  Scaling() {}
  void Transform(std::vector<double>& vertices, double scaling,
                 int numberOfVertices) override;
};
/**
 * @brief This class is the context of the strategy. It is responsible for
 * choosing the strategy for the current action.
 *
 */
class TransformationContext {
 public:
  TransformationContext() {}
  /**
   * @brief Sets the context of the strategy.
   *
   * @param type
   */
  void setContext(int type) {
    if (type == kAXISX) {
      strategy_ = new RotationX;
    } else if (type == kAXISY) {
      strategy_ = new RotationY;
    } else if (type == kAXISZ) {
      strategy_ = new RotationZ;
    } else if (type == kSHIFTX) {
      strategy_ = new ShiftX;
    } else if (type == kSHIFTY) {
      strategy_ = new ShiftY;
    } else if (type == kSHIFTZ) {
      strategy_ = new ShiftZ;
    } else if (type == kSCALING) {
      strategy_ = new Scaling;
    }
  }
  /**
   * @brief Executes the strategy.
   *
   * @param vertices
   * @param number
   * @param numberOfVertices
   */
  void executeStrategy(std::vector<double>& vertices, double number,
                       int numberOfVertices) {
    strategy_->Transform(vertices, number, numberOfVertices);
  }

 private:
  TransformationStrategy* strategy_;
};
}  // namespace s21
#endif  // VIEWER_ROTATION_H