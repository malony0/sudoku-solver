#pragma once

#include "Group.h"

#include <vector>
#include <memory>

class Cell;
class Block;
class Column;
class Row;

class Solver
{
public:
    Solver(std::vector<int> nums);
    ~Solver();

    void run();

    void draw() const;

    bool isSolved() const;

private:
    // 全てのマス
    std::vector<std::shared_ptr<Cell>> mCells;
    // 全てのグループ
    std::vector<std::shared_ptr<Group>> mGroups;

    //種類ごとのグループ
    std::vector<std::shared_ptr<Block>>  mBlocks;
    std::vector<std::shared_ptr<Column>> mColumns;
    std::vector<std::shared_ptr<Row>>    mRows;

    void makeCells(const std::vector<int>& nums);
    void makeGroups();
    void makeGroup(int groupIndex, Group::GroupType type);
    // グループに所属するマスの場所
    std::vector<int> getCellIndices(int groupIndex, Group::GroupType type);
};

