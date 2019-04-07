#include "Column.h"

Column::Column(int number, std::vector<std::shared_ptr<Cell>> cells) : Group(number, cells)
{
}

Column::~Column()
{
}

Group::GroupType Column::getType() const
{
    return Group::GroupType::COLUMN;
}
