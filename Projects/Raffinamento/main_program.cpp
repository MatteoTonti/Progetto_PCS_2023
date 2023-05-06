#include "empty_class.hpp"

bool ImportVertices(vector<ProjectLibrary::Vertex>& verticesList);

bool ImportEdges(vector<ProjectLibrary::Edge>& edgesList, vector<ProjectLibrary::Vertex>& verticesList);

bool ImportTriangles(vector<ProjectLibrary::Triangle>& trianglesList, vector<ProjectLibrary::Edge>& edgesList, vector<ProjectLibrary::Vertex>& verticesList);

int main()
{
  // Iniziamo importando i vertici
  vector<ProjectLibrary::Vertex> verticesList = {};

  if(!ImportVertices(verticesList))
  {
    return 1;
  }

  // Importiamo poi i lati
  vector<ProjectLibrary::Edge> edgesList = {};

  if(!ImportEdges(edgesList, verticesList))
  {
    return 1;
  }

  // Importiamo poi i triangoli
  vector<ProjectLibrary::Triangle> trianglesList = {};

  if(!ImportTriangles(trianglesList, edgesList, verticesList))
  {
    return 1;
  }



  ProjectLibrary::Empty empty;

  empty.Show();

  return 0;
}

bool ImportVertices(vector<ProjectLibrary::Vertex>& verticesList)
{
    // Apriamo il file contenente i vertici e creiamo una lista di linee con tutte le info
    ifstream file;
    file.open("./Cell0Ds.csv");

    if(file.fail())
      return false;

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

      unsigned int id;
      unsigned int marker;
      double x;
      double y;

      converter >>  id >> marker >> x >> y;

      ProjectLibrary::Vertex newVertex = ProjectLibrary::Vertex(id, x, y);

      verticesList.push_back(newVertex);

      /*if( marker != 0)
      {
        if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
          mesh.Cell0DMarkers.insert({marker, {id}});
        else
          mesh.Cell0DMarkers[marker].push_back(id);
      }*/

    }
    return true;
}

bool ImportEdges(vector<ProjectLibrary::Edge>& edgesList, vector<ProjectLibrary::Vertex>& verticesList)
{
    ifstream file;
    file.open("./Cell1Ds.csv");

    if(file.fail())
      return false;

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

    for (const string& line : listLines)
    {
      istringstream converter(line);

      unsigned int id;
      unsigned int marker;
      unsigned int id0;
      unsigned int id1;
      vector<ProjectLibrary::Vertex> vertices;

      converter >>  id >> marker >> id0 >> id1;

      unsigned int i = 0;
      while(id0 != verticesList[i]._id)
          i++;

      vertices.push_back(verticesList[i]);

      unsigned int j = 0;
      while(id1 != verticesList[j]._id)
          j++;

      vertices.push_back(verticesList[j]);

      ProjectLibrary::Edge newEdge = ProjectLibrary::Edge(id, vertices);

      edgesList.push_back(newEdge);

      /*if( marker != 0)
      {
        if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
          mesh.Cell1DMarkers.insert({marker, {id}});
        else
          mesh.Cell1DMarkers[marker].push_back(id);
      }*/
    }

    file.close();

    return true;
}

bool ImportTriangles(vector<ProjectLibrary::Triangle>& trianglesList, vector<ProjectLibrary::Edge>& edgesList, vector<ProjectLibrary::Vertex>& verticesList)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
      return false;

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

      vector<ProjectLibrary::Vertex> vertices;
      for(unsigned int i = 0; i < 3; i++)
      {
        unsigned int j = 0;
        while(verticesId[i] != verticesList[j]._id)
            j++;
        vertices.push_back(verticesList[j]);
      }

      vector<ProjectLibrary::Edge> edges;
      for(unsigned int i = 0; i < 3; i++)
      {
        unsigned int j = 0;
        while(edgesId[i] != edgesList[j]._id)
            j++;
        edges.push_back(edgesList[j]);
      }

      ProjectLibrary::Triangle newTriangle = ProjectLibrary::Triangle(id, vertices, edges);

      trianglesList.push_back(newTriangle);
    }
    file.close();
    return true;
}
