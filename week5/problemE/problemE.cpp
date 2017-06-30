#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>


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
    vector <vector <Edge <T>>> adj; // has residual graph inside it!
    vector <T> excess;  // keep track of overflow
    vector <int> dist, count; // dist == height
    vector <bool> active;
    vector <vector <int>> B; // thats our queue right here, depending on the height. first array is depending on height
    int b; // keep track of max height
    queue <int> Q; // lol we don't neet that.

    PushRelabel (int n): n(n), adj(n) {}

    void AddEdge (int from, int to, int cap) {
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
        T amt = min(excess[e.from], e.cap - e.flow); // delta_f
        if (dist[e.from] == dist[e.to] + 1 && amt > T(0)) {
            e.flow += amt;
            adj[e.to][e.index].flow -= amt;
            excess[e.to] += amt;
            excess[e.from] -= amt;
            Enqueue(e.to);
        }
    }

    // use gap heuristic
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
        for (auto e: adj[v]) if (e.cap - e.flow > 0) {
            dist[v] = min(dist[v], dist[e.to] + 1);
        }
        count[dist[v]]++;
        Enqueue(v);
    }

    // determine the suitable operation
    void Discharge(int v) {
        for (auto &e: adj[v]) {
            if (excess[v] > 0) {
                Push(e);
            } else {
                break;
            }
        }

        if (excess[v] > 0) {
            if (count[dist[v]] == 1) {
                Gap(dist[v]);
            } else {
                Relabel(v);
            }
        }
    }

    T GetMaxFlow (int s, int t) {
        dist = vector <int>(n, 0), excess = vector<T>(n, 0), count = vector <int>(n + 1, 0), active = vector <bool>(n, false), B = vector <vector <int>>(n), b = 0;

        // init with most flow possible
        for (auto &e: adj[s]) {
            excess[s] += e.cap;
        }

        count[0] = n;
        Enqueue(s);
        active[t] = true;

        // stop if max height is negative (i.e. everyone was 0)
        while (b >= 0) {
            if (!B[b].empty()) {
                int v = B[b].back();  // pop last
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

int main()
{
    std::ios_base::sync_with_stdio(false);

    // put your code here
    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int n, m, p, s;
        std::cin >> n; // wariors
        std::cin >> m; // wizards
        std::cin >> p; // powder
        std::cin >> s; // different spells

        PushRelabel<int> pr (1+m+s+n+1 + 1);

        // get wariors
        std::vector<int> maxSpells (n+1);
        std::vector<std::vector<int>> warriorSpells (n+1);
        for (int i=1; i<=n; ++i)
        {
            int c_i, k_i;
            std::cin >> c_i; // max spells
            maxSpells[i] = c_i;
            // edge from warior to target with max spells capacity
            // pr.AddEdge(m+2+s-1+i, m+2+s+n, c_i);

            std::cin >> k_i; // different spells
            for (int j=1; j<=k_i; ++j)
            {
                int s_ij;
                std::cin >> s_ij;
                warriorSpells[i].push_back(s_ij);
            }
        }

        std::vector<std::vector<int>> sorcererSpells (m+1);
        for (int i=1; i<=m; ++i)
        {
            int a_j;
            std::cin >> a_j;

            for (int j=1; j<=a_j; ++j)
            {
                int t_ij;
                std::cin >> t_ij;
                sorcererSpells[i].push_back(t_ij);
            }
        }

        // let's build the graph
        // restrict the powder
        pr.AddEdge(0, 1, p);
        // std::cout << "0-1 (" << p << ")\n";

        // distribute powder to sorcerers
        for (int i=1; i<=m; ++i)
        {
            pr.AddEdge(1, 1+i, 1000000);
            // std::cout << "1-" << 1+i << " (1000000)\n";
        }

        // apply spells
        for (int i=1; i<=m; ++i)
        {
            for (auto spell : sorcererSpells[i])
            {
                pr.AddEdge(1+i, 1+m+spell, 1000000);
                // std::cout << 1+i << "-" << 1+m+spell << " (1000000)\n";
            }
        }

        // to wariors
        for (int i=1; i<=n; ++i)
        {
            for (auto spell : warriorSpells[i])
            {
                pr.AddEdge(1+m+spell, 1+m+s+i, 1000000);
            }
        }

        // apply max spells
        for (int i=1; i<=n; ++i)
        {
            pr.AddEdge(1+m+s+i, 1+m+s+n+1, maxSpells[i]);
            // std::cout << 1+m+s+i << "-" << 1+m+s+n+1 << " (" << maxSpells[i] << ")\n";
        }

        std::cout << pr.GetMaxFlow(0, 1+m+s+n+1) << "\n";

    }

    return 0;
}
