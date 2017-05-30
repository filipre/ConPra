#include <iostream>
#include <vector>
#include <queue>

// manage a and bs and return false if something is bad
// v - u
bool partition(int v, int u, std::vector<char> &toppings)
{
    // std::cout << '\n';
    // for (int i=1; i<toppings.size(); ++i)
    // {
    //     std::cout << toppings[i] << " ";
    // }
    // std::cout << '\n';

    if (toppings[v] == 'e' && toppings[u] == 'e')
    {
        toppings[v] = 'a';
        toppings[u] = 'b';
    }
    else if (toppings[v] == 'e' && toppings[u] != 'e')
    {
        if (toppings[u] == 'a')
            toppings[v] = 'b';
        else
            toppings[v] = 'a';
    }
    else if (toppings[v] != 'e' && toppings[u] == 'e')
    {
        if (toppings[v] == 'a')
            toppings[u] = 'b';
        else
            toppings[u] = 'a';
    }
    else
    {
        // both are set
        // check if something goes wrong
        if (toppings[v] == 'a' && toppings[u] == 'a')
        {
            return false;
        }
        else if (toppings[v] == 'b' && toppings[u] == 'b')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int t;
    std::cin >> t;
    for (int testCase=1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n, m;
        std::cin >> n; // available pizza toppings: 1 to n
        std::cin >> m; // number of pairs which topings don't tase well

        std::vector<bool> explored (n+1); // ignore 0
        for (int i=1; i<=n; ++i)
            explored[i] = false;

        std::vector<std::vector<int>> graph (n+1); // ignore 0

        for (int i=1; i<=m; ++i)
        {
            int node1, node2;
            std::cin >> node1;
            std::cin >> node2;
            graph[node1].push_back(node2);
            graph[node2].push_back(node1);
        }

        std::vector<char> toppings (n+1); // ignore 0, will match [i] to {a, b}
        for (int i=1; i<=n; ++i)
            toppings[i] = 'e'; // for empty

        // do BFS starting with 1 (exists always)
        std::queue<int> bfs_queue;
        for (int vertex=1; vertex<=n; ++vertex)
        {
            if (!explored[vertex])
            {
                bfs_queue.push(vertex);
                while (!bfs_queue.empty())
                {
                    const auto &v = bfs_queue.front();
                    bfs_queue.pop();
                    explored[v] = true;
                    for (const auto &u : graph[v])
                    {
                        if(!partition(v, u, toppings))
                        {
                            std::cout << "no\n";
                            goto stop;
                        }
                        if (!explored[u])
                        {
                            bfs_queue.push(u);
                            explored[u] = true;
                        }
                    }
                }
            }
        }
        std::cout << "yes\n";

        stop:
        std::cout << "";
        // start with new testCase
    }
}
