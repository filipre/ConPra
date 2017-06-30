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

int getIndexSmallerEqualThanValue(int value, std::vector<int> &vec, int minIndex, int maxIndex)
{
    // return -1 if there does not exist one
    int res = -1;
    for (int i=minIndex; i<maxIndex; ++i)
    {
        if (vec[i] <= value)
        {
            res = i;
        }
        else
        {
            break;
        }
    }
    return res;
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

        int l, n, d;
        std::cin >> l; // length of the main street
        std::cin >> n; // number of street lights
        std::cin >> d; // radius of each light cone

        std::vector<int> positions;
        for (int i=1; i<=n; ++i)
        {
            int p_i;
            std::cin >> p_i; // position of street light
            positions.push_back(p_i);
        }

        // Edge cases. Make sure that positions contains at least one element
        if (n == 0)
        {
            std::cout << "impossible\n";
            continue;
        }

        if (d == 0)
        {
            std::cout << "impossible\n";
            continue;
        }

        std::sort(positions.begin(), positions.end());
        // for (std::vector<int>::iterator it = positions.begin(); it != positions.end(); ++it)
        // {
        //     std::cout << *it << " ";
        // }
        // std::cout << "\n";

        int index = 0;
        bool possible = true;
        int from = 0;
        int to = from + d;
        int counter = 0;

        // TODO
        while(true)
        {
            if (to-d >= l)
            {
                break;
            }

            index = getIndexSmallerEqualThanValue(to, positions, index, n);
            if (index == -1)
            {
                possible = false;
                break;
            }

            if (from <= positions[index] && positions[index] <= to)
            {
                // everything ok!
                ++counter;
                from = positions[index];
                to = from + 2 * d;
                // std::cout << positions[index] << "\n";
                ++index;
            }
            else
            {
                break;
            }
        }

        // std::cout << from << " - " << to-d << "\n"; // TODO IMPORTANT!!!
        // std::cout << l << "\n";
        if (possible && (to-d >= l))
        {
            std::cout << counter << "\n";
        }
        else
        {
            std::cout << "impossible\n";
        }















        //

        //
        // auto currentIterator = positions.begin();
        // auto lastIterator = std::prev(positions.end(), 1);
        // int startValue = 0;
        // currentIterator = std::upper_bound(currentIterator, positions.end(), 0);
        // if (currentIterator == positions.begin())
        // {
        //     // if the iterator is the beginning, that means that even the beginning is already
        //     // too far away from current maxValue so we are done.
        //     std::cout << "impossible\n";
        //     continue;
        // }
        //
        // while (true)
        // {
        //     std::cout << "Current Iterator at: " << *currentIterator << "\n";
        //
        // }





        // // identify new max value
        // int maxValue = *currentIterator + d;
        // std::cout << maxValue << "\n";
        //
        // // find element that is equal or lower than max value
        // // -> find value that is strictly larger then max value, then take precedence
        // currentIterator = std::upper_bound(currentIterator, positions.end(), 100);
        // if (currentIterator == positions.begin())
        // {
        //
        // }
        // else
        // {
        //     currentIterator = std::prev(currentIterator, 1);
        //
        //     if (currentIterator == lastIterator)
        //     {
        //         std::cout << "thats the end\n";
        //     } else {
        //         std::cout << *currentIterator << "\n";
        //     }
        //
        // }







        //
        //






        // given: 3
        // int current = 0; // 2
        // while (true)
        // {
        //     // get upper bound of our value -> strictly larger
        //     auto it = std::upper_bound(positions.begin(), positions.end(), positions[current]);
        //
        //     // from there on go right until we find an element that is suitable
        //
        //
        //     if (positions[current] > positions[current-1] + d)
        //     {
        //         std::cout << "not possible\n";
        //         break;
        //     }
        //     else
        //     {
        //
        //     }
        // }






















































        // int current = 0;
        // int number = 0;
        //
        //
        //
        // auto it = positions.begin();
        // int lastValue = -1000000;
        // while (true)
        // {
        //     // std::cout << current << " -> ";
        //     it = std::upper_bound(it, positions.end(), current);
        //     it = std::prev(it, 1);
        //     // std::cout << *it << "\n";
        //
        //
        //     // std::cout << lastValue << " == " << *it << "\n";
        //
        //     if (lastValue == *it || current >= l)
        //     {
        //         break;
        //     }
        //     else
        //     {
        //         lastValue = *it;
        //         current = *it + 2*d;
        //         ++number;
        //     }
        // }
        //
        // if (current < l)
        //     std::cout << "impossible\n";
        // else
        //     std::cout << number << '\n';
        //

    }

    return 0;
}
