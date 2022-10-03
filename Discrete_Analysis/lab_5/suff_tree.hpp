#ifndef T_B_SUFF_TREE_HPP
#define T_B_SUFF_TREE_HPP

#include <vector>
#include <map>
#include <string>

#include "suff_tree_node.hpp"

class SuffTree
{
    private:
        SuffTreeNode suff_tree_;
    public:
        SuffTree(std::string in_str) {
            in_str += '$';
            for(int i = 0; i < in_str.length(); ++i) {
                suff_tree_.Insert(in_str.substr(i), i + 1);
            }
        }
        ~SuffTree(){}
        std::vector<unsigned> SubstringSearch(std::string in_str) {
            std::vector<unsigned> ans;
            if(in_str.length() == 0) {
                return ans;
            }
            suff_tree_.SubstringSearchInNode(in_str, ans);
            return ans;
        }
};

#endif