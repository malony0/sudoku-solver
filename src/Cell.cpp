#include "Cell.h"

#include "Block.h"
#include "Row.h"
#include "Column.h"

Cell::Cell(
    int number,
    PII position
    ):
    mCandidates(0b111111111),
    mNumber(number),
    mPosition(position)
{
    // 初めから数字が埋まっている場合、数字決定処理を行う
    if (isSolved())
    {
        setNumber(number);
    }
}

Cell::~Cell()
{
}

void Cell::setNumber(int number)
{
    mNumber = number;
    mCandidates = 0b1 << (mNumber - 1);

    //TODO: 更新通知
}

void Cell::setGroup(const std::shared_ptr<Group>& group, Group::GroupType type)
{
    switch (type)
    {
    case Group::GroupType::BLOCK:
        mBlock = group;
        break;
    case Group::GroupType::COLUMN:
        mColumn = group;
        break;
    case Group::GroupType::ROW:
        mRow = group;
        break;
    }
}

void Cell::removeCandidate(int num)
{
    unsigned short candidateBit = 0b1 << (num - 1);
    mCandidates &= !candidateBit;

    if (countCandidate() == 1)
    {
        int number = bitToNum(mCandidates);
        setNumber(number);
    }
}


// 候補中の1の数を数える
int Cell::countCandidate() const
{
    unsigned short c = mCandidates - ((mCandidates >> 1) & 0x0055);
    c = (c & 0x0333) + ((c >> 2) & 0x0033);
    c = (c + (c >> 4)) & 0x0f0f;
    return  c + (c >> 8);
}

bool Cell::isSolved() const
{
    return mNumber != 0;
}

int Cell::getNumber() const
{
    return mNumber;
}

Cell::PII Cell::getPosition() const
{
    return mPosition;
}

int Cell::bitToNum(unsigned short bit) const
{
    for (int number = 1; number <= 9; ++number)
    {
        if ((bit & 0b1) == 1)
        {
            return number;
        }
        bit = bit >> 1;
    }

    return 0;
}