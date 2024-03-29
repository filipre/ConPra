#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>

typedef std::vector<std::vector<bool>> chessboard_t;
typedef std::priority_queue<int, std::vector<int>, std::greater<int> > pqRows_t;

void printChessboard(const chessboard_t &solution, int n)
{
    for (int i=1; i<=n; ++i)
    {
        for (int j=1; j<=n; ++j)
        {
            if (solution[i][j])
                std::cout << 'x';
            else
                std::cout << '.';
        }
        std::cout << "\n";
    }
}

bool checkPartialSolution(const chessboard_t &solution, int i, int j, int n)
{
    // // vertical up
    // for (int k=1; k<i; ++k)
    //     if (solution[k][j])
    //         return false;
    //
    // // diagonal left-up
    // for (int k=1; k<=std::min(i-1, j-1); ++k)
    //     if (solution[i-k][j-k])
    //         return false;
    //
    // // diagnoal right-up
    // for (int k=1; k<=std::min(i-1, n-j); ++k)
    //     if (solution[i-k][j+k])
    //         return false;

    // horizontal left
    // for (int k=1; k<j; ++k)
    //     if (solution[i][k])
    //         return false;

    // // horizonal right
    // for (int k=j+1; k<=n; ++k)
    //     if (solution[i][k])
    //         return false;

    // // vertical up
    for (int k=1; k<i; ++k)
        if (solution[k][j])
            return false;

    // // vertical down
    for (int k=i+1; k<=n; ++k)
        if (solution[k][j])
            return false;

    // diagonal left-up
    for (int k=1; k<=std::min(i-1, j-1); ++k)
        if (solution[i-k][j-k])
            return false;

    // diagnoal right-up
    for (int k=1; k<=std::min(i-1, n-j); ++k)
        if (solution[i-k][j+k])
            return false;

    // diagnoal right-down
    for (int k=1; k<=std::min(n-i, j-1); ++k)
        if (solution[i+k][j-k])
            return false;

    // diagnoal left-down
    for (int k=1; k<=std::min(n-i, n-j); ++k)
        if (solution[i+k][j+k])
            return false;




    return true;
}


bool checkWholeChessboard(chessboard_t board, int n)
{
    for (int row=1; row<=n; ++row)
    {
        // check that there is at most one queen
        int queens = 0;
        for (int column=1; column<=n; ++column)
        {
            if (board[row][column])
            {
                bool res = checkPartialSolution(board, row, column, n);
                if (!res)
                {
                    return false;
                }
                ++queens;
            }
        }
        if (queens > 1)
        {
            return false;
        }
    }

    return true;
}

// bool checkAtTheEnd(chessboard_t board, int n)
// {
//     bool check1 = checkWholeChessboard(board, n);
//     if (!check1)
//         return false;
//
//     int sum = 0;
//     for (int i=1; i<=n; ++i)
//     {
//         for (int j=1; j<=n; ++j)
//         {
//             if (board[i][j])
//                 ++sum;
//         }
//     }
//
//     if (sum != n)
//         return false;
//
//     return true;
// }

// assume that in our row no other queen is placed
void findSolutionsForRow(const chessboard_t &currentSolution, int row, int n, std::vector<chessboard_t> &allSolutions)
{
    for (int column=1; column<=n; ++column)
    {
        chessboard_t possibleSolution (currentSolution);
        possibleSolution[row][column] = true;
        bool works = checkPartialSolution(possibleSolution, row, column, n);
        if (works)
        {
            allSolutions.push_back(possibleSolution);
        }
    }
}

bool backtrack(const chessboard_t &currentSolution, int n, pqRows_t pqRows)
{
    // we were able to place a queen in every row
    if (pqRows.empty())
    {
        printChessboard(currentSolution, n);
        return true;
    }

    int nextRow = pqRows.top();
    pqRows.pop();

    std::vector<chessboard_t> nextSolutions;
    findSolutionsForRow(currentSolution, nextRow, n, nextSolutions);

    for (const auto &nextSolution : nextSolutions)
    {
        bool result = backtrack(nextSolution, n, pqRows);
        if (result)
        {
            return true;
        }
    }

    return false;
}

// int countQueens(const chessboard &solution, int n)
// {
//     int numberOfQueens = 0;
//     for (int i=1; i<=n; ++i)
//         for (int j=1; j<=n; ++j)
//             if (solution[i][j])
//                 ++numberOfQueens;
//
//     return numberOfQueens;
// }
//
// bool completed(int queens, int n)
// {
//     return queens == n;
// }
//
// // TODO check in more detail
// bool isValid(chessboard &solution, int n)
// {
//     // iterate over all elements
//     for (int i=1; i<=n; ++i)
//     {
//         for (int j=1; j<=n; ++j)
//         {
//             // queen in cell [i][j]
//             if (solution[i][j])
//             {
//
//                 // horizontal left
//                 for (int k=1; k<j; ++k)
//                     if (solution[i][k])
//                         return false;
//
//                 // horizonal right
//                 for (int k=j+1; k<=n; ++k)
//                     if (solution[i][k])
//                         return false;
//
//                 // vertical up
//                 for (int k=1; k<i; ++k)
//                     if (solution[k][j])
//                         return false;
//
//                 // vertical down
//                 for (int k=i+1; k<=n; ++k)
//                     if (solution[k][j])
//                         return false;
//
//                 // diagonal left-up
//                 for (int k=1; k<=std::min(i-1, j-1); ++k)
//                     if (solution[i-k][j-k])
//                         return false;
//                 //
//                 // // diagnoal right-up
//                 for (int k=1; k<=std::min(i-1, n-j); ++k)
//                     if (solution[i-k][j+k])
//                         return false;
//                 //
//                 // // diagnoal right-down
//                 // for (int k=1; k<=std::min(n-i, j-1); ++k)
//                 //     if (solution[i+k][j+k])
//                 //         return false;
//                 //
//                 // // diagnoal left-down
//                 // for (int k=1; k<=std::min(n-i, n-j); ++k)
//                 //     if (solution[i+k][j-k])
//                 //         return false;
//             }
//         }
//     }
//
//     return true;
// }
//
// void generateNextSolutions(const chessboard &solution, int n, std::vector<chessboard> &solutions)
// {
//     for (int i=1; i<=n; ++i)
//     {
//         for (int j=1; j<=n; ++j)
//         {
//             if (!solution[i][j])    // empty
//             {
//                 chessboard newSolution = solution; // TODO?
//                 newSolution[i][j] = true;
//                 if (isValid(newSolution, n))
//                     solutions.push_back(newSolution);
//             }
//         }
//     }
// }
//
// bool backtrack(chessboard &solution, int queens, int n)
// {
//     if (!isValid(solution, n))
//         return false;
//
//     if (completed(queens, n))
//     {
//         printChessboard(solution, n);
//         return true;
//     }
//
//
//     std::vector<chessboard> nextSolutions;
//     generateNextSolutions(solution, n, nextSolutions);
//     for (auto &nextSolution : nextSolutions)
//     {
//         if (backtrack(nextSolution, queens+1, n))
//             return true;
//     }
//
//     return false;
// }

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ":";
        std::cout << "\n";

        int n;
        std::cin >> n;

        chessboard_t solution (n+1, std::vector<bool>(n+1));

        std::vector<bool> rowsToConsider (n+1);
        for (int k=1; k<=n; ++k)
        {
            rowsToConsider[k] = true;
        }

        for (int i=1; i<=n; ++i)
        {
            for (int j=1; j<=n; ++j)
            {
                char queen;
                std::cin >> queen;
                if (queen == 'x')
                {
                    solution[i][j] = true;
                    rowsToConsider[i] = false;
                }
            }
        }

        bool initWorks = checkWholeChessboard(solution, n);
        if (!initWorks)
        {
            std::cout << "impossible\n";
            continue;
        }

        // create pq for rows
        pqRows_t pqRows;
        for (int i=1; i<=n; ++i)
        {
            if (rowsToConsider[i])
            {
                pqRows.push(i);
            }
        }









        bool works = backtrack(solution, n, pqRows);
        if (!works)
        {
            std::cout << "impossible\n";
        }
        // std::cout << "works: " << works << "\n";



        // std::vector<chessboard_t> solutions;
        // findSolutionsForRow(solution, 2, n, solutions);
        // std::cout << solutions.size() << "\n";
        // chessboard_t s0 = solutions[0];
        // std::vector<chessboard_t> solutions2;
        // findSolutionsForRow(s0, 3, n, solutions2);
        // printChessboard(solutions2[0], n);










































        // int numberOfQueens = countQueens(solution, n);

        // bool possible = backtrack(solution, numberOfQueens, n);
        // if (!possible)
        //     std::cout << "impossible\n";

        // std::cout << "valid: " << isValid(solution, n) << "\n";
        //
        // std::vector<chessboard> nextSolutions;
        // generateNextSolutions(solution, n, nextSolutions);
        //
        // for (const auto &s : nextSolutions)
        // {
        //     std::cout << "possible solution: \n";
        //     for (int i=1; i<=n; ++i)
        //     {
        //         for (int j=1; j<=n; ++j)
        //         {
        //             std::cout << s[i][j] << " ";
        //         }
        //         std::cout << "\n";
        //     }
        // }


    }

    return 0;
}
