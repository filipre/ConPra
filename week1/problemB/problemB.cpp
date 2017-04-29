#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    unsigned long long int c(299792458);
    unsigned long long int energy;

    for (int i=0; i<n; ++i)
    {
        unsigned int m;
        std::cin >> m;
        energy = m * c * c;
        std::cout << "Case #" << i+1 << ": " << energy << "\n";
    }

    return 0;
}
