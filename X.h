// Todo: maybe do some constexpr optimization?

#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

class X {
 public:
  using name_type = std::string;
  using count_type = std::size_t;
  X(const name_type &name)
      : pname(std::make_shared<name_type>(name)),
        pcount(std::make_shared<count_type>(1)) {
    print_member("X(const name_type &)");
  }
  // the order of member initialization is the same as the order in which they
  // appear in the class definition. See page 289
  X(const X &other) : pname(other.pname), pcount(other.pcount), no(++*pcount) {
    print_member("X(const X &)");
  }
  X &operator=(const X &) {
    print_member("X& operator=(const X &)");
    return *this;
  }
  ~X() { print_member("~X()"); }

 private:
  std::ostream &print_member(const name_type &func_sig) {
    return std::cout << *pname << '[' << no << ']' << ": " << func_sig
                     << std::endl;
  }
  const std::shared_ptr<const name_type> pname;
  const std::shared_ptr<count_type> pcount;
  const std::size_t no = 1;
};
