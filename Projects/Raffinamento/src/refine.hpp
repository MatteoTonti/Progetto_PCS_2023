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
              vector<Edge>& edgesList);

  void Bisect(vector<Triangle>& trianglesList,
              Triangle& triangle,
              vector<Vertex>& verticesList,
              vector<Edge>& edgesList,
              unsigned int& lastVertex,
              unsigned int& lastEdge,
              unsigned int& lastTriangle,
              unsigned int& counter,
              vector<Vertex>& newVertices,
              vector<Edge>& newEdges);
}

#endif // __REFINE_H
