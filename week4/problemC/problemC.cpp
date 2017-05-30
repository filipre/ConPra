#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>

typedef int32_t node_t;
typedef std::vector<std::vector<node_t>> graph_t;

void printOrder(const std::vector<node_t> &order, int n)
{
    std::cout << "Order: ";
    for (int i=1; i<=n; ++i)
    {
        std::cout << order[i] << " ";
    }
    std::cout << "\n";
}

void printDist(const std::vector<int> &dist, int n)
{
    std::cout << "Dist: ";
    for (int i=1; i<=n; ++i)
    {
        std::cout << dist[i] << " ";
    }
    std::cout << "\n";
}

void printPredecessors(const std::vector<int> &predecessors, int n)
{
    std::cout << "Predecessors: ";
    for (int i=1; i<=n; ++i)
    {
        std::cout << predecessors[i] << " ";
    }
    std::cout << "\n";
}

void printPredecessors(std::vector<node_t> &predecessors, int n)
{
    std::cout << "predecessors:\n";
    for (int i=1; i<=n; ++i)
    {
        std::cout << predecessors[i] << " ";
    }
    std::cout << "\n";
}

// TODO wrong!!!!!!!
void topologicalSort(const graph_t &graph, const graph_t &graphInv, int n, std::vector<node_t> &order, std::vector<node_t> &predecessors)
{
    for (int i=1; i<=n; ++i)
    {
        order[i] = INT32_MAX;
        predecessors[i] = graphInv[i].size();
    }
    // printPredecessors(predecessors, n);

    std::stack<node_t> topo_stack;
    int counter = 1;

    // identify start vertex
    std::vector<node_t> startVertex;
    for (int vertex=1; vertex<=n; ++vertex)
    {
        // std::cout << "new vertex: " << vertex << '\n';
        if (predecessors[vertex] == 0)
        {
            startVertex.push_back(vertex);
        }
    }

    // work through start vertexes
    for (const auto &vertex : startVertex)
    {
        topo_stack.push(vertex);
        while(!topo_stack.empty())
        {
            node_t v = topo_stack.top();
            topo_stack.pop();
            order[v] = counter;
            counter = counter + 1;
            // std::cout << "gonna interate over graph["<< v << "]\n";
            for (node_t u : graph[v])
            {
                // std::cout << "gonna decrease: " << u << "\n";
                predecessors[u] = predecessors[u] - 1;
                if (predecessors[u] == 0)
                {
                    // std::cout << "add " << u << " to topo_stack\n";
                    topo_stack.push(u);
                }
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n;
        std::cin >> n; // 1 ... n

        graph_t graph (n+1);
        graph_t graphInv (n+1); // to get predecessors

        std::vector<int> weights (n+1);

        for (int i=1; i<=n; ++i)
        {
            int p_i, s_i;
            std::cin >> p_i;
            weights[i] = p_i;
            std::cin >> s_i;
            for (int j=1; j<=s_i; ++j)
            {
                int succ;
                std::cin >> succ;
                graph[i].push_back(succ);
                graphInv[succ].push_back(i);
            }
        }

        std::vector<node_t> order (n+1); // ignore 0
        std::vector<node_t> predecessors (n+1);

        topologicalSort(graph, graphInv, n, order, predecessors);
        // printOrder(order, n);
        // printPredecessors(predecessors, n);

        // order[1] = 1;
        // order[2] = 2;
        // order[3] = 3;
        // order[4] = 4;
        // order[5] = 5;
        // order[6] = 6;
        // order[7] = 7;
        // order[8] = 8;

        // printOrder(order, n);

        // problem: it's not the order of the nodes but the new index of the ith node.
        // let's make it an order of the nodes

        // https://stackoverflow.com/questions/17554242/how-to-obtain-the-index-permutation-after-the-sorting
        std::vector<std::pair<node_t,node_t>> V;
        for(int i=1; i<=n; i++)
        {
            std::pair<node_t, node_t> P = std::make_pair(order[i], i);
            V.push_back(P);
        }
        std::sort(V.begin(),V.end());
        for(int i=1; i<n; i++)
        {
            order[i+1] = V[i].second; // notice that we shift +1 because of the 0 element
        }

        // printOrder(order, n);


        std::vector<node_t> dist(n+1);
        for (int i=1; i<=n; ++i)
        {
            dist[i] = INT32_MIN;
        }
        dist[1] = 0;

        // algorithm description from http://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
        for (int i=1; i<=n; ++i)
        {
            node_t u = order[i];
            for (const auto v : graph[u])
            {
                if (dist[v] < (dist[u] + weights[u]))
                {
                    dist[v] = dist[u] + weights[u];
                }
            }
        }

        // printDist(dist, n);

        std::cout << dist[n] + weights[n] << "\n";
    }


    return 0;
}
