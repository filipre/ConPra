#include <iostream>
#include <vector>
#include <stack>
#include <cstdint>

typedef int32_t node_t;
typedef std::vector<std::vector<node_t>> graph_t;

void topologicalSort(const graph_t &graph, const graph_t &graphInv, int n, std::vector<node_t> &order, std::vector<node_t> &predecessors)
{
    for (int i=1; i<=n; ++i)
    {
        order[i] = INT32_MAX;
        predecessors[i] = graphInv[i].size();
        // std::cout << predecessors[i] << " ";
    }
    // std::cout << "\n";
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

bool hasCycle(std::vector<node_t> &predecessors, int n)
{
    for (int i=1; i<=n; ++i)
        if (predecessors[i] > 0)
            return true;

    return false;
}

int main()
{
    // read input
    int t;
    std::cin >> t;
    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n, m, l;
        std::cin >> n; // intersections 1, ..., n
        std::cin >> m; // number of oneway roads
        std::cin >> l; // number of twoway roads

        graph_t graph (n+1);
        graph_t graphInv (n+1); // to get predecessors

        for (int i=1; i<=m; ++i)
        {
            int a_j, b_j;
            std::cin >> a_j;
            std::cin >> b_j;
            graph[a_j].push_back(b_j);
            graphInv[b_j].push_back(a_j);
        }

        std::vector<std::pair<node_t, node_t>> twowayRoads;
        for (int i=1; i<=l; ++i)
        {
            // don't do somehting with them yet
            int a_j, b_j;
            std::cin >> a_j;
            std::cin >> b_j;
            twowayRoads.push_back(std::make_pair(a_j, b_j));
        }

        std::vector<node_t> order (n+1); // ignore 0
        std::vector<node_t> predecessors (n+1);

        topologicalSort(graph, graphInv, n, order, predecessors);
        if (hasCycle(predecessors, n))
        {
            std::cout << "no\n";
            continue; // lets proceed with the next test case
        }

        std::cout << "yes\n";

        // lets add all other edges
        for (const auto &road : twowayRoads)
        {
            // road: first, second
            // notice that order[.first] == order[.second] is never the case
            if (order[road.first] < order[road.second])
            {
                graph[road.first].push_back(road.second);
                graphInv[road.second].push_back(road.first);
                std::cout << road.first << " " << road.second << "\n";
            }
            else
            {
                graph[road.second].push_back(road.first);
                graphInv[road.first].push_back(road.second);
                std::cout << road.second << " " << road.first << "\n";
            }
            // TODO maybe do another topo search since we've added an edge?
        }

        // topologicalSort(graph, graphInv, n, order, predecessors);
        // std::cout << "\ndoes it have a cycle? " << hasCycle(predecessors, n) << "\n";
    }



    return 0;
}
