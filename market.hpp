#ifndef MARKET_HPP
#define MARKET_HPP

#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "shop.hpp"
#include "osoba2.hpp"

using namespace std;

class ticket
{
	list<shop_ptr> * spl;
public:
	ticket( list<shop_ptr> * lsp );
	shop_ptr enter_shop(const string& shop_name);
};

ticket::ticket(list<shop_ptr> *lsp) : spl(lsp)
{
	cout << "new ticket created, number of shopt: " << lsp->size() << endl;
}

shop_ptr ticket::enter_shop(const string & shop_name) {
	for (auto it : *spl)
	{
		if(it->get_name() == shop_name)
			return it;
	}

	return nullptr;
}

class market {

public:
	market() = default;
	market(const string& market_name);
	bool enter_market(shop_ptr shop);
	ticket enter_market(osoba_ptr osoba);
	void quit_market(shop_ptr shop);
	void quit_market( ticket t);
	vector<string> get_all_shops();

private:
	list<shop_ptr> shops;
	list<osoba_ptr> people;
};

ticket market::enter_market(osoba_ptr osoba){
	ticket new_ticket(&shops);
	people.push_back(osoba);

	return new_ticket;
}

bool market::enter_market(shop_ptr shop){
	shops.push_back( shop );
	return true;
}

#endif // MARKET_HPP
