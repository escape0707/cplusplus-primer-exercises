#include "OrRange.h"

#include <memory>
#include <string>

#include "BinaryRange.h"
#include "LineNumberRange.h"

using std::shared_ptr;
using std::string;

using record_type = OrRange::record_type;

OrRange::OrRange(const shared_ptr<LineNumberRange> &p_lhs,
                 const shared_ptr<LineNumberRange> &p_rhs)
    : BinaryRange(p_lhs, p_rhs, "|") {}

record_type OrRange::eval(const TextQuery &text_query) const {
  record_type ret;
  const record_type &lhs = p_lhs_->eval(text_query);
  const record_type &rhs = p_rhs_->eval(text_query);
  record_const_iterator l_beg = lhs.cbegin();
  record_const_iterator r_beg = rhs.cbegin();
  const record_const_iterator l_end = lhs.cend();
  const record_const_iterator r_end = rhs.cend();
  while (l_beg != l_end && r_beg != r_end) {
    line_number_type l = *l_beg;
    line_number_type r = *r_beg;
    if (l < r) {
      ret.push_back(l);
      ++l_beg;
    } else if (l > r) {
      ret.push_back(r);
      ++r_beg;
    } else {
      ret.push_back(l);
      ++l_beg;
      ++r_beg;
    }
  }
  while (l_beg != l_end) {
    ret.push_back(*l_beg++);
  }
  while (r_beg != r_end) {
    ret.push_back(*r_beg++);
  }
  return ret;
}
