#pragma once

#include "Group.h"

class Row : public Group
{
public:
    Row(int number, std::vector<std::shared_ptr<Cell>> cells);
    ~Row();

    GroupType getType() const override;
    void draw() const;
};

