#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>

typedef int32_t vertex_t;
typedef int32_t weight_t;
const weight_t weightMax = INT32_MAX;
struct Edge
{
    vertex_t to;
    weight_t weight;
};
typedef std::vector<std::vector<Edge>> graph_t;

void printDistances(const std::vector<weight_t> &distance, int n)
{
    std::cout << "distance[]: ";
    for (int i=1; i<=n; ++i)
        std::cout << distance[i] << " ";
    std::cout << "\n";
}

void printVisited(const std::vector<bool> &visited, int n)
{
    std::cout << "visited[]: ";
    for (int i=1; i<=n; ++i)
        std::cout << visited[i] << " ";
    std::cout << "\n";
}

weight_t dijkstra(const vertex_t start, const vertex_t end, const graph_t &graph, const int n)
{
    std::vector<bool> visited(n+1);
    std::vector<weight_t> distance(n+1);
    // std::vector<vertex_t> pred(n+1);

    for (int i=1; i<=n; ++i)
    {
        visited[i] = false;
        distance[i] = weightMax;
        // std::cout << distance[i] << " ";
        // pred[i] = 0; // nil
    }
    // std::cout << "\n";

    visited[start] = true;
    distance[start] = 0;

    auto cmp = [](Edge left, Edge right) { return (left.weight > right.weight); }; // TODO
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);

    // printDistances(distance, n);
    // printVisited(visited, n);

    // std::cout << "connected to start: ";
    for (const auto &edge : graph[start])
    {
        // std::cout << edge.to << " ";
        pq.push(edge);
    }
    // std::cout << "\n";

    // not all visited
    while (!pq.empty())
    {
        Edge x = pq.top();
        pq.pop();

        // std::cout << "PQ top: " <<  x.to << ", w: " << x.weight << "\n";

        if (!visited[x.to])
        {
            visited[x.to] = true;
            distance[x.to] = x.weight;
            for (const auto &edge : graph[x.to])
                pq.push({edge.to, distance[x.to] + edge.weight});
                // if (!visited[edge.to]) // if (distance[x.to] + edge.weight < distance[edge.weight])

        }

        // printDistances(distance, n);
        // printVisited(visited, n);
    }

    return distance[end];
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int testCase=1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n; // intersections
        std::cin >> n;
        int m; // walking trails
        std::cin >> m;

        graph_t graph (n+1);
        for (int i=1; i<=m; ++i)
        {
            int from, to, weight;
            std::cin >> from;
            std::cin >> to;
            std::cin >> weight;

            graph[from].push_back({to, weight});
            graph[to].push_back({from, weight});
        }

        weight_t distance = dijkstra(1, n, graph, n);
        std::cout << distance << "\n"; // 1: lea, n: car
    }

    return 0;
}
