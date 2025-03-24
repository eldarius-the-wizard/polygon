#include <iostream>
#include <vector>

struct Item {
    int weight;
    int cost;
};

// function dlya perebora
void findsubset(const std::vector<Item>& items, int index, int current_weight, int current_cost,
    int weight_limit, std::vector<int>& current_selection, std::vector<int>& best_selection, int& best_cost) {
    // proverka na luchshee reshenie
    if (index == items.size()) {
        if (current_weight <= weight_limit && current_cost > best_cost) {
            best_cost = current_cost;
            best_selection = current_selection;
        }
        return;
    }

    // variant ne vkluchat predmet
    findsubset(items, index + 1, current_weight, current_cost, weight_limit,
        current_selection, best_selection, best_cost);

    // variant vkluchit predmet
    current_selection.push_back(items[index].weight);
    findsubset(items, index + 1, current_weight + items[index].weight, current_cost + items[index].cost, weight_limit,
        current_selection, best_selection, best_cost);
    current_selection.pop_back();
}

int main() {
    std::vector<Item> items = { {2, 3}, {3, 4}, {4, 5}, {1, 4}, {2, 4} };
    int weight_limit = 5;

    std::vector<int> current_selection;
    std::vector<int> best_selection;
    int best_cost = 0;

    findsubset(items, 0, 0, 0, weight_limit, current_selection, best_selection, best_cost);

    // vivod resultata
    std::cout << "[";
    for (int i = 0; i < best_selection.size(); i++) {
        std::cout << best_selection[i];
        if (i < best_selection.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]\n";
    std::cout << "(максимальная стоимость " << best_cost << ")" << std::endl;

    return 0;
}
