#include <iostream>
#include <vector>
#include <regex>

#include "person.h"
#include "PersonEstate.h"


void addAddressToPerson(PersonEstate *personEstate, char * address);

vector<Person> createPeople ();

void printPeople (const vector<Person>&people);

void menu ();

void findPersonToAddAddress (const Person& person, vector<PersonEstate>* personEstateList);

char* enterAddress(const string& name);

int chooseMenuOption();

void createPersonEstateObject(const Person& person, char * address, vector<PersonEstate> *personEstateList);

int choosePersonById();

Person findPersonById(int id, const vector<Person>& people);

void addEstateToPerson (vector<Person> * people, vector<PersonEstate> *estates);

void findAllPeopleThatPersonAddressIsTheSameOneOfEstate(const vector<PersonEstate> &estates);

bool checkIfPersonalAddressEqualToAnyOfEstate (const string& address, const PersonEstate& personEstate);

void printPerson(const Person& person);

void findAllEstatesByEGN(const vector<PersonEstate>& estates, const vector<Person>& people);

string enterEGN();

void findAllEstates(const string& egn, const vector<PersonEstate>& estates, const string& name);

string findPersonName( const vector<Person>& people, const string& egn);

void printAllEstates(const PersonEstate& personEstate);


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

    int personId = choosePersonById();

    Person person = findPersonById(personId, *people);

    findPersonToAddAddress(person, estates);
}

void findAllPeopleThatPersonAddressIsTheSameOneOfEstate(const vector<PersonEstate> &estates) {
    string personAddress;
    int isFoundPerson = 0;

    for (auto & estate : estates){
        personAddress = estate.getPerson().getAddress();

        if(checkIfPersonalAddressEqualToAnyOfEstate(personAddress, estate)){
            printPerson(estate.getPerson());
            isFoundPerson = 1;
        }
    }

    if(isFoundPerson == 0){
        cout<< "No People had the same personal address as one of their estates " << endl;
    }
}

void findAllEstatesByEGN(const vector<PersonEstate>& estates, const vector<Person>& people){
    string egn = enterEGN();

    string name = findPersonName(people, egn);

    if(name == "none"){
        cout<<"There are no people with this EGN: "<< egn << endl;
        return;
    }
    findAllEstates(egn, estates, name);

}



//ENTERING INFO

char * enterAddress(const string& name){
    string address;


    cout << "Enter estate address for: "<< name << endl;
    getline(cin, address);

    cout << "enter aadress: "<< address << endl;

    char * charPtr = new char[address.length() + 1];
    strcpy(charPtr, address.c_str());

    return charPtr;
}

int choosePersonById() {
    string id;
    regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
    smatch m;

    for(;;) {
        cout << "Enter person id: " << endl;
        getline(cin, id);

        if(regex_search(id, rx)){
            break;
        }

        cout<<"You entered an invalid ID"<<endl;
    }

    return stoi(id);
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

        cout << "Id: " << person.getId();
        cout << " Name -> "<< person.getName() <<  endl;
    }

}

void printPerson(const Person& person){
    cout<<"Person"<<endl;
    cout<<"ID: " << person.getId()<<endl;
    cout<<"NAME: "<< person.getName()<<endl;
    cout<<"ENG: "<< person.getEgn()<<endl;
    cout<<"ADDRESS: "<< person.getAddress()<<endl;
}

void printAllEstates(const PersonEstate& personEstate){

    for(auto & i : personEstate.adr){
        if(i!= nullptr){
            cout<< "Estate Address: " << i << endl;
        }
    }
}

//OTHER
string findPersonName( const vector<Person>& people, const string& egn){
    string name;

    for(const auto& person: people){
        if(person.getEgn() == egn){
            return person.getName();
        }
    }
    return "none";
}

void findAllEstates(const string& egn, const vector<PersonEstate>& estates, const string& name){

    cout<<"All estates that belong to :" << name << "with EGN: " << egn << endl;

    for(const auto& personEstate: estates){
        if(personEstate.getPerson().getEgn() == egn){
            printAllEstates(personEstate);
            return;
        }
    }
    cout<< "This person doesnt own any estates!"<< endl;

}

bool checkIfPersonalAddressEqualToAnyOfEstate (const string& address, const PersonEstate& personEstate){
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

vector<Person> createPeople(){
    vector<Person> people;

    Person person1;

    person1.setId(1);
    person1.setName("Kristina Stoyanova");
    person1.setEgn("1234567890");
    person1.setAddress("ul Hristo Botev #97 Skutare");


    Person person2;

    person2.setId(2);
    person2.setName("Ivelin Nikolov");
    person2.setEgn("1234567891");
    person2.setAddress("ul Ivan Vazov #93 Veliko Turnavo");

    Person person3;

    person3.setId(3);
    person3.setName("Hristina Varbanova");
    person3.setEgn("1234567892");
    person3.setAddress("ul Dimcho Deleqnov #91 Veliko Turnavo");

    Person person4;

    person4.setId(4);
    person4.setName("Kristian Halachev");
    person4.setEgn("1234567893");
    person4.setAddress("ul 8mi Mart #97 Veliko Turnavo");

    Person person5;

    person5.setId(5);
    person5.setName("Valentin Aleksiev");
    person5.setEgn("1234567899");
    person5.setAddress("ul 6 septemvri #98 Plovdiv");

    Person person6;

    person6.setId(6);
    person6.setName("Georgi Georgiev");
    person6.setEgn("1234567898");
    person6.setAddress("ul Vasil Levski #99 Sofia");

    Person person7;

    person7.setId(7);
    person7.setName("Uliqn Georgiev");
    person7.setEgn("1234567897");
    person7.setAddress("ul Elin Pelin #96 Sofia");

    Person person8;

    person8.setId(8);
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
        if (i.getPerson().getId() == person.getId()){
            addAddressToPerson(&i, address);
            return;
        }
    }

    createPersonEstateObject(person,address, personEstateList);

}

//kak da napravq tova da raboti s getters and setters

void addAddressToPerson(PersonEstate *personEstate, char *address){


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

void createPersonEstateObject(const Person& person, char * address, vector<PersonEstate> *personEstateList) {
    PersonEstate personEstate;
    personEstate.setId((int)personEstateList->size()+1);
    personEstate.setPerson(person);
    personEstate.adr[0] = address;
    personEstate.adr[1]= personEstate.adr[2] = personEstate.adr[3] = personEstate.adr[4] = nullptr;

    personEstateList->push_back(personEstate);
}

Person findPersonById(int id, const vector<Person>& people){
    for (auto & i : people){
        if (i.getId() == id){
            cout << "id: " << id << endl;
            return i;
        }
    }
    Person person;

    return person;
}
