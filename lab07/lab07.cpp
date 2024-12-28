#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        long long money_spent = 0;
        int m = values.size();
        int n = values[0].size();

        // Очередь для отслеживания максимального элемента каждой строки
        priority_queue<pair<int, int>> maxHeap;

        // Инициализация: добавляем первые элементы каждой строки в кучу
        for (int i = 0; i < m; ++i) {
            if (!values[i].empty()) {
                maxHeap.push({ values[i][0], i }); // Добавляем (значение, индекс строки)
            }
        }

        for (int day = m * n; day > 0; --day) {
            if (maxHeap.empty()) break;

            // Извлекаем максимальный элемент
            auto [maximal_value, row] = maxHeap.top();
            maxHeap.pop();

            // Увеличиваем сумму затрат
            money_spent += static_cast<long long>(day) * maximal_value;

            // Удаляем использованный элемент из строки
            values[row].erase(values[row].begin());

            // Если в строке остались элементы, добавляем следующий в кучу
            if (!values[row].empty()) {
                maxHeap.push({ values[row][0], row }); // Новый первый элемент строки
            }
        }

        return money_spent;
    }
};
