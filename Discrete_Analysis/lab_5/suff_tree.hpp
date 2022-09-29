#ifndef T_B_SUFF_TREE_HPP
#define T_B_SUFF_TREE_HPP

#include <vector>
#include <string>

struct SuffTreeChilds
{
    std::vector<SuffTreeNode*> LinkToChild;
    std::vector<char> FstCharInChild;
};


class SuffTree
{
    private:
        std::vector<SuffTreeChilds> childs_;
    public:
};

class SuffTreeChild
{
private:
    bool is_list_;
    int num_list_;
    std::string stored_string_;
    std::vector<SuffTreeChilds> childs_;
public:
    SuffTreeChild(std::string in);
    ~SuffTreeChild();
};

#endif