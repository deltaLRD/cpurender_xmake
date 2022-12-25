#include "Eigen/Dense"
#include "Eigen/src/Core/Matrix.h"
#include "MVP.hpp"
#include "Model.hpp"
#include "Picture.hpp"
#include "fmt/core.h"
#include "gtest/gtest.h"
#include <cstdio>
#include <string>

using ::testing::FloatLE;

TEST(EigenTest, MatrixMultiply) {
  Eigen::Vector3f pos = {2.0, 3.0, 5.0};
  Eigen::Vector4f alignPos;
  alignPos << pos, 1.0;
  Eigen::Matrix4f m;
  m << 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 1.0;
  auto newpos = m * alignPos;
  EXPECT_EQ(newpos.x(), 3.0);
  EXPECT_EQ(newpos.y(), 2.0);
  EXPECT_EQ(newpos.z(), 5.0);
  EXPECT_EQ(newpos.w(), 1.0);
}

TEST(PictureTest, WriteToFile) {
  LRD::Picture pic(1000, 1000, "./test.ppm");
  for (int i = 300; i < 600; i++) {
    for (int j = 300; j < 600; j++) {
      pic.at(i, j) = {255, 0, 0};
    }
  }
  pic.writeToFile();
}

TEST(ModelTest, objloader) {
  std::string inputpath = "../../../../models/cube/cube.obj";
  std::string basepath = inputpath.substr(0, inputpath.rfind("/"));
  EXPECT_EQ(basepath, "../../../../models/cube");
  LRD::Model model("../../../../models/cube/cube.obj");
  bool ret = model.load();
  // std::cout << model.get_warn() << "\n";
  // std::cout << model.get_err() << "\n";
  EXPECT_EQ(model.get_warn(), "");
  EXPECT_EQ(model.get_err(), "");
  EXPECT_EQ(ret, true);
}

TEST(MVPTest, MVPTest1) {
  Eigen::Vector3f pos(1.0, 4.0, 2.0);
  auto RotMatrix = LRD::generateRotMatrix(0.0, 0.0, 1.0, 90.0);
  Eigen::Vector4f alignPos;
  alignPos << pos, 1.0;
  Eigen::Vector4f newAlignPos = RotMatrix * alignPos;
  RotMatrix = LRD::generateRotMatrix(1.0, 0.0, 0.0, 90.0);
  Eigen::Vector4f newAlignPos2 = RotMatrix * alignPos;
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos[0], -4.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos[1], 1.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos[2], 2.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos[3], 1.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos2[0], 1.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos2[1], -2.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos2[2], 4.0f);
  EXPECT_PRED_FORMAT2(FloatLE, newAlignPos2[3], 1.0f);
}

int main(int argc, char **argv) {
  fmt::print("Running main() from {}\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}