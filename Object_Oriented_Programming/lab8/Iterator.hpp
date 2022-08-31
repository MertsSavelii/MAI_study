#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <memory>

template <class Poligon>
class Iterator {
public:
    Iterator(std::shared_ptr<Poligon>* n){ 
        iter = n;
    }
    Poligon operator*(){ 
        return *(*iter);
    }
    Poligon operator->(){ 
        return *(*iter);
    }
    void operator++(){ 
        iter += 1;
    }
    Iterator operator++(int){
        Iterator iter(*this);
        ++(*this);
        return iter;
    }
    bool operator==(Iterator const& i) const{ 
        return iter == i.iter;
    }
    bool operator!=(Iterator const& i) const{ 
        return iter != i.iter;
    }

private:
    std::shared_ptr<Poligon>* iter;
};

#endif
