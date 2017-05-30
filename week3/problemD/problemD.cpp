#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

typedef int32_t node_t;
struct Edge
{
    node_t from;
    node_t to;
    int weight;
};
typedef std::vector<std::vector<Edge>> graph_t;

// http://stackoverflow.com/questions/8300125/union-find-data-structure
class UF {
    int *id, cnt, *sz;
public:
    // Create an empty union find data structure with N isolated sets.
    UF(int N) {
        cnt = N; id = new int[N]; sz = new int[N];
        for (int i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
    ~UF() { delete[] id; delete[] sz; }

    // Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])    root = id[root];
        while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
        return root;
    }
    // Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x); int j = find(y); if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
        else { id[j] = i, sz[i] += sz[j]; }
        cnt--;
    }
    // Are objects x and y in the same set?
    bool connected(int x, int y) { return find(x) == find(y); }
    // Return the number of disjoint sets.
    int count() { return cnt; }
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";

        int n, m;
        std::cin >> n; // number of cities 1, ..., n
        std::cin >> m; // number of roads

        graph_t graph (n+1); // ignore 0
        int overallSum = 0;
        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i, x_i, l_i;
            std::cin >> a_i;
            std::cin >> b_i;
            std::cin >> x_i;
            std::cin >> l_i;
            graph[a_i].push_back({a_i, b_i, (-1) * x_i * l_i }); // -1 because we later calc the MST
            graph[b_i].push_back({b_i, a_i, (-1) * x_i * l_i });
            overallSum += (x_i * l_i);
        }

        // Kruskal to calc MST. if UF data strcutre has more than one (two, because 0) elements, it's impossible
        auto cmp = [](Edge left, Edge right) { return left.weight > right.weight;};
        std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> sortedEdges(cmp);
        for (node_t v=1; v<=n; ++v)
        {
            for (const auto &edge : graph[v])
            {
                // std::cout << "insert " << edge.from << " <-> " << edge.to << "(" << edge.weight << ")\n";
                sortedEdges.push(edge);
            }
        }

        UF connectedNodes(n+1); // don't use 0 element
        int mstSum = 0;
        while(!sortedEdges.empty())
        {
            const auto &edge = sortedEdges.top();
            sortedEdges.pop();
            if (connectedNodes.find(edge.from) != connectedNodes.find(edge.to))
            {
                connectedNodes.merge(edge.from, edge.to);
                mstSum += edge.weight;
                //mst.push(edge);
            }
        }

        if (connectedNodes.count() > 2) // notice the 0 element which I don't use
        {
            std::cout << "impossible\n";
        }
        else
        {
            std::cout << overallSum + mstSum << "\n";
        }

        // if it is, calculate MST
    }

    return 0;
}
