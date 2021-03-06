#include <iostream>
#include <vector>

#include "Bulk_quote.h"
#include "Quote.h"

using std::cout, std::endl;
using std::vector;

int main() {
  vector<Quote> basket;
  basket.push_back(Quote("0-201-82470-1", 50));
  basket.push_back(Bulk_quote("0-201-54848-8", 50, 10, .25));

  cout << basket.front().net_price(15) << endl;  // 750
  cout << basket.back().net_price(15) << endl;   // 750
}
