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


struct Info {
    int i; // number
    double ratio; // score / points
};
auto cmpInfo = [](Info left, Info right)
{
    return (left.ratio < right.ratio);
};
typedef std::priority_queue<Info, std::vector<Info>, decltype(cmpInfo)> pq_t;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int m, n;
        std::cin >> m; // number of chars that fit on cheat sheet
        std::cin >> n; // number of topic

        std::vector<int> lengths (n+1);
        std::vector<int> scores (n+1);
        for (int i=1; i<=n; ++i)
        {
            std::cin >> lengths[i]; // length of piece of information
            std::cin >> scores[i]; // score
        }

        pq_t infos(cmpInfo);
        for (int i=1; i<=n; ++i)
        {
            infos.push({ i, (static_cast<double>(scores[i]) / static_cast<double>(lengths[i])) });
        }

        // info contains the most valuable info at top
        int currentLength = 0; // empty sheet
        int currentValue = 0;
        while (!infos.empty())
        {
            Info mostProfit = infos.top();
            // if there is enough space in it
            if (m - currentLength >= lengths[mostProfit.i])
            {
                std::cout << mostProfit.i << " ";
                currentLength += lengths[mostProfit.i];
                currentValue += scores[mostProfit.i];
            } else {
                infos.pop();
            }
            // otherwise remove the item since it does not fit into the bag anyway
        }
        std::cout << "\n";
    }

    return 0;
}
