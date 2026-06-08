#ifndef VIEWER_DRAFTS_CONTROLLER_H
#define VIEWER_DRAFTS_CONTROLLER_H

#include <vector>

#include "../Model/Model.h"

namespace s21 {
/**
 * @brief This is the controller class for the Viewer that connects the model
 * and the view
 *
 */
class Controller {
 public:
  Controller(){};
  virtual ~Controller() = default;
  int ParceFigure(std::string path);
  void UpdateFigure(int typeOfChange, double value);
  std::vector<double> GetVertices();
  std::vector<int> GetFaces();
  int GetNumberOfVertices();
  int GetNumberOfFaces();

 private:
  // Model *model;
};
}  // namespace s21

#endif