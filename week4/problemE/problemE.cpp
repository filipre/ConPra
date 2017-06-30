#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <set>

/*
    Solution:
    Essentially you want to know the edge count of the shortest path from s to s that contains a circle with a stepcount different from zero. You can easily achieve that by modifying the bellman ford algorithm.

    https://www.youtube.com/watch?v=obWXjtg0L64
*/

struct Edge
{
    int32_t node;
    int32_t weight;
};
typedef std::vector<std::vector<Edge>> graph_t;

void printVec(const std::vector<int32_t> &vec, int n)
{
    for (int i=1; i<=n; ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

bool bellmanFord(int32_t start, const graph_t &graph, int n, std::vector<int32_t> &dist, std::vector<int32_t> &pred, std::vector<int32_t> &count, std::vector<int32_t> &desc)
{
    // init
    for (int u=1; u<=n; ++u)
    {
        dist[u] = INT32_MAX;
        pred[u] = 0;
    }
    dist[start] = 0;
    // pred[start] = start; // ???

    // for i from 1 to |V| - 1:
    //     for (u, v) in E:
    //         relax(u, v)
    //
    // relax(u, v):
    //     if v.distance > u.distance + weight(u, v):
    //         v.distance = u.distance + weight(u, v)
    //         v.p = u

    // for (int i=1; i<=n-1; ++i)
    // {
    //     for (int u=1; u<=n; ++u)
    //     {
    //         for (auto v : graph[u])
    //         {
    //             // std::cout << u << " -> " << v.node << ": " << v.weight << "\n";
    //             if (dist[u] != INT32_MAX && dist[v.node] > dist[u] + v.weight)
    //             {
    //                 dist[v.node] = dist[u] + v.weight;
    //                 pred[v.node] = u;
    //             }
    //         }
    //     }
    // }

    // for (int u=1; u<=n; ++u)
    // {
    //     for (auto v : graph[u])
    //     {
    //         //d[v]> d[u] +w(u,v)
    //         if (dist[v.node] > dist[u] + v.weight)
    //         {
    //             return false;
    //         }
    //     }
    // }

    // return true;









    std::deque<int32_t> Q;
    Q.push_back(start);
    while( !Q.empty() )
    {
        int x = Q.front();
        // std::cout << "x front: " << x << "\n";
        if(dist[x] != INT32_MAX)
        {
            for(int i=0; i < graph[x].size(); ++i)
            {
                int y = graph[x][i].node;
                int c = graph[x][i].weight;
                if(dist[y] > dist[x] + c)
                {
                    dist[y] = dist[x] + c;
                    pred[y] = x;
                    desc[x] = y;
                    Q.push_back(y);
                    //if(++count[y] > n-1)
                    if(++count[y] > n-1)
                    {
                        std::cout << "broke at node " << y << "\n";
                        // std::cout << "increase at " << y << "\n";
                        // std::cout << count[y] << "\n";
                        // std::cout << "negative circle!!\n";
                        // std::cout << "i: " << i << "\n";
                        // std::cout << "x: " << x << ", y: " << y << "\n";
                        return false;
                    }
                }
           }
           Q.pop_front();
       }
    }

   return true;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase = 1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        std::cout << "\n";

        int n, m, s;
        std::cin >> n; // places 1, ..., n
        std::cin >> m; // number of connecting flights of stairs
        std::cin >> s; // start point

        graph_t graph (n+1); // ignore 0

        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i, c_i;
            std::cin >> a_i; // from
            std::cin >> b_i; // to
            std::cin >> c_i; // weight

            // if (a_i == b_i)
            //     continue;

            graph[a_i].push_back({b_i, c_i});
            graph[b_i].push_back({a_i, -1 * c_i});
        }

        std::vector<int32_t> dist (n+1);
        std::vector<int32_t> pred (n+1);
        std::vector<int32_t> count (n+1);
        std::vector<int32_t> desc (n+1);

        // std::cout << "run bellmanFord...\n";
        bool result = bellmanFord(s, graph, n, dist, pred, count, desc);
        std::cout << "result: " << result << "\n";

        // std::cout << "dist: \n";
        // printVec(dist, n);
        std::cout << "pred: \n";
        printVec(pred, n);
        std::cout << "desc: \n";
        printVec(desc, n);

        std::cout << "find out length: \n";

        int32_t currentNode = s;

        std::cout << "pred\n";
        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];

        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];

        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];

        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];

        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];

        std::cout << currentNode << " -> " << pred[currentNode] << "\n";
        currentNode = pred[currentNode];



        // std::cout << "count \n";
        // printVec(count, n);

        // auto min_p = std::min_element(count.begin(), count.end());
        // std::cout << *min_p - 1 << "\n";
        // std::cout << count[s] - 1 << "\n";

    }

    return 0;
}
