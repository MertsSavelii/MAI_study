#ifndef TREEELEM_H
#define TREEELEM_H

#include <memory>
#include "octagon.h"


class TreeElem{
public:
    TreeElem();
    TreeElem(const Octagon octagon);

    const Octagon& get_octagon() const;
    int get_count_fig() const;
    TreeElem* get_left() const;
    TreeElem* get_right() const;
    
    void set_octagon(const Octagon& octagon);
    void set_count_fig(const int count);
    void set_left(TreeElem* to_left);
    void set_right(TreeElem* to_right);

    virtual ~TreeElem();
private:
    Octagon octi;
    int count_fig;
    TreeElem* t_left;
    TreeElem* t_right;
};

#endif