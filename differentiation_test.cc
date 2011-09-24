#include "vector.h"
#include "differentiation.h"

#include <gtest/gtest.h>

namespace {

TEST(VectorTest, VectorCreation) {
  simple_differentiation::Vector<double> vec0(0);
  EXPECT_EQ(0, vec0.size());

  simple_differentiation::Vector<double> vec1(1);
  EXPECT_EQ(1, vec1.size());
  EXPECT_EQ(0.0, vec1[0]);

  simple_differentiation::Vector<double> vec1a(1, 1.0);
  EXPECT_EQ(1, vec1a.size());
  EXPECT_EQ(1.0, vec1a[0]);

  simple_differentiation::Vector<double> vec2(2, 7.0);
  EXPECT_EQ(2, vec2.size());
  EXPECT_EQ(7.0, vec2[0]);
  EXPECT_EQ(7.0, vec2[1]);
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
