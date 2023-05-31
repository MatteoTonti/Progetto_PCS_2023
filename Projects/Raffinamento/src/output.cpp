#include "output.hpp"

namespace OutputLibrary{
    bool ExportVertices(const string& outputFile, vector<Vertex>& verticesList)
    {
      // Iniziamo aprendo il file
      ofstream file;
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

    bool ExportTriangles(const string& outputFile, vector<Triangle>& trianglesList)
    {
      // Apertura file
        ofstream file;
        file.open(outputFile);

        if(file.fail())
        {
          cerr<<"Could not open the refined triangles file"<<endl;
          return false;
        }

        file<<"Id Vertices"<<endl;

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
