#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

typedef std::array<uint32_t, 2> interval_t;

int countBefore(const std::vector<interval_t> &intervals, int s, uint32_t station)
{
    // iterate through every interval
    uint32_t before = 0;
    // std::cout << "before: " << before << '\n';
    for (int i=1; i<=s; ++i)
    {
        // if an interval applies, count how many elements are before in that interval from [min, station) = [min, station-1]

        // check if it is inside the interval
        // std::cout << intervals[i][0] << " <= " << station << " <= " << intervals[i][1] << '\n';
        // std::cout << intervals[i][1] << " < " << station << '\n';
        if (intervals[i][0] <= station && station <= intervals[i][1])
        {
            before += (station - intervals[i][0]);
            // std::cout << "+" << (station - intervals[i][0]) << ": " << before << '\n';
        }
        // check if has passed already
        else if(intervals[i][1] < station)
        {
            before += (intervals[i][1] - intervals[i][0]) + 1;
        }
    }
    // std::cout << "before after: " << before << '\n';
    return before;
}

uint32_t findMin(const std::vector<interval_t> &intervals, int s)
{
    uint32_t min = 2147483647; // 2^31 - 1
    for (int i=1; i<=s; ++i)
    {
        if (intervals[i][0] < min)
            min = intervals[i][0];
    }
    return min;
}

uint32_t findMax(const std::vector<interval_t> &intervals, int s)
{
    uint32_t max = 1;
    for (int i=1; i<=s; ++i)
    {
        if (intervals[i][1] > max)
            max = intervals[i][1];
    }
    return max;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ":\n";

        int s, f;
        std::cin >> s;
        std::cin >> f;

        std::vector<interval_t> intervals (s+1); // don't use 0 element.
        for (int i=1; i<=s; ++i)
        {
            std::cin >> intervals[i][0]; // u_i
            std::cin >> intervals[i][1]; // u_v
        }

        uint32_t min = findMin(intervals, s);
        uint32_t max = findMax(intervals, s);
        // std::cout << "min: " << min << " max: " << max << '\n';

        // for (int i=min; i<=max; ++i)
        // {
        //     std::cout << "i: " << i << "\n";
        //     std::cout << countBefore(intervals, i, min, max) << '\n';
        // }
        // std::cout << '\n';

        uint32_t r_i; // lea's friend
        for (int i=1; i<=f; ++i)
        {
            std::cin >> r_i;
            // std::cout << "leas freund: " << r_i << '\n';

            //binary search
            uint32_t low = min;
            uint32_t high = max;
            // std::cout << "low: " << low << ", high: " << high << '\n';
            // std::cout << "high - low: " << high - low << '\n';

            uint32_t mid;
            uint32_t testIntervalMin, testIntervalMax;

            while (high - low > 0)
            {
                // std::cout << "r_i: " << r_i << '\n';
                // std::cout << "low and high: [" << low << ", " << high << "]\n";
                // std::cout << "low "

                mid = (low + high) / 2; // floor is taken care of type
                // std::cout << "mid: " << mid << '\n';

                testIntervalMin = countBefore(intervals, s, mid) + 1;
                testIntervalMax = countBefore(intervals, s, mid+1);
                // std::cout << "testIntervalMin and Max: [" << testIntervalMin << ", " << testIntervalMax << "]\n";

                if (testIntervalMin <= r_i && r_i <= testIntervalMax)
                {
                    high = mid;
                    break;
                } else {
                    if (r_i < testIntervalMin) {
                        high = mid-1;
                    } else {
                        low = mid+1;
                    }
                }
            }

            std::cout << high << '\n';
        }
    }

    return 0;
}
