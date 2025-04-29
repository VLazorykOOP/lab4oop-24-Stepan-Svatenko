#include <iostream>
#include <string>
#include <map>
#include "tasks.h"

using namespace std;

class Human{
  string Name;
  string Surname;
  string Lastname;

  public:
    Human(string Name, string Surname, string Lastname)
    {
      this->Name = Name;
      this->Surname = Surname;
      this->Lastname = Lastname;
    }
    friend istream& operator>>(istream& is, Human& s) {
      is >> s.Name >> s.Surname >> s.Lastname;
      return is;
    }
    friend ostream& operator<<(ostream& os, Human& s) {
      os << s.Name << " " << s.Surname << " " << s.Lastname << endl;
      return os;
    }
};

class Phone{
  string Number;
  public:
    Phone(string Number)
    {
      this->Number = Number;
    }
    friend istream& operator>>(istream& is, Phone& s) {
      is >> s.Number;
      return is;
    }
    friend ostream& operator<<(ostream& os, Phone& s) {
      os << s.Number << endl;
      return os;
    }
};
template <typename Key, typename Value >
class Assoc{
  map<Key, Value> PhoneBook;
  int count;
  public:
    void add(Key Human, Value Phone){
      PhoneBook.insert(pair<Key, Value>(Human, Phone));
      count++;
    }
    Value& operator[](const Key& key){
      if(PhoneBook.find(key) != PhoneBook.end())
        return PhoneBook[key];
      else
        return PhoneBook[0];
    }
    const Key& operator()(const Value& val){
      for(const auto& pair : PhoneBook){
        if(pair.second == val)
          return pair.first;
      }
      return PhoneBook[0];
    }
    friend istream& operator>>(istream& is, Assoc& s) {
      for(const auto& pair : s.PhoneBook){
        is >> pair.first >> pair.second;
      }
      return is;
    }
    friend ostream& operator<<(ostream& os, Assoc& s) {
      for(const auto& pair : s.PhoneBook){
        os << pair.first << pair.second;
      }

      return os;
    }
};

void unit_assoc() {
  Assoc<string, string> a;
  a.add("Stepan","3800000001");
  a.add("Noname", "380000003");
  cout << a["Stepan"]<< endl;
  cout << a("3800000001")<< endl;

  cout << a << endl;
  

  
}
