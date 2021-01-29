//
// Created by krisa on 12/27/2020.
//

#ifndef UNTITLED_PERSONESTATE_H
#define UNTITLED_PERSONESTATE_H

#include "person.h"
#include <vector>
#include <iostream>
#include <fstream>

class PersonEstate: public Person{ //декларация на производен клас
private:

    char *adr[5]{0};//това оставя private без гетъри и сетъри защо се изпозва само във този клас

    //притират се всички имоти които принадлежат на този човек
    //тази фунция е прайвър защото не се използва извън класа
    static void printAllEstates(const PersonEstate& personEstate){

        for(auto & i : personEstate.adr){
            if(i!= nullptr){
                cout<< "Estate Address: " << i << endl;
            }
        }
    }

public:

    PersonEstate(const string &name, const string &egn, const string &address);//декларация на констуктор

    ~PersonEstate();//декларация на деконстуктор

    //добавя адрес на първото поле на масиява което е nullptr
    static void addAddressToPerson(PersonEstate *personEstate, char *address) {
        for (int i = 0; i < 5;i++){
            if(personEstate->adr[i] == nullptr){
                personEstate->adr[i] = address;
                return;
            }
            if  (i == 4) { //Провеява дали човека вече притежава 3 имота
                cout<<"This person already owns 5 estates!"<<endl;
                return;
            }
        }
    }

    //функция за да се добави елемент към вектора от имоти
    static void createPersonEstateObject(const string& personName, const string& personEGN, const string& personAddress, char * address, vector<PersonEstate> *personEstateList) {
        PersonEstate personEstate(personName,personEGN, personAddress); // създава се обекта

        personEstate.adr[0] = address;
        personEstate.adr[1] = personEstate.adr[2] = personEstate.adr[3] = personEstate.adr[4] = nullptr;// всичко с изключение на първия адес е nullptr

        personEstateList->push_back(personEstate);//добавя се към вектора
    }

    //Проверява дали някои от адресите на притежаваните имоти е равно на домашния адрес на човека
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

    //функция която изважда адресите на всички хора с това егн
    static void findAllEstates(const string& egn, const vector<PersonEstate>& estates, const string& name){

        cout<<"All estates that belong to :" << name << "with EGN: " << egn << endl;

        for(const auto& personEstate: estates){
            if(personEstate.getEgn() == egn){//проверява дали егн на човека съвпада със зададеното егн
                PersonEstate::printAllEstates(personEstate); //притират се всички имоти които принадлежат на този човек
                return;//ако е засечено егн-то се излиза от фунцитя
            }
        }
        cout<< "This person doesnt own any estates!"<< endl; //ако не се излезе от функцията по време на цикленето в търсене на егн се принира това съобщение

    }

    //Записва информация във дадения файл
    //файла се намира във папката cmake-build-debug
    static void addToFile (const PersonEstate& personEstate, string filename){
        ofstream file;// създаване на стрим

        file.open(filename.c_str(), ios::app);// отваряне на файл

        if(!file.good()){
            cout << "Error creating c++.out.txt";
            exit(1);
        }

        //записва следната информация във файла
        file << "Person: " << endl;
        file << "Name: " << personEstate.getName()<<endl;
        file << "EGN: " << personEstate.getEgn()<<endl;
        file << "Address: " << personEstate.getAddress() << endl;
        file << "Estates: ";
        for  (auto &i: personEstate.adr){
            if(i!= nullptr) {
                file << i;
            }
        }
        file.close(); // затваряне на файла
    }

};


#endif //UNTITLED_PERSONESTATE_H
