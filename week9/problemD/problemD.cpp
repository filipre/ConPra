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

// solution taken from https://icpc.tum.de/content/contests/history/2017/gcpc_files/gcpc2017_solutions.pdf

struct Tournament
{
    int64_t start;
    int64_t end;
    int64_t prize;
};

// return best solution at time t
int64_t s(int64_t t, std::map<int64_t, std::vector<Tournament>> &tournaments, std::vector<int64_t> &dp)
{
    if (dp[t] > 0)
    {
        return dp[t];
    }

    if (t == 0)
    {
        return 0;
    }

    // get all tournaments that end on time t
    int64_t currentMax = s(t - 1, tournaments, dp);
    dp[t] = currentMax;

    // either participate in a tournament
    for (auto tournament : tournaments[t])
    {
        // std::cout << tournament.start << " - " << tournament.end << " : " << tournament.prize << "\n";
        currentMax = std::max(currentMax, tournament.prize + s(tournament.start - 1, tournaments, dp));
        dp[t] = currentMax;
    }

    return currentMax;
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

        int64_t n;
        std::cin >> n; // amount of tournaments

        std::map<int64_t, std::vector<Tournament>> tournaments;

        for (int64_t i=1; i<=n; ++i)
        {
            int64_t a, b, p;
            std::cin >> a; // start
            std::cin >> b; // end
            std::cin >> p; // prize money
            tournaments[b].push_back({a, b, p});
        }

        int64_t maxTime = tournaments.rbegin()->first;
        // std::cout << maxTime << "\n";

        std::vector<int64_t> dp (maxTime+1, 0);

        int64_t solution = s(maxTime, tournaments, dp);
        std::cout << solution << "\n";
    }

    return 0;
}
