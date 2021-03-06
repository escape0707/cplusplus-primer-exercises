#include "StrVec.h"

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <utility>

using std::as_const, std::pair;
using std::destroy, std::destroy_at;
using std::equal;
using std::initializer_list;
using std::lexicographical_compare;
using std::uninitialized_copy;
using std::uninitialized_fill_n;
using std::uninitialized_move;
using std::uninitialized_value_construct_n;

using size_type = StrVec::size_type;
using reference = StrVec::reference;
using const_reference = StrVec::const_reference;
using iterator = StrVec::iterator;
using const_iterator = StrVec::const_iterator;

StrVec::StrVec() = default;

StrVec::StrVec(const StrVec &other) {
  pair<iterator, iterator> newdata = alloc_n_copy(other.begin(), other.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&other) noexcept
    : elements(other.elements), first_free(other.first_free), cap(other.cap) {
  other.elements = nullptr;
  // other.elements = other.first_free = other.cap = nullptr;
}

// copying a std::initializer_list does not copy the underlying objects
StrVec::StrVec(initializer_list<value_type> il) {
  // so sad that initializer_list was too old to support move semantics.
  // and it provides only const iterator to its underlying data structure.
  pair<iterator, iterator> newdata = alloc_n_copy(il.begin(), il.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  pair<iterator, iterator> newdata = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = newdata.first;
  first_free = cap = newdata.second;
  return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = nullptr;
    // rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

StrVec &StrVec::operator=(std::initializer_list<value_type> il) {
  pair<iterator, iterator> newdata = alloc_n_copy(il.begin(), il.end());
  free();
  elements = newdata.first;
  first_free = cap = newdata.second;
  return *this;
}

StrVec::~StrVec() {
  free();
}

void StrVec::push_back(const_reference value) {
  chk_n_alloc();
  Alloc_traits::construct(alloc, first_free++, value);
}

void StrVec::push_back(value_type &&value) {
  chk_n_alloc();
  Alloc_traits::construct(alloc, first_free++, std::move(value));
}

void StrVec::pop_back() {
  destroy_at(--first_free);
}

void StrVec::resize(size_type new_size) {
  if (new_size < size()) {
    destroy_starting_from(elements + new_size);
  } else if (size_type diff = new_size - size()) {
    reserve(new_size);
    first_free = uninitialized_value_construct_n(first_free, diff);
  }
}

void StrVec::resize(size_type new_size, const_reference value) {
  if (new_size < size()) {
    destroy_starting_from(elements + new_size);
  } else if (size_type diff = new_size - size()) {
    reserve(new_size);
    first_free = uninitialized_fill_n(first_free, diff, value);
  }
}

bool StrVec::empty() const {
  return elements == first_free;
}

size_type StrVec::size() const {
  return static_cast<size_type>(first_free - elements);
}

void StrVec::reserve(size_type new_cap) {
  if (new_cap > capacity()) {
    _reserve(new_cap);
  }
}

size_type StrVec::capacity() const {
  return static_cast<size_type>(cap - elements);
}

reference StrVec::operator[](size_type pos) {
  return const_cast<reference>(as_const(*this)[pos]);
}

const_reference StrVec::operator[](size_type pos) const {
  return elements[pos];
}

reference StrVec::front() {
  return const_cast<reference>(as_const(*this).front());
}

const_reference StrVec::front() const {
  return *elements;
}

reference StrVec::back() {
  return const_cast<reference>(as_const(*this).back());
}

const_reference StrVec::back() const {
  return first_free[-1];
}

iterator StrVec::begin() {
  return const_cast<iterator>(as_const(*this).begin());
}

const_iterator StrVec::begin() const {
  return cbegin();
}

const_iterator StrVec::cbegin() const {
  return elements;
}

iterator StrVec::end() {
  return const_cast<iterator>(as_const(*this).end());
}

const_iterator StrVec::end() const {
  return cend();
}

const_iterator StrVec::cend() const {
  return first_free;
}

bool operator==(const StrVec &lhs, const StrVec &rhs) {
  return equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

bool operator!=(const StrVec &lhs, const StrVec &rhs) {
  return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs) {
  return lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(),
                                 rhs.cend());
}

bool operator>(const StrVec &lhs, const StrVec &rhs) {
  return rhs < lhs;
}

bool operator<=(const StrVec &lhs, const StrVec &rhs) {
  return !(lhs > rhs);
}

bool operator>=(const StrVec &lhs, const StrVec &rhs) {
  return !(lhs < rhs);
}

iterator StrVec::allocate(size_type n) {
  if (n) {
    return Alloc_traits::allocate(alloc, n);
  }
  return nullptr;
}

pair<iterator, iterator> StrVec::alloc_n_copy(const_iterator beg,
                                              const_iterator end) {
  iterator newbeg = allocate(static_cast<size_type>(end - beg));
  return {newbeg, uninitialized_copy(beg, end, newbeg)};
}

void StrVec::destroy_starting_from(iterator pos) {
  destroy(pos, first_free);
  first_free = pos;
}

void StrVec::_reserve(size_type new_cap) {
  iterator newelements = allocate(new_cap);
  iterator newfirst_free =
      uninitialized_move(elements, first_free, newelements);
  free();
  elements = newelements;
  first_free = newfirst_free;
  cap = newelements + new_cap;
}

void StrVec::chk_n_alloc() {
  if (first_free == cap) {
    _reserve(capacity() ? 2 * capacity() : 1);
  }
}

void StrVec::free() {
  if (elements) {
    destroy(elements, first_free);
    Alloc_traits::deallocate(alloc, elements, capacity());
  }
}
