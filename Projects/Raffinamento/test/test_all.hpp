#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "geometry_class.hpp"
#include "sorting.hpp"
#include "import.hpp"
#include "refine.hpp"

using namespace testing;
using namespace GeometryLibrary;
using namespace SortingLibrary;
using namespace ImportLibrary;
using namespace RefineLibrary;

/*TEST(TestVertex, TestConstructor)
{
  unsigned int id = 5;
  double x = 23.8;
  double y = 3.14159;
  Vertex v = Vertex(id, x, y);
  EXPECT_EQ(v._id, 5);
  EXPECT_EQ(v._x, 23.8);
  EXPECT_EQ(v._y, 3.14159);
}

TEST(TestEdge, TestComputeLength)
{
  unsigned int id = 9;

  unsigned int id1 = 4;
  unsigned int id2 = 9595;

  double x1 = 1;
  double x2 = 20;

  double y1 = 7, y2 = 7;

  Vertex vertice1 = Vertex(id1, x1, y1);
  Vertex vertice2 = Vertex(id2, x2, y2);

  vector<Vertex*> vs = {&vertice1, &vertice2};

  Edge e = Edge(id, vs);

  EXPECT_EQ(e._length, 19);
}

TEST(TestTriangle, TestAreaAndLongestEdge)
{
  unsigned int id = 651, id1 = 4, id2 = 9595, id3 = 6581, eid1 = 489, eid2 = 1, eid3 = 8;

  double x1 = 1,x2 = 20, x3 = 1;

  double y1 = 7, y2 = 7, y3 = 17;

  Vertex vertice1 = Vertex(id1, x1, y1);
  Vertex vertice2 = Vertex(id2, x2, y2);
  Vertex vertice3 = Vertex(id3, x3, y3);

  vector<Vertex*> vs1 = {&vertice1, &vertice2};
  vector<Vertex*> vs2 = {&vertice1, &vertice3};
  vector<Vertex*> vs3 = {&vertice2, &vertice3};

  vector<Vertex*> vs = {&vertice1, &vertice2, &vertice3};

  Edge ed1 = Edge(eid1, vs1);
  Edge ed2 = Edge(eid2, vs2);
  Edge ed3 = Edge(eid3, vs3);

  vector<Edge*> edges = {&ed1, &ed2, &ed3};

  Triangle triangle = Triangle(id, vs, edges);

  EXPECT_EQ(triangle._area, 95);
  EXPECT_EQ(*(triangle._longestEdge), ed3);
  EXPECT_EQ(edges[0]->_edgeOfTriangles[0], id);
}

TEST(TestSorting, TestMergeSort)
{
    vector<int> v = {44, 26, 12, 2, 16, 7, 9, 23, 5, 98, 32, 48};
    MergeSort(v, 0, v.size()-1);
    vector<int> sortedV = {98, 48, 44, 32, 26, 23, 16, 12, 9, 7, 5, 2};
    EXPECT_EQ(v, sortedV);
}

TEST(TestImport1, TestVertices)
{
  vector<Vertex> verticesList;
  string verticesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/0dtry.csv";

  if(ImportVertices(verticesList, verticesFile))
  {
    EXPECT_EQ(verticesList[2]._id, 2);
    EXPECT_EQ(verticesList[3]._y, 0);
  }
}

TEST(TestImport2, TestVertices)
{
  vector<Vertex> verticesList;
  string verticesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/0dtry.csv";

  vector<Edge> edgesList;
  string edgesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/1dtry.csv";

  if(ImportVertices(verticesList, verticesFile) && ImportEdges(edgesList, verticesList, edgesFile))
  {
    EXPECT_EQ(edgesList[4]._length, sqrt(2));
    EXPECT_EQ(edgesList[0]._id, 0);
  }
}

TEST(TestImport3, TestTriangles)
{
  vector<Vertex> verticesList;
  string verticesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/0dtry.csv";

  vector<Edge> edgesList;
  string edgesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/1dtry.csv";

  vector<Triangle> trianglesList;
  string trianglesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/2dtry.csv";


  if(ImportVertices(verticesList, verticesFile) && ImportEdges(edgesList, verticesList, edgesFile) && ImportTriangles(trianglesList, edgesList, verticesList, trianglesFile))
  {
    EXPECT_EQ(trianglesList[0]._longestEdge->_id, 4);
    EXPECT_EQ(trianglesList[1]._area, 0.5);
  }
}*/

#endif // __TEST_EMPTY_H
