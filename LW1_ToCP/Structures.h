#include <string>
#include <vector>

struct Arc {
	std::vector<int> prev;
	int std_time = -1;
	int min_time = -1;
	int std_cost = -1;
	int min_cost = -1;
	int start_point = -1;
	int end_point = -1;
};

struct Point {
	std::vector<int> start_of_arc;
	std::vector<int> end_of_arc;
	int time_early = -1;
	int time_late = -1;
	int reserve = -1;
};