#include <string>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        int max_length = 0;

        // Первый проход: слева направо
        int left = 0, right = 0;
        for (char c : s) {
            if (c == '(') {
                left++;
            }
            else {
                right++;
            }

            if (left == right) {
                max_length = std::max(max_length, 2 * right);
            }
            else if (right > left) {
                left = right = 0;
            }
        }

        // Второй проход: справа налево
        left = right = 0;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            if (*it == ')') {
                right++;
            }
            else {
                left++;
            }

            if (left == right) {
                max_length = std::max(max_length, 2 * left);
            }
            else if (left > right) {
                left = right = 0;
            }
        }

        return max_length;
    }
};