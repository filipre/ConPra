#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

bool inCanyon(double current, int u, int v)
{
    // use 10^-4 as prec.
    double err = 0.000000001;
    return (current - u > err) && (v - current > err);
}

bool greaterThan(double a, double b)
{
    double err = 0.000000001;
    return (a - b) > err;
}

// returns whether the current configuration works or not
bool testDistance(double x, int d, int p, int u, int v)
{
    // find out how many post I can place until I reach u
    int n1 = ((u - 0) / x + 1); // 1

    // find out NEW minimum position for the next post
    double positionOfPostBeforeU = (n1 - 1) * x;
    double newV = v;
    if (greaterThan(positionOfPostBeforeU + x, v))
        newV = positionOfPostBeforeU + x;

    int n2 = ((d - newV) / x + 1);

    return n1 + n2 >= p;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        int d;
        std::cin >> d;
        int p;
        std::cin >> p;
        int u, v;
        std::cin >> u;
        std::cin >> v;

        double low = 0;
        double high = d;

        double err = 0.000000001;
        double mid;

        while (high - low > err)
        {
            mid = (low+high) / 2;
            if (testDistance(mid, d, p, u, v))
            {
                low = mid; // seems to work. there is place to find a better mid!
            } else {
                high = mid; // nope. mid is too high. better make it smaller
            }
            //std::cout << "[" << low << ", " << high << "]\n";
        }

        std::cout << "Case #" << testCase << ": " << std::setprecision(11) << high << '\n';
    }

    return 0;
}
