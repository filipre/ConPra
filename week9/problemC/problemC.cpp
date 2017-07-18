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

// Solution taken from http://www.geeksforgeeks.org/dynamic-programming-set-21-box-stacking-problem/

struct Box
{
    int64_t depth;
    int64_t width;
    int64_t height;
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int64_t h, n;
        std::cin >> h; // height
        std::cin >> n; // number of case types
        // std::cout << "h: " << h << ", n: " << n << "\n";

        std::vector<Box> boxes;
        for (int64_t i=1; i<=n; ++i)
        {
            int64_t x_i, y_i, z_i;
            std::cin >> x_i;
            std::cin >> y_i;
            std::cin >> z_i;

            if (x_i <= y_i)
                boxes.push_back({ x_i, y_i, z_i});
            else
                boxes.push_back({ y_i, x_i, z_i});

            if (x_i <= z_i)
                boxes.push_back({ x_i, z_i, y_i});
            else
                boxes.push_back({ z_i, x_i, y_i});

            if (y_i <= z_i)
                boxes.push_back({ y_i, z_i, x_i});
            else
                boxes.push_back({ z_i, y_i, x_i});
        }

        // sort Boxes according to area
        std::sort(boxes.rbegin(), boxes.rend(), [](const Box &lhs, const Box &rhs)
        {
            return (lhs.depth * lhs.width) < (rhs.depth * rhs.width);
        });
        // for (auto box : boxes)
        // {
        //     std::cout << box.depth << " x " << box.width << " : " << box.height << "\n";
        // }

        // msh(i) = maximum possible Stack Height with box i at top of stack
        // initialize best height array
        std::vector<int64_t> msh (3*n);
        for (int64_t i=0; i<3*n; ++i)
        {
            msh[i] = boxes[i].height;
        }

        // for any box i, consider all possible boxes j before i (since they have a larger area) and check if we could place them below us
        for (int64_t i=1; i<3*n; ++i)
        {
            for (int64_t j=0; j<i; ++j)
            {
                if (boxes[i].depth < boxes[j].depth && boxes[i].width < boxes[j].width && msh[i] < msh[j] + boxes[i].height)
                {
                    msh[i] = msh[j] + boxes[i].height; // update the ith box since we found a better solution
                }
            }
        }

        // for (int i=0; i<3*n; ++i)
        // {
        //     std::cout << msh[i] << " ";
        // }
        // std::cout << "\n";

        auto maxHeight = std::max_element(msh.begin(), msh.end());
        if (*maxHeight >= h)
        {
            std::cout << "yes\n";
        }
        else
        {
            std::cout << "no\n";
        }


    }

    return 0;
}
