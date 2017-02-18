#ifndef MARKET_HPP
#define MARKET_HPP

#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "shop.hpp"
#include "osoba2.hpp"

using namespace std;

class market;

class ticket
{
private:
	int ticket_id;
	market * market_ptr;
	bool is_closed;
	list<shop_ptr> * shop_list;

public:
	ticket() = default;
	ticket( int id, market* m, list<shop_ptr>* s)  :
		ticket_id(id),
		market_ptr(m),
		shop_list(s)
	{}
	shop_ptr enter_shop(const string& shop_name);
	~ticket();
	void market_close();
	bool is_valid_ticket();
};
bool ticket::is_valid_ticket()
{
	if(!is_closed)
		return true;
	return false;
}

shop_ptr ticket::enter_shop(const string &shop_name)
{
	if(is_closed)
		return nullptr;
	else
	{
		for(auto it : *shop_list)
			if (it->get_name() == shop_name)
				return it;
	}
	return nullptr;
}


void ticket::market_close()
{
	is_closed = true;
}



class market {

public:
	market() = default;
	market(const string& market_name);
	bool enter_market(shop_ptr shop);
	shared_ptr<ticket> enter_market(osoba_ptr osoba);
	void quit_market(shop_ptr shop);
	void quit_market( ticket t);
	vector<string> get_all_shops();
	void get_all_customers();
	shared_ptr<ticket> create_ticket();
	void remove_ticket(const int);
	~market();

private:
	list<shop_ptr> shops;
	list<osoba_ptr> people;
	map<int, shared_ptr<ticket>> ticket_id;
};

shared_ptr<ticket> market::enter_market(osoba_ptr osoba){
	auto tick = create_ticket();

	people.push_back(osoba);

	return tick;
}

bool market::enter_market(shop_ptr shop){
	shops.push_back( shop );
	return true;
}

shared_ptr<ticket> market::create_ticket()
{
	static int new_id = 0;
	++new_id;
	auto new_ticket = make_shared<ticket>(new_id, this, &shops);
	ticket_id.insert(make_pair(new_id, new_ticket));
	return new_ticket;
}

void market::remove_ticket(const int id)
{
	ticket_id.erase(id);
}

market::~market()
{
	cout << "niszcze market " << endl;
	for( auto it : ticket_id)
		it.second->market_close();
}


ticket::~ticket()
{
	cout << "niszcze ticket" << ticket_id << endl;
	if(!is_closed)
		market_ptr->remove_ticket(ticket_id);
}

vector<string> market::get_all_shops()
{
	vector<string> vs;
	for ( auto it : shops)
	{
		vs.push_back(it->get_name());
		cout << it->get_name() << endl;
	}

	return vs;

}


void market::get_all_customers()
{
	for ( auto it : people)
		it->pokaz_osobe();
}

#endif // MARKET_HPP
