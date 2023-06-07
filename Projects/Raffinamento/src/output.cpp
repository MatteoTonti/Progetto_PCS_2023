#include "output.hpp"

namespace OutputLibrary{
    bool ExportVertices(vector<Vertex>& verticesList)
    {
      // Iniziamo aprendo il file
      ofstream file;
      string outputFile = "refVertices.csv";
      file.open(outputFile);

      if(file.fail())
      {
        cerr<<"Could not open the refined vertices file"<<endl;
        return false;
      }

      file<<"Id X Y"<<endl; // Struttura dell'output file

      for(unsigned int i = 0; i < verticesList.size();i++)
      {
        file<<verticesList[i]._id<<" "<<verticesList[i]._x<<" "<<verticesList[i]._y<<endl;
      }

      file.close();
      return true;
    }

    bool ExportEdges(vector<Edge>& edgesList, vector<Vertex>& verticesList)
    {
        // Apertura file
        ofstream file;
        string outputFile = "refEdges.csv";
        file.open(outputFile);

        if(file.fail())
        {
          cerr<<"Could not open the refined edges file"<<endl;
          return false;
        }

        file<<"Id x1 y1 x2 y2"<<endl;

        for(unsigned int i = 0; i < edgesList.size(); i++)
        {
          if(edgesList[i]._status)
            file<<edgesList[i]._id<<' '<<verticesList[edgesList[i]._vertices[0]]._x << ' ' <<verticesList[edgesList[i]._vertices[0]]._y<<' '<<verticesList[edgesList[i]._vertices[1]]._x<<' '<<verticesList[edgesList[i]._vertices[1]]._y<<endl;
        }
        file.close();

        return true;
    }

    bool ExportTriangles(vector<Triangle>& trianglesList)
    {
      // Apertura file
        ofstream file;
        string outputFile = "refTriangles.csv";
        file.open(outputFile);

        if(file.fail())
        {
          cerr<<"Could not open the refined triangles file"<<endl;
          return false;
        }

        file<<"Id V1 V2 V3"<<endl;

        for(unsigned int i = 0; i<trianglesList.size(); i++)
        {
          if(trianglesList[i]._status)
          {
            file<<trianglesList[i]._id<<' ';
            for(unsigned int j = 0; j < 3; j++)
            file<<trianglesList[i]._vertices[j]<<' ';
            file<<endl;
          }
        }

        file.close();
        return true;
    }

}
