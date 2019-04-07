#include "Group.h"
#include "Cell.h"

#include <cassert>

Group::Group(int number, std::vector<std::shared_ptr<Cell>> cells):
    mFoundNumbers({})
{
    assert(cells.size() == LENGTH);

    mNumber = number;
    mCells = cells;
    mUnsolvedCells = cells;
}

void Group::addFoundNumber(int number)
{
    mFoundNumbers.push_back(number);
}

bool Group::removeCandidates()
{
    // 候補を消す必要がないマスを外しておく
    updateSolvedCells();

    // 候補の更新がない場合
    if (mFoundNumbers.empty())
    {
        return false;
    }

    // 更新されるのでコピーしておく
    auto foundNumbers = mFoundNumbers;
    mFoundNumbers.clear();
    mFoundNumbers.shrink_to_fit();

    for (int foundNumber : foundNumbers)
    {
        for (auto& cell : mUnsolvedCells)
        {
            cell->removeCandidate(foundNumber);
        }
    }

    return true;
}

bool Group::isSolved() const
{
    return mUnsolvedCells.empty();
}

void Group::updateSolvedCells()
{
    for (int number : mFoundNumbers)
    {
        for (auto itr = mUnsolvedCells.begin(); itr != mUnsolvedCells.end(); itr++)
        {
            auto& cell = *itr;
            if (cell->getNumber() == number)
            {
                mUnsolvedCells.erase(itr);
                break;
            }
        }
    }
}