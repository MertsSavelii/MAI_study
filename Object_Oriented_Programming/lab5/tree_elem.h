#ifndef TREEELEM_H
#define TREEELEM_H

#include <memory>
#include "octagon.h"

#define SPTR(T) std::shared_ptr<T>
#define MakeSPTR(T) std::make_shared<T>

class TreeElem{
public:
    TreeElem();
    TreeElem(const Octagon octagon);

    const Octagon& get_octagon() const;
    int get_count_fig() const;
    SPTR(TreeElem) get_left() const;
    SPTR(TreeElem) get_right() const;
    
    void set_octagon(const Octagon& octagon);
    void set_count_fig(const int count);
    void set_left(SPTR(TreeElem) to_left);
    void set_right(SPTR(TreeElem) to_right);

    virtual ~TreeElem();
private:
    SPTR(Octagon) octi;
    int count_fig;
    SPTR(TreeElem) t_left;
    SPTR(TreeElem) t_right;
};

#endif