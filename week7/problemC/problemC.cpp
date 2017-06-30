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

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int64_t n, m;
        std::cin >> n; // amout of trees felled
        std::cin >> m; // amounf of disk saws

        std::vector<int64_t> time;
        for (int i=1; i<=n; ++i)
        {
            int64_t l_i;
            std::cin >> l_i; // time to cut tree i
            time.push_back(l_i);
        }
        std::sort(time.begin(), time.end());

        // std::priority_queue<int, std::vector<int>, std::greater<int> > buckets;
        std::multiset<int64_t> buckets;
        for (int i=1; i<=m; ++i)
        {
            // buckets.push(0);
            buckets.insert(0);
        }

        while (!time.empty())
        {
            // get biggest value
            auto biggest = time.back();
            time.pop_back();
            // std::cout << biggest << " ";

            // put it into the "emptiest" bucket
            auto saw_it = buckets.begin();
            int64_t saw = *saw_it;
            buckets.erase(saw_it);
            saw += biggest;
            buckets.insert(saw);
        }
        // std::cout << "\n";

        auto max_it = buckets.rbegin();
        std::cout << *max_it << "\n";


    }

    return 0;
}
