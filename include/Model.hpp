#pragma once

#include "Eigen/Dense"
#include "tiny_obj_loader.h"
#include <string>
#include <vector>

namespace LRD {

class Model {
public:
  Model() = delete;

  Model(std::string objfilepath) {
    this->inputfile = objfilepath;
    this->basedir = this->inputfile.substr(0, this->inputfile.rfind("/"));
  }

  bool load() {
    bool ret = tinyobj::LoadObj(&(this->attrib), &(this->shapes),
                                &(this->materials), &(this->warn), &(this->err),
                                this->inputfile.c_str(), this->basedir.c_str());
    return ret;
  }

  void applyMatrix(const Eigen::Matrix4f &m) {
    auto VSize = this->attrib.vertices.size();
    for (int i = 0; i < VSize; i += 3) {
      Eigen::Vector4f v{this->attrib.vertices[i], this->attrib.vertices[i + 1],
                        this->attrib.vertices[i + 2], 1.0f};
      Eigen::Vector4f nv = m * v;
      this->attrib.vertices[i] = nv[0] / nv[3];
      this->attrib.vertices[i + 1] = nv[1] / nv[3];
      this->attrib.vertices[i + 2] = nv[2] / nv[3];
    }
  }

  size_t getVerticesNum() { return this->attrib.vertices.size(); }

  const std::string get_err() { return this->err; }

  const std::string get_warn() { return this->warn; }

private:
  // attrib_t::vertices => 3 floats per vertex

  //        v[0]        v[1]        v[2]        v[3]               v[n-1]
  //   +-----------+-----------+-----------+-----------+      +-----------+
  //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
  //   +-----------+-----------+-----------+-----------+      +-----------+

  // attrib_t::normals => 3 floats per vertex

  //        n[0]        n[1]        n[2]        n[3]               n[n-1]
  //   +-----------+-----------+-----------+-----------+      +-----------+
  //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
  //   +-----------+-----------+-----------+-----------+      +-----------+

  // attrib_t::texcoords => 2 floats per vertex

  //        t[0]        t[1]        t[2]        t[3]               t[n-1]
  //   +-----------+-----------+-----------+-----------+      +-----------+
  //   |  u  |  v  |  u  |  v  |  u  |  v  |  u  |  v  | .... |  u  |  v  |
  //   +-----------+-----------+-----------+-----------+      +-----------+

  // attrib_t::colors => 3 floats per vertex(vertex color. optional)

  //        c[0]        c[1]        c[2]        c[3]               c[n-1]
  //   +-----------+-----------+-----------+-----------+      +-----------+
  //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
  //   +-----------+-----------+-----------+-----------+      +-----------+

  std::string inputfile;
  std::string basedir;
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;
};
} // namespace LRD
