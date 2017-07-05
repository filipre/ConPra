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

// https://stackoverflow.com/questions/12826114/euclids-extended-algorithm-c
uint64_t xGCD(uint64_t a, uint64_t b, uint64_t &x, uint64_t &y) {
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    uint64_t x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

uint64_t lcm (uint64_t a, uint64_t b)
{
    uint64_t x, y;
    // std::cout << (a * b) << "\n";
    return ((a * b) / xGCD(a, b, x, y));
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

        uint64_t n;
        std::cin >> n; // number of leas friends

        std::vector<uint64_t> hunger;
        // int M = 1;
        for (uint64_t i=1; i<=n; ++i)
        {
            uint64_t c_i;
            std::cin >> c_i;
            hunger.push_back(c_i);
            // M = M * (c_i + 1);
        }

        // generate all possibilities of candy taking
        uint64_t max = std::pow(2, n);
        std::vector<uint64_t> hungerCombinations;
        for (uint64_t j=0; j<max; ++j)
        {
            uint64_t sum = 1;
            for(uint64_t i=0; i<n; ++i)
            {
                // check ith LSB if it is "turned" on.
                if (1 == ( (j >> i) & 1))
                {
                    sum = sum + hunger[i];
                }
            }
            // hungerCombinations.insert(std::make_pair(sum, sum));
            hungerCombinations.push_back(sum);
            // std::cout << "sum: " << sum << "\n";
        }

        // std::cout << "l: " << hungerCombinations.size() << "\n";

        uint64_t x = lcm(hungerCombinations[0], hungerCombinations[1]);
        for (uint64_t i=1; i<hungerCombinations.size()-1; ++i)
        {
            x = lcm(x, hungerCombinations[i+1]);
        }

        std::cout << x << "\n";

        // std::cout << "l: " << hungerCombinations.size() << "\n";
        // auto minIt = std::min(hungerCombinations.begin(), hungerCombinations.end());
        // auto maxIt = std::max(hungerCombinations.begin(), hungerCombinations.end());
        // std::cout << (*minIt) << "\n";
        // std::cout << (*maxIt) << "\n";
    }

    return 0;
}
