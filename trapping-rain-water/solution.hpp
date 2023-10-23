/*
Пусть left_maximum - максимум на префиксе.
Тогда до первого следующего столбца >= left_maximum вода
будет на уровне left_maximum.
Если же нет следующего столбца >= left_maximum, значит мы нашли самый правый глобальный максимум.
Для столбцов правее него применимы те же рассуждения, только с другого конца.
Можно просто сделать reverse и применить тот же алгоритм.
Время работы - O(height.size())

Через views это написать нельзя, т.к. leetcode не поддерживает.
Пробовал это переписать через ranges, но чек ranges походу тоже криво работают.
например, нельзя сделать
std::ranges::subrange new_range(ranges::begin(height), ranges::end(height));
хотя должно быть можно
*/
class Solution {
public:
    using Iterator = vector<int>::iterator;
    int trap(vector<int>& height) {
        auto [result, last_left_maximum] = calculateOneDirectionTrap(height.begin(), height.end());
        reverse(last_left_maximum, height.end());
        result += calculateOneDirectionTrap(last_left_maximum, height.end()).first;
        return result;
    }
    std::pair<int, Iterator> calculateOneDirectionTrap(Iterator begin, Iterator end) {
        int result = 0;
        Iterator left_maximum = end;
        int sum = 0;
        for (auto it = begin; it != end; ++it) {
            if (left_maximum != end && *it < *left_maximum) {
                sum += *left_maximum - *it;
                continue;
            }
            result += sum;
            left_maximum = it;
            sum = 0;
        }
        return {result, left_maximum};
    }
};
