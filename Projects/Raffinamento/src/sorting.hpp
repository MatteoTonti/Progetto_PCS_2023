#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include "Eigen/Eigen"
#include "cmath"
#include <fstream>

using namespace std;
using namespace Eigen;

namespace SortLibrary {
    template<typename T>
    void Merge(vector<T>& v,
               const unsigned int& sx,
               const unsigned int& cx,
               const unsigned int& dx)
    {
        unsigned int i = sx, j = cx + 1, k = 0;
        vector<T> b(v.size());
        while((i <= cx) && (j <= dx))
        {
            if (v[i] >= v[j])
            {
                b[k] = v[i];
                i++;
            }
            else
            {
                b[k] = v[j];
                j++;
            }
            k++;
        }
        for (; i <= cx; i++, k++)
            b[k] = v[i];
        for (; j <= dx; j++, k++)
            b[k] = v[j];
        for (i = sx; i <= dx; i++)
            v[i] = b[i-sx];
    }

    template<typename T>
    void MergeSort(vector<T>& v,
               const unsigned int& sx,
               const unsigned int& dx)
    {
        if (sx < dx)
        {
            unsigned int cx = (sx + dx) / 2;
            MergeSort(v, sx, cx);
            MergeSort(v, cx+1, dx);
            Merge(v, sx, cx, dx);
        }
    }
}

#endif // SORTING_HPP
