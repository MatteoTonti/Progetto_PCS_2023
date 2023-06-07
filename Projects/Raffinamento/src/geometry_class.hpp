#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>

using namespace std;


namespace GeometryLibrary
{
  constexpr double max_tolerance(const double& x, const double& y)
  {
    return x > y ? x : y;
  }

  static constexpr double geometricTol = 1.0e-12;
  static constexpr double geometricTol_Squared = max_tolerance(geometricTol * geometricTol,
                                                             numeric_limits<double>::epsilon());

  class Empty
  {
    public:
      void Show() const { std::cout<< "Funziona"<< std::endl; }
  };

  class Vertex
  {
    public:
      unsigned int _id;
      double _x;
      double _y;
      Vertex() = default;
      Vertex(unsigned int& id,
               double& x,
               double& y);
  };

  class Edge
  {
    public:
      unsigned int _id;
      double _length;
      vector<unsigned int> _vertices;
      vector<unsigned int> _edgeOfTriangles;
      bool _status;

      Edge() = default;
      Edge(unsigned int& id,
           vector<Vertex*>& vertices);
      double ComputeLength(vector<Vertex*>& vertices);
  };

  inline bool operator==(const Edge& e1, const Edge& e2)
  {
    return e1._id == e2._id;
  }

  inline bool operator!=(const Edge& e1, const Edge& e2)
  {
    return !(e1 == e2);
  }

  class Triangle
  {
    public:
      unsigned int _id;
      vector<unsigned int> _vertices;
      vector<unsigned int> _edges;
      double _area;
      unsigned int _longestEdge;
      bool _status;


      Triangle() = default;
      Triangle(unsigned int& id,
               vector<Vertex*>& vertices,
               vector<Edge*>& edges);
      double Area(vector<Vertex*>& vertices);
      unsigned int LongestEdge(vector<Edge*>& edges);
  };

  inline bool operator<(const Triangle& t1, const Triangle& t2)
  {
    return t1._area < t2._area + geometricTol_Squared * max(t1._area, t2._area);
  }

  inline bool operator>=(const Triangle& t1, const Triangle& t2)
  {
    return !(t1 < t2);
  }

}

#endif // __GEOMETRY_H
