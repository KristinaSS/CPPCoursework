//
// Created by krisa on 12/27/2020.
//

#ifndef UNTITLED_PERSONESTATE_H
#define UNTITLED_PERSONESTATE_H

#include "person.h"
#include <vector>
#include <iostream>

class PersonEstate: public Person{ //декларация на производен клас
private:

    char *adr[5]{};

    static void printAllEstates(const PersonEstate& personEstate){

        for(auto & i : personEstate.adr){
            if(i!= nullptr){
                cout<< "Estate Address: " << i << endl;
            }
        }
    }

public:

    PersonEstate(const string &name, const string &egn, const string &address);

    ~PersonEstate();

    static void addAddressToPerson(PersonEstate *personEstate, char *address) {
        for (int i = 0; i < 5;i++){
            if(personEstate->adr[i] == nullptr){
                personEstate->adr[i] = address;
                return;
            }
            if  (i == 4) {
                cout<<"This person already owns 5 estates!"<<endl;
                return;
            }
        }
    }

    static void createPersonEstateObject(const string& personName, const string& personEGN, const string& personAddress, char * address, vector<PersonEstate> *personEstateList) {
        PersonEstate personEstate(personName,personEGN, personAddress);

        personEstate.adr[0] = address;
        personEstate.adr[1] = personEstate.adr[2] = personEstate.adr[3] = personEstate.adr[4] = nullptr;

        personEstateList->push_back(personEstate);
    }

    static bool checkIfPersonalAddressEqualToAnyOfEstate (const string& address, const PersonEstate& personEstate){
        for (auto & i : personEstate.adr){
            if(i== nullptr){
                return false;
            }
            if(address == i){
                return true;
            }
        }
        return false;
    }

    static void findAllEstates(const string& egn, const vector<PersonEstate>& estates, const string& name){

        cout<<"All estates that belong to :" << name << "with EGN: " << egn << endl;

        for(const auto& personEstate: estates){
            if(personEstate.getEgn() == egn){
                PersonEstate::printAllEstates(personEstate);
                return;
            }
        }
        cout<< "This person doesnt own any estates!"<< endl;

    }
};


#endif //UNTITLED_PERSONESTATE_H
