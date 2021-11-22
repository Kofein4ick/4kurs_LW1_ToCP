#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Func.h"

std::string str_frag(std::string str, int& pos) {
	std::string temp;
	while ((str[pos] != '\t') && (str[pos] != '\0')) {
		temp = temp + str[pos];
		pos++;
	}
	return(temp);
}


int file_read(std::string*& str, int& c_rib) {
	std::ifstream file;

	file.open("Text.txt");
	if (!file.is_open()) {
		std::cout << "Error! Can't open file\n";
		system("pause");
		file.close();
		return -1;
	}

	file >> c_rib;
	file.get();
	str = new std::string[c_rib];
	for (int i = 0; i < c_rib; i++) {
		if (file.eof()) {
			std::cout << "Error! EOF until end of reading\n";
			system("pause");
			file.close();
			return -2;
		}
		std::getline(file, str[i]);
	}
	file.close();
	return 0;
}


void filling_the_structure(int c_rib, Arc*& arcs, std::string*& str) {
	for (int i = 0; i < c_rib; i++) {
		int j = 0;
		std::string temp2;
		std::string temp3;
		temp2 = str_frag(str[i], j);
		for (int q = 0; q < temp2.size(); q++) {
			if (temp2[q] == '-')
				continue;
			if (temp2[q] == ',') {
				arcs[i].prev.push_back(stoi(temp3) - 1);
				temp3.clear();
				continue;
			}
			temp3 = temp3 + temp2[q];
			if (q == temp2.size() - 1)
				arcs[i].prev.push_back(stoi(temp3) - 1);
		}
		j++;
		arcs[i].std_time = std::stoi(str_frag(str[i], j));
		j++;
		arcs[i].min_time = std::stoi(str_frag(str[i], j));
		j++;
		arcs[i].std_cost = std::stoi(str_frag(str[i], j));
		j++;
		arcs[i].min_cost = std::stoi(str_frag(str[i], j));
	}
}


void graph_building(Arc*& arcs, Point*& points, int MSize, int c_rib) {
	int k = 0;
	int count = 0;
	//Определение начальной вершины каждой дуги
	for (int i = 0; i < c_rib; i++) {
		if (k == MSize)
			break;

		bool flag2 = false;
		for (int b = 0; b < k; b++)
			for (int q = 0; q < points[b].start_of_arc.size(); q++)
				if (i == points[b].start_of_arc[q])
					flag2 = true;
		if (flag2)
			continue;

		points[k].start_of_arc.push_back(i);
		arcs[i].start_point = k;
		for (int j = i + 1; j < c_rib; j++)
			if (arcs[i].prev == arcs[j].prev) {
				count++;
				points[k].start_of_arc.push_back(j);
				arcs[j].start_point = k;
			}
		count = 0;
		k++;
	}

	//Определение конечной вершины у каждой дуги
	for (int i = c_rib - 1; i >= 0; i--) {
		if (arcs[i].prev.size() != 0) {
			for (int j = 0; j < arcs[i].prev.size(); j++) {
				bool flag = false;
				arcs[arcs[i].prev[j]].end_point = arcs[i].start_point;
				for (int k = 0; k < points[arcs[i].start_point].end_of_arc.size(); k++)
					if (arcs[i].prev[j] == points[arcs[i].start_point].end_of_arc[k])
						flag = true;
				if (!flag)
					points[arcs[i].start_point].end_of_arc.push_back(arcs[i].prev[j]);
			}
		}
	}
	for (int i = 0; i < c_rib; i++) {
		if (arcs[i].end_point == -1) {
			arcs[i].end_point = MSize - 1;
			points[MSize - 1].end_of_arc.push_back(i);
		}
	}
}


void critical_path(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration) {
	//Раньше срока
	points[0].time_early = 0;
	for (int i = 1; i < MSize; i++) {
		std::vector<int> temp;
		for (int j = 0; j < points[i].end_of_arc.size(); j++) {
			temp.push_back(points[arcs[points[i].end_of_arc[j]].start_point].time_early + arcs[points[i].end_of_arc[j]].min_time);
		}
		if (points[i].end_of_arc.size() == 1)
			points[i].time_early = temp.back();
		else
			points[i].time_early = std::max(temp[0], temp[1]);
	}

	//Позже срока
	points[MSize - 1].time_late = points[MSize - 1].time_early;
	for (int i = MSize - 2; i >= 0; i--) {
		std::vector<int> temp;
		for (int j = 0; j < points[i].start_of_arc.size(); j++) {
			temp.push_back(points[arcs[points[i].start_of_arc[j]].end_point].time_late - arcs[points[i].start_of_arc[j]].min_time);
		}
		if (points[i].start_of_arc.size() == 1)
			points[i].time_late = temp.back();
		else
			points[i].time_late = std::min(temp[0], temp[1]);
	}

	//Резерв
	for (int i = 0; i < MSize; i++) {
		points[i].reserve = points[i].time_late - points[i].time_early;
		if (points[i].reserve == 0)
			Crit_Path_Points.push_back(i);
	}

	for (int i = 0; i < Crit_Path_Points.size() - 1; i++) {
		for (int j = 0; j < points[Crit_Path_Points[i]].start_of_arc.size(); j++) {
			for (int q = i + 1; q < Crit_Path_Points.size(); q++) {
				if (arcs[points[Crit_Path_Points[i]].start_of_arc[j]].end_point == Crit_Path_Points[q]) {
					Crit_Path_Arcs.push_back(points[Crit_Path_Points[i]].start_of_arc[j]);
					//duration = duration + arcs[points[Crit_Path_Points[i]].start_of_arc[j]].min_time;
				}
			}
		}
	}
	duration = points[Crit_Path_Points.back()].time_early;
}


void optimization(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration, int c_rib) {
	std::vector<int> Not_in_CP;
	int cost;
	int temp_duration = 0;
	critical_path(arcs, points, Crit_Path_Points, Crit_Path_Arcs, MSize, duration);
	std::cout << "Critical path: ";
	for (int i = 0; i < Crit_Path_Arcs.size(); i++) {
		std::cout << Crit_Path_Arcs[i] << " ";
	}
	std::cout << "\n";
	std::cout << "Min duration of work:" << duration << "\n";
	cost = 0;
	for (int i = 0; i < Crit_Path_Arcs.size(); i++)
		cost = arcs[Crit_Path_Arcs[i]].min_cost + cost;
	std::cout << "Cost:" << cost << "\n";
	for (int i = 0; i < c_rib; i++) {
		bool flag = false;
		for (int j = 0; j < Crit_Path_Arcs.size(); j++) {
			if (i == Crit_Path_Arcs[j]) {
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		else
			Not_in_CP.push_back(i);
	}
	std::vector<int> def;
	for (int i = 0; i < Not_in_CP.size(); i++)
		def.push_back(arcs[Not_in_CP[i]].min_cost - arcs[Not_in_CP[i]].std_cost);

	for (int i = 0; i < def.size() - 1; i++) {
		for (int j = 0; j < def.size() - 1; j++)
			if (def[j] > def[j + 1]) {
				int temp = def[j];
				def[j] = def[j + 1];
				def[j + 1] = temp;
				temp = Not_in_CP[j];
				Not_in_CP[j] = Not_in_CP[j + 1];
				Not_in_CP[j + 1] = temp;
			}
	}
	std::cout << "Works outside the critical path\n";
	for (int i = 0; i < Not_in_CP.size(); i++) {
		std::cout << Not_in_CP[i] << " ";
	}
	std::cout << "\n";
	Arc* copy_arcs = new Arc[c_rib];
	Point* copy_points = new Point[MSize];
	for (int i = 0; i < c_rib; i++) {
		copy_arcs[i].prev = arcs[i].prev;
		copy_arcs[i].std_time = arcs[i].std_time;
		copy_arcs[i].min_time = arcs[i].min_time;
		copy_arcs[i].std_cost = arcs[i].std_cost;
		copy_arcs[i].min_cost = arcs[i].min_cost;
		copy_arcs[i].start_point = arcs[i].start_point;
		copy_arcs[i].end_point = arcs[i].end_point;
	}
	for (int i = 0; i < MSize; i++) {
		copy_points[i].start_of_arc = points[i].start_of_arc;
		copy_points[i].end_of_arc = points[i].end_of_arc;
	}
	std::cout << "\n*****************Optimization*****************\n";
	while (Not_in_CP.size() != 0) {
		std::vector<int> Temp_Crit_Path_Points;
		std::vector<int> Temp_Crit_Path_Arcs;
		for (int i = 0; i < MSize; i++) {
			copy_points[i].time_early = -1;
			copy_points[i].time_late = -1;
			copy_points[i].reserve = -1;
		}
		temp_duration = 0;
		copy_arcs[Not_in_CP.back()].min_time = copy_arcs[Not_in_CP.back()].std_time;
		critical_path(copy_arcs, copy_points, Temp_Crit_Path_Points, Temp_Crit_Path_Arcs, MSize, temp_duration);
		std::cout << "\nCritical path: ";
		for (int i = 0; i < Temp_Crit_Path_Arcs.size(); i++) {
			std::cout << Temp_Crit_Path_Arcs[i] << " ";
		}
		std::cout << "\n";
		std::cout << "Duration of work:" << temp_duration << "\n";
		cost = 0;
		for (int i = 0; i < Crit_Path_Arcs.size(); i++)
			cost = arcs[Crit_Path_Arcs[i]].min_cost + cost;
		std::cout << "Cost:" << cost << "\n";
		if (temp_duration != duration) {
			std::cout << "The time of the " << Not_in_CP.back() << " work cannnot be increased\n";
			copy_arcs[Not_in_CP.back()].min_time = arcs[Not_in_CP.back()].min_time;
			Not_in_CP.pop_back();
		}
		else {
			Crit_Path_Points = Temp_Crit_Path_Points;
			Crit_Path_Arcs = Temp_Crit_Path_Arcs;
			arcs[Not_in_CP.back()].min_cost = arcs[Not_in_CP.back()].std_cost;
			std::cout << "The time of the " << Not_in_CP.back() << " work can be increased\n";
			Not_in_CP.pop_back();
		}
	}
}