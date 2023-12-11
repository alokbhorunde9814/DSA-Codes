/*#PROVIDED BY mr.SHLOK
10.   Department maintains student’s database. The file contains roll number, name, division and address. Write
a program to
i. create a sequential file to store and maintain student data.
ii. It should allow the user to add, delete information of student.
iii. Display information of particular student.
->Ifrecord of student does not exist an appropriate message is displayed.
->If student record is found it should display the student details.*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char FILE_NAME[] = "students.dat";
const int NAME_SIZE = 50;
const int ADDRESS_SIZE = 100;

class Student {
    int rollNo;
    char name[NAME_SIZE];
    char division;
    char address[ADDRESS_SIZE];

public:
    void getData();
    void showData();
    int getRollNo();
};

void Student::getData() {
    cout << "Enter Roll No: ";
    cin >> rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(name, NAME_SIZE);
    cout << "Enter Division: ";
    cin >> division;
    cout << "Enter Address: ";
    cin.ignore();
    cin.getline(address, ADDRESS_SIZE);
}

void Student::showData() {
    cout << "Roll No: " << rollNo << endl;
    cout << "Name: " << name << endl;
    cout << "Division: " << division << endl;
    cout << "Address: " << address << endl;
}

int Student::getRollNo() {
    return rollNo;
}

void addStudent() {
    ofstream fout(FILE_NAME, ios::binary | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    Student s;
    s.getData();
    fout.write((char*)&s, sizeof(s));
    fout.close();
}

void displayStudent(int rollNo) {
    ifstream fin(FILE_NAME, ios::binary);
    if (!fin.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    Student s;
    bool found = false;
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            s.showData();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found!" << endl;
    }

    fin.close();
}

void deleteStudent(int rollNo) {
    ifstream fin(FILE_NAME, ios::binary);
    if (!fin.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    ofstream fout("temp.dat", ios::binary);
    if (!fout.is_open()) {
        cout << "Error opening temporary file for writing!" << endl;
        fin.close();
        return;
    }

    Student s;
    bool found = false;
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() != rollNo) {
            fout.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "Student not found!" << endl;
    } else {
        cout << "Student deleted successfully!" << endl;
    }

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
}

int main() {
    int choice, rollNo;
    do {
        cout << "1. Add Student" << endl;
        cout << "2. Display Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll No: ";
                cin >> rollNo;
                displayStudent(rollNo);
                break;
            case 3:
                cout << "Enter Roll No: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
