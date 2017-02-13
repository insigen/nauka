#ifndef SHOP_HPP
#define SHOP_HPP

#include <string>
#include <vector>
#include <map>
#include <utility>


using namespace std;

class product;
using product_ptr = std::shared_ptr<product>;

class product
{
public:
	product(const std::string& name, int remaining);
	std::string get_name();

	virtual bool use_product() = 0; //Use some 'remaining'
	virtual int suggested_price() = 0;
	int get_remaining_status(); //Return the status of the product, if 0 then product to trash
	double get_remaining_ratio();

	template<typename T>
	static product_ptr create(const std::string& name, int remaining) {
		return std::make_shared<T>(name,remaining);
	}

	/*
	 * Converts automatically a product type to std::string.
	 *
	 * Is possible to do:
	 * product p(..);
	 * std::string str = p;
	 * int n = p;
	 */
	operator std::string() {
		return get_name();
	}

	operator int() {
		return m_remaining;
	}

protected:
	const int m_max_value;
	int m_remaining;
	string m_name;

};

product::product(const std::string& name, int remaining) :
	m_name(name), m_remaining(remaining),
	m_max_value(remaining)
{
}


int product::get_remaining_status()
{
	return m_remaining;
}

double product::get_remaining_ratio()
{
	return m_remaining / m_max_value;
}

string product::get_name()
{
	return m_name;
}


class alcohol : public product
{
public:
	alcohol(const string& name, int remaining) :
		product( name, remaining ) //Pass to base constructor
	{}
	bool use_product() override
	{
		if(m_remaining > 0)
			m_remaining -= 50;
		else
			return false;

		return true;

	}

	int suggested_price() override
	{
		std::size_t hash_v = std::hash<std::string>{}(m_name);
		return hash_v % 1000; //number between 0, 999
	}
};

class drugs : public product
{
	drugs(const string& drug_name, int remaining) :
		product(drug_name, remaining)
	{}

	bool use_product() override
	{
		if(m_remaining > 0)
			m_remaining -= 10;
		else
			return false;

		return true;

	}

	int suggested_price() override
	{
		std::size_t hash_v = std::hash<std::string>{}(m_name);
		return hash_v % 100; //number between 0, 99
	}
};


class cars : public product
{
	cars(const string& car_name, int remaining) :
		product( car_name, remaining)
	{}

	bool use_product() override
	{
		if(m_remaining > 0)
			m_remaining -= 1;
		else
			return false;

		return true;
	}


	int suggested_price() override
	{
		std::size_t hash_v = std::hash<std::string>{}(m_name);
		return hash_v % 10000; //number between 0, 9999
	}
};

class shop
{
public:
	/*
	 * Return the list of name products
	 * available in the shop and the
	 * corresponding price.
	 */
	std::vector<string> get_list_of_producs();
	/*
	 * Buy the selected product.
	 * if return pointer == nullptr, PAf.. no more products
	 */
	product_ptr buy( const std::string& product_name );
	/*
	 * Sell a product (m_remaining must be > 0)
	 * Return the amount of money received for the product
	 */
	int sell( product_ptr product );
	/*
	 * Return true if the product is available
	 */
	int inquiry( const std::string& product_name);
	/*
	 * Produce a random product, and add to shop
	 */
	void produce();

private:
	//VARIABLES..
	map<std::string,product_ptr> stock;
	//map<std::string,int> quantity;
	map<string,pair<int,int>> product_info; //Price and quantity

	void erase_product(const string& product_name);
};


vector<string> shop::get_list_of_producs()
{
	vector<string> v;
	for (auto& it : stock)
	{
		//Every map element, is a PAIR<product_ptr,int>;
		v.push_back(it.first);
	}
	return v;
}


int shop::inquiry(const string& product_name)
{
	/*
	 * first option
	 *//*
	for(auto& elem:stock) { //O(n) instead of O(logN)
		if( elem.first->get_name() == product_name )
			return elem.second;
	}
	*/
	auto it = product_info.find( product_name ); //O(LogN) = worst case, O(1) average
	if( it != product_info.end() ) {
		return it->second.first;
	}
	return -1;
}


product_ptr shop::buy(const string &product_name)
{
	auto it = stock.find(product_name);
	if(it != stock.end())
	{
		auto it2 = product_info.find(product_name);
		if(it2 != product_info.end() ) {
			--it2->second.second;
			if(it2->second.second == 0)
				erase_product(product_name);
		}
	}
	return it->second;
}

void shop::erase_product(const string& product_name)
{
	auto it = stock.find(product_name);
	if(it != stock.end())
		stock.erase(it);

	auto it2 = product_info.find(product_name);
	if(it2 != product_info.end())
		product_info.erase(it2);

}

int shop::sell(product_ptr product)
{
	auto it = stock.find(product->get_name());
	double current_price{ -1 };
	if (it != stock.end())
	{
		current_price = product_info[ product->get_name() ].first;
		current_price *= product->get_remaining_ratio();
		if( current_price != 0 ) {
			//Buy
			++product_info[ product->get_name() ].second;
		}
		else
		{
			current_price = -1;
		}
	}
	else
	{
		current_price = product->suggested_price();
		stock[ product->get_name() ] =  product;
		product_info[product->get_name()] = make_pair( current_price * 1.5 , 1);
	}
	return current_price;
}

#endif // SHOP_HPP
