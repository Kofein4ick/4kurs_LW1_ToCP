#include <iostream>
#include <string>
#include <vector>
#include "Structures.h"
#include "Func.h"


int main()
{
	unsigned int MSize = 0;
	std::vector<int> Crit_Path_Points;
	std::vector<int> Crit_Path_Arcs;
	int duration = 0;
	int c_rib = 0;
	int cost = 0;
	std::string* str;
	Arc* arcs;
	Point* points;
	//Читаем файл
	file_read(str, c_rib);
	arcs = new Arc[c_rib];

	//Разбиваем строку, заносим в структуру
	filling_the_structure(c_rib, arcs, str);
	MSize = c_rib + 1;
	delete[] str;

	//Рассчёт кол-ва узлов(подсчёт кол-ва строк без повторений+1(для последней дуги))
	for (int i = 0; i < c_rib - 1; i++) {
		for (int j = i + 1; j < c_rib; j++)
			if (arcs[i].prev == arcs[j].prev)
				MSize--;
	}
	points = new Point[MSize];
	graph_building(arcs, points, MSize, c_rib);

	//Оптимизация сети
	optimization(arcs, points, Crit_Path_Points, Crit_Path_Arcs, MSize, duration, c_rib);
	cost = 0;
	for (int i = 0; i < Crit_Path_Arcs.size(); i++)
		cost = arcs[Crit_Path_Arcs[i]].min_cost + cost;
	std::cout << "\nDuration of work:" << duration << "\n";
	std::cout << "Final cost " << cost << "\n";
	//График Ганта
	system("pause");
	return 0;
}


std::string str_frag(std::string str, int& pos) {
	std::string temp;
	while ((str[pos] != '\t')&&(str[pos] != '\0')) {
		temp = temp + str[pos];
		pos++;
	}
	return(temp);
}
