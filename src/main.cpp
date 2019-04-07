#include "Solver.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>

std::vector<int> getInput();
std::vector<int> getRowInput();
std::string inputWhileError();

std::vector<int> debugInput = {
    0,1,4,0,5,0,0,0,3,
    6,0,0,0,0,9,4,2,0,
    8,0,0,1,0,0,0,9,0,
    0,0,5,0,9,0,0,4,0,
    4,0,0,7,0,8,0,0,2,
    0,7,0,0,2,0,6,0,0,
    0,9,0,0,0,1,0,0,5,
    0,2,8,3,0,0,0,0,4,
    5,0,0,0,6,0,7,1,0
};

int main() 
{
    //std::vector<int> nums = getInput();
    std::vector<int> nums = debugInput;
    std::unique_ptr<Solver> solver = std::make_unique<Solver>(nums);

    solver->draw();

	return 0;
}

std::vector<int> getInput()
{
    std::vector<int> nums(81);

    std::cout << "Input one row at a time:" << std::endl;
    std::cout << "(Input 0 for empty cells)" << std::endl;
    for (int i = 0; i < 9; ++i)
    {
        std::vector<int> row = getRowInput();
        std::copy(row.begin(), row.end(), std::back_inserter(nums));
    }
    
    return nums;
}

std::vector<int> getRowInput()
{
    std::vector<int> inputs(9);
    std::string inputStr;

    std::cin >> inputStr;
    while (inputStr.length() != 9)
    {
        std::cout << "error : input again" << std::endl;
        std::cin >> inputStr;
    }

    for (int i = 0; i < 9; ++i)
    {
        int input = static_cast<int>(inputStr.at(i) - '0');
        if (input < 0 || 9 < input)
        {
            // TODO
            input = 0;
        }
        inputs[i] = input;
    }

    return inputs;
}

std::string inputWhileError()
{
    std::string inputStr;


    return inputStr;
}