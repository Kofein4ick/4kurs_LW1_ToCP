#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Structures.h"

std::string str_frag(std::string str, int& pos);
int file_read(std::string*& str, int& c_rib);

int main()
{
	unsigned int MSize = 0;
	unsigned int** Matrix;
	int c_rib=0;
	int count = 0;
	std::string* str;
	Arc* arcs;
	Point* points;
	//Читаем файл
	file_read(str, c_rib);
	arcs = new Arc[c_rib];
	//Разбиваем строку, заносим в объект
	for (int i = 0; i < c_rib; i++){
		int j = 0;
		std::string temp2;
		std::string temp3;
		temp2 = str_frag(str[i], j);
		for (int q = 0; q < temp2.size(); q++) {
			if (temp2[q] == '-')
				continue;
			if (temp2[q] == ',') {
				arcs[i].prev.push_back(stoi(temp3)-1);
				temp3.clear();
				continue;
			}
			temp3 = temp3 + temp2[q];
			if (q == temp2.size() - 1)
				arcs[i].prev.push_back(stoi(temp3)-1);
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
	count = c_rib+1;
	delete[] str;
	//Рассчёт кол-ва узлов(подсчёт кол-ва строк без повторений+1(для последней дуги))
	for (int i = 0; i < c_rib-1; i++) {
		for (int j = i+1; j < c_rib; j++)
			if (arcs[i].prev == arcs[j].prev)
				count--;
	}
	MSize = count;
	points = new Point [MSize];
	count = 0; int k = 0;
	//Определение начальной вершины каждой дуги
	for (int i = 0; i < c_rib; i++) {
		if (k == MSize)
			break;

		bool flag2 = false;
		for(int b = 0; b < k; b++)
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
	std::cout << "start_of_arc:\n";
	for (int i = 0; i < MSize; i++) {
		std::cout << "point: "<<i<<"\t";
		for (int j = 0; j < points[i].start_of_arc.size(); j++)
			std::cout << points[i].start_of_arc[j]<<" ";
		std::cout << "\n";
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


	std::cout << "end_of_arc:\n";
	for (int i = 0; i < MSize; i++) {
		std::cout << "point: " << i << "\t";
		for (int j = 0; j < points[i].end_of_arc.size(); j++)
			std::cout << points[i].end_of_arc[j] << " ";
		std::cout << "\n";
	}
	std::cout << "start_point:\n";
	for (int i = 0; i < c_rib; i++) {
		std::cout << "arc: " << i << "\t";
		std::cout << arcs[i].start_point << "\n";
	}
	std::cout << "end_point:\n";
	for (int i = 0; i < c_rib; i++) {
		std::cout << "arc: " << i << "\t";
		std::cout << arcs[i].end_point << "\n";
	}
	//Оптимизация сети
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
	str=new std::string[c_rib];
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