#include "Block.h"

Block::Block(int number, std::vector<std::shared_ptr<Cell>> cells) : Group(number, cells)
{
}

Block::~Block()
{
}

Group::GroupType Block::getType() const
{
    return Group::GroupType::BLOCK;
}
