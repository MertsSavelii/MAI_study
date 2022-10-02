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

    bool IsPrefixOfChild(std::string in_str) {
        int first_mismath = IndxOfFirstDiffFromStoredStr(in_str);
        return childs_.find(in_str.substr(first_mismath)[0]) != childs_.end();
    }
    SuffTreeNode* FindChildByPrefix(std::string in_str) {
        int first_mismath = IndxOfFirstDiffFromStoredStr(in_str);
        return childs_.find(in_str.substr(first_mismath)[0])->second;
    }
    int IndxOfFirstDiffFromStoredStr(std::string in_str) {
        int first_mismatch = 0;
        for(; stored_string_[first_mismatch] == in_str[first_mismatch]; first_mismatch++);
        return first_mismatch;
    }
    void SplitNode(int split_indx) {
        SuffTreeNode* cut_off_part = new SuffTreeNode(stored_string_.substr(split_indx), num_list_);
        cut_off_part->childs_ = childs_;

        is_list_ = false;
        num_list_ = 0;
        stored_string_ = stored_string_.substr(0, split_indx);
        childs_.clear();
        childs_.emplace(cut_off_part->stored_string_[0], cut_off_part);
    }
    void AddNewChild(std::string in_str, int num_list) {
        is_list_ = false;
        num_list_ = 0; // на всякий случай
        childs_.emplace(in_str[0], new SuffTreeNode(in_str, num_list));
    }
    void ForkNode(std::string in_str, int first_mismath, int num_list) {
        SplitNode(first_mismath);
        AddNewChild(in_str.substr(first_mismath), num_list);
    }
    void AddNewNode(std::string in_str, int num_list) {    
        int first_mismath = IndxOfFirstDiffFromStoredStr(in_str);
        if(first_mismath < stored_string_.length()) {
            ForkNode(in_str, first_mismath, num_list);
        } else {
            AddNewChild(in_str.substr(first_mismath), num_list);
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
    ~SuffTreeNode();
    void Insert(std::string in_str, int num_list) {
        if (IsPrefixOfChild(in_str)) {
            int first_mismath = IndxOfFirstDiffFromStoredStr(in_str);
            FindChildByPrefix(in_str)->Insert(in_str.substr(first_mismath), num_list);
        } else {
            AddNewNode(in_str, num_list);
        }
    }
};

#endif