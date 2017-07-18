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

// Solution is from https://cses.fi/book.pdf (Dynamic Programming Chapter)

/*
solve(x)
    = 0 if x=0
    = min_c \in coins{ solve(x-c) + 1 } if x>0
*/

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int64_t n, c;
        std::cin >> n; // number of coins
        std::cin >> c; // money that must be spent

        std::vector<int64_t> coins;
        for (int64_t i=1; i<=n; ++i)
        {
            int64_t a_i;
            std::cin >> a_i;
            coins.push_back(a_i);
        }

        std::vector<int64_t> value (c+1);
        std::vector<int64_t> first (c+1);

        value[0] = 0;
        for (int64_t x=1; x<=c; x++)
        {
            value[x] = INT64_MAX;
            for (auto coin : coins) {
                if (x-coin >= 0 && value[x-coin]+1 < value[x])
                {
                    value[x] = value[x-coin]+1;
                    first[x] = coin;
                }
            }
        }

        // for (int64_t x=1; x<=c; x++)
        // {
        //     std::cout << first[x] << " ";
        // }
        // std::cout << "\n";

        // std::cout << value[c] << "\n";

        std::map<int64_t, int64_t> counter;
        while (c > 0)
        {
            if (counter.find(first[c]) != counter.end())
            {
                // exist already. just increase it
                // (counter.find(first[c])->second)++;
                counter[first[c]] = counter[first[c]] + 1;
            }
            else
            {
                // add entry and count it
                // counter.insert(std::make_pair(first[c], 1));
                counter[first[c]] = 1;
            }
            c -= first[c];
        }

        for (auto coin : coins)
        {
            std::cout << counter[coin] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
