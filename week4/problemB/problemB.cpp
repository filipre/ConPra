#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>

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

void dijkstra(const vertex_t start, const graph_t &graph, const int n, std::vector<weight_t> &distance)
{
    std::vector<bool> visited(n+1);

    for (int i=1; i<=n; ++i)
    {
        visited[i] = false;
        distance[i] = weightMax;
    }

    visited[start] = true;
    distance[start] = 0;

    auto cmp = [](Edge left, Edge right) { return (left.weight > right.weight); }; // TODO
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);

    // printDistances(distance, n);
    // printVisited(visited, n);

    // std::cout << "connected to start: ";
    for (const auto &edge : graph[start])
    {
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
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase = 1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n, m, s;
        std::cin >> n; // intersections
        std::cin >> m; // roads
        std::cin >> s; // subway station at intersection

        graph_t graph (n+1);

        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i, c_i;
            std::cin >> a_i; // from
            std::cin >> b_i; // to
            std::cin >> c_i; // minutes
            graph[a_i].push_back({b_i, c_i});
            graph[b_i].push_back({a_i, c_i});
        }

        std::vector<int> subwayStations;
        for (int i=1; i<=s; ++i)
        {
            int s_i;
            std::cin >> s_i;
            subwayStations.push_back(s_i);
        }

        std::vector<weight_t> distance(n+1);
        dijkstra(1, graph, n, distance);

        // printDistances(distance, n);

        // Find subwaystation minimum and print
        weight_t min = weightMax;
        for (auto subwayStation : subwayStations)
        {
            if (distance[subwayStation] < min)
            {
                min = distance[subwayStation];
            }
        }
        std::cout << min << " ";

        // Find all subwayStations that have this minimum
        std::vector<weight_t> minSubwayStations;
        for (auto subwayStation : subwayStations)
        {
            if (distance[subwayStation] <= min)
            {
                minSubwayStations.push_back(subwayStation);
            }
        }

        // Sort and Print in ascending order
        std::sort(minSubwayStations.begin(), minSubwayStations.end());
        for (auto subwayStation : minSubwayStations)
        {
            std::cout << subwayStation << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
