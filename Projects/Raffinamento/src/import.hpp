#ifndef __IMPORT_H
#define __IMPORT_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>
#include "geometry_class.hpp"

using namespace std;
using namespace GeometryLibrary;


namespace ImportLibrary
{
  bool ImportVertices(vector<Vertex>& verticesList,
                      char** argv);

  bool ImportEdges(vector<Edge>& edgesList,
                   vector<Vertex>& verticesList,
                   char** argv);

  bool ImportTriangles(vector<Triangle>& trianglesList,
                       vector<Edge>& edgesList,
                       vector<Vertex>& verticesList,
                       char** argv);
}

#endif // __IMPORT_H
