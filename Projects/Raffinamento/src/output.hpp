#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "geometry_class.hpp"

using namespace GeometryLibrary;

namespace OutputLibrary
{
  bool ExportVertices(const string& outputFile,
                      vector<Vertex>& verticesList);

  bool ExportTriangles(const string& outputFile,
                       vector<Triangle>& trianglesList);
}

#endif // __OUTPUT_H
