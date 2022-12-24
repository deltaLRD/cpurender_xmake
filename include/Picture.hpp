#pragma once
#include <array>
#include <string>
#include <vector>
#include <fstream>
#include "fmt/core.h"

namespace LRD {

class Picture {

public:
  Picture() = delete;

  /**
   * @brief Construct a new Picture object
   * @brief the picture [0][0] position is on the top left, the [height][width]
   * is on the right bottom
   * @param width the width of the picture
   * @param height the height of the picture
   * @param path the path of the file to storage the picture
   */
  Picture(unsigned int width, unsigned int height, std::string path)
      : width(width), height(height), path(path) {
    data.assign(height, std::vector<std::array<int, 3>>(width, {0, 0, 0}));
  }

  /**
   * @brief write the picture add to a .ppm format picture
   *
   */
  void writeToFile() {
    std::ofstream fs(path, std::ios::out);
    fs << "P3\n";
    fs << "# " << path << "\n";
    fs << fmt::format("{} {}\n", width, height);
    fs << 255 << "\n";
    unsigned int cnt = 0;
    for (auto vec : data) {
      for (auto col : vec) {
        cnt++;
        fs << fmt::format("{:>4}{:>4}{:>4}{}", col[0], col[1], col[2],
                          (cnt % 4 == 0 ? '\n' : ' '));
      }
    }
    fs.close();
  }

  /**
   * @brief return Color at the pixel at [i][j]
   *
   * @param i
   * @param j
   * @return Color&
   */
  std::array<int, 3> &at(unsigned int i, unsigned int j){
    return data[i][j];
  }

private:
  std::vector<std::vector<std::array<int, 3>>> data;
  unsigned int width;
  unsigned int height;
  std::string path;
};

} // namespace LRD