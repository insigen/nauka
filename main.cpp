#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
#include "osoba.hpp"
#include "lista_osob.hpp"
#include "super_karol_pointer.hpp"
#include "praca.hpp"
#include "osoba2.hpp"
#include "shop.hpp"
#include "market.hpp"

using namespace std;

void Lesson1()
{
    osoba karol1; // derfault constructor
    osoba karol2(25,"Karol","Intel");
//    osoba * filip = new osoba(30, "Fillip", "Intel"); //nulltrp

    shared_ptr<osoba> filip = make_shared<osoba>(30,"Filip","Intel");

    if(*filip == karol2) //(*filip).operator ==( karol2)
        cout<<"Ta sama praca!!\n";
    else
        cout<<"Nie, to nie ta sama praca!\n";

    osoba boczula(karol2);
    osoba magda = *filip;

    lista_osob l;
    l.add(karol1);
    l.add(karol2);
    l.add(*filip);
    l.print_all();
    l.print_all2();

    cout << karol2;
//    delete filip; //is possible to delete nullptr
//LESSON 1 cd



    karol_pointer<int> tkp(69);

    {
        karol_pointer<int> tkp2(tkp);

        *tkp2 = 10;
        cout << *tkp << endl;
    }//sequence point, tkp2 destroyed

    cout<<"Here I want to use tkp: " << *tkp << endl;;

    karol_pointer<osoba> okp1(osoba(25,"Karol","Intel"));

    //corrupted tkp
//    cout<<*tkp<<endl;
}

void Lesson3()
{
    //AGENDA:
    //templatey i jeszcze raz templejty

    super_karol_pointer<int> skp(99);
    cout << *skp << endl;

    super_karol_pointer<int[]> skp2(6);
    skp2[0] = 123;
    skp2[5] = 321;

    for(int i=0; i!=6;++i)
        cout << skp2[i] << endl;
}

void Lesson4()
{
    //AGENDA:
    //lambda
    //przeladowanie new i delete
	//...
	try
	{
		facet karol(30, "karol", "programista_wykop");
		facet filip(33, "filip", "bohater");
		babka magda(18, "magda", "pomoc_domowa");
//		facet ktos(99, "ktos", "ksiadz");

		filip.wykonaj_prace();
		magda.wykonaj_prace();
		magda.wykonaj_prace_domowe();
		filip.wykonaj_prace_domowe();

		//osoba2 os = new facet;..
		//os->wykonaj_prace();

	}
	catch(exception & ex)
	{
		cout << "WTF " << ex.what() << endl;
	}


}

//POLYMORPHISM
//void bar(osoba2 * osob)
//{
//	osob->wykonaj_prace(); //Call virtual function
//}

//template<typename T>
//void foo(osoba2_stat<T>& osob) //Like pointer to base class
//{
//	osob.do_job_not_static();
//}

//void Lesson5()
//{
//	//Like providing pointer to derived class
//	osoba2_facet fac;
//	osoba2 * fac2 = new facet(10,"Kacper","programista_wykop");

//	foo(fac);
//	bar(fac2);
//}

void Lesson6()
{
//	product_ptr whisky = product::create<alcohol>("jack_daniels", 1000);

	vector<product_ptr> v;
	v.push_back(product::create<alcohol>("red_label", 1000));
	v.push_back(product::create<alcohol>("black_label", 1000));
	v.push_back(product::create<alcohol>("gold_label", 1000));
	v.push_back(product::create<alcohol>("blue_label", 1000));
	v.push_back(product::create<alcohol>("jack_daniels", 1000));
	v.push_back(product::create<alcohol>("jameson", 1000));
	v.push_back(product::create<alcohol>("red_label", 1000));

	v[ 0 ]->use_product();
	v[ 0 ]->use_product();
	v[ 0 ]->use_product();

	shop s;
	int amount_of_money{ 0 };
	for(auto it = v.begin(); it != v.end(); ++it){
		auto money = s.sell(*it);

		if (money  > 0)  //((*it)->get_name == it->shared_ptr()->get_name
			amount_of_money += money;

		if((*it)->get_name() == "blue_label")
			cout << (*it)->get_name() << " " << money << endl;
	}


	auto vn = s.get_list_of_producs();
	auto price = s.inquiry("blue_label");

	cout << "blue_label" << " " << price <<  endl;

	/* TODO: KAROL:
	 *  1) Create some products and put them in a container of products
	 *  2) Create a shop and attempt to sell some products,
	 *  3) Ask the shop for the product list and verify that everything
	 *     that you've sold is in there
	 *  3) Create a product, use it, and the sell it.. verify the prize
	 *  4) Attempt to buy something, check if everything works
	 */

	/*
	 * TODO: KAROL:
	 *  1) Create a market object, which have the following interface:
	 *     - ticket enter_market( shared ptr to osoba2 ) = A given osoba enter the market place
	 *     - bool enter_market( shared ptr to shop ) = A new shop in the market
	 *     - void quit_market( shared ptr to shop ) = exit the market (No more in the internal list)
	 *     - void quit_market( ticket ) = find the osoba for the ticket, that osoba quit the market.
	 *   Store the list of shops and osoba as variables (vectors, maps, you choose).
	 *  2) the 'ticket' returned by enter_market is an object with the following interface:
	 *     - shared_ptr<shop> enter_shop( name ) = return a pointer to one of the shops
	 *       in the market, one use case is:
	 *       int price = ticket->enter_shop("alkohol shop")->inquiry("Jack Daniels");
	 *       if ( have money ) {
	 *				product_ptr new_product = ticket->enter_shop("alkohol shop")->buy("Jack Deniels");
	 *       }
	 *       where someone is buying a product from one of the shop, if the shop is not in the market
	 *       return nullptr.
	 */

}

//POINTER TO MEMBER EXAMPLE
//struct test
//{
//	std::string name;
//	std::string surname;
//	std::string job;
//};

//test test_instance;

//void foo( std::string test::*pointer ) {

//	std::cout<<test_instance.*pointer<<std::endl;

//}

//void set_var(int parameter,
//	const std::string& value)
//{
///*	std::string test::*pointer_one; //pointer to any member of type std::string
//	int test::*pointer_two; //Pointer to any member of type int

//	test instance_one;

//	pointer_one = &test::surname;

//	instance_one.*pointer_one = "HELLO";

//	foo( &test::job );
//	foo( &test::surname );
//*/
//	std::string test::*pointer[] = {
//		&test::name,
//		&test::surname,
//		&test::job
//	};

//	test_instance.*pointer[parameter] = value;
//}

//void Lesson7() //Pointer to member
//{
//	set_var( 0, "name example");
//	set_var( 1, "bla bla");
//}

//using filip_ptr = std::shared_ptr<facet>;
//shop s1("aa"),s2("bb"),s3("cc");
//std::shared_ptr<shop> p_s1( &s1 );
//std::shared_ptr<shop> p_s2( &s2 );
//std::shared_ptr<shop> p_s3( &s3 );

//ticket get_ticket(filip_ptr ptr){
//	market mk;
//	mk.enter_market( p_s1 );
//	mk.enter_market( p_s2 );
//	mk.enter_market( p_s3 );
//	return mk.enter_market( ptr );
//}

//void lesson7()
//{
//	filip_ptr real_filip = make_shared<facet>(45,"Filip","spawacz");
//	ticket tk = get_ticket( real_filip );
//	shop_ptr my_shop = tk.enter_shop("aa");
//	if( my_shop != nullptr ){
//		my_shop->buy("ddd");
//	}
//}

//class foo;

//class tick
//{
//	int my_id;
//	bool is_closed;
//	foo *ptr_to_foo;
//public:
//	tick( foo * ptr, int id ) : ptr_to_foo{ ptr} my_id { id } {};
//	bool market_close() {
//		is_closed = true;
//	}

//	shop enter_shopt(string)
//	{
//		if( is_closed )
//			return nullptr;
//		return shop;
//	}
//	~tick() {
//		if( !is_close )
//			ptr_to_foo->remove_ticket( my_id );
//	}
//};

//class foo
//{
//public:
//	shared_ptr<tick> create() {
//		//create sp
//		static int new_id = 0;
//		++new_id;
//		tick(new_id); //shared ptr
//		local.push_back( make_pair( new_id, sp ) );
//		return sp;
//	}

//	void remove_ticket( id ) {
//		//search local for id and remove
//	}

//	~foo() {
//		for( auto tk : local )
//			tk.second->market_close();

//	}

//public:
//	map<int,tick*> local;
//};

void Lesson8()
{
	shop_ptr tesco = make_shared<shop>("tesco");
	shop_ptr auchan = make_shared<shop>("auchan");
	shop_ptr carrefour = make_shared<shop>("carrefour");

	product_ptr whisky = product::create<alcohol>("whisky", 100);
	product_ptr audi = product::create<cars>("audi", 2);
	auchan->sell(whisky);
	auchan->sell(audi);

	shared_ptr<ticket> filip_ticket,
					magda_ticket;

	osoba_ptr Filip = make_shared<facet>(33, "Filip", "spawacz");
	osoba_ptr Magda = make_shared<babka>(28, "Magda", "pomoc_domowa");

	{
		market m;
		m.enter_market(tesco);
		m.enter_market(auchan);
		m.enter_market(carrefour);
		m.get_all_shops();


		filip_ticket = m.enter_market(Filip);
		magda_ticket = m.enter_market(Magda);
	}//Here market disappear.

//	m.get_all_customers();

	for ( auto it : auchan->get_list_of_producs())
		cout << it << endl;


	auto auchan_ptr = magda_ticket->enter_shop("auchan");
	if ( auchan_ptr != nullptr){
		auto audi_ptr = auchan_ptr->buy("audi");
		if(audi_ptr!=nullptr)
			cout << "Magda wlasnie kupila: " << audi_ptr->get_name() << endl;

	}

	for ( auto it : auchan->get_list_of_producs())
		cout << "W sklepie pozostalo: "  << it << endl;
}

int main()
{
//    Lesson1();
	//Lesson4();
	//Lesson6();
	//lesson7();

//	foo* f_ptr = new foo;
//	std::shared_ptr<foo> ptr;

//	{
//		std::shared_ptr<foo> ptr2( f_ptr );
//	}

//	//foo is not existing
//	if( ptr == nullptr ) {
//		std::cout<<"OK\n";
//	}
	Lesson8();
	return 0;
}
