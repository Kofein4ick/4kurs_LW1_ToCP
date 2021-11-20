#include "Work.h"

void Work::set_min_cost(int cost) {
	min_cost = cost;
}

void Work::set_std_cost(int cost) {
	std_cost = cost;
}

void Work::set_min_time(int time) {
	min_time = time;
}

void Work::set_std_time(int time) {
	std_time = time;
}

void Work::set_prev(std::string str) {
	prev = str;
}

std::string Work::get_prev() {
	return prev;
}

int Work::get_std_time() {
	return std_time;
}

int Work::get_min_time() {
	return min_time;
}

int Work::get_std_cost() {
	return std_cost;
}

int Work::get_min_cost() {
	return min_cost;
}

Work::Work() {
	min_cost=0;
	min_time=0;
	std_cost=0;
	std_time=0;
	prev = "";
}
Work::~Work() {}