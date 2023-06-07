#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList, Triangle& triangle, vector<Vertex>& verticesList, vector<Edge> &edgesList, unsigned int& counter, vector<Vertex>& newVertices, vector<unsigned int> &newEdges)
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
      unsigned int opposite = 0;
      for(unsigned int i = 0; i < 3; i++)
      {
        if(!(edgesList[toBisect]._vertices[0] == triangle._vertices[i] || edgesList[toBisect]._vertices[1] == triangle._vertices[i]))
        {
           opposite = triangle._vertices[i];
           break;
        }
      }

      edgesList[toBisect]._status = false;

      // Creiamo i nuovi lati dati dal nuovo vertice(punto medio) collegandolo ai vertici del triangolo di partenza
      unsigned int newE = edgesList.size();
      //Lato creato da 0
      vector<Vertex*> v0 = {&verticesList[opposite], &newVertex};
      Edge newEdge1 = Edge(newE, v0);
      edgesList.push_back(newEdge1);

      // Lato bisezionato 1
      v0 = {&verticesList[edgesList[toBisect]._vertices[0]], &newVertex};
      Edge newEdge2 = Edge(++newE, v0);
      newEdges.push_back(newEdge2._id);
      edgesList.push_back(newEdge2);
      // Lato bisezionato 2
      v0 = {&verticesList[edgesList[toBisect]._vertices[1]], &newVertex};
      Edge newEdge3 = Edge(++newE, v0);
      newEdges.push_back(newEdge3._id);
      edgesList.push_back(newEdge3);

      // Spegniamo il triangolo che è stato raffinato
      trianglesList[triangle._id]._status = false;

      // Facciamo nuovi vettori di vertici e lati per creare i nuovi triangoli
      vector<Vertex*> v1 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]};

      vector<Vertex*> v2 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]};

      //Cerchiamo i lati del triangolo non bisezionati
      unsigned int et1 = 0;
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                  && triangle._edges[i] != toBisect)
          {
            et1 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e1 = {&edgesList[et1], &edgesList[newEdge1._id], &edgesList[newEdge2._id]}; // Così perchè altrimenti non aggiorna le adiacenze in edgesList

      // Secondo lato non bisezionato
      unsigned int et2 = 0; // Qua ho messo null per togliere un warning, potrebbe andare bene?
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1]|| edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                  && triangle._edges[i] != toBisect)
          {
            et2 = triangle._edges[i];
            break;
          }
      }
      vector<Edge*> e2 = {&edgesList[et2], &edgesList[newEdge1._id], &edgesList[newEdge3._id]};

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

          /*/Calcoliamo le aree con segno di T1 e T3 per vedere se T3 è parte di T1 o T2: lla positività dell'area me lo dice A new B opp C prec
          double areaT1 = 0.5 * (newVertex._x * (verticesList[opposite]._y - verticesList[edgesList[toBisect]._vertices[0]]._y) + verticesList[opposite]._x * (verticesList[edgesList[toBisect]._vertices[0]]._y - newVertex._y) + verticesList[edgesList[toBisect]._vertices[0]]._x * (newVertex._y - verticesList[opposite]._y));
          double areaT3 = 0.5 * (newVertex._x * (verticesList[opposite]._y - prec->_y) + verticesList[opposite]._x * (prec->_y - newVertex._y) + prec->_x * (newVertex._y - verticesList[opposite]._y));
           */
          //u =opposite - tobisect[0]
          //v = prec - tobisect[0]
          double x_u = verticesList[opposite]._x - verticesList[edgesList[toBisect]._vertices[0]]._x;
          double y_u = verticesList[opposite]._y - verticesList[edgesList[toBisect]._vertices[0]]._y;

          double x_v = prec->_x - verticesList[edgesList[toBisect]._vertices[0]]._x;
          double y_v = prec->_y - verticesList[edgesList[toBisect]._vertices[0]]._y;

          double prodvett = x_u * y_v - y_u * x_v;


          // Se T1 e T3 sono dello stesso segno T1 si splitta in T3 e T4
          if(abs(prodvett) < GeometryLibrary :: geometricTol)
          {
              vector<Vertex*> vT3 = {&newVertex, prec, &verticesList[opposite]};
              unsigned int last = 0; // Troviamo l'ultimo vertice di T1 che non è opposite nè il nuovo vertice(versione con l'id)
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
              unsigned int ed3 = 0;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == opposite && edgesList[newEdges[i]]._vertices[1] == prec->_id) || (edgesList[newEdges[i]]._vertices[1] == opposite && edgesList[newEdges[i]]._vertices[0] == prec->_id))
                {
                  ed3 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&edgesList[newConnection._id], &edgesList[newEdge1._id], &edgesList[ed3]}; // Vettore edges di T3

              unsigned int ed4 = 0;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == last && edgesList[newEdges[i]]._vertices[1] == prec->_id) || (edgesList[newEdges[i]]._vertices[1] == last && edgesList[newEdges[i]]._vertices[0] == prec->_id))
                {
                  ed4 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&edgesList[newConnection._id], &edgesList[newEdge2._id], &edgesList[ed4]}; // Vettore edges di T4

              newT3 = Triangle(++indT, vT3, et3);
              newT4 = Triangle(++indT, vT4, et4);

              trianglesList[newT1._id]._status = false; // Si spegne il triangolo bisezionato
          }

          else
          {
              vector<Vertex*> vT3 = {&newVertex, prec, &verticesList[opposite]}; // Vettore di vertici per t3
              unsigned int last = 0;
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT2._vertices[i] == newVertex._id || newT2._vertices[i] == opposite))
                {
                    last = newT2._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vT4 = {&newVertex, prec, &verticesList[last]};

              unsigned int ed3 = 0; // Qua metto una versione di trovare il lato con gli id per avere un confronto di leggibilità
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == opposite && edgesList[newEdges[i]]._vertices[1] == prec->_id) || (edgesList[newEdges[i]]._vertices[1] == opposite && edgesList[newEdges[i]]._vertices[0] == prec->_id))
                {
                  ed3 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&edgesList[newConnection._id], &edgesList[newEdge1._id], &edgesList[ed3]};

              unsigned int ed4 = 0;
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == last && edgesList[newEdges[i]]._vertices[1] == prec->_id) || (edgesList[newEdges[i]]._vertices[1] == last && edgesList[newEdges[i]]._vertices[0] == prec->_id))
                {
                  ed4 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&edgesList[newConnection._id], &edgesList[newEdge3._id], &edgesList[ed4]};

              newT3 = Triangle(++indT, vT3, et3);
              newT4 = Triangle(++indT, vT4, et4);

              trianglesList[newT2._id]._status = false;  
          }
          trianglesList.push_back(newT3);
          trianglesList.push_back(newT4);
      }
      counter++;

      // Se il lato più lungo del triangolo adiacente coincide con quello del triangolo di partenza congiungiamo il vertice opposto dell'adiacente
      // al nuovo vertice e creiamo i nuovi triangoli ottenuti dividendo il triangolo adiacente con lo stesso algoritmo di cui sopra
      unsigned int numberActive = 0; // Numero di triangoli a cui è adiacente toBisect
      unsigned int adjacent = 0;
      for(unsigned int i = 0; i < edgesList[toBisect]._edgeOfTriangles.size(); i++)
      {
        if(trianglesList[edgesList[toBisect]._edgeOfTriangles[i]]._status)
        {
            numberActive++;
            adjacent = edgesList[toBisect]._edgeOfTriangles[i];
            break;
        }
      }

      if(numberActive == 1)
      {
        if(trianglesList[adjacent]._longestEdge == edgesList[toBisect]._id)
        {
            unsigned int contr = 0; // Id del vertice opposto
            Edge newEdge4;
            for(unsigned int i = 0; i < 3; i++) // Troviamo il vertice opposto al lato più lungo
            {
              if(!(edgesList[toBisect]._vertices[0] == trianglesList[adjacent]._vertices[i] || edgesList[toBisect]._vertices[1] == trianglesList[adjacent]._vertices[i]))
              {
                contr = trianglesList[adjacent]._vertices[i];
              }
            }
            vector<Vertex*> v4 = {&verticesList[contr], &newVertex}; // Vertici del nuovo lato
            newEdge4 = Edge(++newE, v4);
            edgesList.push_back(newEdge4);
            vector<Vertex*> v5 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]}; // Vettore per T5

            vector<Vertex*> v6 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]}; // Vettore per T6

            unsigned int et5 = 0; //Troviamo il lato del triangolo adiacente che appartiene a T5, che è il triangolo con il vertice 0
            for(unsigned int i = 0; i < 3; i++)
            {
                  if((edgesList[trianglesList[adjacent]._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[trianglesList[adjacent]._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                          && trianglesList[adjacent]._edges[i] != toBisect)
                  {
                    et5 = trianglesList[adjacent]._edges[i];
                    break;
                  }
              }
              vector<Edge*> e3 = {&edgesList[et5], &edgesList[newEdge4._id], &edgesList[newEdge2._id]};

              Triangle newT5 = Triangle(++indT, v5, e3);
              trianglesList.push_back(newT5);

              unsigned int et6 = 0; //Troviamo il lato del triangolo adiacente che appartiene a T6, che è il triangolo con il vertice 1
              for(unsigned int i = 0; i < 3; i++)
              {
                  if((edgesList[trianglesList[adjacent]._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1] || edgesList[trianglesList[adjacent]._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                          && trianglesList[adjacent]._edges[i] != toBisect)
                  {
                    et6 = trianglesList[adjacent]._edges[i];
                    break;
                  }
              }

              vector<Edge*> e4 = {&edgesList[et6], &edgesList[newEdge4._id], &edgesList[newEdge3._id]};


              Triangle newT6 = Triangle(++indT, v6, e4);
              trianglesList.push_back(newT6);

              trianglesList[adjacent]._status = false;
          }

          else if(trianglesList[adjacent]._longestEdge != toBisect)
          {
            //In questo caso andiamo avanti con la bisezione
            Bisect(trianglesList, trianglesList[adjacent], verticesList, edgesList, counter, newVertices, newEdges);
          }
      }
    }


    void Refine(vector<Triangle>& sortedTriangles, vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = (trianglesList.size() *percentage)/100;

      unsigned int counter = 0;
      unsigned int counter1 = 0;

      vector<Vertex> newVertices; // Qua mettiamo tutti i vertici nuovi
      vector<unsigned int> newEdges; // Qua mettiamo solo i lati che sono frutto di una bisezione di un lato

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
        if (counter1 == 0)
        {sortedTriangles = HeapSort(trianglesList);
        ++counter1;}
        else
        sortedTriangles = InsertionSort(trianglesList);

        newEdges = {};
        counter = 0;
      }
    }
}
