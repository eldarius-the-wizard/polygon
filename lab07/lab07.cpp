#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        long long money_spent = 0;
        int m = values.size();
        int n = values[0].size();

        // ������� ��� ������������ ������������� �������� ������ ������
        priority_queue<pair<int, int>> maxHeap;

        // �������������: ��������� ������ �������� ������ ������ � ����
        for (int i = 0; i < m; ++i) {
            if (!values[i].empty()) {
                maxHeap.push({ values[i][0], i }); // ��������� (��������, ������ ������)
            }
        }

        for (int day = m * n; day > 0; --day) {
            if (maxHeap.empty()) break;

            // ��������� ������������ �������
            auto [maximal_value, row] = maxHeap.top();
            maxHeap.pop();

            // ����������� ����� ������
            money_spent += static_cast<long long>(day) * maximal_value;

            // ������� �������������� ������� �� ������
            values[row].erase(values[row].begin());

            // ���� � ������ �������� ��������, ��������� ��������� � ����
            if (!values[row].empty()) {
                maxHeap.push({ values[row][0], row }); // ����� ������ ������� ������
            }
        }

        return money_spent;
    }
};
