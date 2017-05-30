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

weight_t findDist(const node_t node1, const node_t node2, const graph_t &graph)
{
    for (const auto &edge : graph[node1])
    {
        if (edge.to == node2)
            return edge.weight;
    }
    return weightMax;
}

weight_t dijkstra(const node_t start, const node_t end, const graph_t &graph, const int n, std::vector<node_t> &pred)
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
    printTime(weightMax);
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
        std::vector<node_t> pred (n+1);
        weight_t shortestPath = dijkstra(a, b, graph, n, pred); // from lea to peter
        weight_t shortestPath = dijkstra(b, a, graph, n, pred2); // calc this since there might be a shorter way to peter from the supermarket
        // printPred(pred, n);
        if (shortestPath == weightMax)
        {
            std::cout << "impossible\n";
            continue;
        }

        // create set that contains all ffrom the shortest path
        std::set<node_t> shortestPathMembers;
        node_t traverseNode = b;
        shortestPathMembers.insert(traverseNode);
        do {
            traverseNode = pred[traverseNode]; // start from peter
            shortestPathMembers.insert(traverseNode);
        } while(traverseNode != a);

        // for (auto it=shortestPathMembers.begin(); it!=shortestPathMembers.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << '\n';

        weight_t currentMin = weightMax;
        weight_t currentTime;

        // now add supermarekt times to shortestPath
        for (const auto &supermarket : supermarkets)
        {
            if (shortestPathMembers.count(supermarket.city))
            {
                // supermarket city is directlz on the shoretest path
                // printTime(shortestPath + supermarket.min); // TODO only which are in the shortest path, prec!!
                currentTime = shortestPath + supermarket.min;
            }
            else if (pred[supermarket.city] == 0)
            {
                // not reachable. continue
                continue;
            }
            else
            {
                // supermarkt is somehwere else... go there and then back to the shortest path
                // sum up distances until one get passed by the shortest path.
                // 2 * travserse path + time supermarket
                // fuck.. traverse again
                int additionalMins = 0;
                node_t currentNode = supermarket.city;

                while(!shortestPathMembers.count(currentNode))
                {
                    additionalMins += (2 * findDist(currentNode, pred[currentNode], graph));
                    currentNode = pred[currentNode];
                }

                currentTime = shortestPath + additionalMins + supermarket.min;
            }

            if (currentTime < currentMin)
            {
                currentMin = currentTime;
            }

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
