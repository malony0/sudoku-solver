#pragma once
#include "Group.h"

class Block : public Group
{
public:
    Block(int number, std::vector<std::shared_ptr<Cell>> cells);
    ~Block();

    GroupType getType() const override;
};

