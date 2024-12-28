#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define HEAP_SORT // Активируйте одну из директив: BRICK_SORT, HEAP_SORT, FLASH_SORT

using namespace std;

// Функция создания случайного списка
vector<int> generateRandomList(int size) {
    vector<int> arr(size);
    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
    return arr;
}

// Функция для вывода первых и последних элементов списка
void printArray(const vector<int>& arr, int limit = 10) {
    int n = arr.size();
    for (int i = 0; i < limit && i < n; i++) {
        cout << arr[i] << " ";
    }
    if (n > limit) {
        cout << "... ";
        for (int i = n - limit; i < n; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

// Brick Sort
#ifdef BRICK_SORT
void brickSort(vector<int>& arr) {
    int n = arr.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        // Чётные индексы
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        // Нечётные индексы
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}
#endif

// Heap Sort
#ifdef HEAP_SORT
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
#endif

// Flash Sort
#ifdef FLASH_SORT
void flashSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    int minVal = arr[0], maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }

    if (arr[maxIdx] == minVal) return;

    int m = int(0.1 * n);
    vector<int> L(m, 0);

    double c = double(m - 1) / (arr[maxIdx] - minVal);

    for (int i = 0; i < n; i++) {
        int k = int(c * (arr[i] - minVal));
        L[k]++;
    }

    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    swap(arr[maxIdx], arr[0]);
    int count = 0, i = 0, k = m - 1;

    while (count < n) {
        while (i > L[k] - 1) {
            i++;
            k = int(c * (arr[i] - minVal));
        }

        int evicted = arr[i];
        while (i != L[k]) {
            k = int(c * (evicted - minVal));
            swap(evicted, arr[--L[k]]);
            count++;
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = L[i - 1]; j < L[i]; j++) {
            int key = arr[j];
            int l = j - 1;
            while (l >= L[i - 1] && arr[l] > key) {
                arr[l + 1] = arr[l];
                l--;
            }
            arr[l + 1] = key;
        }
    }
}
#endif

int main() {
    const int SIZE = 1000000;
    vector<int> arr = generateRandomList(SIZE);

    cout << "Array size: " << SIZE << endl;

    cout << "Initial array (first and last 10 elements):" << endl;
    printArray(arr);

    clock_t start = clock();

#ifdef BRICK_SORT
    brickSort(arr);
#elif defined(HEAP_SORT)
    heapSort(arr);
#elif defined(FLASH_SORT)
    flashSort(arr);
#endif

    clock_t end = clock();

    cout << "Sorted array (first and last 10 elements):" << endl;
    printArray(arr);

    cout << "Time taken: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}