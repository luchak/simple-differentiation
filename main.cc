#include <iostream>

#include "differentiation.h"
#include "math_vector.h"

using namespace simple_differentiation;

int main(int argc, const char* argv[]) {
  MathVector<double> vec;
  vec.push_back(5.0);
  vec.push_back(-2.0);

  MathVector<double> vec2(vec);

  std::cout << vec[0] << std::endl;
  std::cout << vec.size() << " " << vec2.size() << std::endl;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec += vec2;
  vec += vec2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec -= vec2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec *= 7;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec /= 2.0;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = vec2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = vec2 + vec;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = vec2 - vec;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = vec2 * 2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = 2 * vec2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = vec2 / 2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  vec = -vec2;
  std::cout << vec[0] << " " << vec2[0] << std::endl;

  DifferentiationContext<double> dc(2);
  DifferentiationVariable<double> x = dc.MakeVariable(0, 1.0);
  DifferentiationVariable<double> y = dc.MakeVariable(1, 5.0);

  std::cout << x.value() << std::endl;
  std::cout << x.gradient()[0] << " " << x.gradient()[1] << std::endl;
  x = operator/(2.0, x);
  std::cout << x.value() << std::endl;
  std::cout << x.gradient()[0] << " " << x.gradient()[1] << std::endl;

  return 0;
}
