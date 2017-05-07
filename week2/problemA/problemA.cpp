#include <iostream>
#include <vector>
#include <queue>

void printBlocked(const std::vector<int> &v, int a)
{
    for (int i=1; i<=a; ++i)
        std::cout << v[i] << " ";
    std::cout << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase <= t; ++testCase)
    {
        int a; // number of notable people
        std::cin >> a;
        int b; // number of family relations
        std::cin >> b;
        int c; // number of marriages
        std::cin >> c;

        // use simple vector as lookup table for money
        std::vector<int> moneyOfPerson;
        moneyOfPerson.resize(a+1); // a is Jakob himself
        for (int i=1; i<=(a-1); ++i)
        {
            std::cin >> moneyOfPerson[i];
        }

        // TODO debug
        // for (int i=1; i<=(a-1); ++i)
        // {
        //     std::cout << moneyOfPerson[i] << " ";
        // }
        // std::cout << '\n';

        // use list representation for graph since we care about all relationships
        // ignore element at position 0 for both lists
        std::vector<std::vector<int>> relationships(a+1);
        std::vector<int> blocked(a+1); // 0 means not blocked

        //printBlocked(blocked, a);

        // family relationships
        for (int i=0; i<b; ++i)
        {
            // d is related to e
            int d;
            std::cin >> d;
            int e;
            std::cin >> e;
            //std::cout << "d: " << d << ", e: " << e << '\n';
            relationships.at(d).push_back(e);
            relationships.at(e).push_back(d);
        }

        // marriages relationships
        for (int i=0; i<c; ++i)
        {
            int f;
            std::cin >> f;
            int g;
            std::cin >> g;
            //std::cout << "f: " << f << ", g: " << g << '\n';
            relationships.at(f).push_back(g);
            relationships.at(g).push_back(f);

            // since these are married, we need to block them directly
            blocked.at(f) = 1;
            blocked.at(g) = 1;
        }

        //printBlocked(blocked, a);

        //let's traverse through the lists starting from a (Jakob).
        std::queue<int> family;
        family.push(a); // start with jakob

        std::vector<int> traversed(a+1);

        while(!family.empty())
        {
            int member = family.front();
            //std::cout << "check member: " << member << '\n';
            family.pop();
            // make member blocked if not already
            if (traversed.at(member) == 0)
            {
                blocked.at(member) = 1; // block it always. don't care if it has been already
                traversed.at(member) = 1; // also mark it as traversed
                for (auto &related : relationships.at(member))
                {
                    if (traversed.at(related) != 1)
                        family.push(related);
                }
            }
            //printBlocked(blocked, a);
        }

        //std::cout << "Result: ";
        //printBlocked(blocked, a);

        // last but not least get the max of those who are not blocked
        int result = -1; // "impossible"
        for (int i=1; i<a; ++i)
        {
            if (blocked[i] == 1)
                continue;
            if (moneyOfPerson[i] > result)
                result = moneyOfPerson[i];
        }
        if (result == -1)
            std::cout << "Case #" << testCase << ": impossible\n";
        else
            std::cout << "Case #" << testCase << ": " << result << '\n';

    }

    return 0;
}
