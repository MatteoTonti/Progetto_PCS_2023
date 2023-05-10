#include "refine.hpp"

namespace RefineLibrary
{
    void Refine(vector<Triangle>& trianglesList, const double& percentage)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = trianglesList.size() / 100 * percentage;

      // Salviamo in un vettore separato gli id dei triangoli da raffinare, ordinati per area in modo decrescente
      vector<unsigned int> toBeRefined;
      toBeRefined.reserve(numToBeRefined);

      for(unsigned int i = 0; i < numToBeRefined; i++)
        toBeRefined.push_back(trianglesList[i]._id);


    }
}
