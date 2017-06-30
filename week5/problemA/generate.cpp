#include <iostream>

int main()
{
    std::cout << "1\n";
    std::cout << "500 499\n";
    for(int i=1; i<500; ++i)
    {
        std::cout << i << " " << i+1 << " 5000\n";
    }

    return 0;
}
