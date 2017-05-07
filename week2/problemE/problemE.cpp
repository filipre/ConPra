#include <iostream>
#include <vector>
#include <cstdint>

// typedef std::vector<int> bowls_t;
typedef std::vector<int64_t> cumulative_t;

// O(1)
void countCookiesInBowls(const cumulative_t &cumulativeSum, int n, int a, int b, int64_t &left, int64_t &middle, int64_t &right)
{
    left = cumulativeSum[a-1];
    middle = cumulativeSum[b] - cumulativeSum[a-1];
    right = cumulativeSum[n] - cumulativeSum[b];
}

// O(1)
int64_t calcLeasCookies(const cumulative_t &cumulativeSum, int n, int a, int b)
{
    // find max which will grab tom. if something is equal it doesn't really matter...
    if (a > b)
        return 0;

    int64_t left, middle, right;
    countCookiesInBowls(cumulativeSum, n, a, b, left, middle, right);
    if (left >= middle && left >= right)
        return middle + right; // tom will grab left
    else if (middle >= left && middle >= right)
        return left + right;
    else
        return left + middle;
}

int64_t findMax(const cumulative_t &cumulativeSum, int n, int b)
{
    // 9
    // 21	21
    // 25	25	25
    // 32	32	32	32

    // 29	38	42	42	39 <-- example line where b=5

    // 27	36	44	44	39	29
    // 22	31	43	46	39	29	27
    // 14	23	35	39	39	29	27	22
    // 3	12	24	28	35	29	27	22	14
    // 0	9	21	25	32	29	27	22	14	3

    // --> a to the right -->

    int a_low = 1;
    int a_high = b;
    int a_mid;

    int64_t center, left, right;

    while (true)
    {
        a_mid = (a_low + a_high) / 2;
        // std::cout << "[" << a_low << ", " << a_high << "] --> " << a_mid << '\n';

        center = calcLeasCookies(cumulativeSum, n, a_mid, b);
        if (a_mid >= 2)
            left = calcLeasCookies(cumulativeSum, n, a_mid-1, b);
        else
            left = 0;
        if (a_mid < n)
            right = calcLeasCookies(cumulativeSum, n, a_mid+1, b);
        else
            right = 0;
        // std::cout << "| " << left << " | " << center << " | " << right << " |\n";

        if (center > left && center > right)
        {
            return center;
        }
        else if (center == left)
        {
            return center;
        }
        else if (center == right)
        {
            return center;
        }
        else if (left > center)
        {
            a_high = a_mid-1;
        }
        else if (right > center)
        {
            a_low = a_mid+1;
        }
    }

    return 0;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        int n, p, q, r, s;
        std::cin >> n;
        std::cin >> p;
        std::cin >> q;
        std::cin >> r;
        std::cin >> s;

        // calculate bowls
        // bowls_t bowls (n+1); // ignore 0 bowl
        cumulative_t cumulativeSum (n+1); // [0] is always 0
        cumulativeSum[0] = 0; // we don't use this
        // FUCK THIS SHIT!!!! HOW COULD I MISS THAT AUTOMATIC TYPE CONVERSION
        for (int64_t i=1; i<=n; ++i)
        {
            // bowls[i] = ((i * p + q) % r) + s;
            cumulativeSum[i] += (cumulativeSum[i-1] + ((i * p + q) % r) + s);
        }

        // int64_t manualMax = 0;
        // for (int b=1; b<=n; ++b)
        // {
        //     for (int a=1; a<=b; ++a)
        //     {
        //         int64_t result = calcLeasCookies(cumulativeSum, n, a, b);
        //         if (result > manualMax)
        //             manualMax = result;
        //         // std::cout << result << " ";
        //     }
        //     // std::cout << '\n';
        // }
        // std::cout << '\n';
        // std::cout << "manual:\t\t" << manualMax << '\n';


        int64_t mymax = 0;
        int64_t result;
        for (int b=1; b<=n; ++b)
        {
            result = findMax(cumulativeSum, n, b);
            // std::cout << "Case #" << testCase << ", Part " << b << ": " << result << '\n';
            if (result > mymax)
                mymax = result;
        }
        std::cout << "Case #" << testCase << ": " << mymax << '\n';
    }

    return 0;
}
