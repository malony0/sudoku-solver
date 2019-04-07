#include "Row.h"
#include "Cell.h"

#include <string>
#include <iostream>

Row::Row(int number, std::vector<std::shared_ptr<Cell>> cells) : Group(number, cells)
{
}

Row::~Row()
{
}

Group::GroupType Row::getType() const
{
    return Group::GroupType::ROW;
}

void Row::draw() const
{
    std::string str = "|";

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int cellId = i * 3 + j;
            int n = mCells[cellId]->getNumber();

            if (n == 0)
            {
                //‰ð‚¯‚Ä‚¢‚È‚¢‚È‚ç‹ó”’
                str.append(" ");
            }
            else
            {
                str.append(std::to_string(n));
            }
        }
        str.append("|");
    }

    std::cout << str << std::endl;
}
