#include <iostream>
#include <vector>

using namespace std;
#ifndef TP_MAIN_H
#define TP_MAIN_H

void BTauxConPodas(vector<pair<int, int>> &negocios, int i, int g, int c, const vector<int> &missingSum);
void BTconPodas(vector<pair<int, int>>&negocios);

void BTauxSinPodas(vector<pair<int, int>> &negocios, int i, int g, int c);
void BTsinPodas(vector<pair<int, int>>&negocios);

void FBaux(vector<pair<int, int>>&negocios, int i, int g, int c,bool consecutivoPuedeAbrir);
void FB(vector<pair<int, int>>&negocios);

int PDaux(vector<vector<int>> &T, vector<pair<int, int>> &negocios, int i, int c);
int PD(vector<pair<int, int>> &negocios);


#endif //TP_MAIN_H
