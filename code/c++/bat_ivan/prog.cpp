#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

struct students {
    char name[50];
    char sub[50];
    int grade;
};

void populateStudents(students st[], int& index) {
    ifstream namesFile("names.txt");
    ifstream subjectsFile("subjects.txt");
    ifstream gradesFile("grades.txt");

    if (!namesFile || !subjectsFile || !gradesFile) {
        cerr << "Unable to open one of the files." << endl;
        return;
    }

    while (namesFile >> st[index].name && subjectsFile >> st[index].sub && gradesFile >> st[index].grade) {
        // Move to the next student
        index++;

        // Break the loop if you reach the end of the array
        if (index >= 501) {
            break;
        }
    }

    namesFile.close();
    subjectsFile.close();
    gradesFile.close();
}

void displayStudents(const students st[], int index) {
    for (int i = 0; i < index; ++i) {
        cout << "Student " << i + 1 << ": Name - " << st[i].name << ", Subject - " << st[i].sub << ", Grade - " << st[i].grade << endl;
    }
}

void addStudent(students st[], int& index) {
    if (index >= 501) {
        cout << "Array is full, cannot add more students." << endl;
        return;
    }

    cout << "Enter student's name: ";
    cin.getline(st[index].name, 50);

    cout << "Enter student's subject: ";
    cin.getline(st[index].sub, 50);

    cout << "Enter student's grade: ";
    cin >> st[index].grade;
    cin.ignore(); // Clear the input buffer

    // Increment the index for the new student
    index++;
}

void saveStudents(const students st[], int index) {
    ofstream namesFile("names.txt", ios::out | ios::trunc);
    ofstream subjectsFile("subjects.txt", ios::out | ios::trunc);
    ofstream gradesFile("grades.txt", ios::out | ios::trunc);

    if (!namesFile || !subjectsFile || !gradesFile) {
        cerr << "Unable to open one of the files for writing." << endl;
        return;
    }

    for (int i = 0; i < index; ++i) {
        namesFile << st[i].name << endl;
        subjectsFile << st[i].sub << endl;
        gradesFile << st[i].grade << endl;
    }

    namesFile.close();
    subjectsFile.close();
    gradesFile.close();

    cout << "Data saved to files successfully." << endl;
}

int countStudents(int index) {
    return index;
}

void displayStudentData(const students st[], int index, int studentIndex) {
    if (studentIndex >= 0 && studentIndex < index) {
        cout << "Student " << studentIndex + 1 << ": Name - " << st[studentIndex].name << ", Subject - " << st[studentIndex].sub << ", Grade - " << st[studentIndex].grade << endl;
    } else {
        cout << "Invalid student index." << endl;
    }
}

void editStudentData(students st[], int index, int studentIndex) {
    if (studentIndex >= 0 && studentIndex < index) {
        displayStudentData(st, index, studentIndex); // Display the current details of the student
        cout << "\nEnter new name: ";
        cin.getline(st[studentIndex].name, 50);

        cout << "Enter new subject: ";
        cin.getline(st[studentIndex].sub, 50);

        cout << "Enter new grade: ";
        cin >> st[studentIndex].grade;
        cin.ignore(); // Clear the input buffer

        cout << "Data updated for student " << studentIndex + 1 << endl;
    } else {
        cout << "Invalid student index." << endl;
    }
}

float calculateAverageGrade(const students st[], int index) {
    int totalGrades = 0;
    for (int i = 0; i < index; ++i) {
        totalGrades += st[i].grade;
    }
    if (index > 0) {
        return static_cast<float>(totalGrades) / index;
    } else {
        return 0;
    }
}

int main() {
    students st[501];
    int index = 0;

    populateStudents(st, index);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a student\n";
        cout << "2. Display all students\n";
        cout << "3. Display number of students\n";
        cout << "4. Display data for a specific student\n";
        cout << "5. Edit data for a specific student\n";
        cout << "6. Show average grade for all students\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1:
                addStudent(st, index);
                break;
            case 2:
                displayStudents(st, index);
                break;
            case 3:
                cout << "Total students: " << countStudents(index) << endl;
                break;
            case 4:
                int studentIndex;
                cout << "Enter the student index: ";
                cin >> studentIndex;
                displayStudentData(st, index, studentIndex - 1);
                break;
            case 5:
                int editIndex;
                cout << "Enter the index of the student to edit: ";
                cin >> editIndex;
                editStudentData(st, index, editIndex - 1);
                break;
            case 6:
                cout << "Average grade for all students: " << calculateAverageGrade(st, index) << endl;
                break;
            case 7:
                // Save the updated data to files before exiting
                saveStudents(st, index);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 7);

    return 0;
}
