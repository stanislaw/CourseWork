//
// lesson1_summation.cpp
//
// The following program computes
// the sum of the first 40 non-negative integers (starting from 0)

#include <iostream>
#include <vector>

using namespace std;

const int N = 40;

template <class summable>
inline void sum(summable &accumulator, vector<summable> &numbers) {
    accumulator = 0;

    for(int i = 0, size = numbers.size(); i < size; ++i) {
        accumulator += numbers[i];
    }
}

int main() {
    int numbers[N];
    for(int i = 0; i < N; ++i) {
        numbers[i] = i;
    }
 
    vector<int> vector_numbers(numbers, numbers + sizeof(numbers) / sizeof(numbers[0]));

    int sum_accumulator;
    sum(sum_accumulator, vector_numbers);
    
    cout << "sum is " << sum_accumulator << endl;
    
    return 0;
}

