#ifndef T_B_SUFF_TREE_HPP
#define T_B_SUFF_TREE_HPP

#include <vector>
#include <string>

std::string stored_str;
std::string find_str;

class SuffTreeNode
{
private:
    unsigned stored_start_, stored_finish_, num_list_;
    SuffTreeNode* next_bro_;
    SuffTreeNode* child_;

    unsigned MaxPrefix(unsigned fst_start, unsigned fst_finish, unsigned sec_start, unsigned sec_finish)
    {
        for(int i = 0; i < fst_finish - fst_start; i++)
        {
            if(i == sec_finish - sec_start 
            || find_str[i] != stored_str[sec_start + i]) return i;
        }
        return fst_finish - fst_start;
    }
    void Split(unsigned split_indx)
    {
        SuffTreeNode* new_child = new SuffTreeNode(split_indx, stored_finish_, num_list_);
        new_child->child_ = child_;
        child_ = new_child;
        stored_finish_ = split_indx;
        num_list_ = 0;
    }
    void FindAllListsInChild(std::vector<unsigned>& ans)
    {
        if(child_ == nullptr)
        {
            ans.push_back(num_list_);
        }
        if(child_ != nullptr) child_->FindAllListsInChild(ans);
        if(next_bro_ != nullptr) next_bro_->FindAllListsInChild(ans);
    }
public:
    SuffTreeNode(unsigned in_start, unsigned in_finish, unsigned in_num_list)
    {
        stored_start_ = in_start;
        stored_finish_ = in_finish;
        num_list_ = in_num_list;
        next_bro_ = nullptr;
        child_ = nullptr;
    }
    ~SuffTreeNode()
    {
        delete next_bro_;
        delete child_;
    }
    void Insert(unsigned in_start, unsigned in_finish, unsigned in_num_list)
    {
        find_str = stored_str.substr(in_start, in_finish);
        if(stored_str[in_start] != stored_str[stored_start_])
        {
            if(next_bro_ == nullptr) next_bro_ = new SuffTreeNode(in_start, in_finish, in_num_list);
            else next_bro_->Insert(in_start, in_finish, in_num_list);
        }
        else 
        {
            unsigned max_prefix_indx = MaxPrefix(in_start, in_finish, stored_start_, stored_finish_);
            if(max_prefix_indx < in_finish - in_start)
            {
                if(max_prefix_indx < stored_finish_ - stored_start_) Split(max_prefix_indx + stored_start_);
                if(child_ == nullptr) child_ = new SuffTreeNode(in_start + max_prefix_indx, in_finish, in_num_list);
                else child_->Insert(in_start + max_prefix_indx, in_finish, in_num_list);
            }
        }
    }
    void Find(std::string in_str, std::vector<unsigned>& ans)
    {
        find_str = in_str;
        if(find_str[0] != stored_str[stored_start_])
        {
            if(next_bro_ == nullptr) return;
            else next_bro_->Find(in_str, ans);
            return;
        }
        unsigned max_prefix_indx = MaxPrefix(0, in_str.length(), stored_start_, stored_finish_);
        if(max_prefix_indx == in_str.length())
        {
            if(child_!=nullptr) child_->FindAllListsInChild(ans);
            else ans.push_back(num_list_);
            return;
        }
        if(max_prefix_indx == stored_finish_ - stored_start_)
        {
            if(child_ == nullptr) return;
            else child_->Find(in_str.substr(max_prefix_indx), ans);
            return;
        }
    }
};

class SuffTree
{
    private:
        SuffTreeNode* root;
    public:
    SuffTree() { root = nullptr; }
    ~SuffTree() { delete root; }
    void Insert(std::string in_str)
    {
        in_str += '$';
        stored_str = in_str;
        for(int i = 0; i < in_str.length(); ++i)
        {
            if(root == nullptr) root = new SuffTreeNode(i, in_str.length(), i + 1);
            else root->Insert(i, in_str.length(), i + 1);
        }
    }
    void Find(std::string in_str, std::vector<unsigned>& ans)
    {
        if(root == nullptr) return;
        else root->Find(in_str, ans);
    }
};

#endif