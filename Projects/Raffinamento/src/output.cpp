#include "output.hpp"

namespace OutputLibrary{
    bool ExportVertices(vector<Vertex>& verticesList)
    {
      // Iniziamo creando il file di output per i vertici
      ofstream file;
      string outputFile = "refVertices.csv";
      file.open(outputFile);

      if(file.fail())
      {
        cerr<<"Could not open the refined vertices file"<<endl;
        return false;
      }
      // Struttura dell'output file : una colonna contenente gli id, una le coordinate x e una le coordinate y dei vertici
      file<<"Id X Y"<<endl;

      for(unsigned int i = 0; i < verticesList.size();i++)
      {
        file<<verticesList[i]._id<<" "<<verticesList[i]._x<<" "<<verticesList[i]._y<<endl;
      }

      file.close();
      return true;
    }

    bool ExportEdges(vector<Edge>& edgesList, vector<Vertex>& verticesList)
    {
        // Iniziamo creando il file di output per i lati
        ofstream file;
        string outputFile = "refEdges.csv";
        file.open(outputFile);

        if(file.fail())
        {
          cerr<<"Could not open the refined edges file"<<endl;
          return false;
        }
        // Struttura dell'output file : una colonna contenente gli id dei lati, una le coordinate x e una le coordinate y dei vertici di orgine
        //e una con le coordinate x e le coordinate y dei vertici di fine
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
      // Iniziamo creando il file di output per triangoli
        ofstream file;
        string outputFile = "refTriangles.csv";
        file.open(outputFile);

        if(file.fail())
        {
          cerr<<"Could not open the refined triangles file"<<endl;
          return false;
        }
        // Struttura dell'output file : una colonna contenente gli id dei triangoli e tre colonne contenenti gli id dei vertici di ognuno
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
