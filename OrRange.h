#pragma once

#include <memory>
#include <string>

#include "BinaryRange.h"
#include "LineNumberRange.h"
#include "TextQuery.h"

class OrRange : public BinaryRange {
 public:
  OrRange(const std::shared_ptr<LineNumberRange> &p_lhs,
          const std::shared_ptr<LineNumberRange> &p_rhs);
  record_type eval(const TextQuery &text_query) const override;
};
