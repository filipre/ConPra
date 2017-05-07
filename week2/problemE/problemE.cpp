#include <iostream>
#include <vector>
#include <cstdint>

// typedef std::vector<int> bowls_t;
typedef std::vector<uint64_t> cumulative_t;

// O(1)
void countCookiesInBowls(const cumulative_t &cumulativeSum, int n, int a, int b, uint64_t &left, uint64_t &middle, uint64_t &right)
{
    left = cumulativeSum[a-1];
    middle = cumulativeSum[b] - cumulativeSum[a-1];
    right = cumulativeSum[n] - cumulativeSum[b];
}

// O(1)
uint64_t calcLeasCookies(const cumulative_t &cumulativeSum, int n, int a, int b)
{
    // find max which will grab tom. if something is equal it doesn't really matter...
    if (a > b)
        return 0;

    uint64_t left, middle, right;
    countCookiesInBowls(cumulativeSum, n, a, b, left, middle, right);
    if (left >= middle && left >= right)
        return middle + right; // tom will grab left
    else if (middle >= left && middle >= right)
        return left + right;
    else
        return left + middle;
}

uint64_t findMax(const cumulative_t &cumulativeSum, int n)
{
    // 9
    // 21	21
    // 25	25	25
    // 32	32	32	32
    // 29	38	42	42	39
    // 27	36	44	44	39	29
    // 22	31	43	46	39	29	27
    // 14	23	35	39	39	29	27	22
    // 3	12	24	28	35	29	27	22	14
    // 0	9	21	25	32	29	27	22	14	3
    // a to the right, b downwards

    int a_low = 1;
    int a_high = n;

    int b_low = 1;
    int b_high = n;

    int a_current, b_current;

    uint64_t center, north, east, south, west;
    uint64_t northeast, southeast, southwest, northwest;
    int64_t d_north, d_east, d_south, d_west;
    int64_t d_northeast, d_southeast, d_southwest, d_northwest;

    int64_t d_max;
    char direction;

    while (true)
    {
        a_current = (a_low + a_high) / 2;
        b_current = (b_low + b_high) / 2;

        std::cout << "a: [" << a_low << ", " << a_high << "]\n";
        std::cout << "b: [" << b_low << ", " << b_high << "]\n";
        std::cout << "a_current: " << a_current << '\n';
        std::cout << "b_current: " << b_current << '\n';

        // if (a_current > b_current)
        //     a_current = b_current;

        center = calcLeasCookies(cumulativeSum, n, a_current, b_current);

        if (b_current >= 2)
            north = calcLeasCookies(cumulativeSum, n, a_current, b_current-1);
        else
            north = 0; // gives a really bad derivative

        if (a_current <= n)
            east = calcLeasCookies(cumulativeSum, n, a_current+1, b_current);
        else
            east = 0;

        if (b_current <= n)
            south = calcLeasCookies(cumulativeSum, n, a_current, b_current+1);
        else
            south = 0;

        if (a_current >= 2)
            west = calcLeasCookies(cumulativeSum, n, a_current-1, b_current);
        else
            west = 0;


        if (b_current >= 2 && a_current <= n)
            northeast = calcLeasCookies(cumulativeSum, n, a_current+1, b_current-1);
        else
            northeast = 0;

        if (b_current <= n && a_current <= n)
            southeast = calcLeasCookies(cumulativeSum, n, a_current+1, b_current+1);
        else
            southeast = 0;

        if (b_current <= n && a_current >= 2)
            southwest = calcLeasCookies(cumulativeSum, n, a_current-1, b_current+1);
        else
            southwest = 0;

        if (b_current >= 2 && a_current >= 2)
            northwest = calcLeasCookies(cumulativeSum, n, a_current-1, b_current-1);
        else
            northwest = 0;

        std::cout << "center: " << center << '\n';

        if (center >= north && center >= east && center >= south && center >= west
            && center >= northeast && center >= southeast && center >= southwest && center >= northwest)
        {
            // we are done...
            return center;
        }

        // calc direction of deepest ascent

        d_north = north - center;
        d_east = east - center;
        d_south = south - center;
        d_west = west - center;

        d_northeast = northeast - center;
        d_southeast = southeast - center;
        d_southwest = southwest - center;
        d_northwest = northwest - center;

        std::cout << "{"
            << d_north << ", " << d_northeast << ", "
            << d_east << ", " << d_southeast << ", "
            << d_south << ", " << d_southwest << ", "
            << d_west << ", " << d_northwest
        << "}\n";

        d_max = 0;
        if (d_north >= d_max)
        {
            d_max = d_north;
            direction = 'n';
        }
        if (d_east >= d_max)
        {
            d_max = d_east;
            direction = 'e';
        }
        if (d_south >= d_max)
        {
            d_max = d_south;
            direction = 's';
        }
        if (d_west >= d_max)
        {
            d_max = d_west;
            direction = 'w';
        }
        if (d_northeast >= d_max)
        {
            d_max = d_northeast;
            direction = 'v';
        }
        if (d_southeast >= d_max)
        {
            d_max = d_southeast;
            direction = 'x';
        }
        if (d_southwest >= d_max)
        {
            d_max = d_southwest;
            direction = 'y';
        }
        if (d_northwest >= d_max)
        {
            d_max = d_northwest;
            direction = 'z';
        }
        std::cout << "max: " << d_max << " , direction: " << direction << '\n';

        switch (direction)
        {
            case 'n': b_high = b_current; break;
            case 'e': a_low = a_current; break;
            case 's': b_low = b_current; break;
            case 'w': a_high = a_current; break;

            case 'v': b_high = b_current; a_low = a_current; break;
            case 'x': b_low = b_current; a_low = a_current; break;
            case 'y': b_low = b_current; a_high = a_current; break;
            case 'z': b_high = b_current; a_high = a_current; break;
        }
    }
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
        for (int i=1; i<=n; ++i)
        {
            // bowls[i] = ((i * p + q) % r) + s;
            cumulativeSum[i] += cumulativeSum[i-1] + ((i * p + q) % r) + s;
            // std::cout << "bowls[" << i << "]: " << ((i * p + q) % r) + s << '\n';
        }

        for (int b=1; b<=n; ++b)
        {
            for (int a=1; a<=n; ++a)
            {
                std::cout << calcLeasCookies(cumulativeSum, n, a, b) << "\t";
            }
            std::cout << '\n';
        }

        std::cout << "Case #" << testCase << ": \n" << findMax(cumulativeSum, n) << '\n';
    }

    return 0;
}
