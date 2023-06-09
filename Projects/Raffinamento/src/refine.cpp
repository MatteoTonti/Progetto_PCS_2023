#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle> &sortedTriangles, vector<Triangle>& trianglesList, Triangle& triangle, vector<Vertex>& verticesList, vector<Edge> &edgesList, unsigned int& counter, vector<unsigned int> &newVertices, vector<unsigned int> &newEdges)
    {
      // Troviamo il lato da bisezionare e calcoliamo le coordinate del punto medio
      unsigned int toBisect = triangle._longestEdge;
      double xm = (verticesList[edgesList[toBisect]._vertices[0]]._x + verticesList[edgesList[toBisect]._vertices[1]]._x) *0.5;
      double ym = (verticesList[edgesList[toBisect]._vertices[0]]._y + verticesList[edgesList[toBisect]._vertices[1]]._y) *0.5;

      // Creiamo il nuovo vertice dato dal punto medio e lo aggiungiamo alla lista dei vertici e alla lista dei vertici creati con la bisezione
      unsigned int newIndex = verticesList.size();
      Vertex newVertex = Vertex(newIndex, xm, ym);
      verticesList.push_back(newVertex);
      newVertices.push_back(newVertex._id);

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
       //Spegniamo il lato bisezionato da cui estraiamo in seguito i due nuovi lati
      edgesList[toBisect]._status = false;

      // Creiamo i nuovi lati dati dal nuovo vertice (punto medio) collegandolo ai vertici del triangolo di partenza
      unsigned int newE = edgesList.size();

      //Lato nuovo creato dal nuovo vertice (punto medio) al vertice opposto
      vector<Vertex*> v0 = {&verticesList[opposite], &newVertex};
      Edge newEdge1 = Edge(newE, v0);
      edgesList.push_back(newEdge1); // Lo inseriamo nella lista dei lati

      // Creazione lato bisezionato 1
      v0 = {&verticesList[edgesList[toBisect]._vertices[0]], &newVertex};
      Edge newEdge2 = Edge(++newE, v0);
      newEdges.push_back(newEdge2._id);  // Lo inseriamo nella lista dei lati nuovi dati dalla bisezione
      edgesList.push_back(newEdge2); // Lo inseriamo nella lista dei lati

      // Creazione lato bisezionato 2
      v0 = {&verticesList[edgesList[toBisect]._vertices[1]], &newVertex};
      Edge newEdge3 = Edge(++newE, v0);
      newEdges.push_back(newEdge3._id); // Lo inseriamo nella lista dei lati nuovi dati dalla bisezione
      edgesList.push_back(newEdge3); // Lo inseriamo nella lista dei lati

      // Spegniamo il triangolo che è stato raffinato
      trianglesList[triangle._id]._status = false;

      // Facciamo nuovi vettori di vertici e lati per creare i nuovi triangoli
      vector<Vertex*> vt1 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]};

      vector<Vertex*> vt2 = {&verticesList[opposite], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]};

      //Cerchiamo i lati non bisezionati del triangolo che abbiamo raffinato
      unsigned int oldEdge1 = -1;  //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                  && triangle._edges[i] != toBisect)
          {
            oldEdge1 = triangle._edges[i];
            break;
          }
      }

      //Lati del nuovo triangolo newT1
      vector<Edge*> et1 = {&edgesList[oldEdge1], &edgesList[newEdge1._id], &edgesList[newEdge2._id]}; // Così perchè altrimenti non aggiorna le adiacenze in edgesList

      // Secondo lato non bisezionato
      unsigned int oldEdge2 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
      for(unsigned int i = 0; i < 3; i++)
      {
          if((edgesList[triangle._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1]|| edgesList[triangle._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                  && triangle._edges[i] != toBisect)
          {
            oldEdge2 = triangle._edges[i];
            break;
          }
      }
      //Lati del nuovo triangolo newT2
      vector<Edge*> et2 = {&edgesList[oldEdge2], &edgesList[newEdge1._id], &edgesList[newEdge3._id]};

      // Creiamo i nuovi triangoli ottenuti bisezionando il triangolo di partenza e inseriamo nella liste di triangoli
      unsigned int indT = trianglesList.size();
      Triangle newT1 = Triangle(indT, vt1, et1);
      trianglesList.push_back(newT1);
      sortedTriangles.push_back(newT1);
      Triangle newT2 = Triangle(++indT, vt2, et2);
      trianglesList.push_back(newT2);
      sortedTriangles.push_back(newT2);

      if(counter != 0) // Caso in cui non ci troviamo nel triangolo originale, bensì stiamo raffinando un altro triangolo adiacente come conseguenza
      {
          Triangle newT3;
          Triangle newT4;

          // Troviamo il vertice della bisezione  precedente (prec) per connettere i due vertici e creare il nuovo lato
          unsigned int prec = newVertices[newVertices.size() - 2]; //penultimo perché abbiamo già inserito il nuovo newvertex
          //vertici v3 del nuovo lato newConnection ottenuto collegando il punto medio (prec) del lato precedentemente bisezionato e del punto medio(newvertex) del nuovo lato bisezionato

          vector<Vertex*> v3 = {&newVertex, &verticesList[prec]};
          Edge newConnection = Edge(++newE, v3);
          edgesList.push_back(newConnection);

          /*/ Uno tra i triangoli newT1 o newT2 è stato così diviso in due triangoli newT3 e newT4: dobbiamo capire quale
           // Metodo 1: Calcoliamo le aree con segno di newT1 e newT3: se il prodotto delle aree è positivo, è newT1 a dividersi in newT3 e newT4
          double areanewT1 = 0.5 * (newVertex._x * (verticesList[opposite]._y - verticesList[edgesList[toBisect]._vertices[0]]._y) + verticesList[opposite]._x * (verticesList[edgesList[toBisect]._vertices[0]]._y - newVertex._y) + verticesList[edgesList[toBisect]._vertices[0]]._x * (newVertex._y - verticesList[opposite]._y));
          double areanewT3 = 0.5 * (newVertex._x * (verticesList[opposite]._y - verticesList[prec]._y) + verticesList[opposite]._x * (verticesList[prec]._y - newVertex._y) + verticesList[prec]._x * (newVertex._y - verticesList[opposite]._y));
           */

          // Metodo 2: Usiamo prodotto vettoriale tra lato(opposite,[edgesList[toBisect]._vertices[0]]) e
          //lato(prec,[edgesList[toBisect]._vertices[0]]) (che in 2d restituisce uno scalare):se è = 0, allora newT3 fa parte di newT1

          double x_u = verticesList[opposite]._x - verticesList[edgesList[toBisect]._vertices[0]]._x;
          double y_u = verticesList[opposite]._y - verticesList[edgesList[toBisect]._vertices[0]]._y;

          double x_v = verticesList[prec]._x - verticesList[edgesList[toBisect]._vertices[0]]._x;
          double y_v = verticesList[prec]._y - verticesList[edgesList[toBisect]._vertices[0]]._y;

          double prodvett = x_u * y_v - y_u * x_v;


          // Se il prodotto vettoriale è = 0 (oppure il prodotto delle aree di newT1 e T3 > 0) newT1 si splitta in newT3 e newT4
          if(abs(prodvett) < GeometryLibrary :: geometricTol)
            //if (areanewT1*areanewT3 > 0)
          {

              //Vertici di newT3
              vector<Vertex*> vT3 = {&newVertex, &verticesList[prec], &verticesList[opposite]};
              unsigned int last = -1; // Troviamo l'ultimo vertice (last) di newT1 che non è opposite nè il nuovo vertice
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT1._vertices[i] == newVertex._id || newT1._vertices[i] == opposite))
                {
                    last = newT1._vertices[i];
                    break;
                }
              }
              //Vertici di newT4
              vector<Vertex*> vT4 = {&newVertex, &verticesList[prec], &verticesList[last]}; // Abbiamo così creato i vettori di vertici dei due triangoli

              // Troviamo i lati oldEdge3 (lati di newT3) e oldEdge4 (lati di newT4)
              unsigned int oldEdge3 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == opposite && edgesList[newEdges[i]]._vertices[1] == prec) || (edgesList[newEdges[i]]._vertices[1] == opposite && edgesList[newEdges[i]]._vertices[0] == prec))
                {
                  oldEdge3 = newEdges[i];
                  break;
                }
              }

              //Lati di newT3
              vector<Edge*> et3 = {&edgesList[newConnection._id], &edgesList[newEdge1._id], &edgesList[oldEdge3]}; // Vettore edges di T3

              unsigned int oldEdge4 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == last && edgesList[newEdges[i]]._vertices[1] == prec) || (edgesList[newEdges[i]]._vertices[1] == last && edgesList[newEdges[i]]._vertices[0] == prec))
                {
                  oldEdge4 = newEdges[i];
                  break;
                }
              }

              //Lati di newT4
              vector<Edge*> et4 = {&edgesList[newConnection._id], &edgesList[newEdge2._id], &edgesList[oldEdge4]}; // Vettore edges di T4

              newT3 = Triangle(++indT, vT3, et3);
              newT4 = Triangle(++indT, vT4, et4);

              trianglesList[newT1._id]._status = false; // Spregniamo il triangolo newT1 bisezionato
          }

          else

          // Se il prodotto vettoriale è != 0 (oppure il prodotto delle aree di newT1 e T3 < 0) newT2 si splitta in newT3 e newT4
          // Procediamo come nel caso precedente, con newT2 al posto di newT1
          {
              vector<Vertex*> vt3 = {&newVertex, &verticesList[prec], &verticesList[opposite]}; // Vettore di vertici per t3
              unsigned int last = -1; //Nuovo vertice inizializzato a un valore non corrispondente a nessun vertice
              for(unsigned int i = 0; i < 3; i++)
              {
                if(!(newT2._vertices[i] == newVertex._id || newT2._vertices[i] == opposite))
                {
                    last = newT2._vertices[i];
                    break;
                }
              }
              vector<Vertex*> vt4 = {&newVertex, &verticesList[prec], &verticesList[last]};

              unsigned int oldEdge3 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == opposite && edgesList[newEdges[i]]._vertices[1] == prec) || (edgesList[newEdges[i]]._vertices[1] == opposite && edgesList[newEdges[i]]._vertices[0] == prec))
                {
                  oldEdge3 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et3 = {&edgesList[newConnection._id], &edgesList[newEdge1._id], &edgesList[oldEdge3]};

              unsigned int oldEdge4 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
              for(unsigned int i = 0; i<newEdges.size(); i++)
              {
                if((edgesList[newEdges[i]]._vertices[0] == last && edgesList[newEdges[i]]._vertices[1] == prec) || (edgesList[newEdges[i]]._vertices[1] == last && edgesList[newEdges[i]]._vertices[0] == prec))
                {
                  oldEdge4 = newEdges[i];
                  break;
                }
              }
              vector<Edge*> et4 = {&edgesList[newConnection._id], &edgesList[newEdge3._id], &edgesList[oldEdge4]};

              newT3 = Triangle(++indT, vt3, et3);
              newT4 = Triangle(++indT, vt4, et4);

              trianglesList[newT2._id]._status = false;  
          }
          //Inseriamo i nuovi triangoli nelle liste di triangoli
          trianglesList.push_back(newT3);
          sortedTriangles.push_back(newT3);
          trianglesList.push_back(newT4);
          sortedTriangles.push_back(newT4);
      }
      counter++;

      // Se il lato più lungo del triangolo adiacente coincide con quello del triangolo di partenza congiungiamo il vertice opposto dell'adiacente
      // al nuovo vertice e creiamo i nuovi triangoli ottenuti dividendo il triangolo adiacente con lo stesso algoritmo di cui sopra
      unsigned int numberActive = 0; // Numero di triangoli di cui faceva parte toBisect: al massimo 1 perché un triangolo di cui faceva parte è stato appena bisezionato
      unsigned int adjacent = -1; //Triangolo inizializzato a un valore non corrispondente a nessun triangolo
      for(unsigned int i = 0; i < edgesList[toBisect]._edgeOfTriangles.size(); i++)
      {
        if(trianglesList[edgesList[toBisect]._edgeOfTriangles[i]]._status)
        {
            numberActive++;
            adjacent = edgesList[toBisect]._edgeOfTriangles[i];
            break;
        }
      }
      //Se toBisect faceva parte anche di un altro triangolo
      if(numberActive == 1)
      {
        if(trianglesList[adjacent]._longestEdge == edgesList[toBisect]._id)

        //Caso in cui i due triangoli hanno stesso longestEdge : devo collegare al punto medio (newVertex) con il vertice opposto nel triangolo adiacente
        {
            unsigned int contr = -1; // Id del vertice opposto inizializzato a un valore non corrispondente a nessun vertice
            Edge newEdge4;
            for(unsigned int i = 0; i < 3; i++) // Troviamo il vertice opposto (contr) al lato più lungo
            {
              if(!(edgesList[toBisect]._vertices[0] == trianglesList[adjacent]._vertices[i] || edgesList[toBisect]._vertices[1] == trianglesList[adjacent]._vertices[i]))
              {
                contr = trianglesList[adjacent]._vertices[i];
              }
            }
            vector<Vertex*> v4 = {&verticesList[contr], &newVertex}; // Vertici del nuovo lato newEdge4
            newEdge4 = Edge(++newE, v4);
            edgesList.push_back(newEdge4);

            //Lati del nuovo triangolo newT5
            vector<Vertex*> vt5 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[0]]};

            //Lati del nuovo triangolo newT6
            vector<Vertex*> vt6 = {&verticesList[contr], &newVertex, &verticesList[edgesList[toBisect]._vertices[1]]};

            //Troviamo il lato del triangolo adiacente che appartiene a newT5, che è il triangolo con il vertice 0
            unsigned int oldEdge5 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
            for(unsigned int i = 0; i < 3; i++)
            {
                  if((edgesList[trianglesList[adjacent]._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[0] || edgesList[trianglesList[adjacent]._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[0])
                          && trianglesList[adjacent]._edges[i] != toBisect)
                  {
                    oldEdge5 = trianglesList[adjacent]._edges[i];
                    break;
                  }
              }
              vector<Edge*> et5 = {&edgesList[oldEdge5], &edgesList[newEdge4._id], &edgesList[newEdge2._id]};
               //Nuovo triangolo newT5
              Triangle newT5 = Triangle(++indT, vt5, et5);
              trianglesList.push_back(newT5);
              sortedTriangles.push_back(newT5);

              //Troviamo il lato del triangolo adiacente che appartiene a newT6, che è il triangolo con il vertice 1
              unsigned int oldEdge6 = -1; //Lato da cercare inizializzato a un valore non corrispondente a nessun lato
              for(unsigned int i = 0; i < 3; i++)
              {
                  if((edgesList[trianglesList[adjacent]._edges[i]]._vertices[0] == edgesList[toBisect]._vertices[1] || edgesList[trianglesList[adjacent]._edges[i]]._vertices[1] == edgesList[toBisect]._vertices[1])
                          && trianglesList[adjacent]._edges[i] != toBisect)
                  {
                    oldEdge6 = trianglesList[adjacent]._edges[i];
                    break;
                  }
              }

              vector<Edge*> et6 = {&edgesList[oldEdge6], &edgesList[newEdge4._id], &edgesList[newEdge3._id]};

              //Nuovo triangolo newT6
              Triangle newT6 = Triangle(++indT, vt6, et6);
              trianglesList.push_back(newT6);
              sortedTriangles.push_back(newT6);
              //Spegniamo il triangolo adiacente
              trianglesList[adjacent]._status = false;
          }
           //Se il triangolo adiacente ha un _longestedge diverso
          else if(trianglesList[adjacent]._longestEdge != toBisect)
          {
            //In questo caso andiamo avanti con la bisezione
            Bisect(sortedTriangles, trianglesList, trianglesList[adjacent], verticesList, edgesList, counter, newVertices, newEdges);
          }
      }
    }

    //Iniziamo da qui
    void Refine(vector<Triangle>& sortedTriangles, vector<Triangle>& trianglesList, const double& percentage,vector<Vertex>& verticesList, vector<Edge>& edgesList)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = (trianglesList.size() * percentage)/100;

      //Contatore che se = 0 ci dice che il triangolo che stiamo raffinando è stato preso dalla lista dei triangoli ordinati per area;
      //se > 0 il triangolo viene raffinato come conseguenza di triangolo raffinato percedentemente in modo da mantenere la mesh ammissibile
      unsigned int counter = 0;
      vector<unsigned int> newVertices; // Qua mettiamo tutti i vertici nuovi
      vector<unsigned int> newEdges; // Qua mettiamo solo i lati che sono frutto di una bisezione di un lato

      // Ripetiamo il seguente algoritmo per numToBeRefined volte, in modo da raffinare il triangolo ad area maggiore il numero di volte richiesto
      for(unsigned int i = 0; i < numToBeRefined; i++)

      // Prendiamo il primo triangolo della lista attivo, che sappiamo essere quello ad area maggiore
      {
        cout<<"Refining triangle n. "<< i+1<<endl;

        // Finchè abbiamo triangoli non attivi, prendiamo il successivo finché non ne troviamo uno attivo
        //togliamo da sortedTriangles i triangoli non attivi in modo da mantere una lista con meno elementi
        //ed avere un sorting più efficiente
        while(!trianglesList[sortedTriangles[0]._id]._status)
            sortedTriangles.erase(sortedTriangles.begin());

      // Bisezioniamo il triangolo
        Bisect(sortedTriangles, trianglesList, sortedTriangles[0], verticesList, edgesList, counter, newVertices, newEdges); // Possiamo levare lastEdge e lastTriangle secondo me e usare sempre la size della lista

      //Per motivi di efficienza, usiamo InsertionSort per ordinare i triangoli per area decrescente dopo che abbiamo già raffinato almeno un triangolo
        sortedTriangles = InsertionSort(sortedTriangles);

        newEdges = {};
        counter = 0;
      }
    }
}
