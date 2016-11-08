#include <exception>
#include <memory>
#include <iostream>

#ifndef KAROL_POINTER_HPP
#define KAROL_POINTER_HPP
using namespace std;


namespace {
template<typename T>
void deallocate_single(T* p)
{
    delete p;
    p = nullptr;
    cout << "wywolanie deallocator single" << endl;
}

template<typename T>
void deallocate_array(T* p)
{
    delete [] p;
    p = nullptr;
    cout << "wywoalnie deallocator array" << endl;
}
}

template<typename T>
using deallocator_ptr = void(*)(T*);

template<typename T, deallocator_ptr<T> dealloc = deallocate_single<T> >
class karol_pointer
{
public:
    karol_pointer();
    karol_pointer(T a);
    karol_pointer(const karol_pointer<T, dealloc>& kp);
    karol_pointer<T, dealloc >& operator=(const karol_pointer<T,dealloc>& kp);
    T& operator*();
    virtual ~karol_pointer();

protected:
    T* wsk {nullptr};
    long* m_refCounter {nullptr};
    void createRefCounter();
    void incrementRefCounter();
    void decrementRefCounter();

//    1.zarzadzanie pamiecia
//    2.increment
//    3.
};

template<typename T, deallocator_ptr<T> dealloc>
void karol_pointer<T, dealloc>::createRefCounter()
{
    m_refCounter = new long(0);
}

template<typename T, deallocator_ptr<T> dealloc>
void karol_pointer<T, dealloc>::incrementRefCounter()
{
    ++(*m_refCounter);
    cout << "plus " << *m_refCounter << endl;
}
template<typename T, deallocator_ptr<T> dealloc>
void karol_pointer<T, dealloc>::decrementRefCounter()
{
    --(*m_refCounter);
    cout<<"minus!. " << *m_refCounter << "\n";
    if(*m_refCounter == 0)
    {
        delete m_refCounter;
        m_refCounter = nullptr;
        cout << "po kasowaniu\n";
    }
}

template<typename T, deallocator_ptr<T> dealloc>
karol_pointer<T, dealloc>::karol_pointer()
{

}

template<typename T, deallocator_ptr<T> dealloc>
karol_pointer<T, dealloc>::karol_pointer(T a)
{
    try
    {
        wsk = new T(a);
    }
    catch(bad_alloc& ex)
    {
        cout << ex.what() << endl;
        wsk = nullptr;
    }
    createRefCounter();
    incrementRefCounter();
}

template<typename T, deallocator_ptr<T> dealloc>
karol_pointer<T, dealloc>::karol_pointer(const karol_pointer<T, dealloc> &kp)
{
    m_refCounter = kp.m_refCounter;
    wsk = kp.wsk;
    incrementRefCounter();
}

template<typename T, deallocator_ptr<T> dealloc>
karol_pointer<T,dealloc> &karol_pointer<T, dealloc>::operator =(const karol_pointer<T, dealloc>& kp)
{
    m_refCounter = kp.m_refCounter;
    wsk = kp.wsk;
    incrementRefCounter();
}

template<typename T, deallocator_ptr<T> dealloc>
T& karol_pointer<T, dealloc>::operator *()
{
    return *wsk;
}

template<typename T, deallocator_ptr<T> dealloc>
karol_pointer<T, dealloc>::~karol_pointer()
{
    cout << "destruktor karol pointer" << endl;
    decrementRefCounter();
    if(m_refCounter == nullptr)
        dealloc(wsk);
}

#endif // KAROL_POINTER_HPP

