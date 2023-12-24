/*
Решение, похожее на предыдущее. 
Используем два указателя. Поддерживаем, на префиксе
или на суффиксе самый высокий столбец. Например, если
на префиксе столбец меньше, то можем обновить результат на префиксе
(аналогично как предыдущем решении).
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int result = 0;
        size_t l = 0;
        size_t r = height.size() - 1;
        int l_maximum = 0;
        int r_maximum = 0;
        while (l < r) {
            l_maximum = std::max(l_maximum, height[l]);
            r_maximum = std::max(r_maximum, height[r]);
            result += l_maximum < r_maximum ? l_maximum - height[l++] :
                                              r_maximum - height[r--];  
        }
        return result;
    }
};

