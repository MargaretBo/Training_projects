#include <gtest/gtest.h>

#include "../Controller/Controller.h"
#include "../Model/Model.h"

using namespace s21;

void VectorChecker(std::vector<double> v1, std::vector<double> v2, int size) {
  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(v1[i], v2[i], 0.0000001);
  }
}

void VectorChecker(std::vector<int> v1, std::vector<int> v2, int size) {
  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(v1[i], v2[i], 0.0000001);
  }
}

TEST(Model, Parcer) {
  int result = Model::GetModelInstance().Parcer("Tests/box.obj");
  EXPECT_EQ(result, 0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {
      0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5,
      0.5, 0.5,  -0.5, 0.5, 0.5,  0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Parcer2) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {0.5, 0.5, 0.5, -0.5, -0.5, -0.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
  std::vector<int> faces1 = Model::GetModelInstance().GetFaces();
  std::vector<int> faces2 = {0, 1};
  int size2 = Model::GetModelInstance().GetNumberOfFaces() * 2;
  VectorChecker(faces1, faces2, size2);
}

TEST(Model, Parcer3) {
  int result = Model::GetModelInstance().Parcer("Tests/nonexistent_file.obj");
  EXPECT_EQ(result, 1);
}

TEST(Model, Rotation1) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(0, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {
      0.5,  -0.66272213168641203, 0.24657529513926965,
      -0.5, 0.66272213168641203,  -0.24657529513926965};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Rotation2) {
  int result =
      Model::GetModelInstance().Parcer("Tests/dumb_negative_shape.obj");
  EXPECT_EQ(result, 0);
  std::vector<int> faces1 = Model::GetModelInstance().GetFaces();
  std::vector<int> faces2 = {0, 1};
  int size2 = Model::GetModelInstance().GetNumberOfFaces();
  VectorChecker(faces1, faces2, size2);
  Model::GetModelInstance().TransformFigure(1, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {
      -0.66272213168641203, 0.5,  0.24657529513926965,
      0.66272213168641203,  -0.5, -0.24657529513926965};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Rotation3) {
  int result =
      Model::GetModelInstance().Parcer("Tests/dumb_negative_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(2, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {
      -0.66272213168641203, 0.24657529513926965,  0.5,
      0.66272213168641203,  -0.24657529513926965, -0.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Shift1) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(3, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {2.5, 0.5, 0.5, 1.5, -0.5, -0.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Shift2) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(4, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {0.5, 2.5, 0.5, -0.5, 1.5, -0.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Shift3) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(5, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {0.5, 0.5, 2.5, -0.5, -0.5, 1.5};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Model, Scale) {
  int result = Model::GetModelInstance().Parcer("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  Model::GetModelInstance().TransformFigure(6, 2.0);
  std::vector<double> vertices1 = Model::GetModelInstance().GetVertices();
  std::vector<double> vertices2 = {1.0, 1.0, 1.0, -1.0, -1.0, -1.0};
  int size = Model::GetModelInstance().GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
}

TEST(Controller, Parcer) {
  Controller controller;
  int result = controller.ParceFigure("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  std::vector<double> vertices1 = controller.GetVertices();
  std::vector<double> vertices2 = {0.5, 0.5, 0.5, -0.5, -0.5, -0.5};
  int size = controller.GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
  std::vector<int> faces1 = controller.GetFaces();
  std::vector<int> faces2 = {0, 1};
  int size2 = controller.GetNumberOfFaces();
  VectorChecker(faces1, faces2, size2);
}

TEST(Controller, Parcer1) {
  Controller controller;
  int result = controller.ParceFigure("Tests/nonexistent_file.obj");
  EXPECT_EQ(result, 1);
}
TEST(Controller, UpdateFigure) {
  Controller controller;
  int result = controller.ParceFigure("Tests/dumb_shape.obj");
  EXPECT_EQ(result, 0);
  std::vector<double> vertices1 = controller.GetVertices();
  std::vector<double> vertices2 = {0.5, 0.5, 0.5, -0.5, -0.5, -0.5};
  int size = controller.GetNumberOfVertices();
  VectorChecker(vertices1, vertices2, size);
  controller.UpdateFigure(6, 2.0);
  std::vector<double> vertices3 = controller.GetVertices();
  std::vector<double> vertices4 = {1.0, 1.0, 1.0, -1.0, -1.0, -1.0};
  int size2 = controller.GetNumberOfVertices();
  VectorChecker(vertices3, vertices4, size2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
