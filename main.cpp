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

void bar(osoba2 * osob)
{
	osob->wykonaj_prace(); //Call virtual function
}

template<typename T>
void foo(osoba2_stat<T>& osob) //Like pointer to base class
{
	osob.do_job_not_static();
}

void Lesson5()
{
	//Like providing pointer to derived class
	osoba2_facet fac;
	osoba2 * fac2 = new facet(10,"Kacper","programista_wykop");

	foo(fac);
	bar(fac2);
}

void Lesson6()
{
	product_ptr whisky = product::create<alcohol>("jack_daniels", 1000);

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
	 *     - ticket enter_market( osoba2 ) = A given osoba enter the market place
	 *     - bool enter_market( shop ) = A new shop in the market
	 *     - void quit_market( oboba2 or shop ) = exit the market (No more in the internal list)
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

int main()
{
//    Lesson1();
	//Lesson4();
	Lesson5();
      return 0;
}
