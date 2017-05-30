#include <iostream>

int main()
{
    std::cout << "1\n";
    std::cout << "1000 999\n";
    for (int i=1; i<1000; ++i)
    {
        std::cout << i << " " << i+1 << " " << 1000 << "\n";
    }

    return 0;
}
