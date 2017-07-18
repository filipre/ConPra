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
#include <tuple>

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
    int32_t health;
    int32_t gold;
};

// typedef std::map<std::tuple<int32_t, int32_t, int32_t>, int32_t> memo_t;
typedef std::vector<std::vector<std::vector<int32_t>>> memo_t;

// monster i has always lowest hp.
int32_t f (int32_t i, int32_t hp, int32_t shots, int32_t n, int32_t m, int32_t k, std::vector<Henchman> &henchmen, memo_t &memo)
{
    // avoid negative hp
    if (hp < 0)
    {
        hp = 0;
    }

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

    // if (memo.find(std::make_tuple(i, hp, shots)) != memo.end())
    // {
    //     return memo[std::make_tuple(i, hp, shots)];
    // }
    if (memo[i][hp][shots] > -1)
    {
        return memo[i][hp][shots];
    }

    // tower shoots -> lea saves shot
    int32_t result = f(i, hp - k, shots + 1, n, m, k, henchmen, memo);

    // lea shoots now. check if shot kills the monster and gather gold
    if (shots > 0)
    {
        int32_t g = 0;
        if (hp <= m)
            g = henchmen[i].gold;
        else
            g = 0;

        result = std::max(result, g + f(i, hp - m, shots - 1, n, m, k, henchmen, memo));
    }

    // memo[std::make_tuple(i, hp, shots)] = result;
    memo[i][hp][shots] = result;
    return result;

}


int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    memo_t memo (53, std::vector<std::vector<int32_t>> (103, std::vector<int32_t> (103, -1)));

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int32_t n, m, k;
        std::cin >> n; // n attacking henchman
        std::cin >> m; // lea can shoot at any henchman or not shoot at all, m damage
        std::cin >> k; // tower shoots lowest one, k damage

        std::vector<Henchman> henchmen;
        for (int32_t i=1; i<=n; ++i)
        {
            int32_t h_i, g_i;
            std::cin >> h_i; // henchman i has health h_i
            std::cin >> g_i; // it yields g_i gold if killed by lea
            henchmen.push_back({ h_i, g_i });
        }

        for (int a1=0; a1<53; ++a1)
        {
            for (int a2=0; a2<103; ++a2)
            {
                for (int a3=0; a3<103; ++a3)
                {
                    memo[a1][a2][a3] = -1;
                }
            }
        }
        int32_t result = f(0, henchmen[0].health, 1, n, m, k, henchmen, memo);
        std::cout << result << "\n";
    }

    return 0;
}
