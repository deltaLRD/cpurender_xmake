#pragma once

#include "Eigen/Dense"
// #include "Transform.h"
#include "Camera.hpp"
#include "Eigen/src/Core/GlobalFunctions.h"

namespace LRD {

/*
 *    _//  z
 *  _//
 * //
 * ||----------> y
 * ||
 * ||
 * ||
 * \/
 * x
 */

Eigen::Matrix4f generateRotMatrix(float ax, float ay, float az, float angle) {
//   // Use Rodriguez rotation formula
   float radian = (-angle / 360.0) * 2 * 3.1415926;
//   Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
//   Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
//   Eigen::Matrix3f M;
//   Eigen::Matrix3f Rk;
//   Rk << 0, -az, ay, az, 0, -ax, -ay, ax, 0;

//   M = I + (1 - cos(radian)) * Rk * Rk + sin(radian) * Rk;

//   model << M(0, 0), M(0, 1), M(0, 2), 0, M(1, 0), M(1, 1), M(1, 2), 0, M(2, 0),
//       M(2, 1), M(2, 2), 0, 0, 0, 0, 1;
//   return model;
    Eigen::Matrix4f model;
    model << (ax*ax*(1-cos(radian))+cos(radian)), (ax*ay*(1-cos(radian))+az*sin(radian)), (ax*az*(1-cos(radian))-ay*sin(radian)),0,
        (ax*ay*(1-cos(radian))-az*sin(radian)), (ay*ay*(1-cos(radian))+cos(radian)), (az*ay*(1-cos(radian))+ax*sin(radian)),0,
        (ax*az*(1-cos(radian))+ay*sin(radian)), (ay*az*(1-cos(radian))-ax*sin(radian)), (az*az*(1-cos(radian))+cos(radian)),0,
        0,0,0,1;
    return model;
}
Eigen::Matrix4f generateRotMatrix(const Eigen::Vector3f &axiso, float angle) {
  return LRD::generateRotMatrix(axiso.x(), axiso.y(), axiso.z(), angle);
}

Eigen::Matrix4f generateScaleMatrix(float x, float y, float z) {
  Eigen::Matrix4f M;
  M << x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0;
  return M;
}
Eigen::Matrix4f generateScaleMatrix(const Eigen::Vector3f &scale) {
  return LRD::generateScaleMatrix(scale.x(), scale.y(), scale.y());
}

Eigen::Matrix4f generateMoveMatrix(float dx, float dy, float dz) {
  Eigen::Matrix4f M;
  M << 1.0, 0.0, 0.0, dx, 0.0, 1.0, 0.0, dy, 0.0, 0.0, 1.0, dz, 0.0, 0.0, 0.0,
      1.0;
  return M;
}
Eigen::Matrix4f generateMoveMatrix(const Eigen::Vector3f &d) {
  return LRD::generateMoveMatrix(d.x(), d.y(), d.z());
}

// Eigen::Matrix4f generateModelMatrix(LRD::Transform trans);

Eigen::Matrix4f generateViewMatrix(LRD::Camera &camera) {
  // https://zhuanlan.zhihu.com/p/373489211
  Eigen::Matrix4f m;
  Eigen::Vector3f Up{0, 1, 0};
  Eigen::Vector3f R = Up.cross(camera.dir);
  Eigen::Vector3f U = camera.dir.cross(R);
  m << R[0], R[1], R[2], -camera.pos[0], U[0], U[1], U[2], -camera.pos[1],
      camera.dir[0], camera.dir[1], camera.dir[2], -camera.pos[2], 0, 0, 0, 1;
  return m;
}

Eigen::Matrix4f generateProjMatrix(LRD::Camera &camera, float znear, float zfar,
                                   float width, float height) {
  Eigen::Matrix4f m;
  m << 2.0 * znear / height, 0, 0, 0, 0, 2.0 * znear / width, 0, 0, 0, 0,
      -2.0f / (zfar - znear), -(zfar + znear) / (zfar - znear), 0, 0, 0, 1;
  return m;
}
} // namespace LRD
