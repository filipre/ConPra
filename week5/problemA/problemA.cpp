#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>

// Graph datastructures for c, c_f, ...

typedef std::vector<int32_t> list_t;
void printList(const list_t &list, int n, const std::string &name)
{
    std::cout << "list: " << name << ": ";
    for (int u=1; u<=n; ++u)
    {
        std::cout << list[u] << " ";
    }
    std::cout << "\n";
}


typedef std::vector<list_t> adjMatrix_t;
void printAdjMatrix(const adjMatrix_t &matrix, int n, const std::string &name)
{
    std::cout << "matrix: " << name << "\n";
    for (int u=1; u<=n; ++u)
    {
        for (int v=1; v<=n; ++v)
        {
            std::cout << matrix[u][v] << "\t";
        }
        std::cout << "\n";
    }
}

/*
    // TODO make two graphs
    struct Graph
    {
        adjacencyMatrix_t &adjacencyMatrix;
        adjacencyList_t &adjacencyList;
    };

    // typedef std::vector<int32_t> height_t;
    // typedef std::vector<int32_t> excess_t;
    // typedef std::vector<std::vector<int32_t>> preflow_t;

    // struct Edge
    // {
    //     int vertex;
    //     int32_t capacity;
    // };
    // typedef std::vector<std::vector<Edge>> adjList_t;
*/

/*
Notation:

u, v: nodes
s: start node
c: graph with capacities
f: current flow
c_f: residuals
E_f: residual edge
h: height
e: excess


E_f = {(u, v) \in V \times V : c_f(u, v) > 0}
*/

int32_t c_f(int u, int v, const adjMatrix_t &c, const adjMatrix_t &f)
{
    if (c[u][v] > 0)
        return c[u][v] - f[u][v];
    else if (c[v][u] > 0)
        return f[v][u];
    else
        return 0;
}

bool couldPush(int u, int v, const adjMatrix_t &c, const adjMatrix_t &f, const list_t &h, const list_t &e)
{
    if (u == v)
        return false;

    if (c_f(u, v, c, f) <= 0)
        return false;

    // u is overflowing and
    if (e[u] <= 0)
        return false;

    // h(u) = h(v) + 1
    if (h[u] != h[v] + 1)
        return false;

    return true;
}

// push vertex u to v
void push(int u, int v, adjMatrix_t &c, adjMatrix_t &f, list_t &h, list_t &e)
{
    int delta_f;
    if (e[u] <= c_f(u, v, c, f))
        delta_f = e[u];
    else
        delta_f = c_f(u, v, c, f);

    if (c[u][v] > 0)
    {
        f[u][v] = f[u][v] + delta_f;
        // c[v][u] = c[v][u] + f[u][v]; // TODO, do I need that?
    }
    else
    {
        f[v][u] = f[v][u] - delta_f;
        // c[u][v] = c[u][v] + f[v][u]; // TODO, do I need that?
    }

    e[u] = e[u] - delta_f;
    e[v] = e[v] + delta_f;
}




bool couldRelabel(int u, int n, const adjMatrix_t &c, const adjMatrix_t &f,  const list_t &h, const list_t &e)
{
    // u is overflowing
    if (e[u] <= 0)
        return false;

    //

    for (int v=1; v<=n; ++v)
        if (u != v && c_f(u, v, c, f) > 0 && h[u] > h[v])
            return false;

    return true;
}

// relabel a single node
// changes height of u
void relabel(int u, int n, const adjMatrix_t &c, const adjMatrix_t &f, list_t &h, const list_t &e)
{
    // calc min
    int32_t minHeight = INT32_MAX;
    for (int v=1; v<=n; ++v)
    {
        if (u != v && c_f(u, v, c, f) > 0 && h[v] < minHeight)
            minHeight = h[v];
    }
    if (minHeight >= INT32_MAX)
        h[u] = INT32_MAX;
    else
        h[u] = minHeight + 1;
}

void pushRelabel(int s, int n, adjMatrix_t &c, adjMatrix_t &f, list_t &h, list_t &e)
{
    for (int v=1; v<=n; ++v)
    {
        h[v] = 0;
        e[v] = 0;
    }

    for (int u=1; u<=n; ++u)
        for (int v=1; v<=n; ++v)
            if (u != v && c[u][v] > 0)
                f[u][v] = 0;

    h[s] = n;

    for (int v=1; v<=n; v++)
    {
        if (s != v && c[s][v] > 0)
        {
            f[s][v] = c[s][v];
            // c[v][s] = c[v][s] + f[s][v]; // TODO
            e[v] = e[v] + c[s][v];
            e[s] = e[s] - c[s][v];
        }
    }

    nextIteration:
    // printList(h, n, "height");
    // printList(e, n, "excess");

    // check for push operation
    for (int u=1; u<=n; ++u)
    {
        for (int v=1; v<=n; ++v)
        {
            if (u != v && couldPush(u, v, c, f, h, e))
            {
                // std::cout << "perform push on " << u << " to " << v << "\n";
                push(u, v, c, f, h, e);
                goto nextIteration;
            }
        }
    }

    // check for relabel operation
    for (int u=1; u<n; ++u)
    {
        if (couldRelabel(u, n, c, f, h, e))
        {
            // std::cout << "perform relabel on " << u << "\n";
            relabel(u, n, c, f, h, e);
            goto nextIteration;
        }
    }

    // if both do not work, we are done...


    /*
        // TODO!!
        // 1: s; 2: a; ... 6: t;
        // relabel(2, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(2, 4, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(3, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(3, 5, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(4, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(4, 6, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(5, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(5, 6, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(2, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(2, 1, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(5, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(5, 4, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(5, 3, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(4, 6, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(3, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(3, 5, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(5, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(5, 3, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(3, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(3, 5, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(5, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(5, 3, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // relabel(3, n, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // push(3, 1, c, f, h, e);
        // printList(h, n, "height");
        // printList(e, n, "excess");
        //
        // std::cout << "?: " << couldRelabel(6, n, c, f, h, e) << "\n";
    */
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int testCase = 1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int n, m;
        std::cin >> n; // numbers of cities, 1: strata, n: tempolis
        std::cin >> m; // number of railroads

        adjMatrix_t c (n+1, list_t (n+1));  // capacities
        adjMatrix_t f (n+1, list_t (n+1));  // flow
        list_t h (n+1);                     // height
        list_t e (n+1);                     // excess

        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i, w_i;
            std::cin >> a_i; // from
            std::cin >> b_i; // to
            std::cin >> w_i; // maximal baggage

            if (a_i == b_i)
                continue;

            c[a_i][b_i] = c[a_i][b_i] + w_i;
            c[b_i][a_i] = c[b_i][a_i] + w_i;
        }

        // printAdjMatrix(c, n, "c");

        pushRelabel(1, n, c, f, h, e);

        //calc flow
        int flow = 0;
        for (int u=1; u<=n; ++u)
            flow += f[1][u];

        if (flow <= 0)
            std::cout << "impossible\n";
        else
            std::cout << flow << "\n";

        // printList(h, n, "height");
        // printList(e, n, "excess");

    }

    return 0;
}
