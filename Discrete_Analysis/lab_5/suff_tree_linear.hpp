#pragma once

#include <string>
#include <vector>
#include <map>

#define SENTINEL '$'

using namespace std;

class SuffixTree;

class Node
{
private:
    map<char, Node*> children_;
    Node* suffix_link_;
    int start_;
    int* end_;
    int suffix_index_;
public:
    friend SuffixTree;
    Node(Node* in_suff_link, int in_start, int* in_end, int in_ind)
    {
        suffix_link_ = in_suff_link;
        start_ = in_start;
        end_ = in_end;
        suffix_index_ = in_ind;
    }
};

class SuffixTree
{
private:
    Node *root_ = new Node(nullptr, -1, new int(-1), -1);
    Node *last_created_internal_node_ = nullptr;

    string text_;

    Node *active_node_ = nullptr;
    int active_edge_ = -1;
    int active_length_ = 0;
    int remaining_suffix_count_ = 0;
    int leaf_end_ = -1;

    int MaxPrefix(string& in_str)
    {
        for(int i = 0; i < in_str.length(); ++i)
        {
            if(i == EdgeLength(active_node_) || in_str[i] != text_[i + active_node_->start_])
                return i;
        }
        return in_str.length();
    }
    void DeleteSuffixTree(Node *node)
    {
        for (auto it : node->children_)
            DeleteSuffixTree(it.second);
        if (node->suffix_index_ == -1)
            delete node->end_;
        delete node;
    }
    void CountIndex(Node *node, vector<int> &vec)
    {
        if (!node)
            return;
        for (auto it : node->children_)
            CountIndex(it.second, vec);
        if (node->suffix_index_ != -1)
            vec.push_back(node->suffix_index_);
    }
    int EdgeLength(Node *node)
    {
        return *(node->end_) - (node->start_) + 1;
    }
    void CreateSuffixLink(Node* internal_node)
    {
        if (last_created_internal_node_ != nullptr && active_node_ != root_)
            last_created_internal_node_->suffix_link_ = internal_node;
    }
    void AddNewChild(int& pos)
    {
        active_node_->children_.emplace(
            text_[active_edge_],
            new Node(root_, pos, &leaf_end_, pos - remaining_suffix_count_ + 1));
        CreateSuffixLink(active_node_);
        last_created_internal_node_ = nullptr;
    }
    Node* SplitNode(int split_indx, Node* splited_node)
    {
        Node *new_internal_node = new Node(root_, splited_node->start_, new int(splited_node->start_ + active_length_ - 1), -1);
        active_node_->children_[text_[active_edge_]] = new_internal_node;
        splited_node->start_ += active_length_;
        new_internal_node->children_.emplace(text_[split_indx], 
                                 new Node(root_, split_indx, &leaf_end_, split_indx - remaining_suffix_count_ + 1));
        new_internal_node->children_.emplace(text_[splited_node->start_], splited_node);
        CreateSuffixLink(new_internal_node);
        last_created_internal_node_ = new_internal_node;
        return new_internal_node;
    }
    void ExtendSuffixTree(int pos)
    {
        last_created_internal_node_ = nullptr;
        leaf_end_++;
        remaining_suffix_count_++;

        while (remaining_suffix_count_ > 0)
        {
            if (active_length_ == 0)
                active_edge_ = pos;
            auto find = active_node_->children_.find(text_[active_edge_]);

            if (find == active_node_->children_.end())
                AddNewChild(pos);
            else
            {
                Node *next = find->second;
                int edge_length = EdgeLength(next);

                // спуск по дуге(-ам)
                if (active_length_ >= edge_length)
                {
                    active_edge_ += edge_length;
                    active_length_ -= edge_length;
                    active_node_ = next;
                    continue;
                }

                // правило 3: если текущий символ есть на дуге,
                // т.е. суффикс уже есть в дереве, то просто увеличим activeLength
                // как бы "шагнем вперед" по дуге
                if (text_[next->start_ + active_length_] == text_[pos])
                {
                    CreateSuffixLink(active_node_);
                    active_length_++;
                    break;
                }
                SplitNode(pos, next);
            }

            remaining_suffix_count_--;

            // это, можно сказать, альтернатива суфф. ссылке в случае, когда activeNode == root
            if (active_node_ == root_ && active_length_ > 0)
            {
                active_length_--;
                active_edge_++;
            }
            else if (active_node_ != root_) // если же activeNode != root, то радостно скачем по имеющейся суффиксной ссылке
                active_node_ = active_node_->suffix_link_;
        }
    }
public:
    SuffixTree(string &in_text)
    {
        text_ = in_text + SENTINEL;
        BuildSuffixTree();
    }
    void BuildSuffixTree()
    {
        active_node_ = root_;
        for (size_t i = 0; i < text_.length(); i++)
            ExtendSuffixTree(i);
    }
    void FindSubStr(string& in_str, vector<int>& ans)
    {
        active_node_ = root_;
        int max_prefix = 0;
        while (in_str.length() > 0)
        {
            for(int i = 0; i < in_str.length(); ++i)
            {
                if(i == EdgeLength(active_node_) || active_node_ == root_)
                {
                    in_str = in_str.substr(max_prefix);
                    auto find = active_node_->children_.find(in_str[0]);
                    if(find == active_node_->children_.end())
                        return;
                    active_node_ = find->second;
                    break;
                }
                if(in_str[i] != text_[i + active_node_->start_])
                    return;
            }
            CountIndex(active_node_, ans);
            return;
        }
        active_node_ = root_;
    }
    ~SuffixTree()
    {
        DeleteSuffixTree(root_);
    }
};