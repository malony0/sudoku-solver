#include "Group.h"
#include "Cell.h"

#include <cassert>

Group::Group(int number, std::vector<std::shared_ptr<Cell>> cells)
{
    assert(cells.size() == LENGTH);

    mNumber = number;
    mCells = cells;
}