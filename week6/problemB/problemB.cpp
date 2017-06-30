#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <cmath>

bool checkSolution(std::vector<char> tactic)
{
    // check if goalkeeper is only once
    // check that the sum is never 13

    if (tactic[2] == tactic[11] || tactic[3] == tactic[10] || tactic[4] == tactic[9] || tactic[5] == tactic[8] || tactic[6] == tactic[7])
        return false;

    int amountG = 0;
    for (int i=1; i<=11; ++i)
        if (tactic[i] == 'G')
            ++amountG;

    if (amountG != 1)
        return false;

    return true;
}

bool checkConflict(std::vector<char> &tactic, int player)
{
    if (tactic[player] == 'G')
    {
        // check that there is only one goaly
        int amountG = 0;
        for (int i=1; i<=11; ++i)
            if (tactic[i] == 'G')
                ++amountG;

        if (amountG != 1)
            return false;
    }
    else
    {
        // check that player does not contracitct with other player
        if (player != 1)
        {
            int partner = 13 - player;
            if (tactic[partner] != '0' && tactic[partner] == tactic[player])
            {
                return false;
            }
        }
    }
    return true;
}

void getAllPartialSolutionsForGivenTactic(std::vector<char> tactic, int player, const std::vector<std::vector<char>> &positions, std::vector<std::vector<char>> &allSolutions)
{
    for (auto p : positions[player])
    {
        std::vector<char> testTactic (tactic);
        testTactic[player] = p;
        if (checkConflict(testTactic, player))
        {
            allSolutions.push_back(testTactic);
        }
    }
}

void printTactic(std::vector<char> &tactic)
{
    for (int i=1; i<=11; ++i)
    {
        std::cout << tactic[i] << " ";
    }
    std::cout << "\n";
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

        std::vector<std::vector<char>> positions (11+1);

        for (int player=1; player<=11; ++player)
        {
            std::string playerPositions;
            std::cin >> playerPositions;
            for (auto pos : playerPositions)
                positions[player].push_back(pos);
        }

        int numberOfSolutions = 0;
        std::vector<char> tactic (11+1);
        for (int i=1; i<=11; ++i)
        {
            tactic[i] = '0'; // default
        }

        std::vector<std::vector<char>> solutionsForPlayer_2;
        getAllPartialSolutionsForGivenTactic(tactic, 2, positions, solutionsForPlayer_2);
        // std::cout << solutionsForPlayer_2.size() << "\n";
        for (auto solution_2 : solutionsForPlayer_2)
        {
            std::vector<std::vector<char>> solutionsForPlayer_11;
            getAllPartialSolutionsForGivenTactic(solution_2, 11, positions, solutionsForPlayer_11);
            // std::cout << solutionsForPlayer_11.size() << "\n";
            for (auto solution_11 : solutionsForPlayer_11)
            {
                std::vector<std::vector<char>> solutionsForPlayer_3;
                getAllPartialSolutionsForGivenTactic(solution_11, 3, positions, solutionsForPlayer_3);
                // std::cout << solutionsForPlayer_3.size() << "\n";
                for (auto solution_3 : solutionsForPlayer_3)
                {
                    std::vector<std::vector<char>> solutionsForPlayer_10;
                    getAllPartialSolutionsForGivenTactic(solution_3, 10, positions, solutionsForPlayer_10);
                    // std::cout << solutionsForPlayer_10.size() << "\n";
                    for (auto solution_10 : solutionsForPlayer_10)
                    {
                        std::vector<std::vector<char>> solutionsForPlayer_4;
                        getAllPartialSolutionsForGivenTactic(solution_10, 4, positions, solutionsForPlayer_4);
                        // std::cout << solutionsForPlayer_4.size() << "\n";
                        for (auto solution_4 : solutionsForPlayer_4)
                        {
                            std::vector<std::vector<char>> solutionsForPlayer_9;
                            getAllPartialSolutionsForGivenTactic(solution_4, 9, positions, solutionsForPlayer_9);
                            // std::cout << solutionsForPlayer_9.size() << "\n";
                            for (auto solution_9 : solutionsForPlayer_9)
                            {
                                std::vector<std::vector<char>> solutionsForPlayer_5;
                                getAllPartialSolutionsForGivenTactic(solution_9, 5, positions, solutionsForPlayer_5);
                                // std::cout << solutionsForPlayer_5.size() << "\n";
                                for (auto solution_5 : solutionsForPlayer_5)
                                {
                                    std::vector<std::vector<char>> solutionsForPlayer_8;
                                    getAllPartialSolutionsForGivenTactic(solution_5, 8, positions, solutionsForPlayer_8);
                                    // std::cout << solutionsForPlayer_8.size() << "\n";
                                    for (auto solution_8 : solutionsForPlayer_8)
                                    {
                                        std::vector<std::vector<char>> solutionsForPlayer_6;
                                        getAllPartialSolutionsForGivenTactic(solution_8, 6, positions, solutionsForPlayer_6);
                                        // std::cout << solutionsForPlayer_6.size() << "\n";
                                        for (auto solution_6 : solutionsForPlayer_6)
                                        {
                                            std::vector<std::vector<char>> solutionsForPlayer_7;
                                            getAllPartialSolutionsForGivenTactic(solution_6, 7, positions, solutionsForPlayer_7);
                                            // std::cout << solutionsForPlayer_7.size() << "\n";
                                            for (auto solution_7 : solutionsForPlayer_7)
                                            {
                                                std::vector<std::vector<char>> solutionsForPlayer_1;
                                                getAllPartialSolutionsForGivenTactic(solution_7, 1, positions, solutionsForPlayer_1);
                                                // std::cout << solutionsForPlayer_1.size() << "\n";
                                                for (auto solution_1 : solutionsForPlayer_1)
                                                {
                                                    if (checkSolution(solution_1))
                                                    {
                                                        ++numberOfSolutions;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        std::cout << numberOfSolutions << "\n";














        //
        //
        // for (auto p1 : positions[1])
        // {
        //     for (auto p2 : positions[2])
        //     {
        //         for (auto p3 : positions[3])
        //         {
        //             for (auto p4 : positions[4])
        //             {
        //                 for (auto p5 : positions[5])
        //                 {
        //                     for (auto p6 : positions[6])
        //                     {
        //                         for (auto p7 : positions[7])
        //                         {
        //                             for (auto p8 : positions[8])
        //                             {
        //                                 for (auto p9 : positions[9])
        //                                 {
        //                                     for (auto p10 : positions[10])
        //                                     {
        //                                         for (auto p11 : positions[11])
        //                                         {
        //                                             tactic[1] = p1;
        //                                             tactic[2] = p2;
        //                                             tactic[3] = p3;
        //                                             tactic[4] = p4;
        //                                             tactic[5] = p5;
        //                                             tactic[6] = p6;
        //                                             tactic[7] = p7;
        //                                             tactic[8] = p8;
        //                                             tactic[9] = p9;
        //                                             tactic[10] = p10;
        //                                             tactic[11] = p11;
        //
        //                                             if (checkSolution(tactic))
        //                                             {
        //                                                 // std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " " << p6 << " " << p7 << " " << p8 << " " << p9 << " " << p10 << " " << p11 << "\n";
        //                                                 ++numberOfSolutions;
        //                                             }
        //
        //                                         }
        //                                     }
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        //
        // std::cout << numberOfSolutions << "\n";

        // std::vector<char> tactic (11+1);
        // tactic[1] = 'G';
        // tactic[2] = 'M';
        // tactic[3] = 'D';
        // tactic[4] = 'D';
        // tactic[5] = 'D';
        // tactic[6] = 'M';
        // tactic[7] = 'M';
        // tactic[8] = 'D';
        // tactic[9] = 'S';
        // tactic[10] = 'S';
        // tactic[11] = 'S';

        // std::cout << checkSolution(tactic) << "\n";


    }

    return 0;
}
