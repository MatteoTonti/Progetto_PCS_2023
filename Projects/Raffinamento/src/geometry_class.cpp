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
    for(unsigned int i = 0; i < 2; i++)
    {
        _vertices.push_back(vertices[i]->_id);
    }
    _length = ComputeLength(vertices);
  }

  double Edge::ComputeLength(vector<Vertex *> &vertices)
  {
    // Calcoliamo la lunghezza del lato tramite i vertici piuttosto che farcela dare in input
    double length = sqrt(pow((vertices[0]->_x - vertices[1]->_x),2) + pow((vertices[0]->_y - vertices[1]->_y),2));
    return length;
  }

  Triangle::Triangle(unsigned int& id, vector<Vertex*> &vertices, vector<Edge*>& edges)
  {
    _id = id;
    for(unsigned int i = 0; i < 3; i++)
    {
        _vertices.push_back(vertices[i]->_id);
    }
    for(unsigned int i = 0; i < 3; i++)
    {
        _edges.push_back(edges[i]->_id);
    }
    for(int i = 0; i < 3; i++)
      edges[i]->_edgeOfTriangles.push_back(_id);
    _area = Area(vertices);
    _longestEdge = LongestEdge(edges);
    _status = true;
  }

  double Triangle::Area(vector<Vertex *> &vertices)
  {
    // Metodo di Gauss semplificato per calcolare l'area del triangolo dati i suoi vertici
    double area = 0.5 * ((vertices[0]->_x - vertices[1]->_x) * (vertices[2]->_y - vertices[0]->_y) - (vertices[2]->_x - vertices[0]->_x) * (vertices[1]->_y - vertices[0]->_y));
    if(area<0) // Per ordinare i vertici in senso antiorario
    {
      unsigned int swap = _vertices[1];
      _vertices[1] = _vertices[2];
      _vertices[2] = swap;
      area = -area;
    }
    return area;
  }

  Triangle::~Triangle(){
    cout<<"Removing triangle "<<_id<<endl;
  }

  unsigned int Triangle::LongestEdge(vector<Edge*>& edges)
  {
    // Metodo per trovare il lato più lungo
    unsigned int longestEdge = edges[0]->_id;
    double length = edges[0]->_length;
    for(unsigned int i = 1; i < 3; i++)
    {
      if(edges[i]->_length > length)
      {
         longestEdge = _edges[i];
         length = edges[i]->_length;
      }
    }

    return longestEdge;
  }
}
