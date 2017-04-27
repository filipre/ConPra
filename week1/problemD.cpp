#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

typedef std::array<int, 5> chessTeam;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i=0; i<t; ++i)
    {
        std::cout << "Case #" << i+1 << ":\n";

        int n;
        std::cin >> n;

        // get all n chess teams with 5 players each
        std::vector<chessTeam> teams;
        teams.resize(n);
        for (int j=0; j<n; ++j)
        {
            for (int k=0; k<5; ++k)
                std::cin >> teams[j][k];
            std::sort(teams[j].rbegin(), teams[j].rend());
        }

        // lets sort that vector
        std::sort(teams.begin(), teams.end(), [](const chessTeam &team1, const chessTeam &team2)
        {
            for (int k=0; k<5; ++k)
            {
                if (team1[0] != team2[0])
                {
                    return team1[0] > team2[0];
                }
            }
            return true; // all are equal so it does not matter
        });

        // print result
        for (int j=0; j<n; ++j)
        {
            std::cout << teams[j][0] << " " << teams[j][1] << " " << teams[j][2] << " " << teams[j][3] << " " << teams[j][4] << "\n";
        }
    }
    
    return 0;
}
