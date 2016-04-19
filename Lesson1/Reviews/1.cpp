/*
 * excercise.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: quentinn.r.roby
 */
// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function



#include <iostream>
#include <vector>

using namespace std;

const int sizes = 40;

// Function sum computes the sum of n elements in array d
// and return the value in the last parameter d.
inline void sum(const std::vector<int>& d, const int n, int* p) {
  *p = 0;
  for (int i= 0; i < n; ++i) {
    *p += d[i];
  }
}

// Function main initializes vector data with 40 (sizes)
// numbers and call sum function to compute the sum from 0 to 39.
int main() {
  vector<int> data;
  for (int i = 0; i < sizes; ++i) {
    data.push_back(i);
  }

  int accum = 0;
  sum(data, sizes, &accum);
  cout << "sum is " << accum << endl;
  return 0;
}
