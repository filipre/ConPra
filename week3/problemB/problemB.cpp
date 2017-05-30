#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <cstdint>



// typedef std::vector<edges_t> graph_t;

// 0: we don't use that
// 1: [(1, 100), (3, 23)]
// 2: [(2, 12), (4, 11), (5, 1)]
// .size() = 3


typedef int32_t Vertex;
typedef std::pair<Vertex, Vertex> Edge;
// typedef std::pair<Edge, int32_t> WeightEdge;

struct WeightEdge
{
    Edge edge;
    int32_t weight;
};

typedef std::vector<Vertex> edges_t;
typedef std::vector<std::vector<Vertex>> graph_t; // lets use a matrix since it is fully connected


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
    int t;
    std::cin >> t;

    for (int testCase = 1; testCase <= t; ++testCase)
    {
        std::cout << "Case #" << testCase << ":\n";

        int n;
        std::cin >> n;

        graph_t graph (n+1, edges_t(n+1));

        for (int i=1; i<=n; ++i)
        {
            for (int j=1; j<=n; ++j)
            {
                std::cin >> graph[i][j]; // weights
            }
        }

        // for (int i=1; i<=n; ++i)
        // {
        //     for (int j=1; j<=n; ++j)
        //     {
        //         std::cout << graph[i][j] << " ";
        //     }
        //     std::cout << '\n';
        // }

        auto cmp = [](WeightEdge left, WeightEdge right) { return left.weight > right.weight;};
        std::priority_queue<WeightEdge, std::vector<WeightEdge>, decltype(cmp)> listOfEdges(cmp);

        for (uint32_t i=1; i<=n; ++i)
        {
            for (uint32_t j=i+1; j<=n; ++j)
            {
                listOfEdges.push(WeightEdge { std::make_pair(i, j), graph[i][j] });
            }
        }

        // while(!listOfEdges.empty())
        // {
        //     const auto &p = listOfEdges.top();
        //     std::cout << p.edge.first << "-" << p.edge.second << ": " << p.weight << "\n";
        //     listOfEdges.pop();
        // }

        UF connectedNodes(n+1); // don't use 0 element

        auto cmp2 = [](WeightEdge left, WeightEdge right)
        {
            if (left.edge.first != right.edge.first)
                return left.edge.first > right.edge.first;
            else
                return left.edge.second > right.edge.second;
        };
        std::priority_queue<WeightEdge, std::vector<WeightEdge>, decltype(cmp2)> mst(cmp2);

        while(!listOfEdges.empty())
        {
            const auto &edge = listOfEdges.top();
            if (connectedNodes.find(edge.edge.first) != connectedNodes.find(edge.edge.second))
            {
                connectedNodes.merge(edge.edge.first, edge.edge.second);
                mst.push(edge);
            }
            listOfEdges.pop();
        }

        while (!mst.empty())
        {
            const auto &p = mst.top();
            std::cout << p.edge.first << " " << p.edge.second << "\n";
            mst.pop();
        }

    }
}
