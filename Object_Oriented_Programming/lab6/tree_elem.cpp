#include <iostream>
#include <memory>
#include "tree_elem.h"

template <class Poligon>
TreeElem<Poligon>::TreeElem() {
    polig = nullptr;
    count_fig = 0;
    t_left = nullptr;
    t_right = nullptr;
}

template <class Poligon>
TreeElem<Poligon>::TreeElem(const Poligon poligon) {
    polig = MakeSPTR(Poligon)(poligon);
    count_fig = 1;
    t_left = nullptr;
    t_right = nullptr;
}

template <class Poligon>
const Poligon& TreeElem<Poligon>::get_poligon() const{
    return *polig;
}
template <class Poligon>
int TreeElem<Poligon>::get_count_fig() const{
    return count_fig;
}
template <class Poligon>
SPTR(TreeElem<Poligon>) TreeElem<Poligon>::get_left() const{
    return t_left;
}
template <class Poligon>
SPTR(TreeElem<Poligon>) TreeElem<Poligon>::get_right() const{
    return t_right;
}

template <class Poligon>
void TreeElem<Poligon>::set_poligon(const Poligon& poligon){
    polig = MakeSPTR(Poligon)(poligon);
}
template <class Poligon>
void TreeElem<Poligon>::set_count_fig(const int count) {
    count_fig = count;
}
template <class Poligon>
void TreeElem<Poligon>::set_left(SPTR(TreeElem<Poligon>) to_left) {
    t_left = to_left;
}
template <class Poligon>
void TreeElem<Poligon>::set_right(SPTR(TreeElem<Poligon>) to_right) {
    t_right = to_right;
}

template <class Poligon>
TreeElem<Poligon>::~TreeElem() {
}

#include "octagon.h"
template class TreeElem<Octagon>;