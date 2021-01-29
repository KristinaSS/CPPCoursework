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

void addToFileAllPeopleWithTheirEstates(const vector<PersonEstate>& personEstateList);

//Мейн функцията
int main() {

    vector<Person> peopleVector = createPeople(); //Инициализирам personVector със хора

    vector<PersonEstate> personEstateList; // създаваме вектор-а personEstateList

    int option; //в тази променлива записваме стойност на опцията която ще въведем
    bool isActive = true; // проверява дали сме готови да излезнем от безкрайния цикъл

    while (isActive) {
        menu();// викаме функция за приниране на менюто
        option = chooseMenuOption(); // викаме функция да дадем стойност на променливата option

        switch (option) {//използваме switch-case да избирем в коя функционалност ще влезнем
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
                cout << "Goodbye!" << endl; // излизаме от цикъла
                isActive = false; // задаваме isActive на false за да можем да излезнем от цикъла
                break;
            default:
                cout << "Not a valid option." << endl; // при опция която не е валидна
                break;
        }

    }

    addToFileAllPeopleWithTheirEstates(personEstateList); // викаме фунция която записва всички хора с поне един имот във файл

    return 0;
}

//Опции от менюто

//функция която вика набор от други функции за да запише адрес на имот който човека притежава
void addEstateToPerson (vector<Person> * people, vector<PersonEstate> *estates){

    printPeople(*people);// вика функция която изписва всички хора със имената им и егн-тата им

    string personEGN = Person::enterPersonEGN();// запиваш във personEGN егн-то на човек, на който искаш да запишеш адреса на имота

    Person person = Person::findPersonByEGN(personEGN, *people);// намираш човека със егн-то което си въвел

    if(person.getEgn() == "none"){ //ако егн-то е "none" означава, че няма човек с такова ЕГН и се излиза от функцията
        cout<<"There are no people with this EGN: "<< personEGN << endl;
        return;
    }

    findPersonToAddAddress(person, estates); // вика се фунция която създава personEstate обект, и я добавя във вектора estates
}

//Вика функции с цел да изведе инфорацията за лицата, чиито адрес съвпада с някой от адресите на притежаваните имоти
void findAllPeopleThatPersonAddressIsTheSameOneOfEstate(const vector<PersonEstate> &estates) {
    string personAddress;
    int isFoundPerson = 0;//индикатор дали е намерен човека

    for (auto & estate : estates){
        personAddress = estate.getAddress();

        if(PersonEstate::checkIfPersonalAddressEqualToAnyOfEstate(personAddress, estate)){
            Person::printPerson(estate);// ако е намерен такъв човек се притира в конзолата
            isFoundPerson = 1;// маркера става на 1
        }
    }

    if(isFoundPerson == 0){// ако маркера остане 0 означава, че не е намерен такъв човек и принтира съобщение в конзолата
        cout<< "No People had the same personal address as one of their estates " << endl;
    }
}

//Вика функции с цел да изведе притежаваните имоти от лице, зададено от ЕГН-то
void findAllEstatesByEGN(const vector<PersonEstate>& estates, const vector<Person>& people){
    string egn = enterEGN();//Вика функция за въвеждане на егн

    string name = Person::findPersonName(people, egn);//намира името на човека ако няма такъв човек с такова егн връша "none"

    if(name == "none"){
        cout<<"There are no people with this EGN: "<< egn << endl;
        return;
    }

    PersonEstate::findAllEstates(egn, estates, name);//вика се функция която изважда адресите на всички хора с това егн
}

//Фунции за въвеждане на информация

//Фиункция която връща адрес който да се запомети като имот на някого
char * enterAddress(const string& name){
    string address;

    cout << "Enter estate address for: "<< name << endl;
    getline(cin, address);

    cout << "enter address: "<< address << endl;

    char * charPtr = new char[address.length() + 1];
    strcpy(charPtr, address.c_str());

    return charPtr;
}

//функция за въвеждане за избор на опция от менюо
int chooseMenuOption(){
    string option;
    regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))"); // регекс който проверява дали стринга е чило
    smatch m;

    for(;;) {
        cout << "Choose menu Option:" << endl;
        getline(cin, option);

        if(regex_search(option, rx) && (option =="1" || option == "2" || option == "3" || option == "4")){// проверява дали стринга е раен на 1,2,3 или 4 (единствените избори)
            break;
        }

        cout<<"You entered an invalid option"<<endl;

    }

    return stoi(option);
}

//функция за въвеждане на ЕГН
string enterEGN(){
    string egn;
    regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");// регекс който проверява дали стринга е чило
    smatch m;

    for (;;) {
        cout << "Enter the person's EGN:" << endl;
        getline(cin, egn);

        if(regex_search(egn, rx)){//проверява дали въведеното е стринг от само от цифри
            break;
        }

        cout<<"You entered an invalid egn"<<endl;
    }

    return egn;
}

//Функции за принтиране на информация

//фунция за притиране на менюто
void menu () {
    cout << "-----Menu-----" << endl;
    cout << "--------------" << endl;
    cout << "1. Add Estate to person" << endl;
    cout << "2. Find All people where personal address is the same as one of the estate addresses" << endl;
    cout << "3. Find all Estate by person's EGN"<< endl;
    cout << "4. Exit" << endl;
}

//фунжия за приниране на информация за хората
void printPeople(const vector<Person>&people) {

    cout << "-----People-----" << endl;

    for (const auto& person: people){

        cout << "EGN: " << person.getEgn();
        cout << " Name -> "<< person.getName() <<  endl;
    }

}

//Други функции

//фунция която иницилизира вектор пълен с хора
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

//набор от фунции които имат за цел с въведения адрвс да се добави към масива от адреси на  имоти на даден човек
void findPersonToAddAddress (const Person& person, vector<PersonEstate>* personEstateList) {

    char * address = enterAddress(person.getName());// вика се фунция за въвеждане не адреса

    for (auto & i : *personEstateList){
        if (i.getEgn() == person.getEgn()){
            PersonEstate::addAddressToPerson(&i, address);//вика се фунция за добавяне на този адрес към човека
            return;
        }
    }

    PersonEstate::createPersonEstateObject(person.getName(),person.getEgn(), person.getAddress(),address, personEstateList);//вика се функция за да се добави елемент към вектора от имоти
}

//фунция за записване във файл всички хора които имат имоти и техните имоти във файла "data.txt"
void addToFileAllPeopleWithTheirEstates(const vector<PersonEstate>& personEstateList){
    for(const auto& i : personEstateList){
        PersonEstate::addToFile(i, "data.txt");//вика се фунция да се запише съответния обек във файла
    }
}

