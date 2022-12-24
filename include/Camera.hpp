#pragma once
#include "Eigen/Dense"

namespace LRD {

struct Camera{
  Eigen::Vector3f pos;
  Eigen::Vector3f dir;
  Eigen::Vector3f up;
};

}