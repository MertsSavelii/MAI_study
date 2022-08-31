#include <iostream>
#include <memory>
#include "tree_elem.h"


TreeElem::TreeElem() {
    octi = nullptr;
    count_fig = 0;
    t_left = nullptr;
    t_right = nullptr;
}

TreeElem::TreeElem(const Octagon octagon) {
    octi = MakeSPTR(Octagon)(octagon);
    count_fig = 1;
    t_left = nullptr;
    t_right = nullptr;
}

const Octagon& TreeElem::get_octagon() const{
    return *octi;
}
int TreeElem::get_count_fig() const{
    return count_fig;
}
SPTR(TreeElem) TreeElem::get_left() const{
    return t_left;
}
SPTR(TreeElem) TreeElem::get_right() const{
    return t_right;
}

void TreeElem::set_octagon(const Octagon& octagon){
    octi = MakeSPTR(Octagon)(octagon);
}
void TreeElem::set_count_fig(const int count) {
    count_fig = count;
}
void TreeElem::set_left(SPTR(TreeElem) to_left) {
    t_left = to_left;
}
void TreeElem::set_right(SPTR(TreeElem) to_right) {
    t_right = to_right;
}

TreeElem::~TreeElem() {
}