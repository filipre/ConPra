#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <string>

typedef std::vector<std::vector<char>> crossword_t;

typedef std::vector<std::vector<bool>> crosswordField_t;
// typedef std::vector<std::vector<bool>> completed_t;

struct Field {
    int x;
    int y;
    char direction;
    int length;
};
auto cmpFields = [](Field left, Field right)
{
    return (left.length < right.length);
};
typedef std::priority_queue<Field, std::vector<Field>, decltype(cmpFields)> fields_t;

typedef std::map<int, std::vector<std::string>> allowedWords_t;


// direction: 'H', 'V'
bool insertWord(const crossword_t &crossword, const Field &field, const std::string &word, crossword_t &newCrossword)
{
    // we do not check whether thee is already something filled in
    // this does not check if we have the "best" position  i and j
    // also does not check if word to be insered is a word from our allowedwords
    // and we do not check if word fits into space at all (we do but we shouldn't)

    if (field.length != word.length())
    {
        std::cout << "should not happen!";
        return false;
    }

    if (field.direction == 'H')
    {
        for (int k=0; k<word.length(); ++k)
        {
            // either there is already a letter in the crossword, then we have to check if they are equal
            if (newCrossword[field.y][field.x+k] != '+')
            {
                if (word[k] != newCrossword[field.y][field.x+k])
                {
                    return false;
                }
            }
            // or there is some emptz space (0) where we have to put our word inside it
            else
            {
                newCrossword[field.y][field.x+k] = word[k];
            }
        }
    }
    else
    {
        for (int k=0; k<word.length(); ++k)
        {
            // either there is already a letter in the crossword, then we have to check if they are equal
            if (newCrossword[field.y+k][field.x] != '+')
            {
                if (word[k] != newCrossword[field.y+k][field.x])
                {
                    return false;
                }
            }
            // or there is some emptz space (0) where we have to put our word inside it
            else
            {
                newCrossword[field.y+k][field.x] = word[k];
            }
        }
    }

    return true;
}

void generateNextSolutions(const crossword_t &crossword, int x, int y, const allowedWords_t &allowedWords, const Field &field, std::vector<crossword_t> &nextSolutions)
{
    for (const std::string &word : allowedWords.find(field.length)->second)
    {
        // std::cout << word << "\n";
        crossword_t newCrossword(crossword);
        bool worked = insertWord(crossword, field, word, newCrossword); // this modifies newCrossword
        if (worked)
        {
            nextSolutions.push_back(newCrossword);
        }
    }
}

bool backtrack(const crossword_t &crossword, int x, int y, const allowedWords_t &allowedWords, fields_t fields)
{
    if (fields.empty())
    {
        for (int i=1; i<=y; ++i)
        {
            for (int j=1; j<=x; ++j)
            {
                std::cout << crossword[i][j];
            }
            std::cout << "\n";
        }
        return true; // there is nothing left to fill
    }

    // next field to fill = top of PQ
    // notice that we copy "fields"
    Field field = fields.top();
    // std::cout << "fill out position (" << field.x << ", " << field.y << "): \n";
    fields.pop();

    std::vector<crossword_t> nextSolutions;
    generateNextSolutions(crossword, x, y, allowedWords, field, nextSolutions);

    for (const auto &solution : nextSolutions)
    {
        // TODO should be valid already
        bool result = backtrack(solution, x, y, allowedWords, fields); // fields get copied -> abort condition if empty
        if (result)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    // put your code here
    int t;
    std::cin >> t;

    // TODO
    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        std::cout << "\n";

        int x, y, amount;
        std::cin >> x;
        std::cin >> y;
        std::cin >> amount;

        crosswordField_t crosswordField (y+1, std::vector<bool> (x+1));
        for (int i=1; i<=y; ++i)
        {
            for (int j=1; j<=x; ++j)
            {
                char c;
                std::cin >> c;
                if (c == '_')
                {
                    crosswordField[i][j] = true;
                }
            }
        }

        // for (int i=1; i<=y; ++i)
        // {
        //     for (int j=1; j<=x; ++j)
        //     {
        //         std::cout << crosswordField[i][j];
        //     }
        //     std::cout << "\n";
        // }

        // iterate over field and turn crosswordField into list of jobs
        fields_t fields(cmpFields);
        for (int i=1; i<=y; ++i)
        {
            for (int j=1; j<=x; ++j)
            {
                if (crosswordField[i][j])
                {
                    // horizontal new word iff it has right something (and smaller than x) AND left is nothing
                    if (j < x && crosswordField[i][j+1] && (j <= 1 || !crosswordField[i][j-1]))
                    {
                        int length = 0;
                        for (int k=j; k<=x; ++k)
                        {
                            if (crosswordField[i][k])
                                ++length;
                            else
                                break;
                        }
                        fields.push({ j, i, 'H', length});
                    }
                    // vertical new word iff it has down something (and smaller than y) AND up is nothing

                    if (i < y && crosswordField[i+1][j] && (i <= 1 || !crosswordField[i-1][j]))
                    {
                        int length = 0;
                        for (int k=i; k<=y; ++k)
                        {
                            if (crosswordField[k][j])
                                ++length;
                            else
                                break;
                        }
                        fields.push({ j, i, 'V', length});
                    }
                }
            }
        }

        // std::cout << fields.top().length << "\n";


        allowedWords_t allowedWords;
        //maximum length is 250
        for (int k=1; k<=250; ++k)
        {
            std::vector<std::string> wordsWithLengthK;
            allowedWords.insert(std::pair<int, std::vector<std::string>>(k, wordsWithLengthK));
        }

        for (int k=1; k<=amount; ++k)
        {
            std::string word;
            std::cin >> word;
            allowedWords[word.length()].push_back(word);
            // (allowedWords.find(word.length())->second).push_back(word); // oh god
        }


        crossword_t crossword (y+1, std::vector<char> (x+1));
        for (int i=1; i<=y; ++i)
        {
            for (int j=1; j<=x; ++j)
            {
                crossword[i][j] = '+'; // not part of alphabet
            }
        }

        // std::cout << "--------------------------------\n";
        // for (int i=1; i<=y; ++i)
        // {
        //     for (int j=1; j<=x; ++j)
        //     {
        //         std::cout << crossword[i][j];
        //     }
        //     std::cout << "\n";
        // }
        // std::cout << "--------------------------------\n";



        backtrack(crossword, x, y, allowedWords, fields);
        std::cout << "\n";




















        // // Field field { 1, 2, 'H', 5 };
        // Field field { 2, 1, 'V', 4 };
        // std::vector<crossword_t> solutions;
        // generateNextSolutions(crossword, x, y, allowedWords, field, solutions);
        // for (auto s : solutions)
        // {
        //     std::cout << "next solution\n";
        //     for (int i=1; i<=y; ++i)
        //     {
        //         for (int j=1; j<=x; ++j)
        //         {
        //             std::cout << s[i][j];
        //         }
        //         std::cout << "\n";
        //     }
        // }










        // Field field { 1, 2, 'H', 5 };
        // crossword_t solution1 (solutionNow);
        // bool works;
        // works = insertWord(solutionNow, { 2, 1, 'V', 4 }, "tuna", solution1);
        // std::cout << works << "\n";
        // crossword_t solution2 (solution1);
        // works = insertWord(solution1, { 4, 1, 'V', 2 }, "hi", solution2);
        // std::cout << works << "\n";
        // solutionNow = insertWord(solutionNow, { 5, 2, 'V', 3 }, "can", works);
        // std::cout << works << "\n";
        // solutionNow = insertWord(solutionNow, { 1, 2, 'H', 5 }, "mussc", works);
        // std::cout << works << "\n";

        //
        // std::cout << "--------------------------------\n";
        // for (int i=1; i<=y; ++i)
        // {
        //     for (int j=1; j<=x; ++j)
        //     {
        //         std::cout << solution2[i][j];
        //     }
        //     std::cout << "\n";
        // }
        // std::cout << "--------------------------------\n";


        // std::vector<crossword_t> nextSolutions;

        // generateNextSolutions(solutionNow, x, y, allowedWords, fields.top(), nextSolutions);
        //





    }

    return 0;
}
