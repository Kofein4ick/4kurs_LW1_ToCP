#include <string>
#include <vector>
#include "Structures.h"

//String fragmentation function
std::string str_frag(std::string str, int& pos);
//Input file read function
int file_read(std::string*& str, int& c_rib);
//Function for getting arcs from a string
void filling_the_structure(int c_rib, Arc*& arcs, std::string*& str);
//Graph creation function
void graph_building(Arc*& arcs, Point*& points, int MSize, int c_rib);
//Critical path search function
void critical_path(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration);
//Graph optimization function
void optimization(Arc*& arcs, Point*& points, std::vector<int>& Crit_Path_Points, std::vector<int>& Crit_Path_Arcs, int MSize, int& duration, int c_rib);
