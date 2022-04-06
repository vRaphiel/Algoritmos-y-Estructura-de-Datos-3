#include <vector>
#include <list>
using namespace std;

typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) :
            dst(d), peso(p) {}
};
struct Salida{
    int N;
    int costoSol;
    vector<int> ordenVertices;
};

typedef vector<vector<Vecino>> Grafo;
