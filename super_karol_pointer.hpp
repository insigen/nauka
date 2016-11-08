#ifndef SUPER_KAROL_POINTER_HPP
#define SUPER_KAROL_POINTER_HPP

#include "karol_pointer.hpp"


template<typename T>
class super_karol_pointer :public  karol_pointer<T>
{
public:
    super_karol_pointer();
    super_karol_pointer(T tt) : karol_pointer<T>(tt) {}
    super_karol_pointer(const super_karol_pointer<T>& skp) : karol_pointer<T>(skp) {}
};

////specjalizacja klasy
//template<>
//class super_karol_pointer<int>
//{

//}
//specjalnizacja czesciowa
template<typename T>
class super_karol_pointer<T[]> : public karol_pointer<T, deallocate_array<T>>
{
public:
    super_karol_pointer();
    super_karol_pointer(int size);
    super_karol_pointer(const super_karol_pointer<T[]>& skp) : karol_pointer<T>(skp) {}
    T& operator[](int idx);
    ~super_karol_pointer();
};

template<typename T>
super_karol_pointer<T[]>::super_karol_pointer(int size)
{
   karol_pointer<T, deallocate_array<T>>::wsk = new T[size];
   karol_pointer<T, deallocate_array<T>>::createRefCounter();
   karol_pointer<T, deallocate_array<T>>::incrementRefCounter();
}

template<typename T>
T& super_karol_pointer<T[]>::operator[](int idx)
{
    return karol_pointer<T, deallocate_array<T>>::wsk[idx];
}

template<typename T>
super_karol_pointer<T[]>::~super_karol_pointer()
{
    cout << "destruktor super karol pointer" << endl;
}

#endif // SUPER_KAROL_POINTER_HPP
