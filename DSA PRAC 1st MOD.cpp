/*
1.Consider a student database of SEIT class (at least 15 records). Database contains different
Fields of every student like Roll No, Name and SGPA.(array of structure)
a. Design a roll call list, arrange list of students according to roll numbers in ascending
order (Use Bubble Sort)
b. Arrange list of students alphabetically. (Use Insertion sort)
c. Arrange list of students to find out first ten toppers from a class. (Use Quick sort)
d. Search students according to SGPA. If more than one student having same SGPA,
then print list of all students having same SGPA.
e. Search a particular student according to name using binary search without recursion.
(all the student records having the presence of search key should be displayed)
(Note: Implement either Bubble sort or Insertion Sort.)*/
#include <iostream>
#include <cstring>

using namespace std;

struct student {
    int roll_no;
    char name[50];
    float sgpa;
};

void bubbleSort(student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].roll_no > arr[j + 1].roll_no) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(student arr[], int n) {
    for (int i = 1; i < n; i++) {
        student key = arr[i];
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j].name, key.name) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partition(student arr[], int low, int high) {
    student pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].sgpa >= pivot.sgpa) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void searchBySGPA(student arr[], int n, float sgpa) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].sgpa == sgpa) {
            cout << "Roll No: " << arr[i].roll_no << ", Name: " << arr[i].name << ", SGPA: " << arr[i].sgpa << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No student found with SGPA " << sgpa << endl;
    }
}

void searchByName(student arr[], int n, const char name[]) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (strcmp(arr[m].name, name) == 0) {
            cout << "Roll No: " << arr[m].roll_no << ", Name: " << arr[m].name << ", SGPA: " << arr[m].sgpa << endl;
            return;
        }
        if (strcmp(arr[m].name, name) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << "No student found with name " << name << endl;
}

void displayMenu() {
    cout << "\nOptions:\n";
    cout << "1. Design a roll call list (sorted by roll numbers in ascending order Using bubble sort)\n";
    cout << "2. Arrange list of students alphabetically Using Insertion Sort\n";
    cout << "3. Arrange list of students to find the first ten toppers from a class Using Quic Sort\n";
    cout << "4. Search students according to SGPA\n";
    cout << "5. Search a particular student according to name using binary search\n";
    cout << "6. Exit\n";
}

void performOption(int option, student arr[], int n) {
    switch (option) {
        case 1:
            cout << "\nRoll call list sorted by roll numbers in ascending order:\n";
            bubbleSort(arr, n);
            break;
        case 2:
            cout << "\nList of students sorted alphabetically:\n";
            insertionSort(arr, n);
            break;
        case 3:
            cout << "\nList of students sorted by SGPA (Top to Bottom):\n";
            quickSort(arr, 0, n - 1);
            break;
        case 4:
            float searchSGPA;
            cout << "\nEnter SGPA to search: ";
            cin >> searchSGPA;
            searchBySGPA(arr, n, searchSGPA);
            return; // Skip further output
        case 5:
            char searchName[50];
            cout << "\nEnter Name to search: ";
            cin.ignore(); // Ignore newline character left by previous input
            cin.getline(searchName, 50);
            searchByName(arr, n, searchName);
            return; // Skip further output
        case 6:
            exit(0);
        default:
            cout << "\nInvalid option. Please enter a valid option.\n";
            return; // Skip further output
    }

    // Display the sorted list
    for (int i = 0; i < n; i++) {
        cout << "Roll No: " << arr[i].roll_no << ", Name: " << arr[i].name << ", SGPA: " << arr[i].sgpa << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    student arr[n];

    // Input student data
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> arr[i].roll_no;
        cout << "Name: ";
        cin.ignore(); // Ignore newline character left by previous input
        cin.getline(arr[i].name, 50);
        cout << "SGPA: ";
        cin >> arr[i].sgpa;
    }

    int option;
    do {
        displayMenu();
        cout << "\nEnter your choice (1-6): ";
        cin >> option;

        if (option < 1 || option > 6) {
            cout << "\nInvalid option. Please enter a valid option.\n";
            continue;
        }

        performOption(option, arr, n);

    } while (option != 6);

    return 0;
}
