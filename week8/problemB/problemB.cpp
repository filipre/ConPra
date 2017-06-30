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

// http://www.geeksforgeeks.org/sieve-of-eratosthenes/ (sort of)
void SieveOfEratosthenes(std::vector<bool> &prime, std::vector<int> &primeList)
{
    // // Create a boolean array "prime[0..n]" and initialize
    // // all entries it as true. A value in prime[i] will
    // // finally be false if i is Not a prime, else true.
    // bool prime[n+1];
    // memset(prime, true, sizeof(prime));
    int n = prime.size();
    prime[0] = false;
    prime[1] = false;
    for (int p=2; p*p<=n; p++)
    {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            primeList.push_back(p);
            // Update all multiples of p
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    // for (int p=2; p<=20; p++)
    //     if (prime[p])
    //         std::cout << p << " ";
    // std::cout << "\n";
    //
    // std::cout << prime[12345678];
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    // generate primes up to sqrt(10^8) = 10^4 and save them in array

    std::vector<bool> primes (100000000+1, true);
    std::vector<int> primeList;
    SieveOfEratosthenes(primes, primeList);

    // for (int i=0; i<20; i++)
    //     std::cout << primeList[i] << " ";
    // std::cout << "\n";

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int n;
        std::cin >> n;

        if (n % 2 == 0)
        {
            for (int i=2; i<n; ++i)
            {
                if (primes[i] && primes[n-i])
                {
                    if (i <= n-i)
                        std::cout << i << " " << n-i;
                    else
                        std::cout << n-i << " " << i;

                    goto next;
                }
            }
        }
        else
        {
            for (int i=2; i<n; ++i)
            {
                if (primes[i])
                {
                    for (int j=i; j<=n-i; ++j)
                    {
                        if (primes[j] && primes[n-j-i])
                        {
                            if (i <= j && j <= n-j-i)
                            {
                                std::cout << i << " " << j << " " << n-j-i;
                            }
                            else if (i <= n-j-i && n-j-i <= j)
                            {
                                std::cout << i << " " << n-j-i << " " << j;
                            }
                            else
                            {
                                std::cout << n-j-i << " " << i << " " << j;
                            }
                            goto next;
                        }
                    }
                }
            }


            // std::cout << "todo\n";
        }

    next:
        std::cout << "\n";

    }

    return 0;
}
