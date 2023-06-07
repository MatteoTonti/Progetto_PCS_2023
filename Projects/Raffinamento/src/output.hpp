#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "geometry_class.hpp"

using namespace GeometryLibrary;

namespace OutputLibrary
{
  bool ExportVertices(vector<Vertex>& verticesList);

  bool ExportEdges(vector<Edge>& edgesList,
                   vector<Vertex>& verticesList);

  bool ExportTriangles(vector<Triangle>& trianglesList);
}

#endif // __OUTPUT_H
