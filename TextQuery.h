#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "StrBlob.h"

class QueryResult;  // declaration for TextQuery::query's return type

class TextQuery {
 public:
  using shared_container_type = StrBlob;
  using key_type = shared_container_type::value_type;
  using line_no = shared_container_type::size_type;
  using map_type = std::map<key_type, std::shared_ptr<std::vector<line_no>>>;
  TextQuery(std::ifstream &fin);
  QueryResult query(const key_type &keyword) const;

 private:
  // pointer to shared container of text in fin
  shared_container_type file;
  map_type wm;  // map from word to shared container of corresponding ln
};

#include "QueryResult.h"