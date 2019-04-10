#pragma once
#include <cassert> 

class BitTools
{
public:
    static int bitToNum(unsigned short bit)
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

    static unsigned short numToBit(int num)
    {
        assert(num > 0 && num < 10 && "num2bit out of range");

        return 0b1 << (num - 1);
    }


private:
    BitTools() {};
    BitTools(const BitTools& other) {};
    BitTools& operator =(const BitTools& other) {};
};
