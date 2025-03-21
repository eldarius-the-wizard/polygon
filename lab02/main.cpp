#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// ������� ��� �������� ���������� ������
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

    // ������ ��������� ������
    std::vector<std::string> arr = generateRandomList(size);
    std::vector<int> result(size, 0);

    // ����� �������
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    // ������� ��������� � �� ���������� � ����� ������
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        result[i] = count;
    }

    // ����� ����������
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << result[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}