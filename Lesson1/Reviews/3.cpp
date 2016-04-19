


//This program takes a vector and sums all of its element and print out the result

#include <iostream>
#include <vector>

const int N = 40;
using namespace std;
template <class summable>

//summing function
//Sum over the vector and store the result 
inline void sum(summable& sum, int n, vector<summable> data)
{
	int i;
	sum = 0;
	for(i = 0; i < n; ++i)
		sum +=  data[i];
}


//main, initializes the vector by the pre determined size N
//Set the initial value of each component in increasing order
int main()
{
	int accum = 0;
	vector<int> data;	

	for(int i = 0; i < N; ++i)
		data.push_back(i);

	sum(accum, N, data);
	
	cout << "sum is " << accum << endl;

return 0;

}
