/*
Сначала считаем количество вхождений каждого числа.
Перебираем числа
Пусть дошли до числа x. Оно встречается k раз. 
уже построили все подмножества из чисел < x по предположению индукции.
Тогда для перехода нужно добавить ко всем старым подмножествам число x
0, 1, 2, ..., k раз.

чтобы уменьшить константу времени, можно добавить сначала элементы с 1 x'ом, потом
по ним построить с 2 x'ами, и т.д.

Ещё решение не использует рекурсию, что тоже улучшает время, хотя на таком размере данных это незаметно.
асимптотика O(kMaximumNumValue - kMinimumNumValue) + O(размер ответа).  
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        static constexpr int kMaximumNumValue = 10;
        static constexpr int kMinimumNumValue = -10;
        static_assert(kMinimumNumValue <= kMaximumNumValue);
        std::array<size_t, kMaximumNumValue - kMinimumNumValue + 1> occurences_count = {0};
        // думаю не нужно заменять 3 строчки на stl алгоритм
        for (int number : nums) {
            ++occurences_count[number - kMinimumNumValue];
        }
        for (int shifted_number = 0; shifted_number < occurences_count.size();
                ++shifted_number) { 
            int number = shifted_number + kMinimumNumValue;
            size_t iterations_count = result.size() * occurences_count[shifted_number];
            for (size_t i = 0; i < iterations_count; ++i) {
                result.push_back(result[i]);
                result.back().push_back(number);
            }
        }
        return result;
    }
};
