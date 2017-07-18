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

int64_t startWithCar(int64_t day, std::vector<int64_t> &carTimes, std::vector<int64_t> &bikeTimes, int64_t c, int64_t m)
{
    std::vector<int64_t> dp_without (c+1, 0);
    std::vector<int64_t> dp_with (c+1, 0);

    int64_t offset = (day-1) * (c+1); // start time = day * (c+1) - c - 1

    dp_without[0] = carTimes[offset];
    dp_with[0] = (INT64_MAX / 2);

    for (int64_t i=1; i<=c; ++i)
    {
        dp_without[i] = dp_without[i-1] + carTimes[offset + i];
        dp_with[i] = std::min(
            dp_without[i-1] + bikeTimes[offset + i] + m,
            dp_with[i-1] + bikeTimes[offset + i]
        );
    }

    // std::cout << "car (no change): " << dp_without[c] << ",car -> bike: " << dp_with[c] << "\n";

    return std::min(dp_without[c], dp_with[c]);
}

int64_t startWithBike(int64_t day, std::vector<int64_t> &carTimes, std::vector<int64_t> &bikeTimes, int64_t c, int64_t m)
{
    std::vector<int64_t> dp_without (c+1, 0);
    std::vector<int64_t> dp_with (c+1, 0);

    int64_t offset = (day-1) * (c+1); // start time = day * (c+1) - c - 1

    dp_without[0] = bikeTimes[offset];
    dp_with[0] = INT64_MAX / 2;

    for (int64_t i=1; i<=c; ++i)
    {
        dp_without[i] = dp_without[i-1] + bikeTimes[offset + i];
        dp_with[i] = std::min(
            dp_without[i-1] + carTimes[offset + i] + m,
            dp_with[i-1] + carTimes[offset + i]
        );
    }

    // std::cout << "bike (no change): " << dp_without[c] << ",bike -> car: " << dp_with[c] << "\n";

    return std::min(dp_without[c], dp_with[c]);
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

        int64_t d, c, m;
        std::cin >> d; // number of days
        std::cin >> c; // number of checkpoints
        std::cin >> m; // time for switch in minutes
        // std::cout << d << ", " << c << ", " << m << "\n";

        std::vector<int64_t> carTimes;
        for (int64_t i=1; i<=(d*(c+1)); ++i)
        {
            int64_t time_i;
            std::cin >> time_i;
            carTimes.push_back(time_i);
        }

        std::vector<int64_t> bikeTimes;
        for (int64_t i=1; i<=(d*(c+1)); ++i)
        {
            int64_t time_i;
            std::cin >> time_i;
            bikeTimes.push_back(time_i);
        }

        // solve each day on it's own
        int64_t result = 0;
        for (int64_t day=1; day<=d; ++day)
        {
            // std::cout << "day " << day << "\n";
            int64_t carSolution = startWithCar(day, carTimes, bikeTimes, c, m);
            int64_t bikeSolution = startWithBike(day, carTimes, bikeTimes, c, m);
            // std::cout << "add: " << std::min(carSolution, bikeSolution) << "\n";
            result = result + std::min(carSolution, bikeSolution);
        }

        std::cout << result << "\n";

    }

    return 0;
}
