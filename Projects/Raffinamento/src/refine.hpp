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
              const double& percentage);

  void Bisect(vector<Triangle>& trianglesList,
              Triangle& triangle);
}

#endif // __REFINE_H
