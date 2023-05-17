#ifndef __REFINE_H
#define __REFINE_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>
#include "geometry_class.hpp"

using namespace std;
using namespace GeometryLibrary;


namespace RefineLibrary
{
  void Refine(vector<Triangle>& trianglesList,
              const double& percentage,
              vector<Vertex>& verticesList,
              unsigned int& lastVertex,
              vector<Edge>& edgesList);

  void Bisect(vector<Triangle>& trianglesList,
              Triangle& triangle,
              vector<Vertex>& verticesList,
              unsigned int& lastVertex,
              unsigned int& lastEdge);
}

#endif // __REFINE_H
