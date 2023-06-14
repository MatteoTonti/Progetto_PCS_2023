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
  // Tolleranza che useremo per le lunghezze
  static constexpr double geometricTol = 1.0e-12;
  //Tolleranza che useremo per le aree
  static constexpr double geometricTol_Squared = max_tolerance(geometricTol * geometricTol,
                                                             numeric_limits<double>::epsilon());

//Classe dei vertici
  class Vertex
  {
    public:
      unsigned int _id; //id del vertice
      double _x; // coordinata x del vertice
      double _y; // coordinata y del vertice
      Vertex() = default; //Costruttore di default del vertice
      Vertex(unsigned int& id,
               double& x,
               double& y); //Costruttore del vertice
  };
//Classe dei lati
  class Edge
  {
    public:
      unsigned int _id; //id del lato
      double _length; //lunghezza del lato
      vector<unsigned int> _vertices; //vettore contenente gli id dei vertici del lato
      vector<unsigned int> _edgeOfTriangles; //vettore contenente gli id dei triangoli di cui fa parte il lato
      bool _status; //variabile booleana che indica se il lato esiste ancora o no

      Edge() = default; //Costruttore di default del lato
      Edge(unsigned int& id,
           vector<Vertex*>& vertices); //Costruttore del lato
      double ComputeLength(vector<Vertex*>& vertices); //Metodo che restituisce la lunghezza del lato
  };

  inline bool operator==(const Edge& e1, const Edge& e2) //operatore di uguaglianza tra lati
  {
    return e1._id == e2._id;
  }

  inline bool operator!=(const Edge& e1, const Edge& e2)
  {
    return !(e1 == e2);
  }
//Classe dei triangoli
  class Triangle
  {
    public:
      unsigned int _id; //id del triangolo
      vector<unsigned int> _vertices; //vettore contenente gli id dei vertici del triangolo
      vector<unsigned int> _edges; //vettore contenente gli id dei lati del triangolo
      double _area; //area del triangolo
      unsigned int _longestEdge; //id del lato più lungo del triangolo
      bool _status; //variabile booleana che indica se il triangolo esiste ancora o no


      Triangle() = default; //Costruttore di default del triangolo
      Triangle(unsigned int& id,
               vector<Vertex*>& vertices,
               vector<Edge*>& edges); //Costruttore del triangolo
      double Area(vector<Vertex*>& vertices); //Metodo che restituisce l'area del triangolo
      unsigned int LongestEdge(vector<Edge*>& edges); //Metodo che restituisce l'id del lato più lungo del triangolo
  };

  inline bool operator<(const Triangle& t1, const Triangle& t2)  //operatore di confronto tra triangoli basato sull'area
  {
    return t1._area < t2._area + geometricTol_Squared * max(t1._area, t2._area);
  }

  inline bool operator>=(const Triangle& t1, const Triangle& t2)
  {
    return !(t1 < t2);
  }

}

#endif // __GEOMETRY_H
