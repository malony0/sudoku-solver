#pragma once

#include <memory>
#include <vector>

class Cell;

// Block, Row, Columnで共通の部分
class Group
{
public:
    enum  struct GroupType
    {
        BLOCK,
        ROW,
        COLUMN
    };

    Group(int number, std::vector<std::shared_ptr<Cell>> cells);
    virtual ~Group() {};

    virtual GroupType getType() const = 0;

protected:
    static const int LENGTH = 9;

    int mNumber;
    std::vector<std::shared_ptr<Cell>> mCells;
};