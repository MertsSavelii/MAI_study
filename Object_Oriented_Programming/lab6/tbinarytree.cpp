#include "tbinarytree.h"
#include <stdexcept>

template <class Poligon>
TBinaryTree<Poligon>::TBinaryTree() {
    t_root = nullptr;
}

template <class Poligon>
void TBinaryTree<Poligon>::Push(const Poligon& octagon) {
    SPTR(TreeElem<Poligon>) curr = t_root;
    SPTR(TreeElem<Poligon>) OctSptr(new TreeElem<Poligon>(octagon));
    
    if (!curr)
    {
        t_root = OctSptr;
    }
    while (curr)
    {
        if (curr->get_poligon() == octagon)
        {
            curr->set_count_fig(curr->get_count_fig() + 1);
            return;
        }
        if (octagon.Area() < curr->get_poligon().Area())
            if (curr->get_left() == nullptr)
            {
                curr->set_left(OctSptr);
                return;
            }
        if (octagon.Area() >= curr->get_poligon().Area())
            if (curr->get_right() == nullptr && !(curr->get_poligon() == octagon))
            {
                curr->set_right(OctSptr);
                return;
            }
        if (curr->get_poligon().Area() > octagon.Area())
            curr = curr->get_left();
        else
            curr = curr->get_right();
    }
}

template <class Poligon>
const Poligon& TBinaryTree<Poligon>::GetItemNotLess(double area) {
    SPTR(TreeElem<Poligon>) curr = t_root;
    while (curr)
    {
        if (area == curr->get_poligon().Area()) 
            return curr->get_poligon();
        if (area < curr->get_poligon().Area())
        {
            curr = curr->get_left();
            continue;
        }
        if (area >= curr->get_poligon().Area())
        {
            curr = curr->get_right();
            continue;
        }
    }
    throw std::out_of_range("out of range");
}

template <class Poligon>
size_t TBinaryTree<Poligon>::Count(const Poligon& octagon) {
    size_t count = 0;
    SPTR(TreeElem<Poligon>) curr = t_root;
    
    while (curr)
    {
        if (curr->get_poligon() == octagon)
            count = curr->get_count_fig();
        if (octagon.Area() < curr->get_poligon().Area())
        {
            curr = curr->get_left();
            continue;
        }
        if (octagon.Area() >= curr->get_poligon().Area())
        {
            curr = curr->get_right();
            continue;
        }
    }
    return count;
}

template <class Poligon>
void Pop_List(SPTR(TreeElem<Poligon>) curr, SPTR(TreeElem<Poligon>) parent) {
    if (parent->get_left() == curr)
                parent->set_left(nullptr);
            else
                parent->set_right(nullptr);
}
template <class Poligon>
void Pop_Part_of_Branch(SPTR(TreeElem<Poligon>) curr, SPTR(TreeElem<Poligon>) parent) {
    if (parent) {
        if (curr->get_left()) {
            if (parent->get_left() == curr)
                parent->set_left(curr->get_left());

            if (parent->get_right() == curr)
                parent->set_right(curr->get_left());
    
            curr->set_right(nullptr);
            curr->set_left(nullptr);
            return;
        }

        if (curr->get_left() == nullptr) {
            if (parent && parent->get_left() == curr)
                parent->set_left(curr->get_right());

            if (parent && parent->get_right() == curr)
                parent->set_right(curr->get_right());

            curr->set_right(nullptr);
            curr->set_left(nullptr);
            return;
        }
    }
}
template <class Poligon>
void Pop_Root_of_Subtree(SPTR(TreeElem<Poligon>) curr, SPTR(TreeElem<Poligon>) parent) {
    SPTR(TreeElem<Poligon>) replace = curr->get_left();
    SPTR(TreeElem<Poligon>) rep_parent = curr;
    while (replace->get_right())
    {
        rep_parent = replace;
        replace = replace->get_right();
    }

    curr->set_poligon(replace->get_poligon());
    curr->set_count_fig(replace->get_count_fig());
    
    if (rep_parent->get_left() == replace)
        rep_parent->set_left(nullptr);
    else
        rep_parent->set_right(nullptr);
    return;
}
template <class Poligon>
void TBinaryTree<Poligon>::Pop(const Poligon& octagon) {

    SPTR(TreeElem<Poligon>) curr = t_root;
    SPTR(TreeElem<Poligon>) parent = nullptr;

    while (curr && curr->get_poligon() != octagon)
    {
        parent = curr;
        if (curr->get_poligon().Area() > octagon.Area())
            curr = curr->get_left();
        else
            curr = curr->get_right();
    }

    if (curr == nullptr)
        return;

    curr->set_count_fig(curr->get_count_fig() - 1);

    if(curr->get_count_fig() <= 0)
    {
        if (curr->get_left() == nullptr && curr->get_right() == nullptr)
        {
            Pop_List(curr, parent);
            return;
        }
        if (curr->get_left() == nullptr || curr->get_right() == nullptr)
        {
            Pop_Part_of_Branch(curr, parent);
            return;
        }
        if (curr->get_left() != nullptr && curr->get_right() != nullptr)
        {
           Pop_Root_of_Subtree(curr, parent);
           return;
        }
    }
}

template <class Poligon>
bool TBinaryTree<Poligon>::Empty() {
    return t_root == nullptr ? true : false;
}

template <class Poligon>
void Tree_out (std::ostream& os, SPTR(TreeElem<Poligon>) curr) {
    if (curr)
    {
        if(curr->get_poligon().Area() >= 0) 
            os << curr->get_count_fig() << "*" << curr->get_poligon().Area();
        if(curr->get_left() || curr->get_right()) 
        {
            os << ": [";
            if (curr->get_left())
                Tree_out(os, curr->get_left());
            if(curr->get_left() && curr->get_right())
                os << ", ";
            if (curr->get_right())
                Tree_out(os, curr->get_right());
            os << "]";
        }
    }
}
template <class A>
std::ostream& operator<<(std::ostream& os, const TBinaryTree<A>& tree) {
    SPTR(TreeElem<A>) curr = tree.t_root;
    Tree_out(os, curr);
    return os;
}

template <class Poligon>
void recursive_clear(SPTR(TreeElem<Poligon>) curr){
    if(curr)
    {
        if (curr->get_left())
            recursive_clear(curr->get_left());
        curr->set_left(nullptr);
        if (curr->get_right())
            recursive_clear(curr->get_right());
        curr->set_right(nullptr);
    }
}
template <class Poligon>
void TBinaryTree<Poligon>::Clear() {
    if (t_root->get_left())
        recursive_clear(t_root->get_left());
    t_root->set_left(nullptr);
    if (t_root->get_right())
        recursive_clear(t_root->get_right());
    t_root->set_right(nullptr);
    t_root = nullptr;
}

template <class Poligon>
TBinaryTree<Poligon>::~TBinaryTree() {
}

#include "octagon.h"
template class TBinaryTree<Octagon>;
template std::ostream& operator<<(std::ostream& os, const TBinaryTree<Octagon>& stac);