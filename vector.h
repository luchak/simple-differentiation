// vector.h
//
// An STL vector with basic arithmetic operators.

#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>

namespace simple_differentiation {

template <class T, class Allocator = std::allocator<T> >
class Vector : public std::vector<T, Allocator> {
 public:
  typedef typename std::vector<T, Allocator> base_type;
  typedef typename base_type::size_type size_type;

  explicit Vector(const Allocator& allocator = Allocator())
      : base_type(allocator) { }
  explicit Vector(size_type n, const T& value = T())
      : base_type(n, value) { } 

  template <class InputIterator>
  Vector(InputIterator first,
         InputIterator last,
         const Allocator& allocator = Allocator())
      : base_type(first, last, allocator) { }

  Vector(const Vector<T, Allocator>& x) : base_type(x) { }

  virtual ~Vector() { };

  Vector operator-() const {
    Vector result(this->size());
    for (size_type i = 0; i < this->size(); ++i) {
      result[i] = -(*this)[i];
    }
    return result;
  }

  Vector& operator+=(const Vector& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] += rhs[i];
    }
    return *this;
  }

  Vector& operator-=(const Vector& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] -= rhs[i];
    }
    return *this;
  }

  template <class U>
  Vector& operator*=(const U& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] *= rhs;
    }
    return *this;
  }

  template <class U>
  Vector& operator/=(const U& rhs) {
    for (size_type i = 0; i < this->size(); ++i) {
      (*this)[i] /= rhs;
    }
    return *this;
  }

  Vector operator+(const Vector& rhs) const {
    return Vector(*this) += rhs;
  }

  Vector operator-(const Vector& rhs) const {
    return Vector(*this) -= rhs;
  }

  template <class U>
  Vector operator*(const U& rhs) const {
    return Vector(*this) *= rhs;
  }

  template <class U>
  Vector operator/(const U& rhs) const {
    return Vector(*this) /= rhs;
  }
};

// Handle cases where the scalar is on the left.
template <class T, class Allocator, class U>
Vector<T, Allocator> operator*(const U& lhs,
                               const Vector<T, Allocator>& rhs) {
  return rhs * lhs;
}

}  // namespace simple_differentiation

#endif  // VECTOR_H_

