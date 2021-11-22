#include <iostream>
#include <string>
#include <vector>
#include "Func.h"


int main()
{
	unsigned int MSize = 0;									//Number of points
	std::vector<int> Crit_Path_Points;						//Critical path by points
	std::vector<int> Crit_Path_Arcs;						//Critical path by arcs
	int duration = 0;										//Project duration
	int c_rib = 0;											//Number of arcs
	int cost = 0;											//Project cost
	std::string* str;										//String for input
	Arc* arcs;												//Arcs array
	Point* points;											//Points array
	//Reading the input file
	file_read(str, c_rib);
	arcs = new Arc[c_rib];

	//Getting arcs from a string
	filling_the_structure(c_rib, arcs, str);
	MSize = c_rib + 1;
	delete[] str;

	//Getting points from arcs
	for (int i = 0; i < c_rib - 1; i++) {
		for (int j = i + 1; j < c_rib; j++)
			if (arcs[i].prev == arcs[j].prev)
				MSize--;
	}
	points = new Point[MSize];
	//Graph creation
	graph_building(arcs, points, MSize, c_rib);

	//Graph optimization
	optimization(arcs, points, Crit_Path_Points, Crit_Path_Arcs, MSize, duration, c_rib);
	cost = 0;
	for (int i = 0; i < Crit_Path_Arcs.size(); i++)
		cost = arcs[Crit_Path_Arcs[i]].min_cost + cost;
	std::cout << "\nDuration of work:" << duration << "\n";
	std::cout << "Final cost " << cost << "\n";
	system("pause");
	return 0;
}