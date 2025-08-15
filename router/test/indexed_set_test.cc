#include "indexed_set.h"

#include <gtest/gtest.h>

TEST(IndexedSetTest, TestInsert) {
    IndexedSet<int> set;
    set.insert(0);
    set.insert(1);
    set.insert(2);

    ASSERT_EQ(0, set[0]);
    ASSERT_EQ(1, set[1]);
    ASSERT_EQ(2, set[2]);
}

TEST(IndexedSetTest, TestInsertDuplicate) {
    IndexedSet<int> set;
    set.insert(0);
    set.insert(0);

    ASSERT_EQ(1, set.size());
    ASSERT_EQ(0, set[0]);
}

TEST(IndexedSetTest, TestRemoveNonexistentData) {
    IndexedSet<int> set;

    ASSERT_THROW(set.remove(0), std::runtime_error);
}

TEST(IndexedSetTest, TestRemove) {
    IndexedSet<int> set;
    set.insert(0);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);

    set.remove(2);
    set.remove(3);

    ASSERT_EQ(3, set.size());
    ASSERT_EQ(0, set[0]);
    ASSERT_EQ(1, set[1]);
    ASSERT_EQ(4, set[2]);
}

TEST(IndexedSetTest, TestSize) {
    IndexedSet<int> set;
    set.insert(0);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.remove(2);

    ASSERT_EQ(4, set.size());
}

TEST(IndexedSetTest, TestEmptyReturnsTrue) {
    IndexedSet<int> set;
    ASSERT_TRUE(set.empty());
}

TEST(IndexedSetTest, TestEmptyReturnsFalse) {
    IndexedSet<int> set;
    set.insert(0);

    ASSERT_FALSE(set.empty());
}

TEST(IndexedSetTest, TestIndexOperator) {
    IndexedSet<int> set;
    set.insert(5);
    set.insert(2);
    set.insert(1);

    ASSERT_EQ(5, set[0]);
    ASSERT_EQ(2, set[1]);
    ASSERT_EQ(1, set[2]);
}
