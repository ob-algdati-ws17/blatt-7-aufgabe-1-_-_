#include "testAvlTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

// insert and search

TEST(AvlTreeTest, One_Node) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
}

TEST(AvlTreeTest, Two_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
}

TEST(AvlTreeTest, Three_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
}

TEST(AvlTreeTest, Four_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    b.insert(1255);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_TRUE(b.search(1255));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 1255, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 1255, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(1255, 215, 123712, 12213));
}

// insert, remove and search

TEST(AvlTreeTest, Root_SymS) {
    AvlTree b;
    b.insert(5);
    b.insert(4);
    b.insert(6);
    EXPECT_TRUE(b.search(5));
    EXPECT_TRUE(b.search(4));
    EXPECT_TRUE(b.search(6));
    b.remove(5);
}

/*
TEST(BinTreeTest, One_Node_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

TEST(AvlTreeTest, Two_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

TEST(AvlTreeTest, Three_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
    b.remove(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}
*/
TEST(AvlTreeTest, Insert_InEmptyTree) {
AVLTree t;
t.insert(5);
EXPECT_TRUE(t.search(5));
}


TEST(AvlTreeTest, Insert_ForLeftRotate) {
AVLTree t;
for (int i = 1; i <= 30; i++) {
t.insert(i);
}
EXPECT_TRUE(t.search(30));
}


TEST(AvlTreeTest, Insert_ForeRightRotate) {
AVLTree t;
for (int i = 30; i > 0; i--) {
t.insert(i);
}
EXPECT_TRUE(t.search(1));
}


TEST(AvlTreeTest, Insert_RotateRightLeft) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(32);
t.insert(7);
t.insert(27);
t.insert(42);
t.insert(37);
t.insert(47);
t.insert(36);
EXPECT_TRUE(t.search(36));
}

TEST(AvlTreeTest, Insert_RotateLeftRight) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(32);
t.insert(17);
t.insert(7);
t.insert(42);
t.insert(4);
t.insert(9);
t.insert(11);
EXPECT_TRUE(t.search(11));
}

///////////////////////
//Remove-Tests
///////////////////////


TEST(AvlTreeTest, Remove_Root) {
AVLTree t;
for (int i = 30; i > 0; i--) {
t.insert(i);
}
t.remove(15);
EXPECT_FALSE(t.search(15));
}

TEST(AvlTreeTest, Remove_NodeTwoChilds) {
AVLTree t;
for (int i = 30; i > 0; i--) {
t.insert(i);
}
t.remove(11);
EXPECT_FALSE(t.search(11));
}

TEST(AvlTreeTest, Remove_NodeOneChilds) {
AVLTree t;
for (int i = 26; i > 0; i--) {
t.insert(i);
}
t.remove(2);
EXPECT_FALSE(t.search(2));
}

TEST(AvlTreeTest, Remove_NodeNoChild) {
AVLTree t;
t.insert(3);
t.insert(4);
t.insert(5);
t.remove(5);
EXPECT_FALSE(t.search(5));
}

TEST(AvlTreeTest, Remove_NodeNotExist) {
AVLTree t;
t.insert(33);
t.remove(200);
EXPECT_FALSE(t.search(200));
EXPECT_TRUE(t.search(33));
}

TEST(AvlTreeTest, Remove_RotateRightSubtree) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(32);
t.insert(7);
t.insert(27);
t.insert(42);
t.insert(37);
t.insert(47);
t.remove(27);
EXPECT_FALSE(t.search(27));
}


TEST(AvlTreeTest, Remove_RotateLeftRight) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(32);
t.insert(17);
t.insert(7);
t.insert(42);
t.insert(4);
t.insert(9);
t.remove(17);
EXPECT_FALSE(t.search(17));
}

TEST(AvlTreeTest, Remove_LeftRightRotate) {
AVLTree t;
t.insert(22);
t.insert(27);
t.insert(12);
t.insert(7);
t.insert(17);
t.remove(17);
EXPECT_FALSE(t.search(17));
}

TEST(AvlTreeTest, Remove_LeftRightNoLeftChild) {
AVLTree t;
t.insert(22);
t.insert(27);
t.insert(12);
t.insert(17);
t.remove(17);
EXPECT_FALSE(t.search(17));
}

TEST(AvlTreeTest, Remove_RightLeftNoRightChild) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(27);
t.insert(7);
t.insert(17);
t.insert(24);
t.remove(24);
EXPECT_FALSE(t.search(24));
}

TEST(AvlTreeTest, Remove_RightLeaf) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(7);
t.insert(17);
t.remove(17);
EXPECT_FALSE(t.search(17));
}

TEST(AvlTreeTest, Remove_LeftLeaf) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(7);
t.insert(17);
t.remove(7);
EXPECT_FALSE(t.search(7));
}

TEST(AvlTreeTest, Remove_PreviousWithOnLeftLeaf) {
AVLTree t;
t.insert(22);
t.insert(12);
t.insert(27);
t.insert(7);
t.insert(17);
t.insert(24);
t.insert(25);
t.remove(24);
EXPECT_FALSE(t.search(24));
}


TEST(AvlTreeTest, Remove_LeftRotate){
AVLTree t;
t.insert(10);
t.insert(7);
t.insert(14);
t.insert(13);
t.insert(12);
t.insert(4);
t.insert(15);
t.insert(11);
t.remove(4);
EXPECT_FALSE(t.search(4));
}

TEST(AvlTreeTest, Remove_RightLeftRotate_UpOut){
AVLTree t;
t.insert(12);
t.insert(7);
t.insert(17);
t.insert(14);
t.insert(13);
t.insert(4);
t.insert(15);
t.insert(16);
t.remove(4);
EXPECT_FALSE(t.search(4));
}

TEST(AvlTreeTest, Remove_LeftRightRotate_UpOut){
AVLTree t;
t.insert(22);
t.insert(32);
t.insert(15);
t.insert(17);
t.insert(18);
t.insert(42);
t.insert(11);
t.insert(19);
t.remove(42);
EXPECT_FALSE(t.search(42));
}

TEST(AvlTreeTest, Remove_RightRotate_UpOut){
AVLTree t;
t.insert(22);
t.insert(32);
t.insert(15);
t.insert(17);
t.insert(18);
t.insert(42);
t.insert(11);
t.remove(42);
EXPECT_FALSE(t.search(42));
EXPECT_THAT(*t.preorder(), testing::ElementsAre(17, 15, 11, 22, 18, 32));
EXPECT_THAT(*t.inorder(), testing::ElementsAre(11, 15, 17, 18, 22, 32));
EXPECT_THAT(*t.postorder(), testing::ElementsAre(11, 15, 18, 32, 22, 17));
}

TEST(AvlTreeTest, Remove_LoopInsertLowToHigh) {
AVLTree t;
for (int i = 20; i > 0; i--) {
t.insert(i);
}
t.remove(6);
t.remove(18);
t.remove(4);
t.remove(1);
t.remove(20);
t.remove(12);
t.remove(9);
t.remove(6);
t.remove(7);
EXPECT_FALSE(t.search(6));
EXPECT_FALSE(t.search(18));
EXPECT_FALSE(t.search(4));
EXPECT_FALSE(t.search(1));
EXPECT_FALSE(t.search(20));
EXPECT_FALSE(t.search(12));
EXPECT_FALSE(t.search(9));
EXPECT_FALSE(t.search(6));
EXPECT_FALSE(t.search(7));
}

TEST(AvlTreeTest, Remove_LoopInsertLowToHigh_toRemoveIsLeft) {
AVLTree t;
t.insert(30);
t.insert(20);
t.insert(17);
t.insert(10);
t.insert(25);
t.insert(15);
t.insert(19);
t.insert(5);
t.insert(11);
t.insert(23);
t.insert(14);
t.insert(10);
t.insert(3);
t.insert(12);
t.remove(10);
EXPECT_FALSE(t.search(10));

}


TEST(AvlTreeTest, Remove_LoopTenToZero){
AVLTree t;
for (int i = 10; i > 0; i--) {
t.insert(i);
}
t.remove(4);
t.remove(2);
t.remove(10);
t.remove(9);
EXPECT_FALSE(t.search(4));
EXPECT_FALSE(t.search(2));
EXPECT_FALSE(t.search(10));
EXPECT_FALSE(t.search(9));
}

TEST(AvlTreeTest, Remove_BothLeaf_RoatetLeft){
AVLTree t;
t.insert(10);
t.insert(13);
t.insert(5);
t.insert(3);
t.insert(6);
t.insert(14);
t.insert(8);
t.remove(14);
EXPECT_FALSE(t.search(14));
}
