/*
Ну dfs тупа
*/
class Solution {
    static constexpr char kUsed = '2';
    static constexpr char kIsland = '1';
    static constexpr char kWater = '0';
    void dfs(int i, int j, vector<vector<char>>& grid) {
        static constexpr size_t kNeighbourCellsCount = 4;
        static constexpr int di[] = {0, 0, 1, -1};
        static constexpr int dj[] = {1, -1, 0, 0};
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[i].size()) {
            return;
        }
        if (grid[i][j] != kIsland) {
            return;
        }
        grid[i][j] = kUsed;
        for (size_t index = 0; index < kNeighbourCellsCount; ++index) {
            dfs(i + di[index], j + dj[index], grid);
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] != kIsland) {
                    continue;
                }
                ++result;
                dfs(i, j, grid);
            }
        }
        return result;
    }
};
