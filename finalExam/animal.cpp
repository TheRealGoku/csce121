#include <iostream>
#include <vector>

using namespace std;

class Animal {
 public:
    virtual string said() {
        return "Animal said what?.";
    }
    string eat() {
        return "Animal is eating.";
    }
    Animal() {
        cout<<"Animal constructor called!"<<endl;
    }
    ~Animal() {
        cout<<"Animal destructor called!"<<endl;
    }
};

class HoneyBadger : public Animal {
 public:
    string said() {
        return "HoneyBadger growls!";
    }
    string eat() {
        return "HoneyBadger is eating.";
    }
    ~HoneyBadger() {
        cout<<"HoneyBadger destructor called!"<<endl;
    }
};

class Cricket : public Animal {
    string *said_str, *eat_str;

 public:
    Cricket() :
        said_str(new string("Cricket chirps...chirps...")),
	eat_str(new string("Cricket is eating")) {}
    ~Cricket() {
        cout<<"Cricket destructor called!"<<endl;
        delete said_str;
        delete eat_str;
    }
    string said() {
        return *said_str;
    }
    string eat()  {
        return *eat_str;
    }
};

int main () {
    vector<Animal*> animals;
    animals.push_back(new HoneyBadger());
    animals.push_back(new Cricket());
    while (animals.size()>0) {
    	cout << animals.at(0)->said() << "--";
    	cout << animals.at(0)->eat()  << endl;
    	delete animals.at(0);
    	animals.erase(animals.begin());
        // delete the first element from animals
    }
}