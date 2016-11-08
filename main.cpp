#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>
\
#include "osoba.hpp"
#include "lista_osob.hpp"
#include "super_karol_pointer.hpp"

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
}

int main()
{
//    Lesson1();
    Lesson3();

      return 0;
}
