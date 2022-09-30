#ifndef T_B_SUFF_TREE_NODE_HPP
#define T_B_SUFF_TREE_NODE_HPP

#include <vector>
#include <map>
#include <string>

class SuffTreeNode
{
private:
    bool is_list_;
    int num_list_;
    std::string stored_string_;
    std::map<char, SuffTreeNode*> childs_;

    void ForkNode(std::string in_str, int num_list) {
        for(int last_match = 0; last_match < stored_string_.length() - 1; ++last_match) {
            if(in_str[last_match + 1] != stored_string_[last_match + 1]) {
                // обрубок от этой ноды
                SuffTreeNode part_of_this(stored_string_.substr(last_match), num_list_);
                part_of_this.is_list_ = false;
                part_of_this.childs_ = childs_;

                SuffTreeNode insert_node(in_str.substr(last_match), num_list);
                // изменение этой ноды
                is_list_ = false;
                num_list_ = 0;
                stored_string_ = stored_string_.substr(0, last_match);
                childs_.clear();
                childs_.emplace(stored_string_[last_match + 1], &part_of_this);
                childs_.emplace(in_str[last_match + 1], &insert_node);
                break;
            }
        }
    }
    bool IsPrefixOfChild(std::string in_str) {
        return childs_.find(in_str[0]) != childs_.end();
    }
    SuffTreeNode* FindChildByPrefix(std::string in_str) {
        return childs_.find(in_str[0])->second;
    }
    void AddNewListChild(std::string in_str, int num_list) {
        if(stored_string_.length() == 0) {
            SuffTreeNode insert_node(in_str, num_list);
            childs_.emplace(in_str[0], &insert_node);
        } else {
            for(int last_match = 0; last_match < stored_string_.length() - 1; ++last_match) {
                if(in_str[last_match + 1] != stored_string_[last_match + 1]) {
                    SuffTreeNode insert_node(in_str.substr(last_match), num_list);
                    childs_.emplace(in_str.substr(last_match)[0], &insert_node);
                    break;
                }
            }
        }
    }
public:
    SuffTreeNode() {
        is_list_ = true;
        num_list_ = 0;
    }
    SuffTreeNode(std::string in_str, int num_list) {
        is_list_ = true;
        num_list_ = num_list;
        stored_string_ = in_str;
    }
    ~SuffTreeNode() {}
    void Insert(std::string in_str, int num_list){
        if(in_str.length() < stored_string_.length()) {
            ForkNode(in_str, num_list);
        } else {
            if (IsPrefixOfChild(in_str)) {
                FindChildByPrefix(in_str)->Insert(in_str, num_list);
            } else {
                AddNewListChild(in_str, num_list);
            }
        }
    }
};

#endif