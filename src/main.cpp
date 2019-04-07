#include "Solver.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

std::vector<int> getInput();
std::vector<int> getRowInput();
std::string inputWhileError();

std::vector<int> debugInput = {
    0,7,0,0,0,1,3,0,0,
    0,3,0,0,0,2,5,0,0,
    0,0,4,6,0,0,0,0,0,
    0,0,2,1,0,0,0,9,0,
    0,9,0,0,0,0,0,1,0,
    0,5,0,0,0,9,7,0,0,
    0,0,0,0,0,6,8,0,0,
    0,0,1,9,0,0,0,2,0,
    0,0,7,4,0,0,0,6,0
};

int main() 
{
    //std::vector<int> nums = getInput();
    std::vector<int> nums = debugInput;
    std::unique_ptr<Solver> solver = std::make_unique<Solver>(nums);

    bool changed;
    while(!solver->isSolved())
    {
        changed = solver->run();

        //内容に更新がなければ解けない問題
        if (!changed)
        {
            std::cout << "Couldn't solve..." << std::endl;
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Solved!" << std::endl;

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