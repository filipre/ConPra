#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

typedef std::array<int, 5> chessTeam;

bool compare(const chessTeam &team1, const chessTeam &team2)
{
    if(team1[0] != team2[0])
    {
        return team1[0] > team2[0];
    }
    if(team1[1] != team2[1])
    {
        return team1[1] > team2[1];
    }
    if(team1[2] != team2[2])
    {
        return team1[2] > team2[2];
    }
    if(team1[3] != team2[3])
    {
        return team1[3] > team2[3];
    }
    if(team1[4] != team2[4])
    {
        return team1[4] > team2[4];
    }
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    std::vector<chessTeam> teams;
    for (int i=0; i<t; ++i)
    {
        std::cout << "Case #" << i+1 << ":\n";

        int n;
        std::cin >> n;

        // get all n chess teams with 5 players each
        teams.resize(n);
        for (int j=0; j<n; ++j)
        {
            for (int k=0; k<5; ++k)
                std::cin >> teams[j][k];
            std::sort(teams[j].rbegin(), teams[j].rend());
        }

        // lets sort that vector
        std::sort(teams.begin(), teams.end(), compare);

        // print result
        for (int j=0; j<n; ++j)
        {
            std::cout << teams[j][0] << " " << teams[j][1] << " " << teams[j][2] << " " << teams[j][3] << " " << teams[j][4] << "\n";
        }

        teams.clear();
    }

    return 0;
}
