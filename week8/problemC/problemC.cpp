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

//https://stackoverflow.com/questions/12826114/euclids-extended-algorithm-c
int64_t xGCD(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    int64_t x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    // std::cout << INT64_MAX << "\n";
    // std::cout << INT64_MIN << "\n";

    int64_t t;
    std::cin >> t;

    for (int64_t testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int64_t n, k;
        std::cin >> n; // games
        std::cin >> k; // friends invited

        std::vector<int64_t> size;
        std::vector<int64_t> rest;

        std::map<int64_t, int64_t> foundPrimes;
        bool possible = true;

        int64_t M = 1;
        for (int64_t i=1; i<=n; ++i)
        {
            int64_t size_i, rest_i;
            std::cin >> size_i; // team size for game i, prime for all i
            std::cin >> rest_i; // remained

            if(foundPrimes.find(size_i) != foundPrimes.end())
            {
                // std::cout << "if\n";
                if (foundPrimes[size_i] == rest_i)
                {
                    // std::cout << "ignore\n";
                }
                else
                {
                    // std::cout << "dont\n";
                    possible = false;
                    break;
                }
            }
            else
            {
                // std::cout << "else\n";
                // foundPrimes.insert(std::pair<int64_t,int64_t>(size_i, rest_i));
                foundPrimes[size_i] = rest_i;
                M = M * size_i;
                size.push_back(size_i);
                rest.push_back(rest_i);
            }
            // std::cout << "size: " << size_i2 << ", rest_i: " << rest_i2 << "\n";
        }

        // std::cout << "done\n";
        if (!possible)
        {
            std::cout << "impossible\n";
            continue;
        }

        // std::cout << "M: " << M << "\n";

        // x = rest_i (mod size_i)

        n = size.size();

        int64_t result = 0;
        // std::cout << "init x: " << result << "\n";
        for (int64_t i=0; i<n; ++i)
        {
            int64_t M_i = M / size[i];
            // std::cout << "M_i: " << M_i << "\n";
            int64_t x, y;
            xGCD(size[i], M_i, x, y);
            // std::cout << "x: " << x << ", y: " << y << "\n";
            int64_t e_i = M_i * y;
            // e_i = e_i % M;
            int64_t x_i = e_i * rest[i];
            // x_i = x_i % M;
            // std::cout << "x_i: " << x_i << "\n";
            result = result + x_i;
            // std::cout << "x: " << result << "\n";
        }

        // TODO
        while (result < 0)
        {
            result = result + M;
        }

        if (result > k)
        {
            std::cout << "impossible\n";
        }
        else
        {
            int64_t scale = (k - result) / M;
            std::cout << result + (scale * M) << "\n"; // we need to subtsract M because we "overshot"
        }
    }

    return 0;
}
