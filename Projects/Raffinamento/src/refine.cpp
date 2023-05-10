#include "refine.hpp"

namespace RefineLibrary
{
    void Bisect(vector<Triangle>& trianglesList,
            Triangle& triangle)
    {

    }


    void Refine(vector<Triangle>& trianglesList, const double& percentage)
    {
      // Calcoliamo il numero di triangoli da raffinare
      unsigned int numToBeRefined = trianglesList.size() / 100 * percentage;

      // Salviamo in un vettore separato gli id dei triangoli da raffinare, ordinati per area in modo decrescente
      vector<Triangle> toBeRefined;
      toBeRefined.reserve(numToBeRefined);

      for(unsigned int i = 0; i < numToBeRefined; i++)
        toBeRefined.push_back(trianglesList[i]);

      for(unsigned int i = 0; i < numToBeRefined; i++)
        // Il triangolo da raffinare deve essere all'inizio della lista: se non è quello, allora è già stato raffinato e non c'è più bisogno di farlo
        if(toBeRefined[i]._id == trianglesList[0]._id)
            Bisect(trianglesList, toBeRefined[i]);
    }


}
