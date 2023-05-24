#include "geometry_class.hpp"

namespace GeometryLibrary
{
  Vertex::Vertex(unsigned int& id, double& x, double& y)
  {
    _id = id;
    _x = x;
    _y = y;
  }

  Edge::Edge(unsigned int& id, vector<Vertex *> &vertices)
  {
    _id = id;
    _vertices = vertices;
    _length = ComputeLength();
  }

  double Edge::ComputeLength()
  {
    // Calcoliamo la lunghezza del lato tramite i vertici piuttosto che farcela dare in input
    double length = sqrt(pow((_vertices[0]->_x - _vertices[1]->_x),2) + pow((_vertices[0]->_y - _vertices[1]->_y),2));
    return length;
  }

  Triangle::Triangle(unsigned int& id, vector<Vertex*> &vertices, vector<Edge*>& edges)
  {
    _id = id;
    _vertices = vertices;
    _edges = edges;
    for(int i = 0; i < 3; i++)
      edges[i]->_edgeOfTriangles.push_back(_id); // Problema qua: non creiamo le adiacenze nel lato vero
    _area = Area();
    _longestEdge = LongestEdge();
  }

  double Triangle::Area()
  {
    // Metodo di Gauss semplificato per calcolare l'area del triangolo dati i suoi vertici
    double area = 0.5 * ((_vertices[0]->_x - _vertices[1]->_x) * (_vertices[2]->_y - _vertices[0]->_y) - (_vertices[2]->_x - _vertices[0]->_x) * (_vertices[1]->_y - _vertices[0]->_y));
    if(area<0) // Per ordinare i vertici in senso antiorario
    {
      Vertex* swap = _vertices[1];
      _vertices[1] = _vertices[2];
      _vertices[2] = swap;
      area = -area;
    }
    return area;
  }

  Triangle::~Triangle(){
    cout<<"Removing triangle "<<_id<<endl;
  }

  Edge Triangle::LongestEdge()
  {
    // Metodo per trovare il lato più lungo
    Edge longestEdge = *_edges[0];
    for(unsigned int i = 1; i < 3; i++)
    {
      if(_edges[i]->_length > longestEdge._length)
        longestEdge = *_edges[i];
    }

    return longestEdge;
  }
}
