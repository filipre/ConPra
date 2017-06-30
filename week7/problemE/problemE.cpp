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

/*
I think the authors were not that creative this time. I like the setting though :)
Solution:
https://www.topcoder.com/community/data-science/data-science-tutorials/greedy-is-good/

"If we always give the highest possible score to the combination that has the most occurrences in the group, we’ll obtain in the end the highest possible score for the entire group."
*/

double calcAvgHomologyScore(std::vector<int> &f, std::vector<int> &s)
{
    double sum = 0;
    for (int i=0; i<10; ++i)
    {
         sum += (f[i] * s[i]);
    }
    return sum; // divide by N * (N-1) / 2
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

        int n, m;
        std::cin >> n; // number of human sequences
        std::cin >> m; // number of dolphin sequences

        std::vector<std::string> humanSequences;
        for (int i=1; i<=n; ++i)
        {
            std::string sequence;
            std::cin >> sequence;
            humanSequences.push_back(sequence);
        }

        std::vector<std::string> dolphinSequences;
        for (int i=1; i<=m; ++i)
        {
            std::string sequence;
            std::cin >> sequence;
            dolphinSequences.push_back(sequence);
        }

        // Calculate frequencies
        // representation: 0: AA, 1: AC, 2: AT, 3: AG, 4: CC, ..., 9: GG
        std::vector<int> freq (10);
        for (int i=0; i<10; ++i)
        {
            freq[i] = 0;
        }



        std::vector<std::vector<int> > freq0 (200, std::vector<int> (200));
        for (std::string &humanSequence : humanSequences)
        {
            for (std::string &dolphinSequence : dolphinSequences)
            {
                for (int i=0; i<humanSequence.length(); ++i)
                {
                    ++freq0[humanSequence[i]][dolphinSequence[i]];

                    // if (humanSequence[i] == 'A' && dolphinSequence[i] == 'A')
                    //     ++freq[0];
                    // else if ((humanSequence[i] == 'A' && dolphinSequence[i] == 'C') || (humanSequence[i] == 'C' && dolphinSequence[i] == 'A'))
                    //     ++freq[4];
                    // else if ((humanSequence[i] == 'A' && dolphinSequence[i] == 'T') || (humanSequence[i] == 'T' && dolphinSequence[i] == 'A'))
                    //     ++freq[5];
                    // else if ((humanSequence[i] == 'A' && dolphinSequence[i] == 'G') || (humanSequence[i] == 'G' && dolphinSequence[i] == 'A'))
                    //     ++freq[6];
                    //
                    // else if ((humanSequence[i] == 'C' && dolphinSequence[i] == 'C'))
                    //     ++freq[1];
                    // else if ((humanSequence[i] == 'C' && dolphinSequence[i] == 'T') || (humanSequence[i] == 'T' && dolphinSequence[i] == 'C'))
                    //     ++freq[7];
                    // else if ((humanSequence[i] == 'C' && dolphinSequence[i] == 'G') || (humanSequence[i] == 'G' && dolphinSequence[i] == 'C'))
                    //     ++freq[8];
                    //
                    // else if ((humanSequence[i] == 'T' && dolphinSequence[i] == 'T'))
                    //     ++freq[2];
                    // else if ((humanSequence[i] == 'T' && dolphinSequence[i] == 'G') || (humanSequence[i] == 'G' && dolphinSequence[i] == 'T'))
                    //     ++freq[9];
                    //
                    // else if ((humanSequence[i] == 'G' && dolphinSequence[i] == 'G'))
                    //     ++freq[3];
                    // else
                    //     std::cout << "should never happen";
                }
            }
        }
        // for (int i=0; i<200; ++i)
        // {
        //     for (int j=0; j<200; ++j)
        //     {
        //         std::cout << freq0[i][j] << " ";
        //     }
        // }
        // std::cout << "\n";

        freq[0] = freq0['A']['A'];
        freq[1] = freq0['C']['C'];
        freq[2] = freq0['T']['T'];
        freq[3] = freq0['G']['G'];
        freq[4] = freq0['A']['C'] + freq0['C']['A'];
        freq[5] = freq0['A']['T'] + freq0['T']['A'];
        freq[6] = freq0['A']['G'] + freq0['G']['A'];
        freq[7] = freq0['C']['T'] + freq0['T']['C'];
        freq[8] = freq0['C']['G'] + freq0['G']['C'];
        freq[9] = freq0['T']['G'] + freq0['G']['T'];

        // for (int i=0; i<10; ++i)
        // {
        //     std::cout << freq[i] << " ";
        // }
        // std::cout << "\n";

        std::sort(std::next(freq.begin(), 4), freq.end(), [](const int a, const int b) {return a > b; });
        // for (int i=0; i<10; ++i)
        // {
        //     std::cout << freq[i] << " ";
        // }
        // std::cout << "\n";

        /*
        Best = -Infinity
        For S [1] = 1 to 10
              For S [2] = 1 to 10
                    For S [3] = 1 to 10
                          For S [4] = 1 to 10
                                If  (S [1] + S [2] + S [3] + S [4]) mod 2 = 0
                                     S [5] = S[6] = 10
                                     S [7] = 10 - (S [1] + S [2] + S [3] + S[4]) / 2
                                     S [8] = S [9] = S [10] = -10
                                     // in Best we save the greatest average homology score obtained so far.
                                     Best = max (Best , score (F,S))
                               Endif
                         Endfor
                   Endfor
              Endfor
        Endfor
        Return Best
        */

        // A C T G
        double best = -1000000.0;
        // std::vector<int> bestSolution (10);
        std::vector<int> s (10);
        for (int i=1; i<=10; ++i)
        {
            for (int j=1; j<=10; ++j)
            {
                for (int k=1; k<=10; ++k)
                {
                    for (int l=1; l<=10; ++l)
                    {
                        if (((i + j + k + l) % 2) == 0)
                        {
                            s[0] = i; //AA
                            s[1] = j; //CC
                            s[2] = k; //TT
                            s[3] = l; //GG

                            s[4] = 10;
                            s[5] = 10;
                            s[6] = 10 - ((s[0] + s[1] + s[2] + s[3]) / 2);
                            s[7] = -10;
                            s[8] = -10;
                            s[9] = -10;

                            // std::cout << calcAvgHomologyScore(freq, s) << " ";
                            double homologyScore = calcAvgHomologyScore(freq, s);
                            // std::cout << homologyScore << "\n";
                            if (homologyScore > best)
                            {
                                best = homologyScore;
                                // for (int i=0; i<10; ++i)
                                // {
                                //     bestSolution[i] = s[i];
                                // }
                            }
                        }
                    }
                }
            }
        }
        // std::cout << "\n";

        std::cout << best << "\n";
        // for (int i=0; i<10; ++i)
        // {
        //     std::cout << bestSolution[i] << " ";
        // }
        // std::cout << "\n";


    }

    return 0;
}
