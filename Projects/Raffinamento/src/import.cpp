#include "import.hpp"

namespace ImportLibrary
{
    bool ImportVertices(vector<Vertex>& verticesList, string argv)
    {
        // Apriamo il file contenente i vertici e creiamo una lista di linee con tutte le info
        ifstream file;
        file.open(argv);

        if(file.fail())
        {
          cerr<<"The first path given in input is not valid"<<endl;
          return false;
        }

        list<string> listLines;
        string line;
        while (getline(file, line))
          listLines.push_back(line);

        file.close();

        listLines.pop_front();

        unsigned int numVertices = listLines.size();

        if (numVertices == 0)
        {
          cerr << "There are no vertices" << endl;
          return false;
        }

        verticesList.reserve(numVertices);

        // Per ogni linea creiamo un nuovo oggetto di tipo Vertex e man mano inseriamo i nuovi oggetti in coda al vettore
        for (const string& line : listLines)
        {
          istringstream converter(line);
          //non usiamo il marker
          unsigned int id;
          unsigned int marker;
          double x;
          double y;

          converter >>  id >> marker >> x >> y;
          //Creiamo il vertice usando il costruttore e lo inseriamo in coda al vettore di vertici
          Vertex newVertex = Vertex(id, x, y);
          verticesList.push_back(newVertex);

        }
        cout<<"Vertices succesfully imported"<<endl;

        return true;
    }

    bool ImportEdges(vector<Edge>& edgesList, vector<Vertex>& verticesList, string argv)
    {
        ifstream file;
        file.open(argv);

        if(file.fail())
        {
          cerr<<"The second path given in input is not valid"<<endl;
          return false;
        }

        list<string> listLines;
        string line;
        while (getline(file, line))
          listLines.push_back(line);

        listLines.pop_front();

        unsigned int numberEdges = listLines.size();

        if (numberEdges == 0)
        {
          cerr << "There are no edges" << endl;
          return false;
        }

        edgesList.reserve(numberEdges);

        // Per ogni linea creiamo un nuovo oggetto di tipo Edge e man mano inseriamo i nuovi oggetti in coda al vettore
        for (const string& line : listLines)
        {
          istringstream converter(line);
          //non usiamo il marker
          unsigned int id;
          unsigned int marker;
          unsigned int id0;
          unsigned int id1;
          vector<Vertex*> vertices;

          converter >>  id >> marker >> id0 >> id1;

          //Troviamo i vertici dei lati cercando nella lista dei vertici  e li inseriamo nel vettore vertices del lato
          unsigned int i = 0;
          while(id0 != verticesList[i]._id)
              i++;

          vertices.push_back(&verticesList[i]);

          unsigned int j = 0;
          while(id1 != verticesList[j]._id)
              j++;

          vertices.push_back(&verticesList[j]);
          //Creiamo il lato usando il costruttore e lo inseriamo in coda al vettore di lati
          Edge newEdge = Edge(id, vertices);
          edgesList.push_back(newEdge);
        }

        file.close();
        cout<< "Edges succesfully imported"<<endl;

        return true;
    }

    bool ImportTriangles(vector<Triangle>& trianglesList, vector<Edge>& edgesList, vector<Vertex>& verticesList, string argv)
    {
        ifstream file;
        file.open(argv);

        if(file.fail())
        {
          cerr<<"The third path given in input is not valid"<<endl;
          return false;
        }

        list<string> listLines;
        string line;
        while (getline(file, line))
          listLines.push_back(line);

        listLines.pop_front();

        unsigned int numTriangles = listLines.size();

        if (numTriangles == 0)
        {
          cerr << "There are no triangles" << endl;
          return false;
        }

        trianglesList.reserve(numTriangles);

        // Per ogni linea creiamo un nuovo oggetto di tipo Triangle e man mano inseriamo i nuovi oggetti in coda al vettore
        for (const string& line : listLines)
        {
          istringstream converter(line);

          unsigned int id;
          array<unsigned int, 3> verticesId;
          array<unsigned int, 3> edgesId;

          converter >>  id;
          for(unsigned int i = 0; i < 3; i++)
            converter >> verticesId[i];
          for(unsigned int i = 0; i < 3; i++)
            converter >> edgesId[i];

        //Troviamo i vertici dei triangoli cercandoli nella lista di vertici e li inseriamo nel vettore vertices del triangolo
          vector<Vertex*> vertices;
          for(unsigned int i = 0; i < 3; i++)
          {
            unsigned int j = 0;
            while(verticesId[i] != verticesList[j]._id)
                j++;
            vertices.push_back(&verticesList[j]);
          }

         //Troviamo i vertici dei lati cercandoli nella lista di vertici e li inseriamo nel vettore edges del triangolo
          vector<Edge*> edges;
          for(unsigned int i = 0; i < 3; i++)
          {
            unsigned int j = 0;
            while(edgesId[i] != edgesList[j]._id)
                j++;
            edges.push_back(&edgesList[j]);
          }

        //Creiamo il triangolo usando il costruttore del triangolo e lo inseriamo in coda al vettore di triangoli
          Triangle newTriangle = Triangle(id, vertices, edges);
          trianglesList.push_back(newTriangle);
        }
        file.close();
        cout<< "Triangles succesfully imported"<<endl;
        return true;

    }

}
