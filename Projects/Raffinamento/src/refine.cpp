#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList, Triangle& triangle, vector<Vertex>& verticesList, vector<Edge> &edgesList, unsigned int& counter, vector<Vertex>& newVertices, vector<Edge> &newEdges)
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
      unsigned int opposite = NULL;
      for(unsigned int i = 0; i < 3; i++)
      {
        if(!(edgesList[toBisect]._vertices[0] == triangle._vertices[i] || edgesList[toBisect]._vertices[1] == triangle._vertices[i]))
        {
           opposite = triangle._vertices[i];
           break;
        }
      }



      // Creiamo i nuovi lati dati dal nuovo vertice(punto medio) collegandolo ai vertici del triangolo di partenza
      unsigned int newE = edgesList.size();
      //Lato creato da 0
      vector<Vertex*> v0 = {&verticesList[opposite], &newVertex};
      Edge newEdge1 = Edge(newE, v0);
      edgesList.push_back(newEdge1);

      // Lato bisezionato 1
      v0 = {&verticesList[edgesList[toBisect]._vertices[0]], &newVertex};
      Edge newEdge2 = Edge(++newE, v0);
      newEdges.push_back(newEdge2);
      edgesList.push_back(newEdge2);

      // Lato bisezionato 2
      v0 = {&verticesList[edgesList[toBisect]._vertices[1]], &newVertex};
      Edge newEdge3 = Edge(++newE, v0);
      newEdges.push_back(newEdge3);
      edgesList.push_back(newEdge3);

      // Spegniamo il triangolo che è stato raffinato
      triangle._status = false;

      // Facciamo nuovi vettori di vertici e lati per creare i nuovi triangoli
      vector<Vertex*> v1 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]};

      vector<Vertex*> v2 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]};

      //Cerchiamo i lati del triangolo non bisezionati
      unsigned int et1 = NULL;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                  && triangle._edges[i] != toBisect)
          {
            et1 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e1 = {&edgesList[et1], &newEdge1, &newEdge2};

      // Secondo lato non bisezionato
      unsigned int et2 = NULL; // Qua ho messo null per togliere un warning, potrebbe andare bene?
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1]|| edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                  && triangle._edges[i] != toBisect)
          {
            et2 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e2 = {&edgesList[et2], &newEdge1, &newEdge3};

      // Creiamo i nuovi triangoli ottenuti bisezionando il triangolo di partenza
      unsigned int indT = trianglesList.size();
      Triangle newT1 = Triangle(indT, v1, e1);
      trianglesList.push_back(newT1);
      Triangle newT2 = Triangle(++indT, v2, e2);
      trianglesList.push_back(newT2);

      if(counter != 0) // Caso in cui non ci troviamo nel triangolo originale, bensì stiamo raffinando un altro triangolo come conseguenza
      {
          Triangle newT3;
          Triangle newT4;

          // Troviamo il vertice della bisezione precedente per connettere i due vertici e creare il nuovo lato
          Vertex *prec = &newVertices[newVertices.size() - 2];
          vector<Vertex*> v3 = {&newVertex, prec};

          Edge newConnection = Edge(++newE, v3);
          edgesList.push_back(newConnection);

          //Calcoliamo le aree con segno di T1 e T3 per vedere se T3 è parte di T1 o T2: lla positività dell'area me lo dice
          double areaT1 = 0.5 * ((newVertex._x - verticesList[opposite]._x) * (verticesList[edgesList[toBisect]._vertices[0]]._y - newVertex._y) - (verticesList[edgesList[toBisect]._vertices[0]]._x - newVertex._x) * (verticesList[opposite]._y - newVertex._y));
          double areaT3 = 0.5 * ((newVertex._x - verticesList[opposite]._x) * (prec->_y - newVertex._y) - (prec->_x - newVertex._x) * (verticesList[opposite]._y - newVertex._y));

          // Se T1 e T3 sono dello stesso segno T1 si splitta in T3 e T4
          if(areaT1 * areaT3 > 0)
          {
              vector<Vertex*> vT3 = {&newVertex, prec, &verticesList[opposite]};
              unsigned int last = NULL; // Troviamo l'ultimo vertice di T1 che non è opposite nè il nuovo vertice(versione con l'id)
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT1._vertices[i] == newVertex._id || newT1._vertices[i] == opposite))
                {
                    last = newT1._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vT4 = {&newVertex, prec, &verticesList[last]}; // Abbiamo così creato i vettori di vertici dei due triangoli

              // Troviamo i lati ed3, che va messo in T3 e ed4, che va messo in T4
              Edge* ed3 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == opposite && newEdges[i]._vertices[1] == prec->_id) || (newEdges[i]._vertices[1] == opposite && newEdges[i]._vertices[0] == prec->_id))
                {
                  ed3 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&newConnection, &newEdge1, ed3}; // Vettore edges di T3

              Edge* ed4 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == last && newEdges[i]._vertices[1] == prec->_id) || (newEdges[i]._vertices[1] == last && newEdges[i]._vertices[0] == prec->_id))
                {
                  ed4 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&newConnection, &newEdge2, ed4}; // Vettore edges di T4

              newT3 = Triangle(++indT, vT3, et3);
              newT4 = Triangle(++indT, vT4, et4);

              newT1._status = false; // Si spegne il triangolo bisezionato

              trianglesList.push_back(newT3);
              trianglesList.push_back(newT4);
          }

          else
          {
              vector<Vertex*> vT3 = {&newVertex, prec, &verticesList[opposite]}; // Vettore di vertici per t3
              unsigned int last = NULL;
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT2._vertices[i] == newVertex._id || newT2._vertices[i] == opposite))
                {
                    last = newT2._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vT4 = {&newVertex, prec, &verticesList[last]};

              Edge* ed3 = nullptr; // Qua metto una versione di trovare il lato con gli id per avere un confronto di leggibilità
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == opposite && newEdges[i]._vertices[1] == prec->_id) || (newEdges[i]._vertices[1] == opposite && newEdges[i]._vertices[0] == prec->_id))
                {
                  ed3 = &edgesList[newEdges[i]._id];
                  break;
                }
              }
              vector<Edge*> et3 = {&newConnection, &newEdge1, ed3};

              Edge* ed4 = nullptr;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((newEdges[i]._vertices[0] == last && newEdges[i]._vertices[1] == prec->_id) || (newEdges[i]._vertices[1] == last && newEdges[i]._vertices[0] == prec->_id))
                {
                  ed4 = &newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&newConnection, &newEdge3, ed4};

              newT3 = Triangle(++indT, vT3, et3);
              newT4 = Triangle(++indT, vT4, et4);

              newT2._status = false;

              trianglesList.push_back(newT3);
              trianglesList.push_back(newT4);
          }
      }
      counter++;



      // Se il lato più lungo del triangolo adiacente coincide con quello del triangolo di partenza congiungiamo il vertice opposto dell'adiacente
      // al nuovo vertice e creiamo i nuovi triangoli ottenuti dividendo il triangolo adiacente con lo stesso algoritmo di cui sopra
      unsigned int numberActive = 0; // Numero di triangoli a cui è adiacente toBisect
      for(unsigned int i = 0; i < edgesList[toBisect]._edgeOfTriangles.size(); i++)
      {
        if(trianglesList[edgesList[toBisect]._edgeOfTriangles[i]]._status)
            numberActive++;
      }

      if(numberActive == 2)
      {
        // Troviamo il triangolo adiacente a cui riapplicare il bisezionamento del lato più lungo
        Triangle *adjacent = nullptr;
        for(unsigned int i = 0; i < edgesList[toBisect]._edgeOfTriangles.size(); i++)
        {
          if(edgesList[toBisect]._edgeOfTriangles[i] != triangle._id && trianglesList[edgesList[toBisect]._edgeOfTriangles[i]]._status)
          {
            adjacent = &trianglesList[edgesList[toBisect]._edgeOfTriangles[i]];
            break;
          }
        }
        if(adjacent->_longestEdge == edgesList[toBisect]._id)
        {
            unsigned int contr = NULL; // Id del vertice opposto
            Edge newEdge4;
            for(unsigned int i = 0; i < 3; i++) // Troviamo il vertice opposto al lato più lungo
            {
              if(!(edgesList[toBisect]._vertices[0] == adjacent->_vertices[i] || edgesList[toBisect]._vertices[1] == adjacent->_vertices[i]))
              {
                 contr = adjacent->_vertices[i];
                 break;
              }

              vector<Vertex*> v4 = {&verticesList[contr], &newVertex}; // Vertici del nuovo lato
              newEdge4 = Edge(++newE, v4);
              edgesList.push_back(newEdge4);// nuovo lato
            }

            vector<Vertex*> v5 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]}; // Vettore per T5

            vector<Vertex*> v6 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]}; // Vettore per T6

            Edge* et5 = nullptr; //Troviamo il lato del triangolo adiacente che appartiene a T5, che è il triangolo con il vertice 0
            for(unsigned int i = 0; i < 3; i++)
            {
                  if((edgesList[adjacent->_edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[adjacent->_edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                          && adjacent->_edges[i] != toBisect)
                  {
                    et5 = &edgesList[adjacent->_edges[i]];
                    break;
                  }
              }
              vector<Edge*> e3 = {et5, &newEdge4, &newEdge2};

              Edge* et6 = nullptr; //Troviamo il lato del triangolo adiacente che appartiene a T6, che è il triangolo con il vertice 1
              for(unsigned int i = 0; i < 3; i++)
              {
                  if((edgesList[adjacent->_edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1] || edgesList[adjacent->_edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                          && adjacent->_edges[i] != toBisect)
                  {
                    et6 = &edgesList[adjacent->_edges[i]];
                    break;
                  }
              }
              vector<Edge*> e4 = {et6, &newEdge4, &newEdge3};

              Triangle newT5 = Triangle(++indT, v5, e3);
              Triangle newT6 = Triangle(++indT, v6, e4);

              adjacent->_status = false;

              trianglesList.push_back(newT5);
              trianglesList.push_back(newT6);

          }

          else if(adjacent->_longestEdge != toBisect)
          {
            //In questo caso andiamo avanti con la bisezione
            Bisect(trianglesList, *adjacent, verticesList, edgesList, counter, newVertices, newEdges);
          }
      }
    }


    void Refine(vector<Triangle>& sortedTriangles, vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = (trianglesList.size() *percentage)/100;

      unsigned int counter = 0;

      vector<Vertex> newVertices; // Qua mettiamo tutti i vertici nuovi
      vector<Edge> newEdges; // Qua mettiamo solo i lati che sono frutto di una bisezione di un lato

      // Ripetiamo il seguente algoritmo per numToBeRefined volte, in modo da raffinare il triangolo ad area maggiore il numero di volte richiesto
      for(unsigned int i = 0; i < numToBeRefined; i++)
      // Prendiamo il primo triangolo della lista attivo, che sappiamo essere quello ad area maggiore
      {
        cout<<"Refining triangle n. "<< i+1<<endl;
        unsigned int j = 0;
        // Finchè abbiamo triangoli non attivi, prendo il successivo finchè non ne trovo uno attivo
        while(!sortedTriangles[j]._status)
            j++;

        // Biseziono il triangolo
        Bisect(trianglesList, sortedTriangles[j], verticesList, edgesList, counter, newVertices, newEdges); // Possiamo levare lastEdge e lastTriangle secondo me e usare sempre la size della lista
        sortedTriangles = HeapSort(trianglesList);
        newEdges = {};
        counter = 0;
      }
    } 
}
