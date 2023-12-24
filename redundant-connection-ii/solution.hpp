/*
Два случая: 
1. добавленное ребро идет в корень дерева
2. не 1

1. Тогда есть цикл, проходящий через корень дерева. 
Его можно найти следующим образом: начать с любой вершины и посмотреть,
в каком моменте мы зациклимся. Тогда эта вершина точно принадлежит циклу (он ровно 1).
Дальше в цикле найдем ребро с наибольшим индексом, оно и будет ответом.

2. Во втором случае найдется вершина, в которую входит два ребра, причем одна.
Нужно выбрать из этих двух рёбер, какое возвращать. Если ребро с большим индексом
можно удалить, при этом останется корректный граф, то возвращать нужно его.
Если останется некорректный граф, значит аналогично как в пункте 1 можно пойти
от вершины, в которую входит дублирующее ребро, и зациклиться. Иначе нельзя.

Асимптотика, память - O(n). (что круче, чем решение через Систему Непересекающихся Множеств) 
*/
class Solution {
    vector<int> parent;
    vector<int> edge_index;
    vector<bool> used;

    bool hasCycle(int current_v) {
        while (!used[current_v]) {
            used[current_v] = true;
            current_v = parent[current_v];
            if (current_v == -1) {
                return false;
            }
        }
        return true;
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        const size_t vertices_count = edges.size();
        parent.resize(vertices_count, -1);
        used.resize(vertices_count, false);
        edge_index.resize(edges.size(), 0);
        int duplicate_edge = -1;

        for (size_t i = 0; i < edges.size(); ++i) {
            const auto& edge = edges[i];
            assert(edge.size() == 2);
            int from = edge[0] - 1;
            int to = edge[1] - 1;
            if (parent[to] != -1) {
                duplicate_edge = i;
                continue;
            }
            parent[to] = from;
            edge_index[to] = i;
        }
        if (duplicate_edge != -1) {
            int to = edges[duplicate_edge][1] - 1;
            size_t result_index = hasCycle(to) ? edge_index[to] : duplicate_edge;
            return edges[result_index];
        }

        int current_v = 0;
        while (!used[current_v]) {
            used[current_v] = true;
            current_v = parent[current_v];
        }
        
        int cycle_start = current_v;
        int result = edge_index[current_v];
        current_v = parent[current_v];
        while (current_v != cycle_start) {
            result = std::max(result, edge_index[current_v]);
            current_v = parent[current_v];
        }
        return edges[result];
    }
};
