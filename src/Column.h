#pragma once
#include "Group.h"

class Column : public Group
{
public:
    Column(int number, std::vector<std::shared_ptr<Cell>> cells);
    ~Column();

    GroupType getType() const override;
};

