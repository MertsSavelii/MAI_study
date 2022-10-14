#include <iostream>
#include <vector>

using namespace std;

int main()
{
    unsigned n,m;
    cin >> n >> m;
    unsigned A[100][100];
    vector<unsigned> w;
    vector<unsigned> c;
    for(int i = 0; i < n; ++i)
    {
        cin >> w[i] >> c[i];
        for(unsigned s: w)
        {
            if(s >= w[i])
            {
                A[i][s] = max(A[i - 1][s], A[i - 1][s - w[i]] + c[i]);
            } 
            else
            {

            }
        }
    }
    return 0;
}