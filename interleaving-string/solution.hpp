
/*
будем перебирать во вложенных циклах i и j

Зафиксируем i, j.
Тогда dp[j] := можем ли из i элементов s1 и j элементов s2 построить interleaving
префикс s3 (его длина равна i + j).

Тогда имеем два перехода: последний символ может быть либо от строки s1, либо от строки s2
(подробнее в коде :) )

База очев крч.

Ответ - dp[s2.size()].

Корректность:
понятно, что если dp[s2.size()] == true, то правильный ответ действительно true
(динамика сама себя по индукции доказывает. стоит только понять, что требование
|n - m| <= 1 выполняется автоматически, как строку ни собирай)

Доказательство в обратную сторону:
замечаем, что s3 - interleaving => префикс s3 без последнего символа тоже interleaving со
строками (s1 без последнего символа и s2) или (s1 и s2 без последнего символа).
По индукции доказываем, что dp[j] == true (пусть dp[j - 1] == true. тогда dp[j] == true
следует из замечания выше.)

Время работы: O(s1.size() * s2.size())
Память: O(s2.size())
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) {
            return false;
        }
        if (s1.size() < s2.size()) {
            swap(s1, s2);
        }
        vector<bool> dp(s2.size() + 1, false);
        dp[0] = true;
        for (size_t j = 1; j <= s2.size(); ++j) {
            dp[j] = dp[j - 1] && s2[j - 1] == s3[0 + j - 1];
        }

        for (size_t i = 1; i <= s1.size(); ++i) {
            dp[0] = dp[0] && s1[i - 1] == s3[i + 0 - 1];
            for (size_t j = 1; j <= s2.size(); ++j) {
                dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return dp[s2.size()];
    }
};
