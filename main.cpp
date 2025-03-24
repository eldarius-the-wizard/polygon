#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

// generirum sluchainie stroki
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

    // vivod massiva
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    // schitaem cherez "unordered map"
    std::unordered_map<std::string, int> frequency;
    for (const auto& word : arr) {
        frequency[word]++;
    }

    // zapolnyaem massiv chislami
    for (int i = 0; i < size; i++) {
        result[i] = frequency[arr[i]];
    }

    // vivod resultata
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << result[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}
