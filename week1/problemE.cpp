#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>

enum Operator
{
    OP_PLUS,
    OP_MINUS,
    OP_TIMES,
    OP_POWEROF
};

Operator findoutOperator(char char2)
{
    switch (char2)
    {
        case 'u': return OP_PLUS; // plus
        case 'n': return OP_MINUS; // minus
        case 'm': return OP_TIMES; // times
        case 't': return OP_POWEROF; // tothepowerof
    }
    return OP_PLUS; // should never happen
}

int solveProblem(const std::string &problem)
{
    int currentlyAt = 0;
    
    // read first number and set as temp result
    while (currentlyAt < problem.length())
    {
        if (!isdigit(problem[currentlyAt]))
            break;
        currentlyAt++;
    }
    std::string numberString (problem.substr(0, currentlyAt));
    int result (std::stoi(numberString));

    // read operator and number and calculate new result
    // allowed operators: plus, minus, times, tothepowerof
    
    while (currentlyAt < problem.length())
    {
        // read operator
        Operator op = findoutOperator(problem[currentlyAt+2]);
        switch (op)
        {
            case OP_PLUS: currentlyAt += 4; break;
            case OP_MINUS: currentlyAt += 5; break;
            case OP_TIMES: currentlyAt += 5; break;
            case OP_POWEROF: currentlyAt += 12; break;
        }
        
        // read number
        int beginNumber = currentlyAt;
        while (currentlyAt < problem.length())
        {
            if (!isdigit(problem[currentlyAt]))
                break;
            currentlyAt++;
        }
        std::string newNumberString (problem.substr(beginNumber, currentlyAt - beginNumber));
        int newNumber (std::stoi(newNumberString)); // TODO maybe outside of loop
            
        // apply operator to number
        switch(op) 
        {
            case OP_PLUS: result += newNumber; break;
            case OP_MINUS: result -= newNumber; break;
            case OP_TIMES: result *= newNumber; break;
            case OP_POWEROF: result = std::pow(result, newNumber); break;        
        }
    }
        
    return result;
}
    
    
int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i=0; i<t; ++i)
    {
        std::cout << "Case #" << i+1 << ": ";
        std::string problem;
        std::cin >> problem;
        std::cout << solveProblem(problem) << '\n';
    }
        
    return 0;
}
