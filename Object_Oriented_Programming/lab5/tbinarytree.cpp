#include "tbinarytree.h"
#include <stdexcept>

TBinaryTree::TBinaryTree() {
    t_root = nullptr;
}

void TBinaryTree::Push(const Octagon& octagon) {
    SPTR(TreeElem) curr = t_root;
    SPTR(TreeElem) OctSptr(new TreeElem(octagon));
    
    if (!curr)
    {
        t_root = OctSptr;
    }
    while (curr)
    {
        if (curr->get_octagon() == octagon)
        {
            curr->set_count_fig(curr->get_count_fig() + 1);
            return;
        }
        if (octagon.Area() < curr->get_octagon().Area())
            if (curr->get_left() == nullptr)
            {
                curr->set_left(OctSptr);
                return;
            }
        if (octagon.Area() >= curr->get_octagon().Area())
            if (curr->get_right() == nullptr && !(curr->get_octagon() == octagon))
            {
                curr->set_right(OctSptr);
                return;
            }
        if (curr->get_octagon().Area() > octagon.Area())
            curr = curr->get_left();
        else
            curr = curr->get_right();
    }
}

const Octagon& TBinaryTree::GetItemNotLess(double area) {
    SPTR(TreeElem) curr = t_root;
    while (curr)
    {
        if (area == curr->get_octagon().Area()) 
            return curr->get_octagon();
        if (area < curr->get_octagon().Area())
        {
            curr = curr->get_left();
            continue;
        }
        if (area >= curr->get_octagon().Area())
        {
            curr = curr->get_right();
            continue;
        }
    }
    throw std::out_of_range("out of range");
}

size_t TBinaryTree::Count(const Octagon& octagon) {
    size_t count = 0;
    SPTR(TreeElem) curr = t_root;
    
    while (curr)
    {
        if (curr->get_octagon() == octagon)
            count = curr->get_count_fig();
        if (octagon.Area() < curr->get_octagon().Area())
        {
            curr = curr->get_left();
            continue;
        }
        if (octagon.Area() >= curr->get_octagon().Area())
        {
            curr = curr->get_right();
            continue;
        }
    }
    return count;
}

void Pop_List(SPTR(TreeElem) curr, SPTR(TreeElem) parent);
void Pop_Part_of_Branch(SPTR(TreeElem) curr, SPTR(TreeElem) parent);
void Pop_Root_of_Subtree(SPTR(TreeElem) curr, SPTR(TreeElem) parent);
void TBinaryTree::Pop(const Octagon& octagon) {

    SPTR(TreeElem) curr = t_root;
    SPTR(TreeElem) parent = nullptr;

    while (curr && curr->get_octagon() != octagon)
    {
        parent = curr;
        if (curr->get_octagon().Area() > octagon.Area())
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

void Pop_List(SPTR(TreeElem) curr, SPTR(TreeElem) parent) {
    if (parent->get_left() == curr)
                parent->set_left(nullptr);
            else
                parent->set_right(nullptr);
}

void Pop_Part_of_Branch(SPTR(TreeElem) curr, SPTR(TreeElem) parent) {
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

void Pop_Root_of_Subtree(SPTR(TreeElem) curr, SPTR(TreeElem) parent) {
    SPTR(TreeElem) replace = curr->get_left();
    SPTR(TreeElem) rep_parent = curr;
    while (replace->get_right())
    {
        rep_parent = replace;
        replace = replace->get_right();
    }

    curr->set_octagon(replace->get_octagon());
    curr->set_count_fig(replace->get_count_fig());
    
    if (rep_parent->get_left() == replace)
        rep_parent->set_left(nullptr);
    else
        rep_parent->set_right(nullptr);
    return;
}

bool TBinaryTree::Empty() {
    return t_root == nullptr ? true : false;
}

void Tree_out (std::ostream& os, SPTR(TreeElem) curr);
std::ostream& operator<<(std::ostream& os, const TBinaryTree& tree) {
    SPTR(TreeElem) curr = tree.t_root;
    Tree_out(os, curr);
    return os;
}

void Tree_out (std::ostream& os, SPTR(TreeElem) curr) {
    if (curr)
    {
        if(curr->get_octagon().Area() >= 0) 
            os << curr->get_count_fig() << "*" << curr->get_octagon().Area();
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

void recursive_clear(SPTR(TreeElem) curr);
void TBinaryTree::Clear() {
    if (t_root->get_left())
        recursive_clear(t_root->get_left());
    t_root->set_left(nullptr);
    if (t_root->get_right())
        recursive_clear(t_root->get_right());
    t_root->set_right(nullptr);
    t_root = nullptr;
}

void recursive_clear(SPTR(TreeElem) curr){
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

TBinaryTree::~TBinaryTree() {
}
