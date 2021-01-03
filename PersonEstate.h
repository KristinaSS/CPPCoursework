//
// Created by krisa on 12/27/2020.
//

#ifndef UNTITLED_PERSONESTATE_H
#define UNTITLED_PERSONESTATE_H

#include "person.h"

class PersonEstate{
private:
    int id;
    Person person;


public:
    char *adr[5];

    PersonEstate();

    virtual ~PersonEstate();

    int getId() const;

    void setId(int id);

    const Person &getPerson() const;

    void setPerson(const Person &person);
};

#endif //UNTITLED_PERSONESTATE_H
