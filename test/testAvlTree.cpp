#include "testAvlTree.h"
#include <memory>

using namespace std;

// empty tree
/*
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

TEST(AvlTreeTest, EquallyBalanced) {
    AvlTree b;
    b.insert(22);
    b.insert(12);
    b.insert(32);
    b.insert(7);
    b.insert(27);
    b.insert(42);
    b.insert(37);
    b.insert(47);
    b.insert(36);
    EXPECT_TRUE(b.search(36));
   // EXPECT_TRUE(b.isEquallyBalanced());
}
*/

TEST(AvlTreeTest, Three_Node_Rotate_Right) {
    AvlTree b;
    b.insert(22);
    b.insert(11);
    b.insert(7);
    EXPECT_TRUE(b.search(22));
    EXPECT_TRUE(b.search(11));
    EXPECT_TRUE(b.search(7));
}

TEST(AvlTreeTest, Three_Node_Rotate_Left) {
    AvlTree b;
    b.insert(22);
    b.insert(33);
    b.insert(44);
    EXPECT_TRUE(b.search(22));
    EXPECT_TRUE(b.search(33));
    EXPECT_TRUE(b.search(44));
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
