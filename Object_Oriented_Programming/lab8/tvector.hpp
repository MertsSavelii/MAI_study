#ifndef TVECTOR_H
#define TVECTOR_H

#include <iostream>
#include "iterator.hpp"
#include <memory>
#define SPTR(T) std::shared_ptr<T>

template <class Polygon>
class TVector
{
public:
    // Конструктор по умолчанию
    TVector();
    // изменение размера массива
    void Resize(size_t nsize);
    // Конструктор копирования
    TVector(const TVector& other);
    // Метод, добавляющий фигуру в конец массива
    void InsertLast(const Polygon& polygon);
    // Метод, удаляющий последнюю фигуру массива
    void RemoveLast();
    // Метод, возвращающий последнюю фигуру массива
    const Polygon& Last();
    // Перегруженный оператор обращения к массиву по индексу
    const SPTR(Polygon) operator[] (const size_t idx);
    // Метод, проверяющий пустоту
    bool Empty();
    // Метод, возвращающий длину массива
    size_t Length();
    // Оператор вывода для массива в формате:
    // "[S1 S2 ... Sn]", где Si - площадь фигуры
    template <class T>
    friend std::ostream& operator<<(std::ostream& os, const TVector<T>& arr);
    // Метод, удаляющий все элементы контейнера,
    // но позволяющий пользоваться им.
    void Clear();
    // Итератор начала
    Iterator<Polygon> begin(){
        return Iterator<Polygon>(data);
    }
    // Итератор конца
    Iterator<Polygon> end(){
        return Iterator<Polygon>(data + size);
    }
    
    // Деструктор
    virtual ~TVector();
private:
    int size;
    SPTR(Polygon)* data;
};

#endif


template <class Polygon>
TVector<Polygon>::TVector(){
    size = 1;
    data = new SPTR(Polygon)[size];
}

template <class Polygon>
void TVector<Polygon>::Resize(size_t nsize){
	if(nsize == size)
        return;
    else{
        SPTR(Polygon)* ndata = new SPTR(Polygon)[nsize];
        for (int i = 0; i < (size < nsize ? size : nsize); i++)
            ndata[i] = data[i];
        delete[] data;
        data = ndata;
        size = nsize;
    }
}

template <class Polygon>
TVector<Polygon>::TVector(const TVector& other){
	size = other.size;
    data = new SPTR(Polygon)[other.size];
    for (int i = 0; i < size; i++)
        data[i] = other.data[i];
}

template <class Polygon>
void TVector<Polygon>::InsertLast(const Polygon& polygon){
	if (data[size - 1] != nullptr)
        Resize(size+1);
    data[size - 1] = std::make_shared<Polygon>(polygon);
}

template <class Polygon>
void TVector<Polygon>::RemoveLast(){
	data[size-1]=nullptr;
}

template <class Polygon>
const Polygon& TVector<Polygon>::Last(){
	return *(data[size - 1]);
}

template <class Polygon>
const SPTR(Polygon) TVector<Polygon>::operator[] (const size_t idx){
    if (idx >= 0 && idx < size)
        return data[idx];
    exit(1);
}

template <class Polygon>
bool TVector<Polygon>::Empty(){
	return size == 0;
}

template <class Polygon>
size_t TVector<Polygon>::Length(){
	return size;
}

template <class Polygon>
std::ostream& operator<<(std::ostream& os, const TVector<Polygon>& arr){
    os << '[';
	for (size_t i = 0; i < arr.size; i++)
        os << (arr.data[i])->Area() << ((i != arr.size-1) ? ' ' : '\0');
    os << ']';
    return os;
}

template <class Polygon>
void TVector<Polygon>::Clear(){
	delete[] data;
    size = 1;
    data = new SPTR(Polygon)[size];
}

template <class Polygon>
TVector<Polygon>::~TVector(){
    delete[] data;
}