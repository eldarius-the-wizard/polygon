#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// функция для созданяи случайного списка
std::vector<std::string> generateRandomList(int size) {
    std::vector<std::string> words = { "Orange", "Red", "Green", "Blue", "Yellow","Purple","Black","White" };
    std::vector<std::string> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = words[rand() % words.size()];
    }
    return arr;
}

int main() {
    srand(time(0));
    int size = 100;

    // делаем случайный массив
    std::vector<std::string> arr = generateRandomList(size);
    std::vector<int> result(size, 0);

    // Вывод массива
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    // Подсчет элементов и их вписывание в новый список
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        result[i] = count;
    }

    // Вывод результата
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << result[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}