//
// Created by krisa on 12/27/2020.
//

#include "PersonEstate.h"
#include <iostream>

//дефиница на деконструктор
PersonEstate::~PersonEstate() {
    cout<<"Deconstructing PersonEstate Object"<<endl;
}

//дефиница на конструктор
PersonEstate::PersonEstate(const string &name, const string &egn, const string &address) : Person(name, egn, address) {}
