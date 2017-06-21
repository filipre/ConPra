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

bool bellmanFord(int32_t start, const graph_t &graph, int n, std::vector<int32_t> &dist, std::vector<int32_t> &pred, std::vector<int32_t> &count)
{
    // init
    for (int u=1; u<=n; ++u)
    {
        dist[u] = INT32_MAX;
        pred[u] = 0;
    }
    dist[start] = 0;

    std::deque<int32_t> Q;

    Q.push_back(start);

    int tempCounter = 0;
    while( !Q.empty() )
    {
        ++tempCounter;
        // std::cout << "dist[start]: " << dist[start] << "\n";
        // std::cout << "tempCounter: " << tempCounter << "\n";
        if (dist[start] < 0)
            std::cout << tempCounter << "\n";

        // std::cout << "dist: ";
        // printVec(dist, n);


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
                    Q.push_back(y);
                    if(++count[y] > n-1)
                    {
                        // std::cout << count[y] << "\n";
                        // std::cout << "negative circle!!\n";
                        std::cout << "i: " << i << "\n";
                        std::cout << "x: " << x << ", y: " << y << "\n";
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

            graph[a_i].push_back({b_i, c_i});
            graph[b_i].push_back({a_i, -1 * c_i});
        }

        std::vector<int32_t> dist (n+1);
        std::vector<int32_t> pred (n+1);
        std::vector<int32_t> count (n+1);

        // std::cout << "run bellmanFord...\n";
        bool result = bellmanFord(s, graph, n, dist, pred, count);
        // std::cout << "result: " << result << "\n";

        std::cout << "dist: \n";
        printVec(dist, n);
        // std::cout << "pred: \n";
        // printVec(pred, n);
        // std::cout << "count \n";
        // printVec(count, n);

        // auto min_p = std::min_element(count.begin(), count.end());
        // std::cout << *min_p - 1 << "\n";
        // std::cout << count[s] - 1 << "\n";

    }

    return 0;
}
