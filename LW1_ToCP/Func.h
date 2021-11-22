#include <string>
#include <vector>
#include "Structures.h"

std::string str_frag(std::string str, int& pos);
int file_read(std::string*& str, int& c_rib);
void filling_the_structure(int c_rib, Arc*& arcs, std::string*& str);
void graph_building(Arc*& arcs, Point*& points, int MSize, int c_rib);
void critical_path(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration);
void optimization(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration, int c_rib);
