#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList, Triangle& triangle,vector<Vertex>& verticesList, unsigned int& lastVertex, unsigned int& lastEdge)
    {
      Edge toBisect = triangle._longestEdge;
      double xm = (toBisect._vertices[0]._x + toBisect._vertices[1]._x) *0.5;
      double ym = (toBisect._vertices[0]._y + toBisect._vertices[1]._y) *0.5;

      Vertex newVertex = Vertex(++lastVertex, xm, ym);

      Vertex opposite;
      for(unsigned int i = 0; i < 3; i++)
      {
        if(!(toBisect._vertices[0]._id == triangle._vertices[i]._id || toBisect._vertices[1]._id == triangle._vertices[i]._id))
        {
           opposite = triangle._vertices[i];
           break;
        }
      }

      // Vediamo poi se ci serve modificare il
      vector<Vertex> uxtv = {opposite, newVertex};
      Edge newEdge1 = Edge(++lastEdge, uxtv);


      uxtv = {toBisect._vertices[0], newVertex};
      Edge newEdge2 = Edge(++lastEdge, uxtv);

      uxtv = {toBisect._vertices[1], newVertex};
      Edge newEdge3 = Edge(++lastEdge, uxtv);

    }


    void Refine(vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList,  unsigned int& lastVertex, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = trianglesList.size() / 100 * percentage;

      // Salviamo in un vettore separato gli id dei triangoli da raffinare, ordinati per area in modo decrescente
      vector<Triangle> toBeRefined;
      toBeRefined.reserve(numToBeRefined);

      unsigned int lastEdge = edgesList.size() - 1;

      for(unsigned int i = 0; i < numToBeRefined; i++)
        toBeRefined.push_back(trianglesList[i]);

      for(unsigned int i = 0; i < numToBeRefined; i++)
        // Il triangolo da raffinare deve essere all'inizio della lista: se non è quello, allora è già stato raffinato e non c'è più bisogno di farlo
        if(toBeRefined[i]._id == trianglesList[0]._id)
            Bisect(trianglesList, toBeRefined[i], lastVertex, edgesList, lastEdge);
    }


}
