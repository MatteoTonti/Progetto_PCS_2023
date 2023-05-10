#include "geometry_class.hpp"
#include "sorting.hpp"
#include "import.hpp"
#include "refine.hpp"

using namespace ImportLibrary;
using namespace GeometryLibrary;

int main(int argc, char** argv)
{
  // Preliminarmente controlliamo che sia stata passata la percentuale al programma
  if(argc < 5)
  {
    cerr<<"At least 4 arguments have to be passed"<<endl;
    return -1;
  }

  double percentage;
  istringstream converter;
  converter.str(argv[1]);
  converter >> percentage;

  if(percentage > 100 || percentage < 0)
  {
    cerr<<"The percentage has to be a number between 0 and 100"<<endl;
    return -1;
  }

  // Iniziamo importando i vertici
  vector<Vertex> verticesList = {};

  if(!ImportVertices(verticesList, argv))
  {
    return 1;
  }

  // Importiamo poi i lati
  vector<Edge> edgesList = {};

  if(!ImportEdges(edgesList, verticesList, argv))
  {
    return 1;
  }

  // Importiamo poi i triangoli
  vector<Triangle> trianglesList = {};

  if(!ImportTriangles(trianglesList, edgesList, verticesList, argv))
  {
    return 1;
  }

  // Ordinamento per area decrescente
  unsigned int numTriangles = trianglesList.size();

  SortingLibrary::MergeSort(trianglesList, 0, numTriangles-1);

  RefineLibrary::Refine(trianglesList, percentage);



  Empty empty;

  empty.Show();

  return 0;
}



