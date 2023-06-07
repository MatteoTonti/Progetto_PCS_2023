#ifndef __REFINE_H
#define __REFINE_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>
#include "geometry_class.hpp"
#include "sorting.hpp"

using namespace std;
using namespace GeometryLibrary;
using namespace SortingLibrary;


namespace RefineLibrary
{
  void Refine(vector<Triangle>& sortedTriangles,
              vector<Triangle>& trianglesList,
              const double& percentage,
              vector<Vertex>& verticesList,
              vector<Edge>& edgesList);

  void Bisect(vector<Triangle>& trianglesList,
              Triangle& triangle,
              vector<Vertex>& verticesList,
              vector<Edge>& edgesList,
              unsigned int& counter,
              vector<Vertex>& newVertices,
              vector<unsigned int>& newEdges);
}

#endif // __REFINE_H
