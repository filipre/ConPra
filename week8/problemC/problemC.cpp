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
__int128 xGCD(__int128 a, __int128 b, __int128 &x, __int128 &y)
{
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    __int128 x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

//https://stackoverflow.com/questions/25114597/how-to-print-int128-in-g
std::ostream& operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int64_t t;
    std::cin >> t;

    for (int64_t testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        std::cout << "\n";

        int64_t n1, k1;
        std::cin >> n1; // games
        std::cin >> k1; // friends invited
        __int128 n, k;
        n = static_cast<__int128>(n1);
        k = static_cast<__int128>(k1);

        std::vector<__int128> size;
        std::vector<__int128> rest;

        std::map<__int128, __int128> foundPrimes;
        bool possible = true;

        __int128 M = 1;
        for (__int128 i=1; i<=n; ++i)
        {
            int64_t size_i1, rest_i1;
            std::cin >> size_i1; // team size for game i, prime for all i
            std::cin >> rest_i1; // remained

            __int128 size_i, rest_i;
            rest_i = static_cast<__int128>(rest_i1);
            size_i = static_cast<__int128>(size_i1);

            if(foundPrimes.find(size_i) != foundPrimes.end())
            {
                if (foundPrimes[size_i] == rest_i)
                {
                    // std::cout << "ignore\n";
                }
                else
                {
                    possible = false;
                    // break;
                }
            }
            else
            {
                foundPrimes[size_i] = rest_i;
                M = M * size_i;
                size.push_back(size_i);
                rest.push_back(rest_i);
            }
        }

        if (!possible)
        {
            std::cout << "impossible\n";
            continue;
        }

        // x = rest_i (mod size_i)

        n = size.size();

        __int128 result = 0;
        for (__int128 i=0; i<n; ++i)
        {
            __int128 M_i = M / size[i];
            // std::cout << M << " / " << size[i] << ": " << M_i << "\n";
            __int128 x, y;
            xGCD(size[i], M_i, x, y);
            __int128 e_i = M_i * y;
            std::cout << M_i << " * " << y << ": " << e_i << "\n";
            // e_i = e_i % M;
            __int128 x_i = e_i * rest[i];
            std::cout << x_i << "\n";
            // x_i = x_i % M;
            result = result + x_i;
        }

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
            __int128 scale = (k - result) / M;
            std::cout << result + (scale * M) << "\n"; // we need to subtsract M because we "overshot"
        }
    }

    return 0;
}
