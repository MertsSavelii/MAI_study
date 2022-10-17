#include <iostream>
#include <vector>
#include <algorithm>

struct item
{
    int worth = 0;
    std::vector<int> subset;
};

int main()
{
    int n, m, wi, ci;
    std::vector<int> W, C;
    std::vector<std::vector<item>> I;
    std::cin >> n >> m;
    item it;
    I.resize(n + 1);
    I[0].resize(m + 1, it);
    for(int i = 0; i < n; ++i)
    {
        std::cin >> wi >> ci;
        W.push_back(wi);
        C.push_back(ci);
        I[i+1].resize(m + 1,it);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= m; ++j)
        {
            if(j >= W[i - 1]) {
                int power_subset = I[i-1][j - W[i-1]].subset.size();
                if(power_subset == 0)
                    power_subset = 1;
                if(I[i-1][j].worth > (I[i-1][j - W[i-1]].worth + C[i-1]) * power_subset)
                    I[i][j] = I[i-1][j];
                else {
                    I[i][j].worth = I[i-1][j - W[i-1]].worth + C[i-1];
                    I[i][j].subset = I[i-1][j - W[i-1]].subset;
                    I[i][j].subset.push_back(i);
                }
            }
            else
                I[i][j] = I[i-1][j];
        }
    return 0;
}