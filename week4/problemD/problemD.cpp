#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>

/*
    Corner cases to think about:
    1) no supermarket at all (s == 0)
    2) Lea and Peter not connected (at least one distance is infinity)
    3) Supermarket not connected (at least one distance is infinity)

    Solution by spahl:
    https://judge.in.tum.de/discuss/t/week-4-problem-d-supermarkets/177/8
    "Find the shortest paths from start and destination then add both for every
    supermarket and find the minimum. This way you only use dijkstra twice not
    number of supermarket many times"

*/

typedef int32_t node_t;
typedef int32_t weight_t;
struct Edge
{
    node_t to;
    weight_t weight;
};
typedef std::vector<std::vector<Edge>> graph_t;
const weight_t weightMax = INT32_MAX;

struct Supermarket
{
    node_t city;
    weight_t min;
};

weight_t dijkstra(const node_t start, const node_t end, const graph_t &graph, const int n)
{
    std::vector<bool> visited(n+1);
    std::vector<weight_t> distance(n+1);

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

    for (const auto &edge : graph[start])
    {
        pq.push(edge);
    }

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

        }

        // printDistances(distance, n);
        // printVisited(visited, n);
    }

    return distance[end];
}

void printTime(weight_t mins)
{
    // minutes
    int minutes = mins / 60;
    // if (minutes < 10)
    //     std::cout << "0";
    std::cout << minutes;

    std::cout << ":";

    int seconds = mins % 60;
    if (seconds < 10)
        std::cout << "0";
    std::cout << seconds;

    std::cout << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n, m, s, a, b;
        std::cin >> n; // number of cities, 1 ... n
        std::cin >> m; // number of roads
        std::cin >> s; // number of supermarkets
        std::cin >> a; // lea's city
        std::cin >> b; // peter's city

        graph_t graph (n+1);

        for (int i=1; i<=m; ++i)
        {
            int x_i, y_i, z_i;
            std::cin >> x_i; // from
            std::cin >> y_i; // to
            std::cin >> z_i; // in minutes
            graph[x_i].push_back({ y_i, z_i });
            graph[y_i].push_back({ x_i, z_i });
        }

        std::vector<Supermarket> supermarkets;
        for (int i=1; i<=s; ++i)
        {
            int c_j, w_j;
            std::cin >> c_j; // supermarkt in city c_j
            std::cin >> w_j; // w_j mins to buy wine
            supermarkets.push_back({ c_j, w_j });
        }

        // if there aren't any supermarkets, we can straight continue
        if (s == 0)
        {
            std::cout << "impossible\n";
            continue;
        }

        // TODO see solution above

        // get all distances from Lea to an supermarket
        weight_t currentMin = weightMax;
        for (const auto &supermarket : supermarkets)
        {
            // if either dijkstra returns max value, then there isn't any connection
            weight_t timeToSupermarket = dijkstra(a, supermarket.city, graph, n);
            if (timeToSupermarket == weightMax)
            {
                // std::cout << "impossible\n";
                continue;
            }

            weight_t timeToPeter =  dijkstra(supermarket.city, b, graph, n);
            if (timeToPeter == weightMax)
            {
                // std::cout << "impossible\n";
                continue;
            }

            weight_t currentTime = timeToSupermarket + supermarket.min + timeToPeter;
            if (currentTime < currentMin)
            {
                currentMin = currentTime;
            }

            // std::cout << a << " - " << supermarket.city << ": " << dijkstra(a, supermarket.city, graph, n) << "\n";
            // std::cout << supermarket.min << "\n";
            // std::cout << supermarket.city << " - " << b << ": " << dijkstra(supermarket.city, b, graph, n) << "\n";
        }

        if (currentMin == weightMax)
        {
            std::cout << "impossible\n";
        } else {
            printTime(currentMin);
        }
    }

    return 0;
}
