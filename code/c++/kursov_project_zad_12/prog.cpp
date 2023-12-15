#include <iostream>
#include <map>
#include <string.h>
using namespace std;

struct Citizen {
    char name[50];
    int age;
    int yearlySalary;
    char education[30];
    enum Profession { SALES_PERSON, DRIVER, DOCTOR, ARMY, TRANSLATOR };
    Profession profession;
};
string getProfessionName(Citizen::Profession profession) {
    switch (profession) {
        case Citizen::SALES_PERSON:
            return "Sales Person";
        case Citizen::DRIVER:
            return "Driver";
        case Citizen::DOCTOR:
            return "Doctor";
        case Citizen::ARMY:
            return "Army";
        case Citizen::TRANSLATOR:
            return "Translator";
        default:
            return "Unknown Profession";
    }
}


void showCitizen(Citizen citizens[], int count) {
    cout << "Entered data for citizens:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << "Citizen " << i + 1 << " - Name: " << citizens[i].name << ", Age: " << citizens[i].age
             << ", Yearly Salary: " << citizens[i].yearlySalary << ", Education: " << citizens[i].education
             << ", Profession: " << getProfessionName(citizens[i].profession) << endl;
    }
}


void showOldestPerson(Citizen citizens[], int count) {
    int oldestAge = -1;
    int oldestIndex = -1;

    for (int i = 0; i < count; ++i) {
        if (citizens[i].age > oldestAge) {
            oldestAge = citizens[i].age;
            oldestIndex = i;
        }
    }

    if (oldestIndex != -1) {
        cout << "\nThe oldest person is: " << citizens[oldestIndex].name << " with age " << citizens[oldestIndex].age
             << ", Yearly Salary: " << citizens[oldestIndex].yearlySalary << ", Education: " << citizens[oldestIndex].education
             << ", Profession: " << getProfessionName(citizens[oldestIndex].profession) << endl;
    } else {
        cout << "\nNo citizens found!" << endl;
    }
}

void findHighestAverageSalary(Citizen citizens[], int count) {
    map<Citizen::Profession, pair<int, int>> professionSalaryMap; // Map to store total salary and count for each profession

    for (int i = 0; i < count; ++i) {
        professionSalaryMap[citizens[i].profession].first += citizens[i].yearlySalary;
        professionSalaryMap[citizens[i].profession].second++;
    }

    double highestAverage = 0;
    Citizen::Profession highestProfession = Citizen::SALES_PERSON;

    for (const auto &pair : professionSalaryMap) {
        double averageSalary = static_cast<double>(pair.second.first) / pair.second.second;

        if (averageSalary > highestAverage) {
            highestAverage = averageSalary;
            highestProfession = pair.first;
        }
    }

    cout << "\nThe profession with the highest average salary is " << getProfessionName(highestProfession)
         << " with an average salary of $" << highestAverage << endl;
}
void showCitizensByProfession(Citizen citizens[], int count, Citizen::Profession profession) {
    cout << "Citizens with Profession " << getProfessionName(profession) << ":" << endl;
    bool found = false;

    for (int i = 0; i < count; ++i) {
        if (citizens[i].profession == profession) {
            found = true;
            cout << "Name: " << citizens[i].name << ", Age: " << citizens[i].age
                 << ", Yearly Salary: " << citizens[i].yearlySalary << ", Education: " << citizens[i].education << endl;
        }
    }

    if (!found) {
        cout << "No citizens found with this profession." << endl;
    }
}
void showCitizensByEducation(Citizen citizens[], int count, const char* education) {
    cout << "Citizens with Education " << education << ":" << endl;
    bool found = false;

    for (int i = 0; i < count; ++i) {
        if (strcmp(citizens[i].education, education) == 0) {
            found = true;
            cout << "Name: " << citizens[i].name << ", Age: " << citizens[i].age
                 << ", Yearly Salary: " << citizens[i].yearlySalary << ", Profession: "
                 << getProfessionName(citizens[i].profession) << endl;
        }
    }

    if (!found) {
        cout << "No citizens found with this education." << endl;
    }
}
void sortByAge(Citizen citizens[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (citizens[j].age > citizens[j + 1].age) {
                // Swap the elements if they are in the wrong order
                Citizen temp = citizens[j];
                citizens[j] = citizens[j + 1];
                citizens[j + 1] = temp;
            }
        }
    }
}
void showEducationWithLowestSalary(Citizen citizens[], int count) {
    map<string, int> lowestSalaryByEducation;

    // Manually set a high initial maximum salary value
    const int MAX_SALARY = 2147483647; // Using the maximum value for a signed int

    // Initialize lowest salary for each education level to a high value
    for (int i = 0; i < count; ++i) {
        if (lowestSalaryByEducation.find(citizens[i].education) == lowestSalaryByEducation.end()) {
            lowestSalaryByEducation[citizens[i].education] = MAX_SALARY;
        }
    }

    // Find the lowest salary for each education level
    for (int i = 0; i < count; ++i) {
        if (citizens[i].yearlySalary < lowestSalaryByEducation[citizens[i].education]) {
            lowestSalaryByEducation[citizens[i].education] = citizens[i].yearlySalary;
        }
    }

    // Find the lowest salary among all education levels
    int lowestSalary = MAX_SALARY;
    string lowestEducation;

    for (const auto &pair : lowestSalaryByEducation) {
        if (pair.second < lowestSalary) {
            lowestSalary = pair.second;
            lowestEducation = pair.first;
        }
    }

    // Display education with the lowest salary
    cout << "Education with the lowest salary is: " << lowestEducation << " with a lowest salary of $" << lowestSalary << endl;
}



int main() {
    Citizen citizens[6] = {
        {"Alice", 30, 50000, "Bachelor's", Citizen::SALES_PERSON},
        {"Bob", 25, 60000, "Master's", Citizen::DRIVER},
        {"Charlie", 35, 70000, "PhD", Citizen::DOCTOR},
        {"David", 40, 80000, "Bachelor's", Citizen::SALES_PERSON},
        {"Eva", 28, 55000, "Master's", Citizen::DOCTOR},
        {"Frank", 32, 65000, "PhD", Citizen::TRANSLATOR}
    };

    showCitizen(citizens, 6);

    showOldestPerson(citizens, 6);

    findHighestAverageSalary(citizens, 6);

    showCitizensByEducation(citizens, 6, "Bachelor's");

    sortByAge(citizens, 6);

    showCitizensByProfession(citizens, 6, Citizen::DOCTOR);

    showEducationWithLowestSalary(citizens, 6);


    


    return 0;
}



/*Задача 12. В структура се съхранява следната информация за граждани - Име и фамилия (в един низ), възраст (всички над 18 години), годишен доход в лева, степен на образование (начално, основно средно, висше), професия - с enum около 5 професии

Напишете програма, която предлага на потребителя следните възможности:

DONE а) Създава в main() масив от тип посочената структура, съдържащ информация за N записа (N около 20) ; 

DONE б) Намира най-възрастния човек;                                                                     

DONE в) Намира професията с най-висок среден доход;

DONE г) Извежда на екран хората с избрано образование.

DONE д) Подрежда масива по възраст;

DONE е) Разпечатва хората от избрана професия.

DONE ж) Намира коя степен на образование има най-нисък доход;

DONE з) Разпечатва масива;

Програмата да се оформи с меню за избор, като всяка подточка без а) бъде отделна функция.

Масивът да е предварително инициализиран, за да не се губи време за въвеждане при всяко пускане на програмата.

Ще ни трябва и масив(и) с размер брой професиите за някои от подточките. */
