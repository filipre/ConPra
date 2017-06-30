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

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int m, n;
        std::cin >> m; // bakers
        std::cin >> n; // juries

        std::vector<std::vector<int>> taste (n+1, std::vector<int> (m+1));
        for (int i=1; i<=n; ++i)
        {
            int preference;
            std::cin >> preference;
            while (preference != 0)
            {
                if (preference > 0)
                {
                    taste[i][preference] = 1;
                }
                else
                {
                    taste[i][-preference] = 2;
                }
                std::cin >> preference;
            }
        }

        if (m < n)
            std::cout << "no\n";
        else
            std::cout << "yes\n";

    }

    return 0;
}
