#ifndef __SORTING_H
#define __SORTING_H

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"

using namespace std;
using namespace Eigen;

namespace SortingLibrary
{
  template<typename T>
  vector<T> MakeHeap(vector<T>& v, int&n, int id_root){
          int id_max = id_root; // inizializzo il più grande col padre
          int s = id_root * 2 + 1; // figlio sinistro ha indice 2*id_root+1
          int d = id_root * 2 + 2; // il destro 2*id_root+ 2
          T max = v[id_max];

          if (s < n && v[s] < v[id_max])  // se s > del padre; è necessaria la condiz s < n, perchè magari ho solo il figlio sinistro
          {
              id_max = s;
              max = v[id_max];
          }

          if (d < n && v[d] < v[id_max]) // se d > dell'attuale max
          {
              id_max = d;
              max = v[id_max];
          }

          if (id_max != id_root) // se il max non è la root
          {
              v[id_max] = v[id_root];
              v[id_root] = max;

              MakeHeap(v, n, id_max);  // ricorsivo
          }
          return v;
      }

  template<typename T>
  vector<T> HeapSort(const vector<T>& v){

      // come prima cosa, trasformo il vettore in un heap
      vector<T> vSorted = v;  //vCopia non è const e quindi posso modificarlo
      int n = v.size();  // dimensione del vettore
      for (int i = n / 2 - 1; i >= 0; i--)
              MakeHeap(vSorted, n, i);  // ho reso il vettore un heap

      // ora lo ordino
      for (int i = n - 1; i >= 0; i--)
      {
          swap(vSorted[0], vSorted[i]);  // sposto in ultima posizione la root, che è il numero più grande
          MakeHeap(vSorted, i, 0);  // uso MakeHeap sul nuovo vettore ridotto
      }
      return vSorted;
  }


  template<typename T>
  vector<T> InsertionSort(const vector<T>& v){
    unsigned int n = v.size();
    vector<T> sortedV = v;
    for(unsigned int i = 0; i < n; i++)
    {
      T next = sortedV[i];
      unsigned int j = i;

      while((j > 0 ) && (sortedV[j-1] < next))
      {
        sortedV[j] = sortedV[j-1];
        j--;
      }
      sortedV[j] = next;
    }

    return sortedV;
  }

}

#endif // __SORTING_H
