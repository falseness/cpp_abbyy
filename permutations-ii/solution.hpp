/*
next_permutation возвращает следующую лексикографическую
перестановку. Понятно, что если мы начнем с лексикографически
наименьшей перестановки, то переберем все перестановки по 1 разу.
*/
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        ranges::sort(nums);
        do {
            result.push_back(nums);
        } while (ranges::next_permutation(nums).found);
        return result;
    }
};
