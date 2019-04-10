#include "Group.h"
#include "Cell.h"
#include "BitTools.h"

#include <cassert>

Group::Group(int number, std::vector<std::shared_ptr<Cell>> cells):
    mNumber(number),
    mUnsolvedNumbers({1,2,3,4,5,6,7,8,9}),
    mFoundNumbers({}),
    mCells(cells),
    mUnsolvedCells(cells)
{
    assert(cells.size() == LENGTH);
}

void Group::addFoundNumber(int number)
{
    mFoundNumbers.push_back(number);
 
    // 見つかっていない数字からは消しておく
    for (auto itr = mUnsolvedNumbers.begin(); itr != mUnsolvedNumbers.end(); ++itr)
    {
        if (*itr == number)
        {
            mUnsolvedNumbers.erase(itr);
            return;
        }
    }
}

bool Group::removeCandidates()
{
    // 候補を消す必要がないマスを外しておく
    updateSolvedCells();

    // 候補の更新がない場合は何もしない
    if (mFoundNumbers.empty())
    {
        return false;
    }

    // 更新されるのでコピーしておく
    auto foundNumbers = mFoundNumbers;
    mFoundNumbers.clear();
    mFoundNumbers.shrink_to_fit();

    // 出現した数字を候補から消す
    for (int foundNumber : foundNumbers)
    {
        for (auto& cell : mUnsolvedCells)
        {
            cell->removeCandidate(foundNumber);
        }
    }

    return true;
}

std::vector<std::shared_ptr<Cell>> Group::getCellsFromCandidate(int candidate) const
{
    unsigned short candidateBit = BitTools::numToBit(candidate);
    std::vector<std::shared_ptr<Cell>> cells = {};

    for (auto& cell : mUnsolvedCells)
    {
        if (cell->getCandidateBit & candidateBit)
        {
            cells.push_back(cell);
        }
    }

    return cells;
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