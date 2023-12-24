/*
Просят найти миностов. 
Использую алгоритм Прима.

Асимптотика O(n^2). Память O(n)
*/

int getDistance(const vector<int>& point1, const vector<int>& point2) {
    assert(point1.size() == point2.size());
    int result = 0;
    for (size_t i = 0; i < point1.size(); ++i) {
        result += abs(point1[i] - point2[i]);
    }
    return result;
}

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        vector<bool> used(points.size(), false);
        static constexpr int kInf = 1e9;
        vector<int> min_distance(points.size(), kInf);
        min_distance[0] = 0;
        int result = 0;
        for (size_t vertices_added = 0; vertices_added < points.size(); ++vertices_added) {
            int vertex_to_add = -1;
            for (int i = 0; i < points.size(); ++i) {
                if (!used[i] && 
                (vertex_to_add == -1 || min_distance[i] < min_distance[vertex_to_add])) {
                    vertex_to_add = i;
                }
            }
            assert(vertex_to_add != -1);
            result += min_distance[vertex_to_add];
            used[vertex_to_add] = true;
            for (size_t to = 0; to < points.size(); ++to) {
                if (used[to]) {
                    continue;
                }
                auto new_distance = getDistance(points[vertex_to_add], points[to]);
                min_distance[to] = std::min(min_distance[to], new_distance);
            }
        }
        return result;
    }
};

