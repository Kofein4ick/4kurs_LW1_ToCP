#include <iostream>
#include <fstream>
#include <string>
#include "Work.h"

std::string str_frag(std::string str, int& pos);
int file_read(std::string*& str, int& c_rib);

int main()
{
	unsigned int MSize = 0;
	unsigned int** Matrix;
	int c_rib=0;
	int count = 0;
	std::string* str;
	Work* cl_w;
	//Читаем файл
	file_read(str, c_rib);

	cl_w = new Work[c_rib];
	//Разбиваем строку, заносим в объект
	for (int i = 0; i < c_rib; i++){
		int j = 0;
		cl_w[i].prev = str_frag(str[i], j);
		j++;
		cl_w[i].std_time = std::stoi(str_frag(str[i], j));
		j++;
		cl_w[i].min_time = std::stoi(str_frag(str[i], j));
		j++;
		cl_w[i].std_cost = std::stoi(str_frag(str[i], j));
		j++;
		cl_w[i].min_cost = std::stoi(str_frag(str[i], j));
	}

	//Рассчёт кол-ва узлов(подсчёт кол-ва строк без повторений+1(для последней дуги))
	//MSize = count + 2;
	//Создание самой сети(заполнение матрицы)
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