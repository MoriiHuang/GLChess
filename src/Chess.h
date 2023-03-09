#pragma once
#include<vector>
#define Chess_Row 13
#define Chess_Col 13
bool flag_man=0;
bool flag_ai=0;
bool start_switch=0;
bool ai_win=0;
bool man_win=0;
std::vector<std::vector<int> > Init_Chess(){
	std::vector<std::vector<int> > Chess_Map;
	for(int i=0;i<Chess_Col;i++){
		std::vector<int> Row;
		for(int i=0;i<Chess_Row;i++){
			Row.push_back(0);
		}
		Chess_Map.push_back(Row);
	}
	return Chess_Map;
}
std::vector<std::vector<int> > Chess_Map = Init_Chess();
