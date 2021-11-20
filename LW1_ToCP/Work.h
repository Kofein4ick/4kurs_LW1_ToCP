#include <string>

class Work {
private:
	std::string prev;
	int std_time;
	int min_time;
	int std_cost;
	int min_cost;
public:
	Work();
	~Work();
	void set_prev(std::string str);
	std::string get_prev();
	void set_std_time(int time);
	int get_std_time();
	void set_min_time(int time);
	int get_min_time();
	void set_std_cost(int cost);
	int get_std_cost();
	void set_min_cost(int cost);
	int get_min_cost();
};