#include "gtest/gtest.h"
#include "DancingLinksGrid.h"
#include "Grid.h"

TEST(Node, linkRight)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);


    n0.linkRight(&n1);
    EXPECT_EQ(n0.getRight(), &n1);
    EXPECT_EQ(n0.getLeft(), &n1);
    EXPECT_EQ(n1.getRight(), &n0);
    EXPECT_EQ(n1.getLeft(), &n0);

    n0.getRight()->linkRight(&n2);
    EXPECT_EQ(n0.getRight()->getRight(), &n2);
    EXPECT_EQ(n0.getRight()->getRight()->getRight(), &n0);
    EXPECT_EQ(n2.getLeft(), &n1);
}

TEST(Node, linkBottom)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);

    n0.linkBottom(&n1);
    EXPECT_EQ(n0.getBottom(), &n1);
    EXPECT_EQ(n0.getTop(), &n1);
    EXPECT_EQ(n1.getBottom(), &n0);
    EXPECT_EQ(n1.getTop(), &n0);

    n0.getBottom()->linkBottom(&n2);
    EXPECT_EQ(n0.getBottom()->getBottom(), &n2);
    EXPECT_EQ(n0.getBottom()->getBottom()->getBottom(), &n0);
    EXPECT_EQ(n2.getTop(), &n1);
}

TEST(Node, unlinkTB)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);

    n0.linkBottom(&n1);
    n0.getBottom()->linkBottom(&n2);

    n1.unlinkTB();
    EXPECT_EQ(n0.getBottom(), &n2);
    EXPECT_EQ(n2.getTop(), &n0);

    n2.unlinkTB();
    EXPECT_EQ(n0.getBottom(), &n0);
    EXPECT_EQ(n0.getTop(), &n0);
}

TEST(Node, relinkTB)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);

    n0.linkBottom(&n1);
    n0.getBottom()->linkBottom(&n2);

    n1.unlinkTB();
    n1.relinkTB();
    EXPECT_EQ(n0.getBottom(), &n1);
    EXPECT_EQ(n2.getTop(), &n1);
}

TEST(Node, unlinkLR)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);

    n0.linkRight(&n1);
    n0.getRight()->linkRight(&n2);

    n1.unlinkLR();
    EXPECT_EQ(n0.getRight(), &n2);
    EXPECT_EQ(n2.getLeft(), &n0);

    n2.unlinkLR();
    EXPECT_EQ(n0.getRight(), &n0);
    EXPECT_EQ(n0.getLeft(), &n0);
}

TEST(Node, relinkLR)
{
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);
    Node n2(2, 2, 2);

    n0.linkRight(&n1);
    n0.getRight()->linkRight(&n2);

    n1.unlinkLR();
    n1.relinkLR();
    EXPECT_EQ(n0.getRight(), &n1);
    EXPECT_EQ(n2.getLeft(), &n1);
}

TEST(Node, linkToColumn)
{
    ColumnHeader c;
    Node n0(0, 0, 0);
    Node n1(1, 1, 1);

    n0.linkToColumn(&c);
    EXPECT_EQ(c.getBottom(), &n0);
    EXPECT_EQ(n0.getTop(), &c);
    EXPECT_EQ(c.getSize(), 1);

    n1.linkToColumn(&c);
    EXPECT_EQ(c.getBottom()->getBottom(), &n1);
    EXPECT_EQ(n1.getTop(), &n0);
    EXPECT_EQ(c.getSize(), 2);
}

TEST(DancingLinksGrid, getHeaderIndexes)
{
    DancingLinksGrid dLG(9);
    std::array<int, 4> res;

    dLG.getHeaderIndexes(0, 0, 1, res);
    EXPECT_EQ(0, res[0]);
    EXPECT_EQ(81, res[1]);
    EXPECT_EQ(162, res[2]);
    EXPECT_EQ(243, res[3]);

    dLG.getHeaderIndexes(8, 8, 9, res);
    EXPECT_EQ(80, res[0]);
    EXPECT_EQ(161, res[1]);
    EXPECT_EQ(242, res[2]);
    EXPECT_EQ(323, res[3]);

    dLG.getHeaderIndexes(4, 5, 6, res);
    EXPECT_EQ(41, res[0]);
    EXPECT_EQ(122, res[1]);
    EXPECT_EQ(212, res[2]);
    EXPECT_EQ(284, res[3]);
}

TEST(DancingLinksGrid, constructor)
{
    int sideLen = 9;
    DancingLinksGrid dLG(sideLen);
    Node* curr = dLG.getRoot()->getRight();
    int i = 0;
    do {
        curr = curr->getRight();
        ++i;
        EXPECT_EQ(0, ((ColumnHeader*)curr)->getSize());
    } while (curr != dLG.getRoot());

    EXPECT_EQ(4 * sideLen * sideLen, i);
    EXPECT_EQ(i, dLG.getHeadersSize());


    sideLen = 6;
    int subGridRow = 2;
    int subGridCols = 3;
    DancingLinksGrid dLG2(sideLen, subGridRow, subGridCols);
    curr = dLG2.getRoot()->getRight();
    i = 0;
    do {
        curr = curr->getRight();
        ++i;
        EXPECT_EQ(0, ((ColumnHeader*)curr)->getSize());
    } while (curr != dLG2.getRoot());

    EXPECT_EQ(4 * sideLen * sideLen, i);
    EXPECT_EQ(i, dLG2.getHeadersSize());
}

TEST(DancingLinksGrid, addRow)
{
    int sideLen = 9;
    DancingLinksGrid dLG(sideLen);
    std::array<int, 4> res;

    int i;
    Node* curr;

    dLG.addGridRowNodes(4, 5, 6);
    dLG.getHeaderIndexes(4, 5, 6, res);
    for(int j = 0; j < res.size(); ++j)
    {
        ColumnHeader* header = dLG.getColumnHeader(res[j]);
        EXPECT_EQ(1, header->getSize());

        i = 0;
        curr = (Node*)header;
        while (curr->getBottom() != header)
        {
            ++i;
            curr = curr->getBottom();   
        }
        EXPECT_EQ(1, i);
        EXPECT_EQ(4, curr->getI());
        EXPECT_EQ(5, curr->getJ());
        EXPECT_EQ(6, curr->getVal());
    }

    Node* currNode = curr;
    i = 0;
    do {
        ++i;
        curr = curr->getRight();
    } while(curr != currNode);
    EXPECT_EQ(4, i);
}