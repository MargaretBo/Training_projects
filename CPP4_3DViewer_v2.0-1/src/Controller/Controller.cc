#include "Controller.h"

using namespace s21;
/**
 * @brief Sends the path to the obj file to the model for parcing
 *
 * @param path the path to the obj file
 * @return int
 */
int Controller::ParceFigure(std::string path) {
  int result = Model::GetModelInstance().Parcer(path);
  return result;
}
/**
 * @brief Updates the existing figure using diffent types of changes
 *
 * @param typeOfChange a number from 0 to 6 that determines the type of change
 * @param value coefficient by which the figure will be changed
 */
void Controller::UpdateFigure(int typeOfChange, double value) {
  Model::GetModelInstance().TransformFigure(typeOfChange, value);
}
/**
 * @brief Returns the vector of vertices to the view
 *
 * @return std::vector<double>
 */
std::vector<double> Controller::GetVertices() {
  return Model::GetModelInstance().GetVertices();
}
/**
 * @brief Returns the number of vertices in the figure
 *
 * @return int
 */
int Controller::GetNumberOfVertices() {
  return Model::GetModelInstance().GetNumberOfVertices();
}
/**
 * @brief Returns the number of lines in the figure
 *
 * @return int
 */
int Controller::GetNumberOfFaces() {
  return Model::GetModelInstance().GetNumberOfFaces();
}
/**
 * @brief Returns the vector of faces to the view
 *
 * @return std::vector<int>
 */
std::vector<int> Controller::GetFaces() {
  return Model::GetModelInstance().GetFaces();
}
