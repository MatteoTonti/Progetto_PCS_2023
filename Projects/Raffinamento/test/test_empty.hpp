#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"

using namespace testing;

TEST(TestVertex, TestConstructor)
{
  unsigned int id = 5;
  double x = 23.8;
  double y = 3.14159;
  ProjectLibrary::Vertex v = ProjectLibrary::Vertex(id, x, y);
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

  ProjectLibrary::Vertex vertice1 = ProjectLibrary::Vertex(id1, x1, y1);
  ProjectLibrary::Vertex vertice2 = ProjectLibrary::Vertex(id2, x2, y2);

  vector<ProjectLibrary::Vertex> vs = {vertice1, vertice2};

  ProjectLibrary::Edge e = ProjectLibrary::Edge(id, vs);

  EXPECT_EQ(e._length, 19);
}

TEST(TestTriangle, TestAreaAndLongestEdge)
{
  unsigned int id = 651, id1 = 4, id2 = 9595, id3 = 6581, eid1 = 489, eid2 = 1, eid3 = 8;

  double x1 = 1,x2 = 20, x3 = 1;

  double y1 = 7, y2 = 7, y3 = 17;

  ProjectLibrary::Vertex vertice1 = ProjectLibrary::Vertex(id1, x1, y1);
  ProjectLibrary::Vertex vertice2 = ProjectLibrary::Vertex(id2, x2, y2);
  ProjectLibrary::Vertex vertice3 = ProjectLibrary::Vertex(id3, x3, y3);

  vector<ProjectLibrary::Vertex> vs1 = {vertice1, vertice2};
  vector<ProjectLibrary::Vertex> vs2 = {vertice1, vertice3};
  vector<ProjectLibrary::Vertex> vs3 = {vertice2, vertice3};

  vector<ProjectLibrary::Vertex> vs = {vertice1, vertice2, vertice3};

  ProjectLibrary::Edge ed1 = ProjectLibrary::Edge(eid1, vs1);
  ProjectLibrary::Edge ed2 = ProjectLibrary::Edge(eid2, vs2);
  ProjectLibrary::Edge ed3 = ProjectLibrary::Edge(eid3, vs3);

  vector<ProjectLibrary::Edge> edges = {ed1, ed2, ed3};

  ProjectLibrary::Triangle triangle = ProjectLibrary::Triangle(id, vs, edges);

  EXPECT_EQ(triangle._area, 95);
  EXPECT_EQ(triangle._longestEdge, ed3);
}

#endif // __TEST_EMPTY_H
