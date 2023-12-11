/*#PROVIDED BY mr.SHLOK
9.   Implement Heap sort to sort given set of values using max or min heap.*/
#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& arr, int n, int i, bool isMaxHeap) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (isMaxHeap) {
        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;
    } else {
        if (left < n && arr[left] < arr[largest])
            largest = left;

        if (right < n && arr[right] < arr[largest])
            largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, isMaxHeap);
    }
}

void buildHeap(vector<int>& arr, bool isMaxHeap) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, isMaxHeap);
    }
}

void heapSort(vector<int>& arr, bool isMaxHeap) {
    buildHeap(arr, isMaxHeap);

    for (int i = arr.size() - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, isMaxHeap);
    }
}

int main() {
    while (true) {
        int n;

        // Input the number of elements
        cout << "Enter the number of elements (0 to exit): ";
        cin >> n;

        if (n == 0) {
            cout << "Exiting...\n";
            break;
        }

        // Input the elements
        vector<int> arr(n);
        cout << "Enter the elements:\n";
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        // Choose heap type
        int heapType;
        cout << "Choose the heap type:\n";
        cout << "1. Max Heap\n";
        cout << "2. Min Heap\n";
        cout << "3. Both Max and Min Heap\n";
        cout << "Enter your choice: ";
        cin >> heapType;

        if (heapType == 1) {
            heapSort(arr, true);
            cout << "Max Heap Sorted array: ";
        } else if (heapType == 2) {
            heapSort(arr, false);
            cout << "Min Heap Sorted array: ";
        } else if (heapType == 3) {
            vector<int> originalArr = arr; // Save original array
            heapSort(arr, true);
            cout << "Max Heap Sorted array: ";
            for (int i : arr) {
                cout << i << " ";
            }
            cout << endl;

            // Restore original array
            arr = originalArr;
            heapSort(arr, false);
            cout << "Min Heap Sorted array: ";
        } else {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        for (int i : arr) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
