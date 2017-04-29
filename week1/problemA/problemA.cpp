#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    for (int i=0; i<n; ++i)
    {
        std::string name;
        std::cin >> name;
        std::cout << "Case #" << i+1 << ": Hello " << name << "!\n";
    }

    return 0;
}
