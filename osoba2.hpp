#include <iostream>
#include <string>
#include <memory>
#include "praca.hpp"


#ifndef OSOBA2_HPP
#define OSOBA2_HPP

using namespace std;
class osoba2;

using osoba_ptr = shared_ptr<osoba2>;

class osoba2
{
	//pointer to virtual table 32/64
public:
	osoba2() = default; // w zaleznosci od optymalizacji kompilator moze do ciala tego
	osoba2( int wiek, const string & imie, const string & praca);

	virtual void wykonaj_prace() = 0; //One additional step
	virtual void wykonaj_prace_domowe() = 0;

	void pokaz_osobe()
	{
		cout << "Mam na imie " << m_imie << " i jestem " << m_praca << endl;
	}

protected:
	int m_wiek;
	string m_imie;
	string m_praca;
	int m_hajs;
	praca_ptr m_pptr;
};


osoba2::osoba2(int wiek, const string &imie, const string &praca) :
	m_wiek(wiek), m_imie(imie), m_praca(praca)
{
	m_hajs = 0;
	m_pptr = available_praca::assign_praca(praca);

}


class facet : public osoba2
{
public:
	facet(int wiek, const string & imie, const string & praca) :
		osoba2(wiek, imie, praca)
	{

	}

	void wykonaj_prace()
	{
		int rozlicz = m_pptr->get_wynagrodzenie() / 12 * m_pptr->get_etat();
		m_hajs +=rozlicz;
		cout << m_imie << " wlasnie zarobiles " << rozlicz << endl;
	}

	void wykonaj_prace_domowe()
	{
		cout << "Jakie prace domowe. Pierdole nie robie!" << endl;
	}
};

class babka : public osoba2
{

public:
	babka(int wiek, const string & imie, const string & praca) :
		osoba2(wiek, imie, praca)
	{

	}

	void wykonaj_prace_domowe()
	{
		m_hajs += 1000;
		cout << "wlasnie dodano 1000 zl do Twojego wynagrodzenia" << endl;
	}

	void wykonaj_prace()
	{
		int rozlicz = m_pptr->get_wynagrodzenie() / 12 * m_pptr->get_etat() / 2;
		m_hajs +=rozlicz;
		cout << m_imie << " wlasnie zarobiles " << rozlicz << endl;
	}


};
//STATIC POLYMORPHISM
//template<typename T>
//class osoba2_stat
//{
//public:
//	void do_job_not_static() {
//		//This call osoba2_face::do_jot_not_static
//		//Works like a virtual function
//		static_cast<T*>(this)->do_job_not_static();
//	}

//	static void do_job() {
//		T::do_job();
//	}
//};

//class osoba2_facet : public osoba2_stat<osoba2_facet>
//{
//public:
//	void do_job_not_static(){
//		cout<<"do_job in derived class, legit member\n";
//	}

//	static void do_job() {
//		cout<<"do_job in derived class\n";
//	}
//};


#endif // OSOBA2_HPP

