#include <iostream>
#include "tbinarytree.h"
#include "octagon.h"

int main()
{
    Octagon a[8];
    TBinaryTree tree;
    for (int i = 0; i < 8; i++)
    {
        std::cin>>a[i];
        tree.Push(a[i]);
    }
    
    std::cout << tree << std::endl;
    a[0] = tree.GetItemNotLess(125);
    //std::cout << tree.Count(a[2]) << std::endl;
    //tree.Pop(a[1]);
    //tree.Pop(a[1]);
    //std::cout << tree << std::endl;
    tree.Clear();
    std::cout << tree << std::endl;
    if (tree.Empty())
        std::cout << "дерево пустое" << std::endl;
    return 0;
}