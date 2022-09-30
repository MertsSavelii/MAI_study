#ifndef T_B_SUFF_TREE_HPP
#define T_B_SUFF_TREE_HPP

#include <vector>
#include <string.h>

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
        SuffTree(std::string in_str) {
            for(int i = 0; i < in_str.l)
        }
        ~SuffTree();
        Insert(std::string in_string) {

        }
};

class SuffTreeChild
{
private:
    bool is_list_;
    int num_list_;
    std::string stored_string_;
    std::vector<SuffTreeChilds> childs_;
public:
    SuffTreeChild(std::string in_string, int num_list) {
        is_list_ = true;
        num_list_ = num_list;
        stored_string_ = in_string;
    }
    ~SuffTreeChild();
};

#endif