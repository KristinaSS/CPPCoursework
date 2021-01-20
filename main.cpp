#include <iostream>
#include <vector>
#include <regex>

#include "person.h"
#include "PersonEstate.h"


vector<Person> createPeople ();

void printPeople (const vector<Person>&people);

void menu ();

void findPersonToAddAddress (const Person& person, vector<PersonEstate>* personEstateList);

char* enterAddress(const string& name);

int chooseMenuOption();

void addEstateToPerson (vector<Person> * people, vector<PersonEstate> *estates);

void findAllPeopleThatPersonAddressIsTheSameOneOfEstate(const vector<PersonEstate> &estates);

void findAllEstatesByEGN(const vector<PersonEstate>& estates, const vector<Person>& people);

string enterEGN();


//MAIN

int main() {

    vector<Person> peopleVector = createPeople();

    vector<PersonEstate> personEstateList;

    int option;
    int isActive = 1;

    while (isActive) {
        menu();
        option = chooseMenuOption();

        switch (option) {
            case 1:
                addEstateToPerson(&peopleVector, &personEstateList);
                break;
            case 2:
                findAllPeopleThatPersonAddressIsTheSameOneOfEstate(personEstateList);
                break;
            case 3:
                findAllEstatesByEGN(personEstateList, peopleVector);
                break;
            case 4:
                cout << "Goodbye!" << endl;
                isActive = 0;
                break;
            default:
                cout << "Not a valid option." << endl;
                break;
        }

    }

    return 0;
}

//MENU OPTIONS

void addEstateToPerson (vector<Person> * people, vector<PersonEstate> *estates){
    printPeople(*people);

    string personEGN = Person::enterPersonEGN();

    Person person = Person::findPersonByEGN(personEGN, *people);

    findPersonToAddAddress(person, estates);
}

void findAllPeopleThatPersonAddressIsTheSameOneOfEstate(const vector<PersonEstate> &estates) {
    string personAddress;
    int isFoundPerson = 0;

    for (auto & estate : estates){
        personAddress = estate.getAddress();

        if(PersonEstate::checkIfPersonalAddressEqualToAnyOfEstate(personAddress, estate)){
            Person::printPerson(estate);
            isFoundPerson = 1;
        }
    }

    if(isFoundPerson == 0){
        cout<< "No People had the same personal address as one of their estates " << endl;
    }
}

void findAllEstatesByEGN(const vector<PersonEstate>& estates, const vector<Person>& people){
    string egn = enterEGN();

    string name = Person::findPersonName(people, egn);

    if(name == "none"){
        cout<<"There are no people with this EGN: "<< egn << endl;
        return;
    }
    PersonEstate::findAllEstates(egn, estates, name);
}

//ENTERING INFO

char * enterAddress(const string& name){
    string address;

    cout << "Enter estate address for: "<< name << endl;
    getline(cin, address);

    cout << "enter address: "<< address << endl;

    char * charPtr = new char[address.length() + 1];
    strcpy(charPtr, address.c_str());

    return charPtr;
}

int chooseMenuOption(){
    string option;
    regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
    smatch m;

    for(;;) {
        cout << "Choose menu Option:" << endl;
        getline(cin, option);

        if(regex_search(option, rx) && (option =="1" || option == "2" || option == "3" || option == "4")){
            break;
        }

        cout<<"You entered an invalid option"<<endl;

    }

    return stoi(option);
}

string enterEGN(){
    string egn;
    regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
    smatch m;

    for (;;) {
        cout << "Enter the person's EGN:" << endl;
        getline(cin, egn);

        if(regex_search(egn, rx)){
            break;
        }

        cout<<"You entered an invalid egn"<<endl;
    }

    return egn;
}

//PRINTING INFO

void menu () {
    cout << "-----Menu-----" << endl;
    cout << "--------------" << endl;
    cout << "1. Add Estate to person" << endl;
    cout << "2. Find All people where personal address is the same as one of the estate addresses" << endl;
    cout << "3. Find all Estate by person's EGN"<< endl;
    cout << "4. Exit" << endl;
}

void printPeople(const vector<Person>&people) {

    cout << "-----People-----" << endl;

    for (const auto& person: people){

        cout << "EGN: " << person.getEgn();
        cout << " Name -> "<< person.getName() <<  endl;
    }

}

//OTHER

vector<Person> createPeople(){
    vector<Person> people;

    Person person1;

    person1.setName("Kristina Stoyanova");
    person1.setEgn("1234567890");
    person1.setAddress("ul Hristo Botev #97 Skutare");


    Person person2;

    person2.setName("Ivelin Nikolov");
    person2.setEgn("1234567891");
    person2.setAddress("ul Ivan Vazov #93 Veliko Turnavo");

    Person person3;

    person3.setName("Hristina Varbanova");
    person3.setEgn("1234567892");
    person3.setAddress("ul Dimcho Deleqnov #91 Veliko Turnavo");

    Person person4;

    person4.setName("Kristian Halachev");
    person4.setEgn("1234567893");
    person4.setAddress("ul 8mi Mart #97 Veliko Turnavo");

    Person person5;

    person5.setName("Valentin Aleksiev");
    person5.setEgn("1234567899");
    person5.setAddress("ul 6 septemvri #98 Plovdiv");

    Person person6;

    person6.setName("Georgi Georgiev");
    person6.setEgn("1234567898");
    person6.setAddress("ul Vasil Levski #99 Sofia");

    Person person7;

    person7.setName("Uliqn Georgiev");
    person7.setEgn("1234567897");
    person7.setAddress("ul Elin Pelin #96 Sofia");

    Person person8;

    person8.setName("Diyan Stoichev");
    person8.setEgn("1234567895");
    person8.setAddress("ul Elizabeta Bagrqna #94 Sofia");

    people.push_back(person1);
    people.push_back(person2);
    people.push_back(person3);
    people.push_back(person4);
    people.push_back(person5);
    people.push_back(person6);
    people.push_back(person7);
    people.push_back(person8);

    return people;
}

void findPersonToAddAddress (const Person& person, vector<PersonEstate>* personEstateList) {

    char * address = enterAddress(person.getName());

    for (auto & i : *personEstateList){
        if (i.getEgn() == person.getEgn()){
            PersonEstate::addAddressToPerson(&i, address);
            return;
        }
    }

    PersonEstate::createPersonEstateObject(person.getName(),person.getEgn(), person.getAddress(),address, personEstateList);
}
