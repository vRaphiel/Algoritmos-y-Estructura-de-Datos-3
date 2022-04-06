#include "tipos.h"

bool estaAgregadoPrim(Vertice& v, vector<int>& vertices);
bool estaAgregado(Vertice& v, vector<int>& vertices);
bool todosVisitados(vector<bool>& visitas);
vector<int> PrimMST(Grafo& g);
Grafo aristasAGM(vector<int>& padre);
vector<int> recorridoDFS(Grafo& grafo);
void recorridoDFSAux(vector<int>& recorrido, vector<bool>& visitados, Grafo& grafo, int& nodo);
int costoSolucion(Grafo& grafo, vector<int>& camino);


vector<vector<int>> obtenerSubvecindad(Salida& sol, int subvecindad);
Salida obtenerMejor(vector<vector<int>>& vecinos, list<vector<int>>& memo,int tipoMemo, vector<int>& solAnterior, Grafo& g, int tamanioMemo);
bool noEstaEnMemo(list<vector<int>>& memo, vector<int>& vecino, vector<int>& solAnterior, int& tipoMemo, vector<int>& swap);
vector<int> memoPos(list<vector<int>>& _memo, int& _i);