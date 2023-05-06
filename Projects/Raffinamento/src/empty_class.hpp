#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>

using namespace std;


namespace ProjectLibrary
{
  class Empty
  {
    public:
      void Show() const { std::cout<< "LMercu"<< std::endl; }
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
      vector<Vertex> _vertices;

      Edge() = default;
      Edge(unsigned int& id,
           vector<Vertex>& vertices);
      double ComputeLength();
  };

  class Triangle
  {
    public:
      unsigned int _id;
      vector<Vertex> _vertices;
      vector<Edge> _edges;
      double _area;
      vector<Triangle> _adjacents;
      Edge _longestEdge;

      Triangle() = default;
      Triangle(unsigned int& id,
               vector<Vertex>& vertices,
               vector<Edge>& edges);
      double Area();
      Edge LongestEdge();

  };

}

#endif // __EMPTY_H
