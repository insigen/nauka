#ifndef PRACA_HPP
#define PRACA_HPP

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <utility>
#include <exception>

using namespace std;

class praca;

typedef shared_ptr<praca> praca_ptr;


class praca
{
public:
	praca(int kasa_roczna, int etat, const string& nazwa_pracy);

	template<typename...T> //template<typename K,typename E,typename N>
	static praca_ptr create_praca(T&&...args) { //create_praca(K&& k,E&& e,N&& n)
		return std::make_shared<praca>(std::forward<T>(args)...); //make_shared<praca>(std::forward<K>(k),...);
	}

	int get_wynagrodzenie() const;
	int get_etat() const;


private:
	int m_wynagrodzenie;
	int m_etat;
	string m_nazwa_pracy;
};

typedef map<string,pair<int,int>> map_praca_t;

class available_praca
{
	//mapping
	map_praca_t map_praca;
public:
	available_praca() {
		map_praca.insert(make_pair("kopacz_rowow", make_pair(10000, 40)));
		map_praca["kopacz_bienych_rowow"] = {3000, 60};
		map_praca["super_bohater"] = {0, 24};
		map_praca["pomoc_domowa"] = {5000, 14};
		map_praca["bohater"] = {50030, 8};
		map_praca["programista_wykop"] = {15000, 12};
		map_praca["spawacz"] = {15000, 12};
	}
	map_praca_t::mapped_type find_praca(const string & nazwa_pracy)
	{
		decltype(map_praca)::iterator it = map_praca.find(nazwa_pracy);
		/*
		sum(1,4.4);
		sum(2,2);
		template<typename T,typename T2>
		auto sum(T t,T2 t2) -> decltype( t + t2 ) {
			return t + t2;
		}
		*/
		if( it == map_praca.end())
			throw runtime_error("jak to praca nie istnieje?");
		else
			return it->second;
	}


	//constructor
	static praca_ptr assign_praca(const std::string& name) {
		//create available_praca
		static available_praca praca_obj;
		auto it = praca_obj.find_praca(name);
		return praca::create_praca(it.first, it.second, name);
	}


};

/*
int test(){

praca::create_praca(1,3,"praca",/*,obj*///); //obj support move semantic (move constructor,move assign. opr)
/*
}
*/
praca::praca(int kasa_roczna, int etat, const string &nazwa_pracy) :
	m_wynagrodzenie(kasa_roczna), m_etat(etat), m_nazwa_pracy(nazwa_pracy)
{
	cout << "wlasnie tworzymy prace " << nazwa_pracy
		 << " gdzie hajs musie sie zgadzac i wynosi " << kasa_roczna
		 << " na etacie o wymiarze " << etat << endl;

}


int praca::get_etat() const
{
	return m_etat;
}

int praca::get_wynagrodzenie() const
{
	return m_wynagrodzenie;
}

#endif // PRACA_HPP
