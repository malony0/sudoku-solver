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

    // 数字が見つかったマスをunsolvedから削除
    for (auto itr = mUnsolvedCells.begin(); itr != mUnsolvedCells.end(); itr++)
    {
        auto& cell = *itr;
        if (cell->getNumber() == number)
        {
            mUnsolvedCells.erase(itr);
            return;
        }
    }
}

void Group::removeCandidates()
{
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
}