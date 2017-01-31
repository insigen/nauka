#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>

#ifndef OSOBA_H
#define OSOBA_H

using namespace std;


class osoba
{
    //to jest priv.
public:
	osoba() = default; // w zaleznosci od optymalizacji kompilator moze do ciala tego
	osoba( int wiek, const string & imie, const string & praca);

	bool operator ==(const osoba& o1);
	osoba(const osoba& druga);
	osoba& operator =(const osoba& druga);
    void print_osoba() const;

    string get_imie() const;

	friend ostream& operator <<(ostream& o, const osoba& os);
	virtual ~osoba();

private:
    int m_wiek;
    string m_imie;
    string m_praca;
};

//lista inicjalizacyjna zapobiega bezsensownemu kopiowaniu
osoba::osoba(int wiek, const string & imie, const string & praca) :
    m_wiek(wiek), m_imie(imie), m_praca(praca)
{
}

//osoba::osoba(int wiek, const string & imie,const string & praca)
//{
//    m_wiek = wiek;
//    m_imie = imie;
//    m_praca = praca;
//}

bool osoba::operator ==(const osoba& o1)
{
    return this->m_praca == o1.m_praca;
}

osoba::osoba(const osoba& druga)
{
    m_wiek = druga.m_wiek;
    m_imie = druga.m_imie;
    m_praca = druga.m_praca;
}

osoba& osoba::operator =(const osoba& druga)
{
    m_wiek = druga.m_wiek;
    m_imie = druga.m_imie;
    m_praca = druga.m_praca;
    return (*this);
}
osoba::~osoba()
{

}

string osoba::get_imie() const
{
    return m_imie;
}

void osoba::print_osoba() const
{
    cout << "imie: " << m_imie << "\n"
         << "wiek: " << m_wiek << "\n"
         << "praca: " << m_praca << "\n";
}

ostream& operator <<(ostream& o, const osoba& os)
{
    o << "imie<<: " << os.m_imie << "\n"
      << "wiek<<: " << os.m_wiek << "\n"
      << "praca<<: " << os.m_praca << "\n";\

    return o;
}

#endif // OSOBA_H

