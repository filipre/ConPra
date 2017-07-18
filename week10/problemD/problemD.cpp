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
#include <cmath>
#include <iomanip>




using namespace std;

/*
taken from http://codeforces.com/blog/entry/14378
*/

template <class T> struct Edge {
    int from, to, index;
    T cap, flow;

    Edge(int from, int to, T cap, T flow, int index): from(from), to(to), cap(cap), flow(flow), index(index) {}
};

template <class T> struct PushRelabel {
    int n;
    vector <vector <Edge <T>>> adj;
    vector <T> excess;
    vector <int> dist, count;
    vector <bool> active;
    vector <vector <int>> B;
    int b;
    queue <int> Q;

    PushRelabel (int n): n(n), adj(n) {}

    void AddEdge (int from, int to, T cap) {
        adj[from].push_back(Edge <T>(from, to, cap, 0, adj[to].size()));
        if (from == to) {
            adj[from].back().index++;
        }
        adj[to].push_back(Edge <T>(to, from, 0, 0, adj[from].size() - 1));

    }

    void Enqueue (int v) {
        if (!active[v] && excess[v] > 0 && dist[v] < n) {
            active[v] = true;
            B[dist[v]].push_back(v);
            b = max(b, dist[v]);
        }
    }

    void Push (Edge <T> &e) {
        T amt = min(excess[e.from], e.cap - e.flow);
        if (dist[e.from] == dist[e.to] + 1 && amt > T(0)) {
            e.flow += amt;
            adj[e.to][e.index].flow -= amt;
            excess[e.to] += amt;
            excess[e.from] -= amt;
            Enqueue(e.to);
        }
    }

    void Gap (int k) {
        for (int v = 0; v < n; v++) if (dist[v] >= k) {
            count[dist[v]]--;
            dist[v] = max(dist[v], n);
            count[dist[v]]++;
            Enqueue(v);
        }
    }

    void Relabel (int v) {
        count[dist[v]]--;
        dist[v] = n;
        for (auto e: adj[v]) if (e.cap - e.flow > 0.0000000001) {
            dist[v] = min(dist[v], dist[e.to] + 1);
        }
        count[dist[v]]++;
        Enqueue(v);
    }

    void Discharge(int v) {
        for (auto &e: adj[v]) {
            if (excess[v] > 0.0000000001) {
                Push(e);
            } else {
                break;
            }
        }

        if (excess[v] > 0.0000000001) {
            if (count[dist[v]] == 1) {
                Gap(dist[v]);
            } else {
                Relabel(v);
            }
        }
    }

    T GetMaxFlow (int s, int t) {
        dist = vector <int>(n, 0), excess = vector<T>(n, 0), count = vector <int>(n + 1, 0), active = vector <bool>(n, false), B = vector <vector <int>>(n), b = 0;

        for (auto &e: adj[s]) {
            excess[s] += e.cap;
        }

        count[0] = n;
        Enqueue(s);
        active[t] = true;

        while (b >= 0) {
            if (!B[b].empty()) {
                int v = B[b].back();
                B[b].pop_back();
                active[v] = false;
                Discharge(v);
            } else {
                b--;
            }
        }
        return excess[t];
    }

    T GetMinCut (int s, int t, vector <int> &cut);
};






/*
PushRelabel<int> pr (n+1);

for (int i=1; i<=m; ++i)
{
    int a_i, b_i, w_i;
    std::cin >> a_i; // from
    std::cin >> b_i; // to
    std::cin >> w_i; // maximal baggage

    pr.AddEdge(a_i, b_i, w_i);
    pr.AddEdge(b_i, a_i, w_i);
}

int result = pr.GetMaxFlow(1, n);
if (result <= 0)
    std::cout << "impossible\n";
else
    std::cout << result << "\n";
    */


double calcArea(int k, double r)
{
    if (k == 0)
    {
        // calc circle radius
        return M_PI * r * r;
    }
    else
    {
        return (static_cast<double>(k) * r * r / 4.0) * tan(M_PI_2 - (M_PI / static_cast<double>(k)));
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
        // std::cout << "\n";

        int n, m;
        std::cin >> n; // valves 1 ... n
        std::cin >> m; // pipes

        PushRelabel<double> pr (n+1);

        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i;
            std::cin >> a_i; // from
            std::cin >> b_i; // to

            int k_i;
            double x_i;
            std::cin >> k_i; // amount of sides
            std::cin >> x_i; // radius or side length

            double area = calcArea(k_i, x_i);
            // std::cout << std::setprecision(9) << calcArea(k_i, x_i) << "\n";

            pr.AddEdge(a_i, b_i, area);
            pr.AddEdge(b_i, a_i, area);

        }

        double result = pr.GetMaxFlow(1, n);
        if (result < 0.0000000001)
            std::cout << "impossible\n";
        else
            std::cout << std::setprecision(16) << result << "\n";
    }

    return 0;
}
