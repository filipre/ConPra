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

#include <sstream>

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
};

std::vector<int> convert(std::string pagesString)
{
    std::stringstream pagesStream(pagesString);
    std::string segment;
    std::vector<int> pages;
    while(std::getline(pagesStream, segment, ','))
    {
        std::stringstream pagesStream2(segment);
        std::string fromString, toString;
        std::getline(pagesStream2, fromString, '-');
        int from = std::stoi(fromString);
        if (std::getline(pagesStream2, toString, '-'))
        {
            // std::cout << fromString << " and " << toString << ". ";
            int to = std::stoi(toString);
            for (int i=from; i<=to; ++i)
            {
                pages.push_back(i);
            }
        } else {
            // std::cout << fromString << ". ";
            pages.push_back(from);
        }
    }
    return pages;
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
        std::cin >> n; // numbers of printer jobs
        std::cin >> m; // number of pages

        // 0:               start
        // 1, ..., n:       jobs
        // n+1, ..., n+m:   pages
        // n+m+1:           target
        // => n+m+2 elements
        PushRelabel<int> pr (n+m+2);
        for (int i=1; i<=n; ++i)
        {
            pr.AddEdge(0, i, 1);

            std::string jobs;
            std::cin >> jobs;
            std::vector<int> result = convert(jobs);
            // page: [1, 3, 4, 5]
            for (auto page : result)
            {
                pr.AddEdge(i, n+page, 1); // job i to page
            }
        }

        for (int i=n+1; i<=n+m; ++i)
        {
            pr.AddEdge(i, n+m+1, 1);
        }

        int result = pr.GetMaxFlow(0, n+m+1);
        if (result == m)
            std::cout << "yes\n";
        else
            std::cout << "no\n";
        // std::cout << result << " == " << m << "\n";
    }
}
