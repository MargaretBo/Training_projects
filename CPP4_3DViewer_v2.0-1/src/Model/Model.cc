#include "Model.h"

using namespace s21;

Model Model::modelInstance;
/**
 * @brief Parces the obj file
 *
 * @param path string containing the path to the obj file
 * @return int
 */
int Model::Parcer(std::string path) {
  vertices_.clear();
  faces_.clear();
  numberOfVertices_ = 0;
  numberOfFaces_ = 0;
  int result = 0;
  std::ifstream file(path);
  if (!file.is_open()) {
    return 1;
  }
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    if (line[0] == 'v' && line[1] == ' ') {
      result = VertexParcer(line);
    } else if (line[0] == 'f' && line[1] == ' ') {
      FaceParcer(line);
    }
  }
  Normalize();
  return result;
}

void Model::Normalize() {
  // double maxValue = *std::max_element(vertices_.begin(), vertices_.end());
  // double minValue = *std::min_element(vertices_.begin(), vertices_.end());
  for (int i = 0; i < numberOfVertices_; i++) {
    vertices_[i] /= (maxValue_ - minValue_);
  }
}
/**
 * @brief Determines if a character is a number (including negative numbers)
 *
 * @param character character to be checked
 * @return true if the character is a number
 * @return false if the character is not a number
 */
bool Model::IsNumber(char character) {
  if ((character >= '0' && character <= '9') || character == '-') {
    return true;
  } else {
    return false;
  }
}

/**
 * Returns the a possitive number for a vertex. -1 vertex corresponds to the
 * last vertex in the vector, -2 is the second last and so on.
 * @param vertex
 * @param numberOfVertices
 * @return int
 */
int Model::NegativeVertex(int vertex, int numberOfVertices) {
  return vertex + numberOfVertices / 3 + 1;
}
/**
 * @brief Parces the faces of the obj file
 *
 * @param line string containing the face
 * @return int
 */
int Model::FaceParcer(std::string line) {
  int numberofVerteces = 0;
  int startSize = faces_.size();
  for (size_t i = 0; i < line.length(); i++) {
    if (IsNumber(line[i])) {
      numberofVerteces++;
      int vertex = std::stoi(line.substr(i)) - 1;
      if (vertex < 0) {
        vertex = NegativeVertex(vertex, numberOfVertices_);
      }
      if (numberofVerteces < 3) {
        faces_.push_back(vertex);
      } else {
        faces_.push_back(faces_[faces_.size() - 1]);
        faces_.push_back(vertex);
      }
      numberOfFaces_++;
      size_t nextSpacePosition = line.substr(i).find_first_of(' ');
      if (nextSpacePosition != std::string::npos) {
        i += nextSpacePosition;
      } else {
        break;
      }
    }
  }
  if (numberofVerteces != 2) {
    faces_.push_back(faces_[faces_.size() - 1]);
    faces_.push_back(faces_[startSize]);
  } else {
    numberOfFaces_--;
  }

  return 0;
}
/**
 * @brief Parces the vertices of the obj file
 *
 * @param line string containing the vertex
 * @return int 0 if successful
 */
int Model::VertexParcer(std::string line) {
  int numberOfCoordinates = 0;
  for (size_t i = 0; i < line.length(); i++) {
    if (IsNumber(line[i])) {
      double vertex = std::stod(line.substr(i));
      if (numberOfVertices_ == 1) {
        maxValue_ = vertex;
        minValue_ = vertex;
      }
      if (maxValue_ < vertex) {
        maxValue_ = vertex;
      }
      if (minValue_ > vertex) {
        minValue_ = vertex;
      }
      vertices_.push_back(vertex);
      numberOfVertices_++;
      numberOfCoordinates++;
      size_t nextSpacePosition = line.substr(i).find_first_of(' ');
      if (nextSpacePosition != std::string::npos) {
        i += nextSpacePosition;
      } else {
        break;
      }
    }
  }
  if (numberOfCoordinates != 3) {
    return kERROR;
  } else {
    return kSUCCESS;
  }
}
/**
 * @brief This function connects model to the strategy to transform the figure
 *
 * @param type Determines the type of the transformation e.g. rotation
 * @param number The value by which the figure will be transformed
 * @return int
 */
int Model::TransformFigure(int type, double number) {
  TransformationContext* strategy = new TransformationContext;
  strategy->setContext(type);
  strategy->executeStrategy(vertices_, number, numberOfVertices_);
  return 0;
}