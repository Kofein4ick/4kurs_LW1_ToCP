#include <string>
#include <vector>

struct Arc {
	std::vector<int> prev;			//Predecessors
	int std_time = -1;				//Usual time
	int min_time = -1;				//Minimum time
	int std_cost = -1;				//Usual time cost
	int min_cost = -1;				//Minimum time cost
	int start_point = -1;			//Arc start point
	int end_point = -1;				//Arc end point
};

struct Point {
	std::vector<int> start_of_arc;	//Array of arcs starting at this point
	std::vector<int> end_of_arc;	//Array of arcs ending at this point
	int time_early = -1;			//Early event execution time
	int time_late = -1;				//Late event execution time
	int reserve = -1;				//Time reserve
};