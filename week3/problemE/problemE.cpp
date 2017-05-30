#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>

typedef int32_t Vertex;
typedef std::vector<Vertex> row_t;
typedef std::vector<row_t> graph_t;

const int c_max(150 * 150000);

struct PQElement { Vertex v; int c; };
auto cmp = [](PQElement left, PQElement right)
{
    if (left.c != right.c)
        return left.c < right.c;
    else
        return left.v < right.v;
};
typedef std::set<PQElement, decltype(cmp)> primPQ_t;

void primVisit(Vertex v, const graph_t &graph, int n, std::vector<Vertex> &visited, std::vector<Vertex> &pre, std::vector<Vertex> &c, primPQ_t &pq)
{
    // std::cout << "c: ";
    // for (int i=1; i<=n; ++i)
    // {
    //     std::cout << "[" << c[i] << "] ";
    // }
    // std::cout << "\n";
    // std::cout << "primVisit: " << v << "\n";

    visited[v] = true;
    c[v] = 0;
    for (Vertex u = 1; u <= n; ++u)
    {
        if (!visited[u])
        {
            int cummWeight = graph[v][u] + c[v];
            if (cummWeight < c[u])
            {
                // std::cout << v << " - " << u << ": " << cummWeight << "\n";
                PQElement oldPQElement = { u, c[u] };
                PQElement newPQElement = { u, cummWeight };
                pre[u] = v;
                c[u] = cummWeight;
                if (pq.find(oldPQElement) != pq.end())
                {
                    pq.erase(oldPQElement);
                    pq.insert(newPQElement);
                }
                else
                {
                    pq.insert(newPQElement);
                }
            }
        }
    }
}

void prim(const graph_t &graph, int n, Vertex start, std::vector<Vertex> &pre)
{
    // S is our result set

    std::vector<Vertex> visited (n+1);

    std::vector<Vertex> c (n+1);
    for (Vertex v = 1; v <= n; ++v)
    {
        visited[v] = false;
        pre[v] = 0; //we don't use 0 so this is fine to set
        c[v] = c_max; // means infinity
    }
    primPQ_t pq (cmp);

    primVisit(start, graph, n, visited, pre, c, pq);
    while (!pq.empty())
    {
        Vertex v = pq.begin()->v;
        // std::cout << "smallest v: " << pq.begin()->v << " with c: " << pq.begin()->c << "\n";
        pq.erase(pq.begin()); // delete first element
        primVisit(v, graph, n, visited, pre, c, pq);
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

        int n; // number of houses
        std::cin >> n;

        // std::cout << "n: " << n << "\n";

        graph_t graph (n+1, row_t (n+1)); // ignore 0
        for (int i=1; i<=n; ++i)
        {
            for (int j=1; j<=n; ++j)
            {
                std::cin >> graph[i][j];
                // if ((i == 1 && j == n) || (i == n && j == 1))
                //     graph[i][j] = c_max;
            }
        }

        std::vector<Vertex> pre (n+1);
        prim(graph, n, 1, pre); // 1 is leas start

        // for (Vertex v = 1; v <= n; ++v)
        // {
        //     std::cout << "[" << pre[v] << "] ";
        // }
        // std::cout << "\n";

        // [0] [4] [1] [1] [2] [5]
        std::stack<Vertex> result;
        Vertex newVertex = n;
        while (true)
        {
            newVertex = pre[newVertex];
            if (newVertex == 0)
                break;
            result.push(newVertex);
        }
        while (!result.empty())
        {
            std::cout << result.top() << " ";
            result.pop();
        }
        std::cout << n << "\n";
    }

    return 0;
}
