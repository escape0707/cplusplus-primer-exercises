#pragma once

#include <iostream>

#include "TextQuery.h"

// QueryResult saves its own copy of shared_container (of inputted text) and
// shared_ptr to key's line number record, and is able to print even after
// TextQuery get destroyed
class QueryResult {
 public:
  using key_type = TextQuery::key_type;
  using shared_container_type = TextQuery::shared_container_type;
  using shared_lns_ptr = TextQuery::map_type::mapped_type;
  using line_number_type = TextQuery::line_number_type;
  // Construct an empty QueryResult when the key is not found
  QueryResult(const key_type &key);
  // Construct a concrete QueryResult when key is found
  QueryResult(const key_type &key,
              const shared_lns_ptr &p_line_numbers,
              const shared_container_type &input);
  std::ostream &print(std::ostream &os = std::cout);

 private:
  key_type key_;
  shared_lns_ptr p_line_numbers_;
  shared_container_type input_;
};
