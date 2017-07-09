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

// Solution taken from https://code.google.com/codejam/contest/3024486/dashboard#s=a&a=1

// lea starts shooting first
// then they take turns shooting at the monsters

// # We are at monster i which has rem_hp HP left and Diana has
// # extra_shots shots saved up, how much gold can she get?
// function rec(i, rem_hp, extra_shots)
//   # Base case: all monsters have been killed.
//   if (rem_hp <= 0 && i + 1 == N) return 0
//
//   # Monster i is dead, move on to the next one.
//   if (rem_hp <= 0) return rec(i + 1, H[i + 1], extra_shots)
//
//   # Memoization.
//   if is_set(memo[i][rem_hp][extra_shots])
//     return memo[i][rem_hp][extra_shots]
//
//   # The tower shoots next. Diana saves up another shot.
//   ret = rec(i, rem_hp - Q, extra_shots + 1)
//
//   # Diana shoots next, using one of the saved up shots.
//   # If the shot kills the current monster, she gets its gold.
//   if (extra_shots > 0)
//     gold = (rem_hp <= P) ? G[i] : 0
//     ret = max(ret, gold + rec(i, rem_hp - P, extra_shots - 1))
//
//   return memo[i][rem_hp][extra_shots] = ret
//
// # Since Diana plays first, she has one extra shot initially.
// print rec(0, H[0], 1)


struct Henchman
{
    int64_t health;
    int64_t gold;
};

typedef std::map<int64_t, std::map<int64_t, std::map<int64_t, int64_t>>> memo_t;

// monster i has always lowest hp.
int64_t f (int64_t i, int64_t hp, int64_t shots, int64_t n, int64_t m, int64_t k, std::vector<Henchman> &henchmen, memo_t &memo)
{
    // all monsters don't have hp left and we covered all monsters
    if (hp <= 0 && i+1 == n)
    {
        return 0; // there is no more gold to get
    }

    // dead monster -> attack the next weakest one
    if (hp <= 0)
    {
        return f(i+1, henchmen[i+1].health, shots, n, m, k, henchmen, memo);
    }

    // memoization, n x hp_max x hp_max
    if (memo[i][hp].find(shots) != memo[i][hp].end())
    {
        return memo[i][hp][shots];
    }

    // tower shoots -> lea saves shot
    // TODO!!!! adapt this algorithm to work with our problem
    int64_t result = f(i, hp - k, shots + 1, n, m, k, henchmen, memo);

    // lea shoots now. check if shot kills the monster and gather gold
    if (shots > 0)
    {
        int64_t g = 0;
        if (hp <= m)
            g = henchmen[i].gold;

        result = std::max(result, g + f(i, hp - m, shots - 1, n, m, k, henchmen, memo));
    }

    memo[i][hp][shots] = result;
    return memo[i][hp][shots];

}


int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        std::cout << "\n";

        int64_t n, m, k;
        std::cin >> n; // n attacking henchman
        std::cin >> m; // lea can shoot at any henchman or not shoot at all, m damage
        std::cin >> k; // tower shoots lowest one, k damage

        std::vector<Henchman> henchmen;
        for (int64_t i=1; i<=n; ++i)
        {
            int64_t h_i, g_i;
            std::cin >> h_i; // henchman i has health h_i
            std::cin >> g_i; // it yields g_i gold if killed by lea
            henchmen.push_back({ h_i, g_i });
        }

        std::sort(henchmen.begin(), henchmen.end(), [](const Henchman &lhs, const Henchman &rhs)
        {
            return lhs.health < rhs.health;
        });

        for (auto henchman : henchmen)
        {
            std::cout << henchman.health << " ";
        }
        std::cout << "\n";

        memo_t memo;

        int64_t result = f(0, henchmen[0].health, 1, n, m, k, henchmen, memo);
        std::cout << result << "\n";
    }

    return 0;
}
