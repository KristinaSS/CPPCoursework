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

    static string enterPersonEGN() {
        string egn;
        regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
        smatch m;

        for(;;) {
            cout << "Enter person EGN: " << endl;
            getline(cin, egn);

            if(regex_search(egn, rx)){
                break;
            }

            cout<<"You entered an invalid EGN"<<endl;
        }

        return egn;
    }

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

    static void printPerson(const Person& person){
        cout<<"Person"<<endl;
        cout<<"NAME: "<< person.getName()<<endl;
        cout<<"ENG: "<< person.getEgn()<<endl;
        cout<<"ADDRESS: "<< person.getAddress()<<endl;
    }

    static string findPersonName( const vector<Person>& people, const string& egn){
        string name;

        for(const auto& person: people){
            if(person.getEgn() == egn){
                return person.getName();
            }
        }
        return "none";
    }
};


#endif //UNTITLED_PERSON_H
