/*
Перебираем все битовые маски. По ним строим подмножества.
Это O(2^num.size() * num.size()) времени.

Далее дедублицируем за O(klog(k) * num.size()) где k = subsets.size()
*/
class Solution {
    // придерживаюсь того же codestyle
    static bool getBit(const int mask, const int index) {
        return (mask >> index) & 1;
    }
    static multiset<int> createSubsetBy(const int mask,
            const vector<int>& nums) {
        multiset<int> subset;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (getBit(mask, i)) {
                subset.insert(nums[i]);
            }
        }
        return subset;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<multiset<int>> subsets;
        for (size_t mask = 0; mask < (1 << nums.size()); ++mask) {
            subsets.push_back(createSubsetBy(mask, nums));
        }
        ranges::sort(subsets);
        // с ranges это выглядит не лучше
        subsets.erase(unique(begin(subsets), end(subsets)), end(subsets));
        vector<vector<int>> result;
        // возможно тут можно воспользоваться stl, но зачем?
        for (auto&& subset : subsets) {
            result.push_back({subset.begin(), subset.end()});
        }
        return result;
    }
};
