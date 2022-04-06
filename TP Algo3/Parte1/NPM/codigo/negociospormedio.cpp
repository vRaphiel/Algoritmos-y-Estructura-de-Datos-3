#include "negociospormedio.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
#include <map>

using namespace std;

/**
 * M es el contagio total que puedo tener
 * n es el tamanio del arreglo de negocios
 * negocios_input es el arreglo de negocios
 * Los negocios estan internamente representados con tuplas
 * */
int M = 0;
int n = 0;
vector<pair<int, int>> negocios_input;
int ganancia_final = 0;

/**
 * Los metodos de BT estan representados con:
 * BTconPodas donde se implementa poda por optimalidad y factiblidad
 * BTsinPodas donde se implementa poda por factibilidad
 *
 * Estos incluyen sus funciones auxiliares propias
 * */
void BTconPodas(vector<pair<int, int>>& negocios){
    ganancia_final=0;

    vector<int> missingSum(negocios.size(),0);
    for (int i = 0; i < negocios.size(); ++i) {
        for (int j = 0; j < i+1; ++j) {
            missingSum[j]+=negocios[i].first;
        }
    }

    BTauxConPodas(negocios,0,0,0, missingSum);
}

void BTsinPodas(vector<pair<int, int>>& negocios){
    ganancia_final=0;
    BTauxSinPodas(negocios,0,0,0);
}

/**
 * Tenemos un vector de negocios
 * n = negocios
 * i = posicion_actual
 * j = posicion_movimiento
 * c = contagio_parcial
 * g = ganancia_parcial
 *
 * En BTAuxConPodas (poda por optimalidad)
 * missingSum es el arreglo de ganancias posibles desde i en adelante
 */

void BTauxConPodas(vector<pair<int, int>> &negocios, int i, int g, int c, const vector<int> &missingSum){
    if( i < negocios.size()){
        if(c + negocios[i].second > M){
            // Hay mucho contagio para agregar el negocio
            BTauxConPodas(negocios, i+1, g, c, missingSum);
        }else if(g+missingSum[i]>ganancia_final) {
            // Poda por optimalidad
            // Agrego negocio
            ganancia_final = max(g+negocios[i].first, ganancia_final);
            BTauxConPodas(negocios, i+2, g+negocios[i].first, c+negocios[i].second, missingSum);
            BTauxConPodas(negocios, i+1, g, c, missingSum);
        }
        // No agrego el negocio, sigo
    }
}

// Analogo al anterior salvo que sin poda por optimalidad
void BTauxSinPodas(vector<pair<int, int>> &negocios, int i, int g, int c){
    if( i < negocios.size()){
        if(c + negocios[i].second > M){
            BTauxSinPodas(negocios, i+1, g, c);
        } else {
            ganancia_final = max(g+negocios[i].first, ganancia_final);
            BTauxSinPodas(negocios, i+2, g+negocios[i].first, c+negocios[i].second);
            BTauxSinPodas(negocios, i+1, g, c);
        }
    }
}

/**
 * FB - Fuerza Bruta
 * negocios = arreglo de negocios
 * */
void FB(vector<pair<int, int>> &negocios){
    ganancia_final=0;
    FBaux(negocios,0,0,0,true);
}

/**
 * FBAux recibe
 * locales = arreglo de locales
 * i = indice que apunta al local
 * g = ganancia acumulada
 * c = contagio acumulado
 * consecutivoPuedeAbrir = indica si el negocio consecutivo puede abrir o no
 * */
void FBaux(vector<pair<int, int>>& negocios, int i, int g, int c,bool consecutivoPuedeAbrir){
    if(i==negocios.size()) {
        //Entre todas las soluciones me quedo con la que mas ganancia genera y cumple con la restriccion de contagiosidad
        if(c <= M && g > ganancia_final){
            ganancia_final = g;
        }
        return;
    }
    // No agrega el negocio
    if(consecutivoPuedeAbrir){
        FBaux(negocios, i+1, g+negocios[i].first, c + negocios[i].second,false);
    }
    FBaux(negocios,  i+1, g, c,true);
    // Agrega el negocio
}

/**
 * PD = DP = Programacion Dinamica (Dynamic Programming)
 * negocios = arreglo de negocios
 * T = matriz de memoizacion
 * */
int PD(vector<pair<int, int>> &negocios, vector<vector<int>> &T){
    ganancia_final = 0;
    return PDaux(T,negocios,0,M);
}

/**
 * T = es la matriz de memoizacion
 * negocios = arreglo de negocios
 * i = indice del local actual
 * c = contagio restante
 * */
int PDaux(vector<vector<int>> &T, vector<pair<int, int>> &negocios, int i, int c){
    if(i >= negocios.size()){
        return 0;
    }
    if(T[i][c]==-1){
        // Agregamos al local y seguimos desde siguiente no consecutivo
        if(c >= negocios[i].second){
            T[i][c] = max(
                            // Ganancia tras no agregar el local
                            PDaux(
                                    T,
                                    negocios,
                                    i+1,
                                    c),

                            // Ganancia tras agregar el local
                            negocios[i].first + PDaux(
                                    T,
                                    negocios,
                                    i+2,
                                    c-negocios[i].second));
        }else{
            T[i][c] = PDaux(T,negocios,i+1,c);
        }
    }
    return T[i][c];
}

/**
 * Funcion principal. Recibe como entrada el tipo de algoritmo a utilizar, luego, permite ingreso de los valores para el cual va a funcionar
 */
int main(int argc, char** argv)
{
    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmos_implementados = {
            {"FB", "Fuerza Bruta"}, {"BT", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"},
            {"BT-O", "Backtracking con poda por optimalidad"}, {"DP", "Programacion dinámica"}
    };

    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> M;
    negocios_input.assign(n, make_pair(0 ,0));
    for (int i = 0; i < n; ++i) {
        int a;
        int b;
        cin >> a >> b;
        negocios_input[i] = make_pair(a, b);
    }

    ganancia_final=0;
    auto start = chrono::steady_clock::now();

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
    if (algoritmo == "FB")
    {
        FB(negocios_input);
    }
    else if (algoritmo == "BT")
    {
        BTsinPodas(negocios_input);
    }
    else if (algoritmo == "BT-O")
    {
        BTconPodas(negocios_input);
    }
    else if (algoritmo == "DP")
    {
        // Generamos para DP la matriz de memoizacion
        vector<vector<int>> T(negocios_input.size(), vector<int>(M + 1, -1));
        ganancia_final = PD(negocios_input, T);
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << (ganancia_final == 0 ? -1 : ganancia_final) << endl;
    return 0;
}