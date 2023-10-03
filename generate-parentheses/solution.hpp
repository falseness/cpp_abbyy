/*
аналогично задаче permutations-ii
перебираем все перестановки скобок по одному разу.
правильные скобочные последовательности сохраняем.
правильность проверяем через скобочный баланс.
*/
class Solution {
    bool isWellFormed(const std::string parentheses) {
        int balance = 0;
        for (auto bracket : parentheses) {
            assert(bracket == '(' || bracket == ')');
            balance += bracket == '(' ? 1 : -1;
            if (balance < 0) {
                return false;
            }
        }
        // баланс по построению будет 0
        assert(balance == 0);
        return true;
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        // здесь используем, что '(' < ')'
        string parentheses = std::string(n, '(') + std::string(n, ')');
        do {
            if (isWellFormed(parentheses)) {
                result.push_back(parentheses);
            }
        } while(ranges::next_permutation(parentheses).found);
        return result;
    }
};
