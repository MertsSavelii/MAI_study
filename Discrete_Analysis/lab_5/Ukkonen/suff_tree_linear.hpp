#ifndef SUFF_TREE_HPP
#define SUFF_TREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define TERMINATION_SYMBOL '$'

using namespace std;

class SuffixTree;

class Node
{
    private:
        map<char, Node*> kinder_; // "массив" детей
        Node *suffix_link_;          // суффиксная ссылка
        int start_;                  // номер первого символа вершины в тексте
        int *end_;                   // номер последнего символа вершины в тексте
        int suffix_index_;           // номер суффикса
    public:
        friend SuffixTree;
        Node(Node *link, int start_, int *end) {
            Node(link, start_, end, -1);
        }
        Node(Node *link, int start_, int *end, int ind) {
            suffix_link_ = link;
            start_ = start_;
            end_ = end;
            suffix_index_ = ind;
        }
};

class SuffixTree
{
    private:
        Node *root_ = new Node(nullptr, -1, new int(-1));    // корень
        Node *last_created_internal_node_ = nullptr;         // последняя созданная внутрення вершина

        string text_; // текст, по которому строится суфтри

        Node *active_node_ = nullptr;    // то, откуда начнется расширение на следующей фазе
        int active_edge_ = -1;           // индекс символа, который задает движение из текущей ноды
        int active_length_ = 0;          // на сколько символов ступаем в направлении active_edge_
        int remaining_suffix_count_ = 0; // сколько суффиксов осталось создать. по сути, сколько суффиксов на прошлом шаге мы не создали.
        int leaf_end_ = -1;              // глобальная переменная, определяет содержимое листьев: её инкремент как бы приписывает новый символ к ним

        void DeleteSuffixTree(Node *node) {
            for (auto it : node->kinder_)
                DeleteSuffixTree(it.second);
            if (node->suffix_index_ == -1)
                delete node->end_;
            delete node;
        }
        void CountIndex(Node *node, vector<int> &vec)
        {
            if (!node)
                return;
            for (auto it : node->kinder_)
                CountIndex(it.second, vec);
            if (node->suffix_index_ != -1)
                vec.push_back(node->suffix_index_);
        }
        int EdgeLength(Node *node)
        {
            return *(node->end_) - (node->start_) + 1;
        }
        void ExtendSuffixTree(int phase)
        {
            last_created_internal_node_ = nullptr;
            leaf_end_++;
            remaining_suffix_count_++;

            while (remaining_suffix_count_ > 0)
            {
                // если active_length_ равна 0, тогда ищем текущий символ из корня
                if (active_length_ == 0)
                    active_edge_ = phase; // индекс текущего символа в тексте определяет дугу, по которой будем двигаться

                // ищем текущий символ в начале исходящих из active_node_ дуг
                auto find = active_node_->kinder_.find(text_[active_edge_]);

                // не нашли
                if (find == active_node_->kinder_.end())
                {
                    // AddChild();
                    // добавим новую листовую дугу, исходящую из active_node_, начинающуся текущим символом
                    active_node_->kinder_.insert(make_pair(text_[active_edge_], 
                                                  new Node(root_, phase, &leaf_end_, phase - remaining_suffix_count_ + 1)));
                    // и коль скоро создали новую внутр. вершинку, установим на нее суффлинку последней созданной внутренней вершины
                    if (last_created_internal_node_ != nullptr)
                    {
                        last_created_internal_node_->suffix_link_ = active_node_;
                        last_created_internal_node_ = nullptr;
                    }
                }
                else
                {
                    // а если-таки есть дуга из active_node_, начинающаяся текущим символом, пойдем по ней спускаться
                    Node *next = find->second;
                    int edge_length = EdgeLength(next);

                    // спуск по дуге(-ам)
                    if (active_length_ >= edge_length)
                    {
                        active_edge_ += edge_length;
                        active_length_ -= edge_length;
                        active_node_ = next;
                        continue; // таким образом мы будем спускаться, покуда не станет active_length_ < edge_length
                    }

                    // правило 3: если текущий символ есть на дуге,
                    // т.е. суффикс уже есть в дереве, то просто увеличим active_length_
                    // как бы "шагнем вперед" по дуге
                    if (text_[next->start_ + active_length_] == text_[phase])
                    {
                        // если last_created_internal_node_ != null
                        // это означает, что 2-е правило было применено ранее (создание новой вн. вершины)
                        // установим суффлинку в active_node_
                        if (last_created_internal_node_ != nullptr && active_node_ != root_)
                            last_created_internal_node_->suffix_link_ = active_node_;
                        active_length_++;
                        break; // выйдем из цикла while
                    }

                    // сюда попали, если текущего символа нет на дуге
                    // создадим новую внутреннюю вершинку
                    Node *split = new Node(root_, next->start_, new int(next->start_ + active_length_ - 1));
                    // подвесим к active_node_ новую вершинку
                    active_node_->kinder_[text_[active_edge_]] = split;
                    // у "следующей" вершинки изменим, очевидно, начало, ибо мы ее "обрубили"
                    next->start_ += active_length_;
                    // подвесим новую листовую вершинку
                    split->kinder_.insert(make_pair(text_[phase], new Node(root_, phase, &leaf_end_, phase - remaining_suffix_count_ + 1)));
                    // подвесим отрубленную вершинку
                    split->kinder_.insert(make_pair(text_[next->start_], next));
                    // и не забудем про установку ссылок при создании новой внутренней вершины
                    if (last_created_internal_node_ != nullptr)
                        last_created_internal_node_->suffix_link_ = split;
                    last_created_internal_node_ = split;
                }

                remaining_suffix_count_--;

                // если active_node_ == root_, тогда согласно правилу 2, мы декр. active_length_ и инкр. active_edge_
                // это, можно сказать, альтернатива суфф. ссылке в случае, когда active_node_ == root_
                if (active_node_ == root_ && active_length_ > 0)
                {
                    active_length_--;
                    active_edge_++;
                }
                else if (active_node_ != root_) // если же active_node_ != root_, то радостно скачем по имеющейся суффиксной ссылке
                    active_node_ = active_node_->suffix_link_;
            }
        }
    public:
        SuffixTree(string &text_) {
            text_ = text_ + TERMINATION_SYMBOL;
            active_node_ = root_;
            for (size_t i = 0; i < text_.length(); i++)
                ExtendSuffixTree(i);
        }
        void BuildSuffixTree();
        ~SuffixTree() {
            DeleteSuffixTree(root_);
        }
};

#endif