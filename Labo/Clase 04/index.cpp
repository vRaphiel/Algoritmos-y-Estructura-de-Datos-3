#include <vector>
#include <iostream>
#include <climits>
#include <set>
#include<algorithm> // std::min

using namespace std;
int main(int argc, char const *argv[])
{
     
    return 0;
}

typedef int Vertice;
typedef int Peso;

struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) :
        dst(d), peso(p) {}
};

typedef vector<vector<Vecino>> Grafo;

Grafo leerGrafo(int& v0){
    int n, m;
    cin >> n >> m >> v0;

    Grafo G(n, vector<Vecino>());
    for(int i = 0; i < m; i ++){
        int v, w, peso;
        cin >> v >> w >> peso;
        G[v].push_back(Vecino(w, peso));
        G[w].push_back(Vecino(v, peso));
    }
    return G;
}

const Peso INFTY = INT_MAX;

Peso suma(Peso p, Peso q){
    if (p == INFTY || q == INFTY){
        return INFTY;
    }else{
        return p + q;
    }
}

vector<Peso> Dijkstra(Grafo G, Vertice v0){
    int n = G.size();
    vector<Peso> dist = vector<Peso>(n, INFTY);
    set<Vertice> pendientes;
    for(int i = 0; i < n; i++){ pendientes.insert(i);}
    dist[v0] = 0;
    while( pendientes.size() > 0){
        Vertice v = *pendientes.begin();
        for(Vertice w : pendientes){
            if(dist[w] < dist[v]) { v = w; }
        }
        pendientes.erase(v);
        for(Vecino e : G[v]){
            dist[e.dst] = min(dist[e.dst], suma(dist[v], e.peso));
        }
    }
    return dist;
}

typedef pair<Peso, Vertice> Pendiente;

vector<Peso> DijkstraOpt(Grafo G, Vertice v0){
    int n = G.size();
    vector<Peso> dist = vector<Peso>(n, INFTY);
    dist[v0] = 0;
    set<Pendiente> cola;
    for(int i = 0; i < n; i++){ 
        cola.insert(Pendiente(dist[i], i));
    }
    while( cola.size() > 0){
        Pendiente p = *cola.begin();
        cola.erase(p);
        Vertice v = p.second;
        for(Vecino e : G[v]){
            Peso dist2 = suma(dist[v], e.peso);
            if(dist[e.dst] > dist2){
                cola.erase(Pendiente(dist[e.dst], e.dst));
                dist[e.dst] = dist2;
                cola.insert(Pendiente(dist[e.dst], e.dst));
            }
        }
    }
    return dist;
}

vector<Peso> DijkstraOptGetCamMin(Grafo G, Vertice v0, vector<Vertice>& pred){
    int n = G.size();
    vector<Peso> dist = vector<Peso>(n, INFTY);
    dist[v0] = 0;
    pred = vector<Vertice>(n, -1);
    set<Pendiente> cola;
    for (int i = 0; i < n; i++)
    {
        cola.insert(Pendiente(dist[i], i));
    }
    while (cola.size() > 0)
    {
        Pendiente p = *cola.begin();
        cola.erase(p);
        Vertice v = p.second;
        for (Vecino e : G[v])
        {
            Peso dist2 = suma(dist[v], e.peso);
            if (dist[e.dst] > dist2)
            {
                cola.erase(Pendiente(dist[e.dst], e.dst));
                dist[e.dst] = dist2;
                pred[e.dst] = v;
                cola.insert(Pendiente(dist[e.dst], e.dst));
            }
        }
    }
    return dist;
}

vector<Peso> BellmanFord(Grafo G, Vertice v0){
    int n = G.size();
    vector<Peso> dist = vector<Peso>(n, INFTY);
    dist[v0] = 0;
    bool cambio = true;
    while(cambio){
        cambio = false;
        for(Vertice v = 0; v < n; v++){
            for(Vecino e : G[v]){
                Peso dist2 = suma(dist[v], e.peso);
                if(dist[e.dst] > dist2){
                    cambio = true;
                    dist[e.dst] = dist2;
                }
            }
        }
    }
    return dist;
}