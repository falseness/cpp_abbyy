/*
пусть построили какой-то префикс скобочной последовательности
если скобочный баланс слишком большой => добавляем )
иначе если баланс = 0 => добавляем только (
иначе можем добавить и (, и )

понятно, что после каждого перехода построенные последовательности уникальны
(доказывается по индукции).

решение не использует рекурсию, поэтому приходится баланс считать в другом vector
(разумнее было бы создать vector<std::pair<string, int>>, но тогда пришлось бы перекопировать
результат в конце). 

рекурсивное решение оказалось бы более cache-friendly, но не обязательно быстрее.

Асимптотика O(размера результата) = O(n-ое число Каталана, умноженное на n)
*/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        const size_t parentheses_size = 2 * n;
        vector<string> result = {string(parentheses_size, '\0')};
        vector<size_t> balance = {0};

        for (size_t i = 0; i < parentheses_size; ++i) {
            size_t result_old_size = result.size();
            for (size_t index_in_result = 0; index_in_result < result_old_size; ++index_in_result) {
                int empty_slots_count = parentheses_size - i;
                if (balance[index_in_result] == empty_slots_count) {
                    result[index_in_result][i] = ')';
                    --balance[index_in_result];
                    continue;
                }
                
                if (balance[index_in_result] != 0) {
                    result.push_back(result[index_in_result]);
                    result.back()[i] = ')';
                    balance.push_back(balance[index_in_result] - 1);
                }
                ++balance[index_in_result];
                result[index_in_result][i] = '(';
            }
        }
        
        return result;
    }
};
