/*
Используем алгоритм Краскала.
Лень писать быструю реализацию СНМ, потому что асимптотически
это то же самое. Моя реализация отвечает на запросы за O(logV)
в среднем
Асимптотика O(ElogE + ElogV) = O(ElogE)

Можно было написать алгоритм Прима с фиббоначиевой пирамидой и получить
асимптотику O(E + VlogV), но зачем?
*/
class DisjointSet {
public:
    DisjointSet(size_t size) : parent_(size) {
        std::iota(parent_.begin(), parent_.end(), 0);
    } 
    bool areInSameSet(size_t i, size_t j) {
        return getParent(i) == getParent(j);
    }
    void unionSets(size_t i, size_t j) {
        parent_[getParent(i)] = getParent(j);
    }
private:
    size_t getParent(size_t i) {
        if (parent_[i] == i) {
            return i;
        }
        return parent_[i] = getParent(parent_[i]);
    }
    vector<size_t> parent_;
};

struct Edge {
    int distance;
    size_t i;
    size_t j;    
};

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
        vector<Edge> edges;
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                edges.push_back({getDistance(points[i], points[j]), i, j});
            }
        }
        std::ranges::sort(edges, {}, &Edge::distance);
        DisjointSet connectivity_component(points.size());
        int result = 0;
        for (auto& edge : edges) {
            if (connectivity_component.areInSameSet(edge.i, edge.j)) {
                continue;
            }
            connectivity_component.unionSets(edge.i, edge.j);
            result += edge.distance;
        }
        return result;
    }
};