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

TEST(TestConstructors, TestVertex)
{
  unsigned int id = 5;
  double x = 23.8;
  double y = 3.14159;
  Vertex v = Vertex(id, x, y);
  EXPECT_EQ(v._id, 5);
  EXPECT_EQ(v._x, 23.8);
  EXPECT_EQ(v._y, 3.14159);
}

TEST(TestConstructors, TestEdge)
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

TEST(TestConstructors, TestTriangle)
{
  unsigned int id = 651, id1 = 4, id2 = 9595, id3 = 6581, eid1 = 489, eid2 = 1, eid3 = 8;

  double x1 = 0,x2 = 1, x3 = 0;

  double y1 = 0, y2 = 0, y3 = 1;

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

  EXPECT_EQ(triangle._area, 0.5);
  //EXPECT_EQ(triangle._longestEdge, ed3._id);
  EXPECT_EQ(edges[0]->_edgeOfTriangles[0], id);
}

TEST(TestSorting, TestHeapSort)
{
    vector<int> v = {44, 26, 12, 2, 16, 7, 9, 23, 5, 98, 32, 48};
    vector<int> heapSorted = HeapSort(v);
    vector<int> sortedV = {98, 48, 44, 32, 26, 23, 16, 12, 9, 7, 5, 2};
    EXPECT_EQ(heapSorted, sortedV);
}

TEST(TestSorting, TestInsertion)
{
    vector<int> v = {44, 26, 12, 2, 16, 7, 9, 23, 5, 98, 32, 48};
    vector<int> insertionSorted = InsertionSort(v);
    vector<int> sortedV = {98, 48, 44, 32, 26, 23, 16, 12, 9, 7, 5, 2};
    EXPECT_EQ(insertionSorted, sortedV);
}

TEST(TestImport, TestVertices)
{
  vector<Vertex> verticesList;
  string verticesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/0dtry.csv";

  if(ImportVertices(verticesList, verticesFile))
  {
    EXPECT_EQ(verticesList[2]._id, 2);
    EXPECT_EQ(verticesList[3]._y, 0);
  }
}

TEST(TestImport, TestEdges)
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

TEST(TestImport, TestTriangles)
{
  vector<Vertex> verticesList;
  string verticesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/0dtry.csv";

  vector<Edge> edgesList;
  string edgesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/1dtry.csv";

  vector<Triangle> trianglesList;
  string trianglesFile = "C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/Fittizi/2dtry.csv";


  if(ImportVertices(verticesList, verticesFile) && ImportEdges(edgesList, verticesList, edgesFile) && ImportTriangles(trianglesList, edgesList, verticesList, trianglesFile))
  {
    EXPECT_EQ(trianglesList[0]._longestEdge, 4);
    EXPECT_EQ(trianglesList[1]._area, 0.5);
  }
}

TEST(TestRefine, TestBisect)
{
    unsigned int idv1 = 0, idv2 = 1, idv3 = 2, idv4 = 3, ide1 = 0, ide2 = 1, ide3 = 2, ide4 = 3, ide5 = 4, idt1 = 0, idt2 = 1;
    double x1 = 2, x2 = 10, x3 = 8, x4 = 0, y1 = 2, y2 = 6, y3 = 10, y4 = 6;

    Vertex v1 = Vertex(idv1, x1, y1), v2 = Vertex(idv2, x2, y2), v3 = Vertex(idv3, x3, y3), v4 = Vertex(idv4, x4, y4);
    vector<Vertex> verticesList = {v1, v2, v3, v4};

    vector<Vertex*> ve1 = {&verticesList[v1._id], &verticesList[v2._id]}, ve2 = {&verticesList[v2._id], &verticesList[v3._id]}, ve3 = {&verticesList[v3._id], &verticesList[v1._id]}, ve4 = {&verticesList[v1._id], &verticesList[v4._id]}, ve5 = {&verticesList[v4._id], &verticesList[v3._id]};
    Edge e1 = Edge(ide1, ve1), e2 = Edge(ide2, ve2), e3 = Edge(ide3, ve3), e4 = Edge(ide4, ve4), e5 = Edge(ide5, ve5);
    vector<Edge> edgesList = {e1, e2, e3, e4, e5};

    vector<Vertex*> vt1 = {&verticesList[v1._id], &verticesList[v2._id], &verticesList[v3._id]}, vt2 = {&verticesList[v3._id], &verticesList[v1._id], &verticesList[v4._id]};
    vector<Edge*> et1 = {&edgesList[e1._id], &edgesList[e2._id], &edgesList[e3._id]}, et2 = {&edgesList[e3._id], &edgesList[e4._id], &edgesList[e5._id]};
    Triangle t1 = Triangle{idt1, vt1, et1}, t2 = Triangle{idt2, vt2, et2};
    vector<Triangle> trianglesList{t1, t2};

    unsigned int counter = 0;
    vector<unsigned int> newVertices = {};
    vector<unsigned int> newEdges = {};
    Bisect(trianglesList, trianglesList[0], verticesList, edgesList, counter, newVertices, newEdges);

    unsigned int idpm = 4;
    double xm = 5, ym = 6;
    Vertex vmedio = Vertex{idpm, xm, ym};

    EXPECT_EQ(verticesList[verticesList.size()-1]._id, vmedio._id);
    EXPECT_EQ(verticesList[verticesList.size()-1]._x, vmedio._x);
    EXPECT_EQ(verticesList[verticesList.size()-1]._y, vmedio._y);
    EXPECT_EQ(trianglesList[0]._status, false);
    EXPECT_EQ(edgesList[ide3]._status, false);
    EXPECT_EQ(trianglesList.size(), 6);
}
#endif // __TEST_EMPTY_H
