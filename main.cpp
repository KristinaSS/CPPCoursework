#include <iostream>
#include <vector>

#include "person.h"
#include "PersonEstate.h"

void addAddressToPerson(PersonEstate *personEstate, char * address);

vector<Person> createPeople ();

void printPeople (vector<Person>people);

void menu ();

void findPersonToAddAddress (Person person, vector<PersonEstate>* personEstateList);

char * enterAddress(string name);


void createPersonEstateObject(Person person, char * address, vector<PersonEstate> *personEstateList);

int choosePersonById();

Person * findPersonById(int id, vector<Person> people);

int main() {

    vector<Person> peopleVector = createPeople();

    vector<PersonEstate> personEstateList;

    menu();

    printPeople(peopleVector);

    int personId = choosePersonById();

    cout << "enter 1" <<endl;

    Person person = *findPersonById(personId, peopleVector);

    cout << "enter 2" <<endl;

    findPersonToAddAddress(person, &personEstateList);

    return 0;
}

void menu () {
    cout << "-----Menu-----" << endl;
    cout << "--------------" << endl;
    cout << "1. Add Estate to person" << endl;
    cout << "2. Find person All people where personal address is the same as one of the estate addresses" << endl;
    cout << "3. Find all Estate by person's EGN"<< endl;
    cout << "4. Exit" << endl;
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

void printPeople(vector<Person>people) {

    cout << "-----People-----" << endl;

    for (auto person: people){

        cout << "Id: " << person.getId();
        cout << " Name -> "<< person.getName() <<  endl;
    }

}

void findPersonToAddAddress (Person person, vector<PersonEstate>* personEstateList) {

    char * address = enterAddress(person.getName());

    for (auto personEstate: *personEstateList){
        if (personEstate.getPerson().getId() == person.getId()){
            addAddressToPerson(&personEstate, address);
            return;
        }
    }

    createPersonEstateObject(person,address, personEstateList);

}

char * enterAddress(string name){
    char * address;

    cout << "Enter estate address for: "<< name << endl;
    cin >> address;

    return address;
}

//kak da napravq tova da raboti s getters and setters

void addAddressToPerson(PersonEstate *personEstate, char *address){
    if(strlen(personEstate->adr[5]) != 0){
        cout<<"This person already owns 5 estates!"<<endl;
        return;
    }

    for (auto & i : personEstate->adr) {
        if(strlen(i)==0){
            i = address;
            return;
        }
    }
}

void createPersonEstateObject(Person person, char * address, vector<PersonEstate> *personEstateList) {
    PersonEstate personEstate;
    personEstate.setId(personEstateList->size()+1);
    personEstate.setPerson(person);
    personEstate.adr[0] = address;

    personEstateList->push_back(personEstate);
}

int choosePersonById() {
    int id;

    cout << "Enter person id: " << endl;
    cin >> id;

    return id;
}

Person* findPersonById(int id, vector<Person> people){
    for (size_t i= 0; i < people.size() ; i++){
        if (people[i].getId() == id){
            cout << "enter 3" << people[i].getName() <<endl;
            return &people[i];
        }
    }
    return nullptr;
}