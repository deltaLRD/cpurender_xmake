#include "Picture.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include "Eigen/Dense"
#include "fmt/core.h"

TEST(EigenTest, MatrixMultiply) {
  Eigen::Vector3f pos = {2.0, 3.0, 5.0};
  Eigen::Vector4f alignPos;
  alignPos << pos, 1.0;
  Eigen::Matrix4f m;
  m << 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 1.0;
  auto newpos = m * alignPos;
  EXPECT_EQ(newpos.x() , 3.0);
  EXPECT_EQ(newpos.y() , 2.0);
  EXPECT_EQ(newpos.z() , 5.0);
  EXPECT_EQ(newpos.w() , 1.0);
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

int main(int argc, char **argv) {
  fmt::print("Running main() from {}\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}