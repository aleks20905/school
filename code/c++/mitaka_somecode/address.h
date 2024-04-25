#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
using namespace std;

class address{
  string name, region, city, street;
  unsigned int postCode;
public:
  address(
  string nameArg="Христо Ботев",
  string regionArg="Карлово", 
  string cityArg="Калофер",
  string streetArg="Христо Ботев",
  unsigned int postCodeArg = 4370)
  {
    name = nameArg ;
    region = regionArg; 
    city = cityArg;
    street = streetArg;
    postCode = postCodeArg;
  }

  void setName(string in){name = in;}
  void setRegion(string in){region = in;}
  void setCity(string in){city = in;}
  void setStreet(string in){street = in;}
  void setPostCode(unsigned int in){postCode = in;}

  string getName(){return name;}
  string getRegion(){return region;}
  string getCity(){return city;}
  string getStreet(){return street;}
  unsigned int getPostCode(){return postCode;}
};

#endif
