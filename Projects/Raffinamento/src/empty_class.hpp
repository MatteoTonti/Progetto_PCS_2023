#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>

using namespace std;


namespace ProjectLibrary
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

  inline bool operator<(const Triangle& t1, const Triangle& t2)
  {
    return t1._area < t2._area + geometricTol_Squared * max(t1._area, t2._area);
  }

  inline bool operator>=(const Triangle& t1, const Triangle& t2)
  {
    return !(t1 < t2);
  }


  template<typename T>
  void Merge(vector<T>& v,
             const unsigned int& sx,
             const unsigned int& cx,
             const unsigned int& dx)
  {
      unsigned int i = sx, j = cx + 1, k = 0;
      vector<T> b(v.size());
      while((i <= cx) && (j <= dx))
      {
          // Notare che è un MergeSort decrescente
          if (v[i] >= v[j])
          {
              b[k] = v[i];
              i++;
          }
          else
          {
              b[k] = v[j];
              j++;
          }
          k++;
      }
      for (; i <= cx; i++, k++)
          b[k] = v[i];
      for (; j <= dx; j++, k++)
          b[k] = v[j];
      for (i = sx; i <= dx; i++)
          v[i] = b[i-sx];
  }

  template<typename T>
  void MergeSort(vector<T>& v,
             const unsigned int& sx,
             const unsigned int& dx)
  {
      if (sx < dx)
      {
          unsigned int cx = (sx + dx) / 2;
          MergeSort(v, sx, cx);
          MergeSort(v, cx+1, dx);
          Merge(v, sx, cx, dx);
      }
  }
}

#endif // __EMPTY_H
