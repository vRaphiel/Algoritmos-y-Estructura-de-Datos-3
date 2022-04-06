#include "extras.h"

using namespace std;

Salida heurGolosaConstructiva(Grafo& g);
Salida heurAGM(Grafo& grafo);
Salida busquedaLocal(Grafo& g);
Salida tabu(Grafo& g,int cantIteraciones, int tamanioMemo, int tipoMemo, int subvecindad);