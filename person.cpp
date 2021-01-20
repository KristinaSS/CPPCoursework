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

