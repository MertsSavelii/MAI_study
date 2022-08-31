#include <iostream>
#include "octagon.hpp"
#include "tvector.hpp"

int main()
{   
    Octagon octi[8];
    TVector<Octagon> vec;
    for (int i = 0; i < 8; i++)
    {
        std::cin>>octi[i];
        vec.InsertLast(octi[i]);
    }
    for (auto i : vec) {
        std::cout << i << std::endl;
    }

    return 0;
}