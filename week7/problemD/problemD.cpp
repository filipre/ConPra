#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <map>

// http://stackoverflow.com/questions/8300125/union-find-data-structure
// class UF {
//     int *id, cnt, *sz;
// public:
//     // Create an empty union find data structure with N isolated sets.
//     UF(int N) {
//         cnt = N; id = new int[N]; sz = new int[N];
//         for (int i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
//     ~UF() { delete[] id; delete[] sz; }
//
//     // Return the id of component corresponding to object p.
//     int find(int p) {
//         int root = p;
//         while (root != id[root])    root = id[root];
//         while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
//         return root;
//     }
//     // Replace sets containing x and y with their union.
//     void merge(int x, int y) {
//         int i = find(x); int j = find(y); if (i == j) return;
//         // make smaller root point to larger one
//         if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
//         else { id[j] = i, sz[i] += sz[j]; }
//         cnt--;
//     }
//     // Are objects x and y in the same set?
//     bool connected(int x, int y) { return find(x) == find(y); }
//     // Return the number of disjoint sets.
//     int count() { return cnt; }
// };

// struct Edge
// {
//     int u;
//     int v;
//     int weight;
// };
// auto cmp = [](Edge left, Edge right)
// {
//   return (left.weight < right.weight);
// };

int calcScore(std::vector<int> &vertecies, std::vector<std::vector<int>> &graph, int n)
{
    int score = 0;
    for (int i=0; i<n-1; ++i)
    {
        score += (graph[vertecies[i]][vertecies[i+1]]);
    }
    score += graph[vertecies[n-1]][vertecies[0]]; // back to beginning
    return score;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int n;
        std::cin >> n; // number of ciites

        std::vector<std::vector<int>> graphInput (n+1, std::vector<int> (n+1));
        for (int i=1; i<=n; ++i)
        {
            for (int j=1; j<=n; ++j)
            {
                int l_ij;
                std::cin >> l_ij;
                graphInput[i][j] = l_ij;
            }
        }

        std::vector<int> vertecies;
        for (int i=1; i<=n; ++i)
        {
            vertecies.push_back(i);
        }

        int bestScore = 1000000;
        int score;
        std::vector<int> bestPermutation (n);
        do {
            // for (int i=0; i<n; ++i)
            // {
            //     std::cout << vertecies[i] << " ";
            // }
            // std::cout << ": ";
            score = calcScore(vertecies, graphInput, n);
            if (score < bestScore)
            {
                 bestPermutation.assign(vertecies.begin(), vertecies.end());
                 bestScore = score;
            }
        } while (std::next_permutation(vertecies.begin(),vertecies.end()));

        for (int i=0; i<n; ++i)
        {
            std::cout << bestPermutation[i] << " ";
        }
        std::cout << "\n";
































































        // if (n == 1)
        // {
        //     // std::cout << "\n";
        //     std::cout << "1" << "\n";
        //     continue;
        // }
        //
        // std::multiset<Edge, decltype(cmp)> graph (cmp);
        // for (int i=1; i<=(n-1); ++i)
        // {
        //     for (int j=i+1; j<=n; ++j)
        //     {
        //         graph.insert({ i, j, graphInput[i][j] });
        //         // graph.insert({ j, i, graphInput[i][j] });
        //     }
        // }
        //
        // // for (auto it=graph.begin(); it!=graph.end(); ++it)
        // //     std::cout << it->u << " - " << it->v << ": " << it->weight << "\n";
        //
        // std::vector<int> amountOfConnections (n+1);
        // for (int i=1; i<=n; ++i)
        //     amountOfConnections[i] = 0;
        //
        // UF connectedNodes(n+1); // ignore 0, this inits 0 to n single sets
        //
        // std::vector<std::vector<int>> traverseGraph (n+1); // ignore 0;
        // // while(connectedNodes.count() > 2) // {0} and {1, ..., n}
        // while(!graph.empty())
        // {
        //     // get minimum edge and remove it
        //     auto minEdge = graph.begin();
        //     graph.erase(minEdge);
        //     //Edge min = *min_it;
        //
        //     // check if any of the nodes it points to has already 2 connections
        //     if ((amountOfConnections[minEdge->u] < 2) && (amountOfConnections[minEdge->v] < 2) && (!connectedNodes.connected(minEdge->u, minEdge->v)))
        //     {
        //         ++amountOfConnections[minEdge->u];
        //         ++amountOfConnections[minEdge->v];
        //         connectedNodes.merge(minEdge->u, minEdge->v);
        //
        //         traverseGraph[minEdge->u].push_back(minEdge->v);
        //         traverseGraph[minEdge->v].push_back(minEdge->u);
        //
        //
        //         // std::cout << minEdge->u << " - " << minEdge->v << "\n";
        //     }
        // }
        //
        // // lets find the first start
        // int start = -1;
        // for (int i=1; i<=n; ++i)
        // {
        //     // std::cout << traverseGraph[i].size() << "\n";
        //     if (traverseGraph[i].size() == 1)
        //     {
        //         start = i;
        //         break;
        //     }
        // }
        // std::cout << start << " ";
        // int old = start;
        // int next = traverseGraph[start][0];
        //
        // for (int i=1; i<n; ++i)
        // {
        //     std::cout << next << " ";
        //     if (traverseGraph[next][0] == old)
        //     {
        //         old = next;
        //         next = traverseGraph[next][1];
        //     }
        //     else
        //     {
        //         old = next;
        //         next = traverseGraph[next][0];
        //     }
        // }
        // std::cout << "\n";




        //
        // if (traverseGraph[next][0] == old)
        // {
        //     old = next;
        //     next = traverseGraph[next][1];
        // }
        // else
        // {
        //     old = next;
        //     next = traverseGraph[next][0];
        // }
        // std::cout << next << "\n";


    }

    return 0;
}
