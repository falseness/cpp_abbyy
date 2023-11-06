/*
Если по'xor'ить все числа, получим xor двух искомых чисел.
Поскольку они различные, полученное число имеет ненулевой бит.

С помощью a & (-a) получаем самый правый бит (здесь используем
явно представление отрицательных чисел. это то же самое, что 
a & (~(a - 1)). Используем unsigned int, т.к. с обычным int'ом возникает
UB при взятии -a)

Далее раз у искомых двух чисел xor в этом бите = 1, значит
они в этом бите различаются. Разобьем все числа по этому биту
на две группы и по'xor'им.
*/

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unsigned int two_numbers_xor = std::accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        int right_bit = two_numbers_xor & (-two_numbers_xor);
        vector<int> result(2, 0);
        for (auto num : nums) {
            result[(bool)(num & right_bit)] ^= num;
        }
        return result;
    }
};
