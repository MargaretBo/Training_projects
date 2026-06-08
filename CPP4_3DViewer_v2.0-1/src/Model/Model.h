#ifndef VIEWER_MODEL_H
#define VIEWER_MODEL_H

#include <fstream>
#include <iostream>
#include <vector>

#include "Transformation.h"

namespace s21 {

enum ModelStatus { kSUCCESS = 0, kERROR = 1, kMAXSIZE = 1000000 };
/**
 * @brief This is the model class for the Viewer.
 *
 */
class Model {
 public:
  static Model &GetModelInstance() { return modelInstance; }
  Model(const Model &) = delete;
  int Parcer(std::string path);

  std::vector<double> GetVertices() { return vertices_; }
  std::vector<int> GetFaces() { return faces_; }
  int GetNumberOfVertices() { return numberOfVertices_; }
  int GetNumberOfFaces() { return numberOfFaces_; }
  int TransformFigure(int type, double number);

 private:
  Model() {
    vertices_.reserve(kMAXSIZE);
    faces_.reserve(kMAXSIZE);
  }
  int NegativeVertex(int vertex, int numberOfVertices);
  int FaceParcer(std::string line);
  int VertexParcer(std::string line);
  bool IsNumber(char character);
  void Normalize();
  static Model modelInstance;
  std::vector<double> vertices_;
  std::vector<int> faces_;
  int numberOfVertices_ = 0;
  int numberOfFaces_ = 0;
  double maxValue_ = 0;
  double minValue_ = 0;
  // TransformationContext *strategy;
};

// Model Model::modelInstance;

}  // namespace s21
#endif