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

    for (int i = 0; i < 9; ++i)
    {
        int n = mCells[i]->getNumber();

        if (n == 0)
        {
            //�����Ă��Ȃ��Ȃ��
            str.append(" ");
        }
        else
        {
            str.append(std::to_string(n));
        }

        // �Ԃɋ󔒂��_������
        if ((i + 1) % 3 == 0)
        {
            str.append("|");
        }
        else
        {
            str.append(" ");
        }
        
    }

    std::cout << str << std::endl;
}
