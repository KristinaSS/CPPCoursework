//
// Created by krisa on 12/27/2020.
//

#ifndef UNTITLED_PERSON_H
#define UNTITLED_PERSON_H

#include <string>

using namespace std;


class Person{
private:
    int id;
    string name;
    string egn;
    string address;

public:
    Person();

    Person(int id, const string &name, const string &egn, const string &address);

    virtual ~Person();

    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    const string &getEgn() const;

    void setEgn(const string &egn);

    const string &getAddress() const;

    void setAddress(const string &address);
};


#endif //UNTITLED_PERSON_H
