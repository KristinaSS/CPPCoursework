//
// Created by krisa on 12/27/2020.
//

#include "person.h"
#include <string>
#include <utility>
using namespace  std;

Person::Person() {}

Person::Person(string name, string egn, string address) : name(std::move(name)), egn(std::move(egn)),
                                                                                       address(std::move(address)) {

}

Person::~Person() {

}

const string &Person::getName() const {
    return name;
}

void Person::setName(const string &name) {
    Person::name = name;
}

const string &Person::getEgn() const {
    return egn;
}

void Person::setEgn(const string &egn) {
    Person::egn = egn;
}

const string &Person::getAddress() const {
    return address;
}

void Person::setAddress(const string &address) {
    Person::address = address;
}

//предефиниране на оператор
ostream& operator<<(ostream& os, const Person& p){
    os<<"Person"<<endl;
    os<<"NAME: ";
    os<<p.getName()<<endl;
    cout<<"ENG: ";
    os<<p.getEgn()<<endl;
    cout<<"ADDRESS: ";
    os<<p.getAddress()<<endl;

    return os;
}

