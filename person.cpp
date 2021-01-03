//
// Created by krisa on 12/27/2020.
//

#include "person.h"
#include <string>
using namespace  std;


Person::Person(int id, const string &name, const string &egn, const string &address) : id(id), name(name), egn(egn),
                                                                                       address(address) {

}

Person::Person() {}

Person::~Person() {

}

int Person::getId() const {
    return id;
}

void Person::setId(int id) {
    Person::id = id;
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


