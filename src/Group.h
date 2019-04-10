#pragma once

#include <memory>
#include <vector>

class Cell;

// Block, Row, Columnで共通の部分
class Group
{
public:
    enum  struct GroupType
    {
        BLOCK,
        ROW,
        COLUMN
    };

    Group(int number, std::vector<std::shared_ptr<Cell>> cells);
    virtual ~Group() {};

    void addFoundNumber(int number);
    // 見つかった数字をマスの候補から削除
    /// return: 削除があったかどうか
    bool removeCandidates();
    // 指定した候補を持つマス
    std::vector<std::shared_ptr<Cell>> getCellsFromCandidate(int candidate) const;

    bool isSolved() const;
    virtual GroupType getType() const = 0;

protected:
    static const int LENGTH = 9;

    int mNumber;

    // このグループでまだ見つかっていない数字
    std::vector<int> mUnsolvedNumbers;
    // このグループで新しく見つかった数字
    std::vector<int> mFoundNumbers;
    // すべてのマス
    std::vector<std::shared_ptr<Cell>> mCells;
    // まだ埋まっていないマス
    std::vector<std::shared_ptr<Cell>> mUnsolvedCells;

private:
    // 数字が決まったマスをunsolvedから削除
    void updateSolvedCells();
};