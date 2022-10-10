#ifndef T_B_SUFF_TREE_HPP
#define T_B_SUFF_TREE_HPP

#include <vector>
#include <map>
#include <string>

std::string stored_str;
std::string find_str;

class SuffTree;
class SuffTreeNode
{
private:
    unsigned stored_start_, stored_finish_, num_list_;
    std::map<char, SuffTreeNode*> child_;

    unsigned MaxPrefix(unsigned fst_start, unsigned fst_finish, unsigned sec_start, unsigned sec_finish)
    {
        for(int i = 0; i < fst_finish - fst_start; i++)
        {
            if(i == sec_finish - sec_start || find_str[i] != stored_str[sec_start + i]) 
                return i;
        }
        return fst_finish - fst_start;
    }
    void Split(unsigned split_indx)
    {
        SuffTreeNode* new_child = new SuffTreeNode(split_indx, stored_finish_, num_list_);
        new_child->child_ = child_;
        child_.emplace(stored_str[new_child->stored_start_], new_child) ;
        stored_finish_ = split_indx;
        num_list_ = 0;
    }
    void FindAllListsInChild(std::vector<unsigned>& ans)
    {
        for(auto it = child_.begin(); it != child_.end(); ++it)
            it->second->FindAllListsInChild(ans);
        if(num_list_ != 0)
            ans.push_back(num_list_);
    }
    void Insert(unsigned in_start, unsigned in_finish, unsigned in_num_list)
    { 
        find_str = stored_str.substr(in_start, in_finish);
        unsigned max_prefix_indx = MaxPrefix(in_start, in_finish, stored_start_, stored_finish_);
        auto find = child_.find(find_str[max_prefix_indx]);

        if(find != child_.end())
            find->second->Insert(in_start + max_prefix_indx, in_finish, in_num_list);
        else
        {
            if(max_prefix_indx <= in_finish - in_start)
                Split(max_prefix_indx + stored_start_);
            num_list_ = 0;
            child_.emplace(find_str[max_prefix_indx], new SuffTreeNode(in_start + max_prefix_indx, in_finish, in_num_list));
        }
    }
    void Find(std::string in_str, std::vector<unsigned>& ans)
    {
        find_str = in_str;
        unsigned max_prefix_indx = MaxPrefix(0, in_str.length(), stored_start_, stored_finish_);
        if(max_prefix_indx == in_str.length())
        {
            FindAllListsInChild(ans);
            return;
        }
        if(max_prefix_indx < stored_finish_ - stored_start_)
        {
            return;
        }
        auto find = child_.find(find_str[max_prefix_indx]);
        if(find == child_.end())
        {
            return;
        }
        find->second->Find(in_str.substr(max_prefix_indx), ans);
    }
public:
    friend SuffTree;
    SuffTreeNode(unsigned in_start, unsigned in_finish, unsigned in_num_list)
    {
        stored_start_ = in_start;
        stored_finish_ = in_finish;
        num_list_ = in_num_list;
    }
    ~SuffTreeNode()
    {
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