#include <iostream>
#include "tbinarytree.h"
#include "octagon.h"

int main()
{
    Octagon octi[8];
    TBinaryTree<Octagon> tree;
    for (int i = 0; i < 8; i++)
    {
        std::cin>>octi[i];
        tree.Push(octi[i]);
    }
    
    std::cout << tree << std::endl;
    //octi[1] = tree.GetItemNotLess(octi[2].Area());
    //std::cout << octi[1] << std::endl;
    //std::cout << tree.Count(octi[0]) << std::endl;
    //tree.Pop(octi[0]);
    //tree.Pop(octi[0]);
    //std::cout << tree << std::endl;
    //tree.Clear();
    //std::cout << tree << std::endl;
    //if (tree.Empty())
        //std::cout << "дерево пустое" << std::endl;
    return 0;
}