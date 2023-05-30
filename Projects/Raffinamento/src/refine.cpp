#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList, Triangle& triangle, vector<Vertex>& verticesList, vector<Edge> &edgesList, unsigned int& lastEdge, unsigned int& lastTriangle, unsigned int& counter, vector<Vertex>& newVertices, vector<Edge> &newEdges)
    {
      // Troviamo il lato da bisezionare e calcoliamo le coordinate del punto medio
      unsigned int toBisect = triangle._longestEdge;
      double xm = (verticesList[edgesList[toBisect]._vertices[0]]._x + verticesList[edgesList[toBisect]._vertices[1]]._x) *0.5;
      double ym = (verticesList[edgesList[toBisect]._vertices[0]]._y + verticesList[edgesList[toBisect]._vertices[1]]._y) *0.5;

      // Creiamo il nuovo vertice dato dal punto medio e lo aggiungiamo alla lista dei vertici e alla lista dei vertici creati con la bisezione
      unsigned int newIndex = verticesList.size();
      Vertex newVertex = Vertex(newIndex, xm, ym);
      verticesList.push_back(newVertex);
      newVertices.push_back(newVertex);

      // Troviamo il vertice opposto al lato più lungo
      unsigned int opposite;
      for(unsigned int i = 0; i < 3; i++)
      {
        if(!(toBisect->_vertices[0]->_id == triangle._vertices[i]->_id || toBisect->_vertices[1]->_id == triangle._vertices[i]->_id))
        {
           opposite = triangle._vertices[i];
           break;
        }
      }



      // Creiamo i nuovi lati dati dal nuovo vertice(punto medio) collegandolo ai vertici del triangolo di partenza
      vector<Vertex*> v0 = {opposite, &newVertex};
      Edge newEdge1 = Edge(++lastEdge, v0);

      v0 = {toBisect->_vertices[0], &newVertex};
      Edge newEdge2 = Edge(++lastEdge, v0);
      //newEdges.push_back(newEdge2);

      v0 = {toBisect->_vertices[1], &newVertex};
      Edge newEdge3 = Edge(++lastEdge, v0);
      //newEdges.push_back(newEdge3);

      // Cancelliamo il triangolo che è stato raffinato dalla lista dei triangoli
      for(unsigned int i = 0; i < trianglesList.size(); i++)
      {
        if(trianglesList[i]._id == triangle._id)
        {
          cout<<"Removing triangle "<<trianglesList[i]._id<<endl;
          trianglesList.erase(trianglesList.begin()+i);
          break;
        }
      }

      // Facciamo nuovi vettori di vertici e lati per creare i nuovi triangoli
      vector<Vertex*> v1 = {opposite, &newVertex, toBisect->_vertices[0]};

      vector<Vertex*> v2 = {opposite, &newVertex, toBisect->_vertices[1]};

      Edge* et1 = nullptr;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((triangle._edges[i]->_vertices[0]->_id == toBisect->_vertices[0]->_id || triangle._edges[i]->_vertices[1]->_id == toBisect->_vertices[0]->_id)
                  && triangle._edges[i] != toBisect)
          {
            et1 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e1 = {et1, &newEdge1, &newEdge2};

      Edge* et2 = nullptr;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((triangle._edges[i]->_vertices[0]->_id == toBisect->_vertices[1]->_id || triangle._edges[i]->_vertices[1]->_id == toBisect->_vertices[1]->_id)
                  && triangle._edges[i] != toBisect)
          {
            et2 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e2 = {et2, &newEdge1, &newEdge3};
      // Togliamo ora l'id del triangolo originale dalla lista di id dei triangoli adiacenti di ciascun lato del triangolo(aggiornamento adiacenze)
      for(unsigned int i = 0; i < et1->_edgeOfTriangles.size();i++)
      {
        if(et1->_edgeOfTriangles[i] == triangle._id)
        {
            et1->_edgeOfTriangles.erase(et1->_edgeOfTriangles.begin()+i);
            break;
        }

      }
      for(unsigned int i = 0; i < et2->_edgeOfTriangles.size();i++)
      {
        if(et2->_edgeOfTriangles[i] == triangle._id)
        {
            et2->_edgeOfTriangles.erase(et2->_edgeOfTriangles.begin()+i);
            break;
        }
      }
      // Creiamo i nuovi triangoli ottenuti bisezionando il triangolo di partenza
      Triangle newT1 = Triangle(++lastTriangle, v1, e1);
      Triangle newT2 = Triangle(++lastTriangle, v2, e2);

      if(counter != 0)
      {
          Triangle newT3;
          Triangle newT4;

          Vertex *prec = &newVertices[newVertices.size() - 1];
          vector<Vertex*> v3 = {&newVertex, prec};

          Edge newConnection = Edge(++lastEdge, v3);

          //Calcoliamo le aree con segno di T1 e T3 per vedere se T3 è parte di T1 o T2
          double areaT1 = 0.5 * ((newVertex._x - opposite->_x) * (toBisect->_vertices[0]->_y - newVertex._y) - (toBisect->_vertices[0]->_x - newVertex._x) * (opposite->_y - newVertex._y));
          double areaT3 = 0.5 * ((newVertex._x - opposite->_x) * (prec->_y - newVertex._y) - (prec->_x - newVertex._x) * (opposite->_y - newVertex._y));

          // Se T1 e T3 sono dello stesso segno T1 si splitta in T3 e T4
          if(areaT1 * areaT3 > 0)
          {
              vector<Vertex*> vT3 = {&newVertex, prec, opposite};
              Vertex* last = nullptr;
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT1._vertices[i]->_id == newVertex._id || newT1._vertices[i]->_id == opposite->_id))
                {
                    last = newT1._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vT4 = {&newVertex, prec, last};

              Edge* ed3 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == opposite && newEdges[i]._vertices[1] == prec) || (newEdges[i]._vertices[1] == opposite && newEdges[i]._vertices[0] == prec))
                {
                  ed3 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&newConnection, &newEdge1, ed3};

              Edge* ed4 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == last && newEdges[i]._vertices[1] == prec) || (newEdges[i]._vertices[1] == last && newEdges[i]._vertices[0] == prec))
                {
                  ed4 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&newConnection, &newEdge2, ed4};

              newT3 = Triangle(++lastTriangle, vT3, et3);
              newT4 = Triangle(++lastTriangle, vT4, et4);

              trianglesList.push_back(newT2);
              trianglesList.push_back(newT3);
              trianglesList.push_back(newT4);

              for(unsigned int i = 0; i < newEdge1._edgeOfTriangles.size();i++)
              {
                if(newEdge1._edgeOfTriangles[i] == triangle._id)
                {
                    newEdge1._edgeOfTriangles.erase(newEdge1._edgeOfTriangles.begin()+i);
                    break;
                }

              }
              for(unsigned int i = 0; i < newEdge2._edgeOfTriangles.size();i++)
              {
                if(newEdge2._edgeOfTriangles[i] == triangle._id)
                {
                    newEdge2._edgeOfTriangles.erase(newEdge2._edgeOfTriangles.begin()+i);
                    break;
                }
              }

          }

          else
          {
              vector<Vertex*> vT3 = {&newVertex, prec, opposite};
              Vertex* last = nullptr;
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT1._vertices[i]->_id == newVertex._id || newT1._vertices[i]->_id == opposite->_id))
                {
                    last = newT1._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vT4 = {&newVertex, prec, last};

              Edge* ed3 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == opposite && newEdges[i]._vertices[1] == prec) || (newEdges[i]._vertices[1] == opposite && newEdges[i]._vertices[0] == prec))
                {
                  ed3 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&newConnection, &newEdge1, ed3};

              Edge* ed4 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == last && newEdges[i]._vertices[1] == prec) || (newEdges[i]._vertices[1] == last && newEdges[i]._vertices[0] == prec))
                {
                  ed4 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&newConnection, &newEdge3, ed4};

              newT3 = Triangle(++lastTriangle, vT3, et3);
              newT4 = Triangle(++lastTriangle, vT4, et4);

              trianglesList.push_back(newT1);
              trianglesList.push_back(newT3);
              trianglesList.push_back(newT4);

              for(unsigned int i = 0; i < newEdge1._edgeOfTriangles.size();i++)
              {
                if(newEdge1._edgeOfTriangles[i] == triangle._id)
                {
                    newEdge1._edgeOfTriangles.erase(newEdge1._edgeOfTriangles.begin()+i);
                    break;
                }

              }
              for(unsigned int i = 0; i < newEdge3._edgeOfTriangles.size();i++)
              {
                if(newEdge3._edgeOfTriangles[i] == triangle._id)
                {
                    newEdge3._edgeOfTriangles.erase(newEdge3._edgeOfTriangles.begin()+i);
                    break;
                }
              }

          }
          newEdges.pop_back();
          newEdges.pop_back();

          newEdges.push_back(newEdge2);
          newEdges.push_back(newEdge3);
      }
      else
      {
        trianglesList.push_back(newT1);
        trianglesList.push_back(newT2);

        newEdges.push_back(newEdge2);
        newEdges.push_back(newEdge3);
      }
      counter++;



      // Troviamo il triangolo adiacente a cui riapplicare il bisezionamento del lato più lungo
      Triangle *adjacent = nullptr;
      for(unsigned int i = 0; i < toBisect->_edgeOfTriangles.size(); i++)
      {
        if(toBisect->_edgeOfTriangles[i] != triangle._id)
        {
          // Poichè nella lista di triangoli a cui appartiene un lato ci sono gli id e non i triangoli, cerchiamo nella
          // lista dei triangoli e scorriamo finchè non troviamo l'id corrette
          for(unsigned int j = 0; j < trianglesList.size(); j++)
          {
            if(trianglesList[j]._id == toBisect->_edgeOfTriangles[i])
            {
              adjacent = &trianglesList[j];
              break;
            }
          }
          break;
        }
      }




      // Se il lato più lungo del triangolo adiacente coincide con quello del triangolo di partenza congiungiamo il vertice opposto dell'adiacente
      // al nuovo vertice e creiamo i nuovi triangoli ottenuti dividendo il triangolo adiacente con lo stesso algoritmo di cui sopra
      switch(toBisect->_edgeOfTriangles.size())
      {
        case 1:
          break;
        case 2:
          if(adjacent->_longestEdge->_id == toBisect->_id)
          {
              Vertex *contr = nullptr;
              Edge newEdge4;
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(toBisect->_vertices[0]->_id == adjacent->_vertices[i]->_id || toBisect->_vertices[1]->_id == adjacent->_vertices[i]->_id))
                {
                   contr = adjacent->_vertices[i];
                   break;
                }

                vector<Vertex*> v4 = {contr, &newVertex};
                newEdge4 = Edge(++lastEdge, v4);
              }

              for(unsigned int i = 0; i < trianglesList.size(); i++)
              {
                if(trianglesList[i]._id == adjacent->_id)
                {
                  trianglesList.erase(trianglesList.begin()+i);
                  break;
                }
              }
              vector<Vertex*> v5 = {contr, &newVertex, toBisect->_vertices[0]};

              vector<Vertex*> v6 = {contr, &newVertex, toBisect->_vertices[1]};

              Edge* et5 = nullptr;
              for(unsigned int i = 0; i < 3; i++)
              {
                  if((adjacent->_edges[i]->_vertices[0]->_id == toBisect->_vertices[0]->_id || adjacent->_edges[i]->_vertices[1]->_id == toBisect->_vertices[0]->_id)
                          && *(adjacent->_edges[i]) != *toBisect)
                  {
                    et5 = adjacent->_edges[i];
                    break;
                  }
              }
              vector<Edge*> e3 = {et5, &newEdge4, &newEdge2};

              Edge* et6 = nullptr;
              for(unsigned int i = 0; i < 3; i++)
              {
                  if((adjacent->_edges[i]->_vertices[0]->_id == toBisect->_vertices[1]->_id || adjacent->_edges[i]->_vertices[1]->_id == toBisect->_vertices[1]->_id)
                          && *(adjacent->_edges[i]) != *toBisect)
                  {
                    et6 = adjacent->_edges[i];
                    break;
                  }
              }
              vector<Edge*> e4 = {et6, &newEdge4, &newEdge3};

              Triangle newT5 = Triangle(++lastTriangle, v5, e3);
              Triangle newT6 = Triangle(++lastTriangle, v6, e4);

              trianglesList.push_back(newT5);
              trianglesList.push_back(newT6);

          }

          else if(adjacent->_longestEdge->_id != toBisect->_id)
          {
            //In questo caso andiamo avanti con la bisezione
            Bisect(trianglesList, *adjacent, verticesList, lastVertex, lastEdge, lastTriangle, counter, newVertices, newEdges);
          }
      }
    }


    void Refine(vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = (trianglesList.size() *percentage)/100;

      unsigned int lastEdge = edgesList.size() - 1;
      unsigned int lastTriangle = trianglesList.size() - 1;
      unsigned int counter = 0;

      vector<Vertex> newVertices;
      vector<Edge> newEdges;

      // Ripetiamo il seguente algoritmo per numToBeRefined volte, in modo da raffinare il triangolo ad area maggiore il numero di volte richiesto
      for(unsigned int i = 0; i < numToBeRefined; i++)
      // Prendiamo il primo triangolo della lista attivo, che sappiamo essere quello ad area maggiore
      {
        unsigned int j = 0;
        // Finchè abbiamo triangoli non attivi, prendo il successivo finchè non ne trovo uno attivo
        while(!trianglesList[j]._status)
            j++;

        // Biseziono il triangolo
        Bisect(trianglesList, trianglesList[j], verticesList, edgesList, lastEdge, lastTriangle, counter, newVertices, newEdges);
      }
    }

}
