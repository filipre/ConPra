// typedef std::vector<std::vector<Edge>> graph_t;
// typedef std::vector<std::vector<int32_t>> graph_t; // lets use a matrix since it is fully connected
// typedef std::vector<std::pair<Vertex, Vertex>> mst_t;
//
// void primVisit(Vertex &v,
//     std::vector<bool> &visited,
//     std::vector<int64_t> &c,
//     std::vector<Vertex> &pre,
//     std::priority_queue<Vertex> &PQ,
//     graph_t &graph
// )
// {
//     visited[v] = true;
//     for (Vertex u = 1; u < graph.size(); ++u)
//     {
//         if (!visited[u])
//         {
//             if (graph[v][u] < c[u])
//             {
//                 pre[u] = v;
//                 c[u] = graph[v][u];
//                 // TODO....
//             }
//         }
//     }
// }
//
// mst_t& prim(graph_t &graph)
// {
//     n = graph.size() - 1;
//     mst_t S; // empty vector
//     std::vector<bool> visited(n+1);
//     std::vector<int64_t> c(n+1);
//     std::vector<Vertex> pre(n+1);
//
//     for (int i = 1; i <= n; ++i)
//     {
//         visited[i] = false;
//         c[i] = INT32_MAX;
//     }
//
//     std::priority_queue<Vertex> PQ;
//     Vertex s = 1; // always exists
//     // TODO primVisit
//     while (!PQ.empty())
//     {
//         Vertex v = PQ.pop();
//         // TODO how do I find out pre(V)?
//         std::pair<int32_t
//         S.push_back()
//     }
// }
