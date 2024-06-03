#include <iostream>
#include <cstring>
#include <algorithm>  // Add this line for the min function

using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float sgpa;
};

void displayStudents(Student students[], int size) {
    cout << "Roll No\tName\t\tSGPA\n";
    for (int i = 0; i < size; ++i) {
        cout << students[i].rollNo << "\t" << students[i].name << "\t\t" << students[i].sgpa << "\n";
    }
}

void bubbleSortByRollNo(Student students[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void insertionSortByName(Student students[], int size) {
    for (int i = 1; i < size; ++i) {
        Student key = students[i];
        int j = i - 1;

        while (j >= 0 && strcmp(students[j].name, key.name) > 0) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

int partitionQuickSort(Student students[], int low, int high) {
    Student pivot = students[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (students[j].sgpa >= pivot.sgpa) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSortBySGPA(Student students[], int low, int high) {
    if (low < high) {
        int pi = partitionQuickSort(students, low, high);

        quickSortBySGPA(students, low, pi - 1);
        quickSortBySGPA(students, pi + 1, high);
    }
}

void searchBySGPA(Student students[], int size, float targetSGPA) {
    cout << "Students with SGPA " << targetSGPA << ":\n";
    for (int i = 0; i < size; ++i) {
        if (students[i].sgpa == targetSGPA) {
            cout << students[i].rollNo << "\t" << students[i].name << "\n";
        }
    }
}

int binarySearchByName(Student students[], int size, const char targetName[]) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int result = strcmp(students[mid].name, targetName);

        if (result == 0) {
            return mid;
        } else if (result < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Not found
}

int main() {
    const int maxSize = 15;
    Student students[maxSize];

    // Input data for each student
    for (int i = 0; i < maxSize; ++i) {
        cout << "Enter details for Student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> students[i].rollNo;
        cout << "Name: ";
        cin.ignore();
        cin.getline(students[i].name, sizeof(students[i].name));
        cout << "SGPA: ";
        cin >> students[i].sgpa;
    }

    int choice;
    int result = -1;  // Declare result outside the switch statement
    do {
        cout << "\n1. Display Students\n";
        cout << "2. Sort by Roll No (Bubble Sort)\n";
        cout << "3. Sort by Name (Insertion Sort)\n";
        cout << "4. Find Top 10 Toppers (Quick Sort)\n";
        cout << "5. Search by SGPA\n";
        cout << "6. Search by Name (Binary Search)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayStudents(students, maxSize);
                break;
            case 2:
                bubbleSortByRollNo(students, maxSize);
                cout << "Sorted by Roll No (Bubble Sort):\n";
                displayStudents(students, maxSize);
                break;
            case 3:
                insertionSortByName(students, maxSize);
                cout << "Sorted by Name (Insertion Sort):\n";
                displayStudents(students, maxSize);
                break;
            case 4:
                quickSortBySGPA(students, 0, maxSize - 1);
                cout << "Top 10 Toppers (Quick Sort):\n";
                displayStudents(students, min(maxSize, 10));
                break;
            case 5:
                float targetSGPA;
                cout << "Enter target SGPA: ";
                cin >> targetSGPA;
                searchBySGPA(students, maxSize, targetSGPA);
                break;
            case 6:
                char targetName[50];
                cout << "Enter target name: ";
                cin.ignore();
                cin.getline(targetName, sizeof(targetName));
                result = binarySearchByName(students, maxSize, targetName);
                if (result != -1) {
                    cout << "Student found at index " << result << ":\n";
                    cout << students[result].rollNo << "\t" << students[result].name << "\t" << students[result].sgpa << "\n";
                } else {
                    cout << "Student not found.\n";
                }
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 0);

    return 0;
}

