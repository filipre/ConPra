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


int64_t binom (int64_t n, int64_t k)
{
    // std::cout << "n: " <<  n << ", k: " << k << "\n";
    int64_t result = 1;
    for (int64_t i=1; i<=k; ++i)
    {
        result = result * (n-k+i) / i;
    }
    return result;
}

void calcCoefficents(int64_t number, int64_t primeBase, std::vector<int64_t> &coeff)
{
    // first get degree k
    // double doubleDegree = std::log(number) / std::log(primeBase);
    int64_t degree = (int64_t)(std::log(number) / std::log(primeBase));
    // std::cout << "doubleDegree: " << doubleDegree << ", degree: " << degree << "\n";

    int64_t b, c, r;
    for (int64_t i=degree; i>=0; --i)
    {
        b = std::pow(primeBase, i);
        c = number / b;
        // std::cout << c << " ";
        coeff.push_back(c);
        r = number % b;
        number = r;
    }
    // std::cout << "\n";
}

int64_t fullNumber = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23;

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

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int64_t n, k;
        std::cin >> n; // courses
        std::cin >> k; // choose k courses

        if (k > n)
        {
            std::cout << 0 << "\n";
        }

        std::vector<int64_t> numbers { 2, 3, 5, 7, 11, 13, 17, 19, 23};
        std::vector<int64_t> results;

        for (int64_t number : numbers)
        {
            // std::cout << "number: " << number << ":\n";

            std::vector<int64_t> n_coeff;
            calcCoefficents(n, number, n_coeff);

            // std::cout << "n_coeff: ";
            // for (int64_t i=0; i<n_coeff.size(); ++i)
            // {
            //     // results[i] += numbers[i];
            //     std::cout << n_coeff[i] << " ";
            // }
            // std::cout << "\n";

            std::vector<int64_t> k_coeff;
            calcCoefficents(k, number, k_coeff);

            // std::cout << "k_coeff: ";
            // for (int64_t i=0; i<k_coeff.size(); ++i)
            // {
            //     // results[i] += numbers[i];
            //     std::cout << k_coeff[i] << " ";
            // }
            // std::cout << "\n";

            int64_t diff = n_coeff.size() - k_coeff.size();
            // std::cout << "diff: " << diff << "\n";
            int64_t result = 1;
            for (int64_t i=0; i<k_coeff.size(); ++i)
            {
                // std::cout << "temp result: " << result << "\n";
                // std::cout << "ncoeff i: " << n_coeff[i+diff] << ", kcoeff i: " << k_coeff[i] << "\n";
                result = result * binom(n_coeff[i+diff], k_coeff[i]);
                result = result % number;
            }
            // std::cout << "real result: " << result << "\n";
            results.push_back(result);
        }

        // for (int64_t i=0; i<numbers.size(); ++i)
        // {
        //     // results[i] += numbers[i];
        //     std::cout << results[i] << " ";
        // }
        // std::cout << "\n";

        int64_t solution = 0;
        for (int64_t i=0; i<numbers.size(); ++i)
        {
            int64_t m_i = fullNumber / numbers[i];
            int64_t x, y;
            xGCD(numbers[i], m_i, x, y);

            int64_t test = x * numbers[i] + m_i * y;
            test = test % fullNumber;
            // std::cout << "test: " << test << "\n";

            // std::cout << x << " " << y << "\n";
            int64_t e_i = m_i * y;
            e_i = e_i % fullNumber;
            // std::cout << e_i << "\n";

            int64_t bla = e_i * results[i];
            bla = bla % fullNumber;

            solution = solution + bla;
            // std::cout << solution << "\n";
            solution = solution % fullNumber;
            // std::cout << solution << "\n";
        }
        
        if (solution < 0)
            solution = solution + fullNumber;
        //
        std::cout << solution << "\n";
    }

    return 0;
}
