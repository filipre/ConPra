#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <set>
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

struct Pq_Edge
{
    Edge e;
    node_t pred;
};

struct Supermarket
{
    node_t city;
    weight_t min;
};

void printPred(const std::vector<node_t> &pred, int n)
{
    std::cout << "Pred: ";
    for (int i=1; i<=n; ++i)
    {
        std::cout << pred[i] << " ";
    }
    std::cout << "\n";
}

void dijkstra(const node_t start, const graph_t &graph, const int n, std::vector<node_t> &pred, std::vector<weight_t> &distance)
{
    std::vector<bool> visited(n+1);

    for (int i=1; i<=n; ++i)
    {
        visited[i] = false;
        distance[i] = weightMax;
    }

    visited[start] = true;
    distance[start] = 0;
    pred[start] = 0; // 0 does not exist

    auto cmp = [](Pq_Edge left, Pq_Edge right) { return (left.e.weight > right.e.weight); }; // TODO
    std::priority_queue<Pq_Edge, std::vector<Pq_Edge>, decltype(cmp)> pq(cmp);

    // printDistances(distance, n);
    // printVisited(visited, n);

    for (const auto &edge : graph[start])
    {
        pq.push({edge, start});
    }

    // not all visited
    while (!pq.empty())
    {
        Pq_Edge x = pq.top();
        pq.pop();

        // std::cout << "PQ top: " <<  x.to << ", w: " << x.weight << "\n";

        if (!visited[x.e.to])
        {
            visited[x.e.to] = true;
            distance[x.e.to] = x.e.weight;
            pred[x.e.to] = x.pred;
            for (const auto &edge : graph[x.e.to])
                pq.push({{edge.to, distance[x.e.to] + edge.weight}, x.e.to});

        }

        // printDistances(distance, n);
        // printVisited(visited, n);
        // printPred(pred, n);
    }
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
        // std::cout << "\n";

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
        std::vector<node_t> pred_lea (n+1);
        std::vector<weight_t> distance_lea (n+1);
        std::vector<node_t> pred_peter (n+1);
        std::vector<weight_t> distance_peter (n+1);

        dijkstra(a, graph, n, pred_lea, distance_lea); // shortest path from lea
        dijkstra(b, graph, n, pred_peter, distance_peter); // shortest path from peter

        // printPred(pred_lea, n);
        // printPred(pred_peter, n);

        weight_t minDistance = weightMax;
        weight_t result = weightMax;
        for (const auto &supermarket : supermarkets)
        {
            // std::cout << "supermarket: " << supermarket.city << "\n";

            // weight_t time1 = calcDistance(a, supermarket.city, pred_lea, distance_lea);
            weight_t time1 = distance_lea[supermarket.city];
            if (time1 == weightMax)
            {
                // std::cout << "impossible\n";
                continue;
            }
            // std::cout << "time1: " << time1 << "\n";
            //
            // std::cout << "supermarket: " << supermarket.min << "\n";

            // if time1 is infinity, then the supermarket is not connected to the shortest path

            weight_t currentDistance = 0;
            weight_t currentNode = supermarket.city;

            while (pred_peter[currentNode] != 0)
            {
                // std::cout << "currentNode: " << currentNode << "\n";
                // std::cout << "pred_peter[currentNode]: " << pred_peter[currentNode] << "\n";
                currentDistance += std::abs(distance_peter[currentNode] - distance_peter[pred_peter[currentNode]]);
                // std::cout << "d: " << currentDistance << "\n";
                currentNode = pred_peter[currentNode];
            }

            if (currentNode != b)
                continue;


            weight_t time2 = currentDistance;
            // std::cout << "time2: " << time2 << "\n";

            result = time1 + time2 + supermarket.min;
            if (result < minDistance)
            {
                minDistance = result;
            }

        }

        if (minDistance == weightMax)
        {
            std::cout << "impossible\n";
        } else {
            printTime(minDistance);
        }

    }

    return 0;
}
