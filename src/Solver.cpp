#include "Solver.h"

#include "Block.h"
#include "Column.h"
#include "Row.h"
#include "Cell.h"

#include <cassert>
#include <string>
#include <iostream>

namespace
{
    const int MAX_X = 9;
    const int MAX_Y = 9;

    const std::string H_BAR = " -----+-----+-----";
}

Solver::Solver(std::vector<int> nums):
    mCells  (std::vector<std::shared_ptr<Cell>>  (MAX_X * MAX_Y)),
    mBlocks (std::vector<std::shared_ptr<Block>> (9)),
    mColumns(std::vector<std::shared_ptr<Column>>(MAX_X)),
    mRows   (std::vector<std::shared_ptr<Row>>   (MAX_Y))
{
    makeCells(nums);
    makeGroups();
}


Solver::~Solver()
{
}

void Solver::draw() const
{
    std::cout << H_BAR << std::endl;
    for (int i = 0; i < 9; i++)
    {
        mRows[i]->draw();
        if ((i+1) % 3 == 0)
        {
            std::cout << H_BAR << std::endl;
        }
    }
}

void Solver::makeCells(const std::vector<int>& nums)
{
    for (int y = 0; y < MAX_Y; ++y)
    {
        for (int x = 0; x < MAX_X; ++x)
        {
            int index = x + y * MAX_X;
            mCells[index] = std::make_shared<Cell>(nums[index], Cell::PII(x, y));
        }
    }
}

void Solver::makeGroups()
{
    for (int i = 0; i < 9; ++i)
    {
        makeGroup(i, Group::GroupType::BLOCK);
        makeGroup(i, Group::GroupType::COLUMN);
        makeGroup(i, Group::GroupType::ROW);
    }
}

void Solver::makeGroup(int groupIndex, Group::GroupType type)
{
    // グループに所属するマス
    std::vector<std::shared_ptr<Cell>> cells;
    std::vector<int> indices = getCellIndices(groupIndex, type);
    for (int index : indices)
    {
        cells.push_back(mCells[index]);
    }

    // 生成されるグループ
    std::shared_ptr<Group> group;
    switch (type)
    {
        case Group::GroupType::BLOCK:
            mBlocks[groupIndex] = std::make_shared<Block>(groupIndex, cells);
            group = mBlocks[groupIndex];
            break;
        case Group::GroupType::COLUMN:
            mColumns[groupIndex] = std::make_shared<Column>(groupIndex, cells);
            group = mColumns[groupIndex];
            break;
        case Group::GroupType::ROW:
            mRows[groupIndex] = std::make_shared<Row>(groupIndex, cells);
            group = mRows[groupIndex];
            break;
    }   
    
    // マスの情報を更新
    for (auto& cell : cells)
    {
        cell->setGroup(group, type);
    }
}

std::vector<int> Solver::getCellIndices(int groupIndex, Group::GroupType type)
{
    int width, height;
    int startIndex;
    std::vector<int> indices(9);

    switch (type)
    {
    case Group::GroupType::BLOCK:
        width = 3;
        height = 3;
        startIndex = (groupIndex % 3) + (groupIndex / 3) * 27;
        break;

    case Group::GroupType::COLUMN:
        width = 1;
        height = 9;
        startIndex = groupIndex;
        break;

    case Group::GroupType::ROW:
        width = 9;
        height = 1;
        startIndex = 9 * groupIndex;
        break;
    default:
        assert(false);
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = startIndex + x + y * width;
            indices[x + y * width] = index;
        }
    }

    return indices;
}
