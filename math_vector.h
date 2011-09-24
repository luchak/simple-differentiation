// math_vector.h
//
// An STL vector with basic arithmetic operators.

#ifndef MATH_VECTOR_H_
#define MATH_VECTOR_H_

#include <vector>

template <class T, class Allocator = std::allocator<T> >
class MathVector : public std::vector<T, Allocator> {
 public:
  typedef typename std::vector<T, Allocator> vector_type;
  typedef typename vector_type::size_type size_type;

  explicit MathVector(const Allocator& allocator = Allocator())
      : vector_type(allocator) { }
  explicit MathVector(size_type n, const T& value = T())
      : vector_type(n, value) { } 

  template <class InputIterator>
  MathVector(InputIterator first,
             InputIterator last,
             const Allocator& allocator = Allocator())
      : vector_type(first, last, allocator) { }

  MathVector(const MathVector<T, Allocator>& x) : vector_type(x) { }

  virtual ~MathVector() { };

  MathVector operator-() const {
    MathVector result(this->size());
    for (size_type i = 0; i < this->size(); ++i) {
      result[i] = -(*this)[i];
    }
    return result;
  }

  MathVector& operator+=(const MathVector& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] += rhs[i];
    }
    return *this;
  }

  MathVector& operator-=(const MathVector& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] -= rhs[i];
    }
    return *this;
  }

  template <class U>
  MathVector& operator*=(const U& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] *= rhs;
    }
    return *this;
  }

  template <class U>
  MathVector& operator/=(const U& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] /= rhs;
    }
    return *this;
  }

  MathVector operator+(const MathVector& rhs) const {
    return MathVector(*this) += rhs;
  }

  MathVector operator-(const MathVector& rhs) const {
    return MathVector(*this) -= rhs;
  }

  template <class U>
  MathVector operator*(const U& rhs) const {
    return MathVector(*this) *= rhs;
  }

  template <class U>
  MathVector operator/(const U& rhs) const {
    return MathVector(*this) /= rhs;
  }
};

// Handle cases where the scalar is on the left.
template <class T, class Allocator, class U>
MathVector<T, Allocator> operator*(const U& lhs,
                                   const MathVector<T, Allocator>& rhs) {
  return rhs * lhs;
}

#endif  // MATH_VECTOR_H_

