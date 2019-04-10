#include "Group.h"
#include "BitTools.h"
#include "Cell.h"

#include <cassert>

namespace
{
    void checkPositionMatch(bool* xMatch, bool* yMatch, const std::vector<std::pair<int,int>>& positions)
    {
        *xMatch = (positions[0].first == positions[1].first);
        *yMatch = (positions[0].second == positions[1].second);

        if (positions.size() > 2)
        {
            *xMatch &= (positions[1].first == positions[2].first);
            *yMatch &= (positions[1].second == positions[2].second);
        }
    }
}

Group::Group(int number, std::vector<std::shared_ptr<Cell>> cells) :
    mNumber(number),
    mUnsolvedNumbers({ 1,2,3,4,5,6,7,8,9 }),
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

bool Group::removeCandidatesByFoundNumbers()
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

bool Group::removeCandidatesByPrediction()
{
    bool result = false;

    updateSolvedCells();

    for (int candidate : mUnsolvedNumbers)
    {
        auto cellsWithCandidate = getCellsFromCandidate(candidate);
        int length = cellsWithCandidate.size();

        // その数字が入るマスが1つなら、そこに入れる
        if (length == 1)
        {
            auto cell = cellsWithCandidate.at(0);
            cell->setNumber(candidate);
            result = true;
        }
        // その数字が入るマスが2or3つなら、そこから予測できる可能性がある
        else if (length <= 3)
        {
            predictByPosition(candidate, cellsWithCandidate);
            result = true;
        }
    }

    return result;
}

void Group::predictByPosition(int number, const std::vector<std::shared_ptr<Cell>> & cells) const
{
    assert(cells.size() >= 2);

    bool xMatch, yMatch;
    std::vector<Cell::PII> cellPositions = {};
    for (auto& cell : cells)
    {
        cellPositions.push_back(cell->getPosition());
    }

    // 同じ数字を候補に持つすべてのマスのxかy座標が同じなら、行または列から候補を消せる
    checkPositionMatch(&xMatch, &yMatch, cellPositions);

    if (cellPositions.size() > 2)
    {
        xMatch &= (cellPositions[1].first == cellPositions[2].first);
        yMatch &= (cellPositions[1].second == cellPositions[2].second);
    }

    if (xMatch)
    {
        auto column = cells[0]->getColumn();
        _predictByPosition(number, cells, column);
    }
    if (yMatch)
    {
        auto row = cells[0]->getRow();
        _predictByPosition(number, cells, row);
    }
}

// otherのマスから候補を消す
void Group::_predictByPosition(int number, const std::vector<std::shared_ptr<Cell>>& cells, const std::shared_ptr<Group>& other) const
{
    for (auto& cell : other->mUnsolvedCells)
    {
        // cellsにあるマス（このグループのマス）からは候補を消さない
        if (std::find(cells.begin(), cells.end(), cell) != cells.end())
        {
            continue;
        }

        cell->removeCandidate(number);
    }
}

std::vector<std::shared_ptr<Cell>> Group::getCellsFromCandidate(int candidate) const
{
    unsigned short candidateBit = BitTools::numToBit(candidate);
    std::vector<std::shared_ptr<Cell>> cells = {};

    for (auto& cell : mUnsolvedCells)
    {
        if (cell->getCandidateBit() & candidateBit)
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

