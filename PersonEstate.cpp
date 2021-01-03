//
// Created by krisa on 12/27/2020.
//

#include "PersonEstate.h"

#include "person.h"


PersonEstate::PersonEstate() {}

PersonEstate::~PersonEstate() {

}

int PersonEstate::getId() const {
    return id;
}

void PersonEstate::setId(int id) {
    PersonEstate::id = id;
}

const Person &PersonEstate::getPerson() const {
    return person;
}

void PersonEstate::setPerson(const Person &person) {
    PersonEstate::person = person;
}

