#ifndef TREEELEM_H
#define TREEELEM_H

#include <memory>

#define SPTR(T) std::shared_ptr<T>
#define MakeSPTR(T) std::make_shared<T>

template <class Poligon>
class TreeElem{
public:
    TreeElem();
    TreeElem(const Poligon poligon);

    const Poligon& get_poligon() const;
    int get_count_fig() const;
    SPTR(TreeElem<Poligon>) get_left() const;
    SPTR(TreeElem<Poligon>) get_right() const;
    
    void set_poligon(const Poligon& poligon);
    void set_count_fig(const int count);
    void set_left(SPTR(TreeElem<Poligon>) to_left);
    void set_right(SPTR(TreeElem<Poligon>) to_right);

    virtual ~TreeElem();
private:
    SPTR(Poligon) polig;
    int count_fig;
    SPTR(TreeElem<Poligon>) t_left;
    SPTR(TreeElem<Poligon>) t_right;
};

#endif