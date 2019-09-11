#include <string>
using std::string;

// compare the length of two strings
constexpr bool isShorter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}
