#include "geometry_class.hpp"
#include "sorting.hpp"
#include "import.hpp"
#include "refine.hpp"
#include "output.hpp"

using namespace ImportLibrary;
using namespace GeometryLibrary;
using namespace OutputLibrary;

int main(int argc, char** argv)
{
  // Preliminarmente controlliamo che sia stata passata la percentuale al programma
  if(argc < 5)
  {
    cerr<<"At least 4 arguments have to be passed"<<endl;
    return -1;
  }
  //Percentuale dei triangoli da raffinare
  double percentage = atof(argv[1]);
  /*istringstream converter;
  converter.str(argv[1]);
  converter >> percentage;*/


  // Iniziamo importando i vertici
  vector<Vertex> verticesList = {};

  if(!ImportVertices(verticesList, argv[2]))
  {
    return 1;
  }

  // Importiamo poi i lati
  vector<Edge> edgesList = {};

  if(!ImportEdges(edgesList, verticesList, argv[3]))
  {
    return 1;
  }

  // Importiamo poi i triangoli
  vector<Triangle> trianglesList = {};

  if(!ImportTriangles(trianglesList, edgesList, verticesList, argv[4]))
  {
    return 1;
  }

  // Ordinamento per area decrescente
  vector<Triangle> sortedTriangles = SortingLibrary::HeapSort(trianglesList);
  cout<< "Vector of triangles successfully sorted by areas"<<endl;

  RefineLibrary::Refine(sortedTriangles, trianglesList, percentage, verticesList, edgesList);

  if(!(ExportVertices(verticesList)))
  {
    return 1;
  }

  if(!(ExportEdges(edgesList, verticesList)))
      return 1;

  if(!(ExportTriangles(trianglesList)))
  {
    return 1;
  }


  return 0;
}
