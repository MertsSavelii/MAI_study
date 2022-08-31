#ifndef ITEM2_H
#define ITEM2_H

#include <memory>

class Item2 {
public:
    Item2(void *ptr);

    Item2* to_right(Item2* next);
    Item2* Next();
    void* GetItem();

    virtual ~Item2();
private:
    void* link;
    Item2* next;
};

#endif // ITEM2_H

Item2::Item2(void* link) {
    this->link = link;
    this->next = nullptr;
}

Item2* Item2::to_right(Item2* next) {
    Item2* set = this->next;
    this->next = next;
    return set;
}

Item2* Item2::Next() {
    return this->next;
}

void* Item2::GetItem() {
    return this->link;
}

Item2::~Item2() {}