// Програма Prog6_7.cpp
// Демонстрация на обобщен клас на опашка.
// Тоя вариант се различава от Опашка_1_хибрид_5.cpp по това, че сега в main() 
// имаме цикъл, с който да управляваме работата с опашката!

//TODO
// Ще създадем един хедър фейл в който ще има клас, в който ще има класс addrss+in_BG. Класът ще име 5 private променливи names, street, city, region, zip или postcode.
// Създайте конструктор който иницализира горните 5 полета, като в конструктора, всеки параматър да има и стойност по подразбиране. 
// Отделна да имаме 5 set-ера и get-ера, който да ...
// Да се направи специализация на функцията инпут дата за ншият нов клас. 
// Да се състави нова функция, printData() която да рзпечатва такущитят елемент на опашката. Ще направим специлизация на функцията принт дата за нашият нов клас.

#include <cstring>
#include <iostream> 
#include <memory>
#include "address.h"

using namespace std;

class Exception {
    string in;
public:
    Exception() { in = "празна грешка"; }
    Exception(string s) : in(s) {}

    string get_text() const { return in; }
};

// Създаване на обобщен клас queue, ползващ обобщен тип QType
template <typename QType = int> 
class queue {
  const int size; // размер на опашката
  unique_ptr<QType[]> q; // или //  QType *q; и new в конструктора.
  int sloc, rloc; // текуща позиция в масива за запис или за четене
  int count {};// брой на елементите в опашката;
public:
  explicit queue( int sizeArg = 4):size(sizeArg) { 
    count = sloc = rloc = 0; 
	q = make_unique<QType[]>(size); // !! ЗАБЕЛЕЖЕТЕ [] защото така сме обявили q
  }
  void qput(QType i);
  QType qget();
  QType inputData();
  void printData();
  int getCurrentSize() { return count;}// строго казано, не е необходима
};

// Поставяме обекта в опашката.
template <typename QType> 
void queue<QType>::qput(QType i){
  if(count == size) {throw Exception("Опашката е запълнена");}
  q[sloc++] = i;
  if (sloc == size) sloc = 0; //  превърти, ако е преминат края на масива
  count++;
}

template <typename QType> 
QType queue<QType>::qget(){// Извличане на обекта от опашката.
  QType buf;
  if (count == 0) { throw Exception("Опашката е празна!");}
  count--;
  if (rloc == size){rloc = 0;} //превърти, ако е преминат края на масива
  return q[rloc++];
}

template <typename QType> 
QType queue<QType>::inputData(){
	cin.sync();
	QType buf;
	cout << "Въведете име: ";
	cin >> buf; 
	return buf; 
}

// специализация на inputData за типа string
template <> 
string queue<string>::inputData(){
	cin.sync();
	string buf;
	cout << "Въведете низ, който ще поставим в опашката: : ";
	getline(cin, buf); // при cin >> buf; входът спира при първия интервал или табулация
	return buf; //
}

template <> 
address queue<address>::inputData(){
	cin.sync();
	string buf;
  address address;
	cout << "Въведете име: ";
	getline(cin, buf);
  address.setName(buf);

  cout << "Въведете регион: ";  
	getline(cin, buf);
  address.setRegion(buf);

	cout << "Въведете град: ";
	getline(cin, buf);
  address.setCity(buf);

  cout << "Въведете улица: ";
	getline(cin, buf);
  address.setStreet(buf);

  cout << "Въведете пощенски код: ";
	getline(cin, buf);
  address.setPostCode(stoi(buf));

	return buf; //
}
template <> 
void queue<address>::printData(){

  if (count == 0) {	
    if (count == 0) { throw Exception("Опашката е празна!");}
    //cout << "Опашката е празна!\n"; 
    return;
  }
  
  address obj = q[rloc];
    cout << "Name: " << obj.getName() << endl;
    cout << "Street: " << obj.getStreet() << endl;
    cout << "City: " << obj.getCity() << endl;
    cout << "Region: " << obj.getRegion() << endl;
    cout << "Zip: " << obj.getPostCode() << endl;
    cout << endl;
}

int main(){
//  setlocale (LC_ALL, "Bulgarian");
//  queue<> myq; //Създаваме опашка с тип и размер по подразбиране
// queue<> myq(5); // Създаваме опашка с тип  по подразбиране
//  queue<char> myq; // Създаваме опашка с размер по подразбиране
  queue<address> myq; // Създаваме опашка с размер по подразбиране ОТ ТИП ЗА КОЙТО ИМАМЕ СПЕЦИАЛИЗАЦИЯ
  
  cout << "__cplusplus = " << __cplusplus << endl;

  cout << "В опашката има " << myq.getCurrentSize() << " елемента." << endl;
  //cout << myq.qget() << " "<< endl; //опит за четене от празна опашка
  
  char choice;
  do {
    try{
      cout << "Въведете 'к' за Край, 'п' за постави, 'и' за извлечи: ";
      cin >> choice;
      choice = choice;
      if(choice == 'p' || choice == 'P'){
      	myq.qput(myq.inputData());
      }
      if(choice == 'i'|| choice == 'I'){
      	myq.printData();
      }
    }
    catch (Exception& e) {
      cout << "error :  " << e.get_text() << endl;
    }
  } while (choice != 'K'  && choice != 'k');
}


