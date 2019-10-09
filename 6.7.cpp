#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::string;
using std::vector;

size_t count_calls() {
	static size_t ctr = 0; // value will persist across calls
	return ctr++;
}

int main() {
	for (size_t i = 0; i != 10; ++i) {
		cout << count_calls() << endl;
	}
}
