#include "vector.h"
#include "differentiation.h"

#include <vector>

#include <gtest/gtest.h>

namespace {

TEST(VectorTest, Create) {
  simple_differentiation::Vector<double> vec0;
  EXPECT_EQ(0, vec0.size());

  simple_differentiation::Vector<double> vec0a(0);
  EXPECT_EQ(0, vec0a.size());

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

  simple_differentiation::Vector<int> vec1i(1, -1);
  EXPECT_EQ(1, vec1i.size());
  EXPECT_EQ(-1, vec1i[0]);

  std::vector<double> src;
  src.push_back(0.1);
  src.push_back(0.2);
  simple_differentiation::Vector<double> dst(src.begin(), src.end());
  EXPECT_EQ(src.size(), dst.size());
  EXPECT_EQ(src[0], dst[0]);
  EXPECT_EQ(src[1], dst[1]);
}

TEST(VectorTest, Negate) {
  simple_differentiation::Vector<double> vec0(0);
  EXPECT_EQ(0, (-vec0).size());

  simple_differentiation::Vector<double> vec1(1, 4.0);
  EXPECT_EQ(1, (-vec1).size());
  EXPECT_EQ(-4.0, (-vec1)[0]);

  simple_differentiation::Vector<double> vec2(1, -4.0);
  vec2.push_back(0.5);
  EXPECT_EQ(2, (-vec2).size());
  EXPECT_EQ(4.0, (-vec2)[0]);
  EXPECT_EQ(-0.5, (-vec1)[1]);
}

TEST(VectorTest, AddAssign) {
  simple_differentiation::Vector<double> vec_a;
  vec_a.push_back(1.0);
  vec_a.push_back(2.0);
  simple_differentiation::Vector<double> vec_b;
  vec_b.push_back(3.0);
  vec_b.push_back(-1.0);

  simple_differentiation::Vector<double> vec_a_copy = (vec_a += vec_b);
  EXPECT_EQ(2, vec_a.size());
  EXPECT_EQ(4.0, vec_a[0]);
  EXPECT_EQ(1.0, vec_a[1]);

  EXPECT_EQ(vec_a.size(), vec_a_copy.size());
  EXPECT_EQ(vec_a[0], vec_a_copy[0]);
  EXPECT_EQ(vec_a[1], vec_a_copy[1]);
}

TEST(VectorTest, Add) {
  simple_differentiation::Vector<double> vec_a;
  vec_a.push_back(1.0);
  vec_a.push_back(2.0);
  simple_differentiation::Vector<double> vec_b;
  vec_b.push_back(3.0);
  vec_b.push_back(-1.0);

  simple_differentiation::Vector<double> vec_c = vec_a + vec_b;
  EXPECT_EQ(2, vec_c.size());
  EXPECT_EQ(4.0, vec_c[0]);
  EXPECT_EQ(1.0, vec_c[1]);
}

TEST(VectorTest, SubtractAssign) {
  simple_differentiation::Vector<double> vec_a;
  vec_a.push_back(1.0);
  vec_a.push_back(2.0);
  simple_differentiation::Vector<double> vec_b;
  vec_b.push_back(3.0);
  vec_b.push_back(-1.0);

  simple_differentiation::Vector<double> vec_a_copy = (vec_a -= vec_b);
  EXPECT_EQ(2, vec_a.size());
  EXPECT_EQ(-2.0, vec_a[0]);
  EXPECT_EQ(3.0, vec_a[1]);

  EXPECT_EQ(vec_a.size(), vec_a_copy.size());
  EXPECT_EQ(vec_a[0], vec_a_copy[0]);
  EXPECT_EQ(vec_a[1], vec_a_copy[1]);
}

TEST(VectorTest, Subtract) {
  simple_differentiation::Vector<double> vec_a;
  vec_a.push_back(1.0);
  vec_a.push_back(2.0);
  simple_differentiation::Vector<double> vec_b;
  vec_b.push_back(3.0);
  vec_b.push_back(-1.0);

  simple_differentiation::Vector<double> vec_c = vec_a - vec_b;
  EXPECT_EQ(2, vec_c.size());
  EXPECT_EQ(-2.0, vec_c[0]);
  EXPECT_EQ(3.0, vec_c[1]);
}

TEST(VectorTest, MultiplyAssign) {
  simple_differentiation::Vector<double> vec;
  vec.push_back(1.0);
  vec.push_back(2.0);

  simple_differentiation::Vector<double> vec_copy = (vec *= 3.0);
  EXPECT_EQ(2, vec.size());
  EXPECT_EQ(3.0, vec[0]);
  EXPECT_EQ(6.0, vec[1]);

  EXPECT_EQ(vec.size(), vec_copy.size());
  EXPECT_EQ(vec[0], vec_copy[0]);
  EXPECT_EQ(vec[1], vec_copy[1]);

  vec.clear();
  vec.push_back(1.0);
  vec.push_back(2.0);
  vec *= 2;
  EXPECT_EQ(2, vec.size());
  EXPECT_EQ(2.0, vec[0]);
  EXPECT_EQ(4.0, vec[1]);
}

TEST(VectorTest, Multiply) {
  simple_differentiation::Vector<double> vec;
  vec.push_back(1.0);
  vec.push_back(2.0);

  simple_differentiation::Vector<double> vec_mult = vec * 3.0;
  EXPECT_EQ(2, vec_mult.size());
  EXPECT_EQ(3.0, vec_mult[0]);
  EXPECT_EQ(6.0, vec_mult[1]);

  vec_mult = vec * 2;
  EXPECT_EQ(2, vec_mult.size());
  EXPECT_EQ(2.0, vec_mult[0]);
  EXPECT_EQ(4.0, vec_mult[1]);

  vec_mult = 4.0 * vec;
  EXPECT_EQ(2, vec_mult.size());
  EXPECT_EQ(4.0, vec_mult[0]);
  EXPECT_EQ(8.0, vec_mult[1]);

  vec_mult = 5 * vec;
  EXPECT_EQ(2, vec_mult.size());
  EXPECT_EQ(5.0, vec_mult[0]);
  EXPECT_EQ(10.0, vec_mult[1]);
}

TEST(VectorTest, DivideAssign) {
  simple_differentiation::Vector<double> vec;
  vec.push_back(60.0);
  vec.push_back(120.0);

  simple_differentiation::Vector<double> vec_copy = (vec /= 3.0);
  EXPECT_EQ(2, vec.size());
  EXPECT_EQ(20.0, vec[0]);
  EXPECT_EQ(40.0, vec[1]);

  EXPECT_EQ(vec.size(), vec_copy.size());
  EXPECT_EQ(vec[0], vec_copy[0]);
  EXPECT_EQ(vec[1], vec_copy[1]);

  vec.clear();
  vec.push_back(60.0);
  vec.push_back(120.0);
  vec /= 2;
  EXPECT_EQ(2, vec.size());
  EXPECT_EQ(30.0, vec[0]);
  EXPECT_EQ(60.0, vec[1]);
}

TEST(VectorTest, Divide) {
  simple_differentiation::Vector<double> vec;
  vec.push_back(60.0);
  vec.push_back(120.0);

  simple_differentiation::Vector<double> vec_div = vec / 3.0;
  EXPECT_EQ(2, vec_div.size());
  EXPECT_EQ(20.0, vec_div[0]);
  EXPECT_EQ(40.0, vec_div[1]);

  vec_div = vec / 2;
  EXPECT_EQ(2, vec_div.size());
  EXPECT_EQ(30.0, vec_div[0]);
  EXPECT_EQ(60.0, vec_div[1]);
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
