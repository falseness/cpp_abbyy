/*
Рассмотрим оптимальный ответ, то есть маршруты src1 -> dest и src2 -> dest в итоговом графе. Понятно, что в какой-то момент оба маршурта посетят одну и ту же вершину (в крайнем случае, dest).
Пусть первая такая вершина - v_first. Тогда найдется оптимальный ответ, такой что:
оба маршрута начиная с v_first совпадают. 

Получается нужно найти min{distance[src1][v_first] + distance[src2][v_first] + distance[v_first][dest]} по всем v_first. 

Если знаем все distance, можем перебрать v_first.
Чтобы посчитать distance, достаточно посчитать distance от src1 и src2 до всех вершин и
distance от всех вершин до dest, что есть distance от dest до всех вершин в графе с обратными ребрами. Это умеет алгоритм Дейкстры.
*/

constexpr inline int64_t kInfinity = std::numeric_limits<int64_t>::max() / 4;
using VertexInfo = pair<int64_t, size_t>; 

vector<int64_t> DijkstraAlgorithm(const vector<vector<VertexInfo>>& graph, size_t source) {
    // distance, index
    priority_queue<VertexInfo, std::vector<VertexInfo>, std::greater<VertexInfo>> vertex_sorted; 
    vector<bool> visited(graph.size(), false);
    vector<int64_t> distance(graph.size(), kInfinity);
    distance[source] = 0;
    vertex_sorted.emplace(0, source);
    while (!vertex_sorted.empty()) {
        auto [_, vertex] = vertex_sorted.top();
        vertex_sorted.pop();
        if (visited[vertex]) {
            continue;
        }
        visited[vertex] = true;
        for (const auto& [edge_weight, to] : graph[vertex]) {
            if (visited[to]) {
                continue;
            }
            int64_t new_distance = distance[vertex] + edge_weight;
            if (new_distance >= distance[to]) {
                continue;
            }
            distance[to] = new_distance;
            vertex_sorted.emplace(new_distance, to);
        }
    }
    return distance;
}

class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<VertexInfo>> graph(n);
        auto graph_reversed = graph;

        for (const auto& edge : edges) {
            assert(edge.size() == 3);
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];

            graph[from].emplace_back(weight, to);
            graph_reversed[to].emplace_back(weight, from);
        }
        auto dist_from_src1 = DijkstraAlgorithm(graph, src1);
        auto dist_from_src2 = DijkstraAlgorithm(graph, src2);
        auto dist_to_dest = DijkstraAlgorithm(graph_reversed, dest);
        int64_t result = kInfinity;
        for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
            int64_t vertex_res = dist_from_src1[vertex] + dist_from_src2[vertex] + 
                dist_to_dest[vertex];
            result = std::min(result, vertex_res);
        }
        return result == kInfinity ? -1 : result;
    }
};
