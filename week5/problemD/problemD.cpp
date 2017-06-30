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
    vector <vector <Edge <T>>> adj;
    vector <T> excess;
    vector <int> dist, count;
    vector <bool> active;
    vector <vector <int>> B;
    int b;
    queue <int> Q;

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
        for (auto e: adj[v]) if (e.cap - e.flow > 0) {
            dist[v] = min(dist[v], dist[e.to] + 1);
        }
        count[dist[v]]++;
        Enqueue(v);
    }

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

    vector <T> GetExcess()
    {
        return excess;
    }
};

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
        std::cin >> n; // teams 1 to n
        std::cin >> m; // number of matches.

        // std::cout << "n: " << n << ", m: " << m << "\n";

        std::vector<int> wins (n+1);
        for (int i=1; i<=n; ++i)
        {
            std::cin >> wins[i];
            // std::cout << wins[i] << " ";
        }
        // std::cout << "\n";


        std::vector<std::pair<int, int>> todo;
        // std::vector<std::vector<int>> todo2 (n+1);
        for (int i=1; i<=m; ++i)
        {
            int a_i, b_i;
            std::cin >> a_i;
            std::cin >> b_i;

            // todo2[a_i].push_back(b_i);
            // todo2[b_i].push_back(a_i);

            // .first is always lower than .second
            if (a_i <= b_i)
                todo.push_back(std::make_pair(a_i, b_i));
            else
                todo.push_back(std::make_pair(b_i, a_i));
        }

        for (int current=1; current<=n; ++current)
        {
            // calc team i points
            int points = wins[current];
            for (auto match : todo)
            {
                if (match.first == current || match.second == current)
                {
                    points++;
                }
            }
            // std::cout << "current: " << current << ", ";
            // std::cout << "points: " << points << "\n";

            // build graph and make calc max flow
            // 0: start
            // 1, ..., n: teams
            // n+1: target
            // -> n+2
            PushRelabel<int> pr (n+2);
            std::vector<int> tempWins (n+1);

            // calc wins of every other one
            for (auto match : todo)
            {
                if (match.first == current || match.second == current)
                    continue;

                tempWins[match.first]++;
                pr.AddEdge(match.first, match.second, 1);
                // std::cout << match.first << "->" << match.second << " (1)\n";
            }

            // from start to each team
            for (int i=1; i<=n; ++i)
            {
                if (i == current)
                    continue;

                pr.AddEdge(0, i, wins[i] + tempWins[i]);
                // std::cout << "0->" << i << " (" << wins[i] + tempWins[i] << ")\n";
            }

            // teams to target
            for (int i=1; i<=n; ++i)
            {
                if (i == current)
                    continue;

                pr.AddEdge(i, n+1, points);
                // std::cout << i << "->" << n+1 << " (" << points << ")\n";
            }

            pr.GetMaxFlow(0, n+1);
            std::vector<int> excess = pr.GetExcess();
            // std::cout << "excess: ";
            bool yes = true;
            for (int i=0; i<=n; ++i)
            {
                if (excess[i] != 0)
                {
                    yes = false;
                    break;
                    // std::cout << excess[i] << " ";
                }
            }

            if (yes)
                std::cout << "yes ";
            else
                std::cout << "no ";


        }

        std::cout << "\n";


    }

    // PushRelabel<int> pr (4);
    // int p = 1;
    //
    // pr.AddEdge(0, 1, 1+1);
    // pr.AddEdge(1, 3, p);
    //
    // pr.AddEdge(0, 2, 1+0);
    // pr.AddEdge(2, 3, p);
    //
    // std::cout << pr.GetMaxFlow(0, 3) << "\n";
    //
    // auto excess = pr.GetExcess();
    // for (int i=1; i<=2; ++i)
    // {
    //     std::cout << excess[i] << " ";
    // }
    // std::cout << "\n";
}
