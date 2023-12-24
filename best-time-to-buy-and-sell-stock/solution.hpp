/*
Нужно найти i, j : i < j и prices[j] - prices[i] -> max
Достаточно поддержать минимум на префиксе
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minimum = prices[0];
        int result = 0;
        for (auto price : prices) {
            result = std::max(result, price - minimum);
            minimum = std::min(minimum, price);
        }
        return result;
    }
};
