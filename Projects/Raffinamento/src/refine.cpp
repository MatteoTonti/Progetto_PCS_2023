#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList, Triangle& triangle,vector<Vertex>& verticesList, unsigned int& lastVertex, unsigned int& lastEdge, unsigned int& lastTriangle, vector<Vertex>& newVertices)
    {
      Edge toBisect = triangle._longestEdge;
      double xm = (toBisect._vertices[0]._x + toBisect._vertices[1]._x) *0.5;
      double ym = (toBisect._vertices[0]._y + toBisect._vertices[1]._y) *0.5;

      Vertex newVertex = Vertex(++lastVertex, xm, ym);
      verticesList.push_back(newVertex);
      newVertices.push_back(newVertex);

      Vertex opposite;
      for(unsigned int i = 0; i < 3; i++)
      {
        if(!(toBisect._vertices[0]._id == triangle._vertices[i]._id || toBisect._vertices[1]._id == triangle._vertices[i]._id))
        {
           opposite = triangle._vertices[i];
           break;
        }
      }

      vector<Vertex> uxtv = {opposite, newVertex};
      Edge newEdge1 = Edge(++lastEdge, uxtv);

      uxtv = {toBisect._vertices[0], newVertex};
      Edge newEdge2 = Edge(++lastEdge, uxtv);

      uxtv = {toBisect._vertices[1], newVertex};
      Edge newEdge3 = Edge(++lastEdge, uxtv);

      for(unsigned int i = 0; i < trianglesList.size(); i++)
      {
        if(trianglesList[i]._id == triangle._id)
        {
          trianglesList.erase(trianglesList.begin()+i);
          break;
        }
      }

      vector<Vertex> v1 = {opposite, newVertex, toBisect._vertices[0]};

      vector<Vertex> v2 = {opposite, newVertex, toBisect._vertices[1]};

      Edge et1;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((triangle._edges[i]._vertices[0]._id == toBisect._vertices[0]._id || triangle._edges[i]._vertices[1]._id == toBisect._vertices[0]._id)
                  && triangle._edges[i] != toBisect)
          {
            et1 = triangle._edges[i];
            break;
          }
      }
      vector<Edge> e1 = {et1, newEdge1, newEdge2};

      Edge et2;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((triangle._edges[i]._vertices[0]._id == toBisect._vertices[1]._id || triangle._edges[i]._vertices[1]._id == toBisect._vertices[1]._id)
                  && triangle._edges[i] != toBisect)
          {
            et2 = triangle._edges[i];
            break;
          }
      }
      vector<Edge> e2 = {et1, newEdge1, newEdge3};

      Triangle newT1 = Triangle(++lastTriangle, v1, e1);
      Triangle newT2 = Triangle(++lastTriangle, v2, e2);

      Triangle adjacent;
      for(unsigned int i = 0; i < 2; i++)
      {
        if(toBisect._edgeOfTriangles[i] != triangle._id)
        {
          for(unsigned int j = 0; j < trianglesList.size(); j++)
          {
            if(trianglesList[j]._id == toBisect._edgeOfTriangles[i])
            {
              Triangle adjacent = trianglesList[j];
              break;
            }
          }
        }
      }

      if(toBisect._edgeOfTriangles.size() != 1 && adjacent._longestEdge._id == toBisect._id)
      {
          Vertex contr;
          for(unsigned int i = 0; i < 3; i++)
          {
            if(!(toBisect._vertices[0]._id == adjacent._vertices[i]._id || toBisect._vertices[1]._id == adjacent._vertices[i]._id))
            {
               contr = adjacent._vertices[i];
               break;
            }

            vector<Vertex> v4 = {contr, newVertex};
            Edge newEdge4 = Edge(++lastEdge, v4);
          }

          for(unsigned int i = 0; i < trianglesList.size(); i++)
          {
            if(trianglesList[i]._id == adjacent._id)
            {
              trianglesList.erase(trianglesList.begin()+i);
              break;
            }
          }
          vector<Vertex> v5 = {contr, newVertex, toBisect._vertices[0]};

          vector<Vertex> v6 = {contr, newVertex, toBisect._vertices[1]};

          Edge et3;
          for(unsigned int i = 0; i < 3; i++)
          {
              if((adjacent._edges[i]._vertices[0]._id == toBisect._vertices[0]._id || adjacent._edges[i]._vertices[1]._id == toBisect._vertices[0]._id)
                      && adjacent._edges[i] != toBisect)
              {
                et3 = adjacent._edges[i];
                break;
              }
          }
          vector<Edge> e3 = {et1, newEdge1, newEdge2};

          Edge et4;
          for(unsigned int i = 0; i < 3; i++)
          {
              if((adjacent._edges[i]._vertices[0]._id == toBisect._vertices[1]._id || adjacent._edges[i]._vertices[1]._id == toBisect._vertices[1]._id)
                      && adjacent._edges[i] != toBisect)
              {
                et4 = adjacent._edges[i];
                break;
              }
          }
          vector<Edge> e4 = {et1, newEdge1, newEdge3};

          Triangle newT3 = Triangle(++lastTriangle, v5, e3);
          Triangle newT4 = Triangle(++lastTriangle, v6, e4);
      }

      else if(toBisect._edgeOfTriangles.size() != 1 && adjacent._longestEdge._id != toBisect._id)
      {

        Bisect(trianglesList, adjacent, verticesList, lastVertex, lastEdge, lastTriangle, newVertices);

        vector<Vertex> v7 = {newVertices[newVertices.size()-1], newVertices[newVertices.size()-2]};
        Edge connection = Edge(++lastEdge, v7);

        newVertices.pop_back();
      }
    }


    void Refine(vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = trianglesList.size() / 100 * percentage;

      // Salviamo in un vettore separato gli id dei triangoli da raffinare, ordinati per area in modo decrescente
      vector<Triangle> toBeRefined;
      toBeRefined.reserve(numToBeRefined);

      unsigned int lastVertex = verticesList.size() - 1;
      unsigned int lastEdge = edgesList.size() - 1;
      unsigned int lastTriangle = trianglesList.size() - 1;

      for(unsigned int i = 0; i < numToBeRefined; i++)
        toBeRefined.push_back(trianglesList[i]);

      vector<Vertex> newVertices;

      for(unsigned int i = 0; i < numToBeRefined; i++)
        // Il triangolo da raffinare deve essere all'inizio della lista: se non è quello, allora è già stato raffinato e non c'è più bisogno di farlo
        if(toBeRefined[i]._id == trianglesList[0]._id)
            Bisect(trianglesList, toBeRefined[i], verticesList, lastVertex, lastEdge, lastTriangle, newVertices);
    }


}
