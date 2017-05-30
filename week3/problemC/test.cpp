#include <iostream>

int main()
{
    long a = 0;
    for (long i=0; i<(2200000000); i++)
    {
        ++a;
    }
    std::cout << a << "\n";

    return 0;
}
