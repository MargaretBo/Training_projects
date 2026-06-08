#include "Transformation.h"

using namespace s21;
/**
 * @brief This function is for rotating the figure about X axis.
 *
 * @param vertices - vector of vertices
 * @param angle - rotation angle
 * @param numberOfVertices - number of vertices
 */
void RotationX::Transform(std::vector<double>& vertices, double angle,
                          int numberOfVertices) {
  double y = 0, z = 0;
  for (int i = 1; i < numberOfVertices; i += 3) {
    y = vertices[i] * cos(angle) - vertices[i + 1] * sin(angle);
    z = vertices[i] * sin(angle) + vertices[i + 1] * cos(angle);
    vertices[i] = y;
    vertices[i + 1] = z;
  }
}
/**
 * @brief This function is for rotating the figure about Y axis.
 *
 * @param vertices - vector of vertices
 * @param angle - rotation angle
 * @param numberOfVertices - number of vertices
 */
void RotationY::Transform(std::vector<double>& vertices, double angle,
                          int numberOfVertices) {
  double x = 0, z = 0;
  for (int i = 0; i < numberOfVertices; i += 3) {
    x = vertices[i] * cos(angle) - vertices[i + 2] * sin(angle);
    z = vertices[i] * sin(angle) + vertices[i + 2] * cos(angle);
    vertices[i] = x;
    vertices[i + 2] = z;
  }
}
/**
 * @brief This function is for rotating the figure about Z axis.
 *
 * @param vertices - vector of vertices
 * @param angle - rotation angle
 * @param numberOfVertices - number of vertices
 */
void RotationZ::Transform(std::vector<double>& vertices, double angle,
                          int numberOfVertices) {
  double x = 0, y = 0;
  for (int i = 0; i < numberOfVertices; i += 3) {
    x = vertices[i] * cos(angle) - vertices[i + 1] * sin(angle);
    y = vertices[i] * sin(angle) + vertices[i + 1] * cos(angle);
    vertices[i] = x;
    vertices[i + 1] = y;
  }
}
/**
 * @brief This function is for shifting the figure along X axis.
 *
 * @param vertices - vector of vertices
 * @param shiftX -  the value of the shift along X axis
 * @param numberOfVertices - number of vertices
 */
void ShiftX::Transform(std::vector<double>& vertices, double shiftX,
                       int numberOfVertices) {
  for (int i = 0; i < numberOfVertices; i += 3) {
    vertices[i] += shiftX;
  }
}
/**
 * @brief This function is for shifting the figure along Y axis.
 *
 * @param vertices - vector of vertices
 * @param shiftY - the value of the shift along Y axis
 * @param numberOfVertices -  number of vertices
 */
void ShiftY::Transform(std::vector<double>& vertices, double shiftY,
                       int numberOfVertices) {
  for (int i = 1; i < numberOfVertices; i += 3) {
    vertices[i] += shiftY;
  }
}
/**
 * @brief This function is for shifting the figure along Z axis.
 *
 * @param vertices - vector of vertices
 * @param shiftZ - the value of the shift along Z axis
 * @param numberOfVertices - number of vertices
 */
void ShiftZ::Transform(std::vector<double>& vertices, double shiftZ,
                       int numberOfVertices) {
  for (int i = 2; i < numberOfVertices; i += 3) {
    vertices[i] += shiftZ;
  }
}
/**
 * @brief This function is for scaling the figure.
 *
 * @param vertices - vector of vertices
 * @param scaling - the value of the scaling
 * @param numberOfVertices - number of vertices
 */
void Scaling::Transform(std::vector<double>& vertices, double scaling,
                        int numberOfVertices) {
  for (int i = 0; i < numberOfVertices; i++) {
    vertices[i] *= scaling;
  }
}