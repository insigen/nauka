#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>

#pragma once


class lista_osob
{
public:
    lista_osob() = default;
    void add(osoba dodawana);
    bool remove(const string & imie);
    void print_all() const;
    void print_all2() const;

private:
    list<osoba> m_listaOsob;
};

void lista_osob::add(osoba dodawana)
{
    m_listaOsob.push_back(dodawana);
}

bool lista_osob::remove(const string &imie)
{
//    auto it = remove_if(m_listaOsob.begin(),
//                m_listaOsob.end(),
//                [&imie](const osoba& os) ->bool { return imie==os.get_imie();} );
//    m_listaOsob.erase(it);

//    nie mozna usuwac z kontenera po ktorym sie aktualnie iteruje!!!!!!!!!!!
    vector<list<osoba>::iterator> do_ksowania;
    for(auto it = m_listaOsob.begin();it!=m_listaOsob.end();++it)
    {
        if(it->get_imie() == imie)
           do_ksowania.push_back(it);
    }
    for(auto it:do_ksowania)
        m_listaOsob.erase(it);

    return true;
}

void lista_osob::print_all() const
{
    for ( auto ii : m_listaOsob)
    {
       ii.print_osoba();
       cout << "\n";
    }
}

void lista_osob::print_all2() const
{
    for ( auto ii : m_listaOsob)
    {
       cout << ii << "\n";
    }
}
