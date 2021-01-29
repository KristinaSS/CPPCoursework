//
// Created by krisa on 12/27/2020.
//

#ifndef UNTITLED_PERSON_H
#define UNTITLED_PERSON_H

#include <string>
#include <regex>
#include <iostream>

using namespace std;

class Person{ //декларация на базов клас
private:

    //член променливи на класа
    string name;
    string egn;
    string address;

public:
    Person();

    Person(string name, string egn, string address); //декларация на констуктор

    ~Person(); // декларация на деконструктор


    //декларация на член-функции

    const string &getName() const;

    void setName(const string &name);

    const string &getEgn() const;

    void setEgn(const string &egn);

    const string &getAddress() const;

    void setAddress(const string &address);

    //фунция за въвеждане егн-то на човек
    static string enterPersonEGN() {
        string egn;
        regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");//регек който проверява дали въведения стринг е от само цифри
        smatch m;

        for(;;) {
            cout << "Enter person EGN: " << endl;
            getline(cin, egn);

            if(regex_search(egn, rx)){//проверява дали стринга се подчинява на егн-то ако да се излиза от цикъла
                break;
            }

            cout<<"You entered an invalid EGN"<<endl;// ако не е въведено валидно егн се изписва това съобщение и цикъла наново се завърва
        }

        return egn;
    }

    //намираме даден човек спрямо даденото егн като се итерира вектора people ако не се намери такъв човек егн-то се задава като 'none'
    static Person findPersonByEGN(const string& egn, const vector<Person>& people){
        for (auto & i : people){
            if (i.getEgn() == egn){
                cout << "egn: " << egn << endl;
                return i;
            }
        }
        Person person;

        person.setEgn("none");

        return person;
    }

    //фунция за принтиране на даден човек
    static void printPerson(const Person& person){
        cout<<person;
    }

    //Функия която намира човек спрямо зададеното егн, ако егн-то не принадлежи на никого връща "none"
    static string findPersonName( const vector<Person>& people, const string& egn){
        string name;

        for(const auto& person: people){
            if(person.getEgn() == egn){
                return person.getName();
            }
        }
        return "none";
    }

    friend ostream& operator<<(ostream &os,const Person & p); // задаваме ostream& operator като friend
};

#endif //UNTITLED_PERSON_H
