#ifndef DIFFERENTIATION_H_
#define DIFFERENTIATION_H_

#include "math_vector.h"

namespace simple_differentiation {

template <class T, class V>
class DifferentiationContext;
template <class T, class V>
class DifferentiationVariable;

template <class T, class V>
DifferentiationVariable<T, V> sin(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> cos(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> tan(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> asin(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> acos(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> atan(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> fabs(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> pow(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> sqrt(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> exp(const DifferentiationVariable<T, V>& x);
template <class T, class V>
DifferentiationVariable<T, V> log(const DifferentiationVariable<T, V>& x);

template <class T, class V = MathVector<T> >
class DifferentiationVariable {
 public:
  friend class DifferentiationContext<T, V>;

  friend DifferentiationVariable<T, V> sin<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> cos<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> tan<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> asin<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> acos<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> atan<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> fabs<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> pow<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> sqrt<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> exp<>(const DifferentiationVariable<T, V>& x);
  friend DifferentiationVariable<T, V> log<>(const DifferentiationVariable<T, V>& x);

  DifferentiationVariable(const DifferentiationVariable& other);
  DifferentiationVariable& operator=(const DifferentiationVariable& rhs);

  DifferentiationVariable operator-() const;

  DifferentiationVariable& operator+=(const DifferentiationVariable& rhs);
  DifferentiationVariable& operator-=(const DifferentiationVariable& rhs);
  DifferentiationVariable& operator*=(const DifferentiationVariable& rhs);
  DifferentiationVariable& operator/=(const DifferentiationVariable& rhs);

  template <class U>
  DifferentiationVariable& operator+=(const U& rhs);
  template <class U>
  DifferentiationVariable& operator-=(const U& rhs);
  template <class U>
  DifferentiationVariable& operator*=(const U& rhs);
  template <class U>
  DifferentiationVariable& operator/=(const U& rhs);

  DifferentiationVariable operator+(const DifferentiationVariable& rhs) const;
  DifferentiationVariable operator-(const DifferentiationVariable& rhs) const;
  DifferentiationVariable operator*(const DifferentiationVariable& rhs) const;
  DifferentiationVariable operator/(const DifferentiationVariable& rhs) const;

  template <class U>
  DifferentiationVariable operator+(const U& rhs) const;
  template <class U>
  DifferentiationVariable operator-(const U& rhs) const;
  template <class U>
  DifferentiationVariable operator*(const U& rhs) const;
  template <class U>
  DifferentiationVariable operator/(const U& rhs) const;

  // This needs to live in the class body to avoid linker errors.
  template <class U>
  friend DifferentiationVariable<T, V> operator/(
      const U& lhs, const DifferentiationVariable<T, V>& rhs) {
    T new_value = lhs / rhs.value();
    V new_gradient = -lhs * rhs.gradient() / (rhs.value() * rhs.value());

    return DifferentiationVariable<T, V>(new_value, new_gradient);
  }


  const T& value() const { return value_; }
  const V& gradient() const { return gradient_; }

 private:
  DifferentiationVariable(const T& value, const V& gradient)
    : value_(value),
      gradient_(gradient) { }

  DifferentiationVariable(int index,
                          const T& value,
                          const DifferentiationContext<T, V>& context)
      : value_(value),
        gradient_(context.size()) {
    gradient_[index] = 1.0;
  }

  T value_;
  V gradient_;
};

template <class T, class V = MathVector<T> >
class DifferentiationContext {
 public:
  DifferentiationContext(int num_vars)
      : num_vars_(num_vars), original_values_(num_vars) { }

  DifferentiationVariable<T, V> MakeVariable(int index, const T& value) const;

  const T& original_value(int index) const { return original_values_[index]; }
  const int size() const { return num_vars_; }

 private:
  int num_vars_;
  std::vector<T> original_values_;

  DifferentiationContext(const DifferentiationContext& other);
  DifferentiationContext& operator=(const DifferentiationContext& other);
};

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationContext<T, V>::MakeVariable(
    int index, const T& value) const {
  return DifferentiationVariable<T, V>(index, value, *this);
}

template <class T, class V>
DifferentiationVariable<T, V>::DifferentiationVariable(
    const DifferentiationVariable& other)
    : value_(other.value_),
      gradient_(other.gradient_) { }

template <class T, class V>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator=(
    const DifferentiationVariable& rhs) {
  if (this != &rhs) {
    value_ = rhs.value_;
    gradient_ = rhs.gradient_;
  }
  return *this;
}

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator-() const {
  DifferentiationVariable result(*this);
  result.value_ = -result.value_;
  result.gradient_ = -result.gradient_;
  return result;
}

template <class T, class V>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator+=(
    const DifferentiationVariable& rhs) {
  value_ += rhs.value_;
  gradient_ += rhs.gradient_;
  return *this;
}

template <class T, class V>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator-=(
    const DifferentiationVariable& rhs) {
  value_ -= rhs.value_;
  gradient_ -= rhs.gradient_;
  return *this;
}

template <class T, class V>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator*=(
    const DifferentiationVariable& rhs) {
  gradient_ = gradient_*rhs.value_ + value_*rhs.gradient_;
  value_ *= rhs.value_;
  return *this;
}

template <class T, class V>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator/=(
    const DifferentiationVariable& rhs) {
  gradient_ = (gradient_*rhs.value_ - value_*rhs.gradient_) /
      (rhs.value_*rhs.value_);
  value_ /= rhs.value_;
  return *this;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator+=(
    const U& rhs) {
  value_ += rhs;
  return *this;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator-=(
    const U& rhs) {
  value_ -= rhs;
  return *this;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator*=(
    const U& rhs) {
  value_ *= rhs;
  gradient_ *= rhs;
  return *this;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V>& DifferentiationVariable<T, V>::operator/=(
    const U& rhs) {
  value_ /= rhs;
  gradient_ /= rhs;
  return *this;
}

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator+(
    const DifferentiationVariable<T, V>& rhs) const {
  return DifferentiationVariable(*this) += rhs;
}

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator-(
    const DifferentiationVariable<T, V>& rhs) const {
  return DifferentiationVariable(*this) -= rhs;
}

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator*(
    const DifferentiationVariable<T, V>& rhs) const {
  return DifferentiationVariable(*this) *= rhs;
}

template <class T, class V>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator/(
    const DifferentiationVariable<T, V>& rhs) const {
  return DifferentiationVariable(*this) /= rhs;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator+(
    const U& rhs) const {
  return DifferentiationVariable(*this) += rhs;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator-(
    const U& rhs) const {
  return DifferentiationVariable(*this) -= rhs;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator*(
    const U& rhs) const {
  return DifferentiationVariable(*this) *= rhs;
}

template <class T, class V>
template <class U>
DifferentiationVariable<T, V> DifferentiationVariable<T, V>::operator/(
    const U& rhs) const {
  return DifferentiationVariable(*this) /= rhs;
}

template <class T, class V, class U>
DifferentiationVariable<T, V> operator+(const U& lhs,
                                        const DifferentiationVariable<T, V>& rhs) {
  return rhs + lhs;
}

template <class T, class V, class U>
DifferentiationVariable<T, V> operator-(const U& lhs,
                                        const DifferentiationVariable<T, V>& rhs) {
  return -rhs + lhs;
}

template <class T, class V, class U>
DifferentiationVariable<T, V> operator*(const U& lhs,
                                        const DifferentiationVariable<T, V>& rhs) {
  return rhs * lhs;
}

template <class T, class V>
DifferentiationVariable<T, V> sin(const DifferentiationVariable<T, V>& x) {
  return DifferentiationVariable<T, V>(sin(x.value()),
                                       cos(x.value()) * x.gradient());
}

template <class T, class V>
DifferentiationVariable<T, V> cos(const DifferentiationVariable<T, V>& x) {
  return DifferentiationVariable<T, V>(cos(x.value()),
                                       -sin(x.value()) * x.gradient());
}

template <class T, class V>
DifferentiationVariable<T, V> tan(const DifferentiationVariable<T, V>& x) {
  T cos_x = cos(x.value());
  return DifferentiationVariable<T, V>(tan(x.value()),
                                       x.gradient() / (cos_x*cos_x));
}

template <class T, class V>
DifferentiationVariable<T, V> asin(const DifferentiationVariable<T, V>& x) {
  return DifferentiationVariable<T, V>(
      asin(x.value()), x.gradient() / sqrt(1.0 - x.value()*x.value()));
}

template <class T, class V>
DifferentiationVariable<T, V> acos(const DifferentiationVariable<T, V>& x) {
  return DifferentiationVariable<T, V>(
      acos(x.value()), -x.gradient() / sqrt(1.0 - x.value()*x.value()));
}

template <class T, class V>
DifferentiationVariable<T, V> atan(const DifferentiationVariable<T, V>& x) {
  return DifferentiationVariable<T, V>(
      atan(x.value()), x.gradient() / (1.0 + x.value()*x.value()));
}

template <class T, class V>
DifferentiationVariable<T, V> fabs(const DifferentiationVariable<T, V>& x) {
  if (x.value() < T()) {
    return DifferentiationVariable<T, V>(-x.value(), -x.gradient());
  } else {
    return DifferentiationVariable<T, V>(x.value(), x.gradient());
  }
}

template <class T, class V>
DifferentiationVariable<T, V> pow(const DifferentiationVariable<T, V>& x) {

}

template <class T, class V>
DifferentiationVariable<T, V> sqrt(const DifferentiationVariable<T, V>& x) {
}

template <class T, class V>
DifferentiationVariable<T, V> exp(const DifferentiationVariable<T, V>& x) {
}

template <class T, class V>
DifferentiationVariable<T, V> log(const DifferentiationVariable<T, V>& x) {
}

}  // namespace simple_differentiation

#endif  // DIFFERENTIATION_H_
