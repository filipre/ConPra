#include <iostream>
#include <vector>
#include <set>
#include <cstddef>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <numeric>

typedef std::vector<int> schedule_t;
typedef std::vector<int> categories_t;
typedef std::vector<int> precedence_t;
typedef std::vector<int> precedenceLevel_t;



void printSchedule(const schedule_t &schedule, int n)
{
    // std::cout << "Schedule: ";
    for (int i=1; i<=n; ++i)
    {
        std::cout << schedule[i] << " ";
    }
    std::cout << "\n";
}

bool isValid (const schedule_t &schedule, int n, int d)
{
    // TODO add other checks as well?
    for (int i=1; i<=n; ++i)
    {
        if (schedule[i] == 0 || schedule[i] > d)
            return false;
    }
    return true;
}

bool isPartiallyValid (const schedule_t &schedule, int n, int m, int d, const categories_t &categories)
{
    // number of workers musn't exceed
    // => aggregate by timeslot and calculate sum
    // TODO we do not check if some values are higher than the deadline...
    std::vector<int> sums (d+1);
    for (int i=1; i<=n; ++i)
    {
        sums[schedule[i]] += categories[i];
    }
    for (int i=1; i<=d; ++i)
    {
        // std::cout << "sums[i]: " << sums[i] << ", m: " << m << "\n";
        if (sums[i] > m) // we require more workers than we have
        {
            return false;
        }
    }

    // TODO check if it is in the right order (maybe we can omit this TODO!)
    return true;
}

void fillCell(const schedule_t currentSolution, int level, std::queue<int> relevantTasks, int n, int m, int d, const precedence_t &precedence, const categories_t &categories, std::vector<schedule_t> &solutions)
{
    if (relevantTasks.empty())
    {
        // we have a valid solution. add it to the global solutions
        // printSchedule(currentSolution, n);
        solutions.push_back(currentSolution);
        return;
    }

    int cell = relevantTasks.front();
    relevantTasks.pop();

    // get min for that cell.
    // std::cout << "cell: " << cell << "\n";
    int startAt;
    if (precedence[cell] == -1)
    {
        startAt = level;
    }
    else
    {
        startAt = std::max(level, currentSolution[precedence[cell]]+1);
    }
    // std::cout << "start at: " << startAt << "\n";
    std::vector<schedule_t> partialSolutions; // add to queue for every one that works
    for (int i=startAt; i<=d; ++i)
    {
        schedule_t potentialSolution (currentSolution);
        potentialSolution[cell] = i;
        bool worked = isPartiallyValid(potentialSolution, n, m, d, categories);
        if (worked)
        {
            partialSolutions.push_back(potentialSolution);
        }
    }

    // for every in queue, start recursion
    for (const auto &s : partialSolutions)
    {
        fillCell(s, level, relevantTasks, n, m, d, precedence, categories, solutions);
    }

    return;
}

void createPartialSolutions(schedule_t currentSolution, int level, int n, int m, int d, const categories_t &categories, const precedence_t &precedence, const precedenceLevel_t &precedenceLevel, std::vector<schedule_t> &solutions)
{
    // get fields which will be filled at current precedenceLevel
    std::queue<int> relevantTasks;
    for (int i=1; i<=n; ++i)
    {
        if (precedenceLevel[i] == level)
        {
            relevantTasks.push(i);
        }
    }

    // currentSolution does not have values at current level yet. fillCell will fill everything and add all to solutions
    fillCell(currentSolution, level, relevantTasks, n, m, d, precedence, categories, solutions);
}

// bool completed(schedule_t currentSolution, int n)
// {
//     for (int i=1; i<=n; ++i)
//     {
//         if (currentSolution[i] <= 0)
//             return false;
//     }
//     return true;
// }

// copy solutions
bool backtrack(schedule_t currentSolution, int level, int n, int m, int d, const categories_t &categories, const precedence_t &precedence, const precedenceLevel_t &precedenceLevel)
{
    // std::cout << "backtrack level: " << level << "\n";
    if (level > d)
    {
        // check if valid
        bool reallyValid = isValid(currentSolution, n, d);
        if (reallyValid)
        {
            printSchedule(currentSolution, n);
            return true;
        }
        else
        {
            return false;
        }
    }

    // create partial solutions for current level
    std::vector<schedule_t> solutions;
    createPartialSolutions(currentSolution, level, n, m, d, categories, precedence, precedenceLevel, solutions);
    // std::cout << "size: " << solutions.size() << "\n";
    for (const auto &s : solutions)
    {
        bool result = backtrack(s, level+1, n, m, d, categories, precedence, precedenceLevel);
        bool result2 = isPartiallyValid(s, n, m, d, categories);
        if (result && result2)
        {
            return true;
        }
    }

    return false;
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

        int n, m, d;
        std::cin >> n; // number of tasks
        std::cin >> m; // number of workers
        std::cin >> d; // deadline

        categories_t categories (n+1);
        precedence_t precedence (n+1);

        for (int i=1; i<=n; ++i)
        {
            int c_i, p_i;
            std::cin >> c_i; // how many workers are needed / category
            categories[i] = c_i;

            std::cin >> p_i; // task that needs to be finished first (no prec has -1)
            precedence[i] = p_i;
        }

        // for (int i=1; i<=n; ++i)
        // {
        //     std::cout << precedence[i] << " ";
        // }
        // std::cout << "\n";

        // calculate precedence level (0 = no precedence, 1 = one before, ...)
        precedenceLevel_t precedenceLevel (n+1);
        for (int i=1; i<=n; ++i)
        {
            int level = 1;
            int currentTask = i;
            while (precedence[currentTask] != -1)
            {
                ++level;
                currentTask = precedence[currentTask];
            }
            precedenceLevel[i] = level;
            // std::cout << "level of " << i << ": " << level << "\n";
        }


        schedule_t currentSolution (n+1);
        bool result = backtrack(currentSolution, 1, n, m, d, categories, precedence, precedenceLevel);
        if (!result)
            std::cout << "impossible\n";

    }

    return 0;
}
