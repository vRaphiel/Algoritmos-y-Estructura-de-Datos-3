#include <iostream>
#include <cmath>
#include "extras.h"
using namespace std;

bool estaAgregadoPrim(Vertice& v, vector<int>& vertices){
    bool esta = false;
    for(int i = 1; i < vertices.size(); i++){
        if(vertices[i] == v) esta=true;
    }
    return esta;
}

bool estaAgregado(Vertice& v, vector<int>& vertices){
    bool esta = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i] == v) esta=true;
    }
    return esta;
}

vector<int> memoPos(list<vector<int>>& _memo, int& _i){
    list<vector<int>>::iterator it = _memo.begin();
    for(int i = 0; i < _i; i++){
        ++it;
    }
    return *it;
}

bool noEstaEnMemo(list<vector<int>>& memo, vector<int>& vecino, vector<int>& solAnterior, int& tipoMemo, vector<int>& swap){
    if(memo.empty()) return true;
    auto it = memo.begin();
    bool resp = true;
    int i=0;
    while(resp && i<memo.size()){
        if(tipoMemo==0){
            if (*it == vecino){
                resp=false;
            }
        }else{
            if (*it == swap){
                resp=false;
            }
        }
        ++it;
        i++;
    }
    return resp;

}

bool todosVisitados(vector<bool>& visitas){
    bool visitados = true;
    for(int i = 1; i < visitas.size(); i++){
        if(!visitas[i]){
            visitados = false;
        }
    }
    return visitados;
}

vector<int> PrimMST(Grafo& g) {
    int INFTY = 10e6;
    Grafo s;
    vector<int> padre(g.size(), 0);
    vector<bool> visitados(g.size(), false);
    vector<int> distancia(g.size(), INFTY);

    // Siempre inicia en 1
    int nodoActual = 1;

    // Recorrer los vecinos de nodoActual
    for (int i = 1; i < g[nodoActual].size(); i++) {
        distancia[i]  = g[nodoActual][i].peso;
        padre[i] = nodoActual;
    }

    // Para cada vecino del nodo i
    // NodoActual = 1 => vecinos de 1
    // Recorremos vecinos(1) {2, 3, 4} => Posicion 0 porque en vecinos(1)[0] = 2
    // Distancia(vecinos(1)[0]) = distancia(2) = 20. nodoActual es 1

    distancia[nodoActual] = 0;
    visitados[nodoActual] = true;


    while (!todosVisitados(visitados)) {

        int distanciaCandidata = INFTY;
        int candidato = 0;

        for (int i = 1; i < distancia.size(); ++i) {
            if (distancia[i] < distanciaCandidata && !visitados[i]) {
                distanciaCandidata = distancia[i];
                candidato = i ;
            }
        }

        visitados[candidato] = true;

        for (int i = 0; i < g[candidato].size(); ++i) {

            // Comparar solo si el nodo no está en la lista de padre
            bool estaAgregado = !estaAgregadoPrim(g[candidato][i].dst, padre);

            if (estaAgregado && distancia[g[candidato][i].dst] > g[candidato][i].peso) {

                distancia[g[candidato][i].dst] = g[candidato][i].peso;
                padre[g[candidato][i].dst] = candidato;

            }

        }

    }
    return padre;
}

Grafo aristasAGM(vector<int>& padre){
    // En primera componente esta el padre, en segunda componente el hijo
    // (a, b) donde b es hijo de a
    Grafo grafo(padre.size());

    for (int i = 2; i < padre.size() ; ++i) {
        grafo[i].push_back(Vecino(padre[i], 0));
        grafo[padre[i]].push_back(Vecino(i, 0));
    }

    return grafo;
}

vector<int> recorridoDFS(Grafo& grafo){

    vector<int> recorrido;
    vector<bool> visitados(grafo.size(), false);
    int raiz=1;
    //La raiz empieza en 1;

    recorridoDFSAux(recorrido,visitados,grafo,raiz);
    return recorrido;

}

void recorridoDFSAux(vector<int>& recorrido, vector<bool>& visitados, Grafo& grafo, int& nodo){
    if(!todosVisitados(visitados)){
        if(!visitados[nodo]){
            visitados[nodo] = true;
            recorrido.push_back(nodo);
        }
        for(int i = 0; i < grafo[nodo].size(); i++){
            // Para cada vecino del nodo, veo si este no está visitado
            if(!visitados[grafo[nodo][i].dst]){
                recorridoDFSAux(recorrido, visitados, grafo, grafo[nodo][i].dst);
            }
        }
    }
}


/*
 * Arbol ejemplo:
        1
       / \
      2   4
     / \
    3   5
   /
  9
*/

// Complejidad = O(|camino|) = O(|V| - 1) = O(|V|)
int costoSolucion(Grafo& grafo, vector<int>& camino){
    int solucion = 0;

    for(int i = 0; i < camino.size()-1; i++){
        for (int j = 0; j < grafo[camino[i]].size(); ++j) {
            if(grafo[camino[i]][j].dst==camino[i+1]){
                solucion+=grafo[camino[i]][j].peso;
            }
        }
    }
    // Caso dfs.size
    // Me quiero conectar con el padre
    for(int i = 0; i < grafo[camino[camino.size()-1]].size(); i++){
        if(grafo[camino[camino.size()-1]][i].dst == camino[0]){
            solucion += grafo[camino[camino.size()-1]][i].peso;
        }
    }
    return solucion;
}

vector<vector<int>> obtenerSubvecindad(Salida& sol, int subvecindad) {
    vector<vector<int>> vecinos;
    Salida opt = sol;
    Salida local = sol;
    int cambio = 0;

    for (int i = 0; i < sol.ordenVertices.size() - 1; ++i) {
        //empieza con [i+1] [i+2] y swapea con [i+3] [i+4] -> [i+1][i+3]   [i+2][i+4]
        //sigue con [i+1] [i+2] y swapea con [i+4] [i+5]
        for (int j = i; j < sol.ordenVertices.size() - 2; ++j) {//AB CD -> AC BD
            cambio = local.ordenVertices[i + 1];
            local.ordenVertices[i + 1] = local.ordenVertices[j + 2];
            local.ordenVertices[j + 2] = cambio;

            vecinos.push_back(local.ordenVertices);
            local = sol;
        }
    }
    //int midPos = vecinos.size() / 2;
    vector<vector<int>> vecinosDevolucion;

    //vecinosDevolucion.push_back(vecinos[midPos]);
    float limiteDoub = 0;

    float division = float(subvecindad) / float(100);

    if(subvecindad>50) {
        limiteDoub = vecinos.size() - division * vecinos.size() ;
    } else {
        limiteDoub = division * vecinos.size() ;
    }

    int limite = (int) limiteDoub;
    if(subvecindad!=100){
        limite++;
    }
    vector<int> pseudoMemo(vecinos.size(),0);

    while(limite>0) {
        int j = rand() % (vecinos.size()-1);
        if(pseudoMemo[j]==0) {
            pseudoMemo[j] = 1;
            limite--;
        }
    }

    for (int i = 0; i < vecinos.size(); ++i) {
        if (subvecindad>50){
            if(pseudoMemo[i]==0){
                vecinosDevolucion.push_back(vecinos[i]);
            }
        } else {
            if (pseudoMemo[i]==1){
                vecinosDevolucion.push_back(vecinos[i]);
            }
        }
    }

/*
    float cantidad = subvecindad/100;
    int random = cantidad*vecinos.size();
    int randomDivideTwo = random/2;

    cout<<"midPos " << midPos<<" random "<<random << " randomDivideTwo" << randomDivideTwo << endl;
    for(int i = 1; i < randomDivideTwo; i++){
        vecinosDevolucion.push_back(vecinos[midPos-i]);
        vecinosDevolucion.push_back(vecinos[midPos+i]);
    }
*/

    return vecinosDevolucion;
}

Salida obtenerMejor(vector<vector<int>>& vecinos, list<vector<int>>& memo, int tipoMemo, vector<int>& solAnterior, Grafo& g,int tamanioMemo){
    int mejor=10e6;
    int mejorOrden=0;
    vector<int> swap={};
    vector<int> mejorSwap={};

    /*
    for (int i = 0; i < vecinos.size(); ++i) {
        int sol= costoSolucion(g,vecinos[i]);
        if (sol<mejor){
            mejor=sol;
            mejorOrden=i;
        }
    }
     */


    if (tipoMemo==0){
        for (int i = 0; i < vecinos.size(); ++i) {
            if (noEstaEnMemo(memo,vecinos[i],solAnterior, tipoMemo, swap)){
                int sol= costoSolucion(g,vecinos[i]);
                if (sol<mejor){
                    mejor=sol;
                    mejorOrden=i;
                }
            }
        }
        if(memo.size()<tamanioMemo){
            memo.push_back(vecinos[mejorOrden]);
        }else{
            if(tamanioMemo != 0){
                memo.pop_front();
                memo.push_back(vecinos[mejorOrden]);
            }
        }
    }else{           //si tipoMemo es de swap entonces por cada vecino calcula que swap tuvo, y se fija en memoria si ya hizo ese movimiento

        for (int i = 0; i < vecinos.size(); ++i) {
            swap={};
            for (int j = 0; j < solAnterior.size(); ++j){
                if (solAnterior[j]!=vecinos[mejorOrden][j]){
                    swap.push_back(solAnterior[j]);
                }
            }
            if (noEstaEnMemo(memo, vecinos[i],solAnterior, tipoMemo,swap)){
                int sol= costoSolucion(g,vecinos[i]);
                if (sol<mejor){
                    mejor=sol;
                    mejorOrden=i;
                    mejorSwap=swap;
                }
            }
        }
        if (memo.size()<tamanioMemo){
            memo.push_back(mejorSwap);
        }else{
            if(tamanioMemo != 0){
                memo.pop_front();
                memo.push_back(mejorSwap);
            }
        }

    }
    Salida sal;
    if(mejor==10e6){ //si no encontro un "mejor" devuelve el anterior otra vez
        sal.ordenVertices=solAnterior;
        sal.N=solAnterior.size();
        sal.costoSol= costoSolucion(g,solAnterior);
    }else{
        sal.ordenVertices=vecinos[mejorOrden];
        sal.N=solAnterior.size();
        sal.costoSol=mejor;
    }

    return sal;
}