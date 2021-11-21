#include <string>
#include <vector>

struct Arc {
	std::vector<int> prev;
	int std_time=0;
	int min_time=0;
	int std_cost=0;
	int min_cost=0;
	int start_point = 0;
	int end_point = 0;
};

struct Point {
	std::vector<int> start_of_arc;
	std::vector<int> end_of_arc;
};