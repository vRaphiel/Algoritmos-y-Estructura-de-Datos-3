#include "extras.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;
int INFTY = 10e6;

// #Nodos = tamanio(g) - 1
Salida heurGolosaConstructiva(Grafo& g) {
    Salida s;
    s.N = g.size() - 1;
    s.costoSol=0;
    s.ordenVertices={};
    // Siempre inicia en 1
    int nodoActual = 1;
    s.ordenVertices.push_back(nodoActual);

    for (int i = 1; i < g.size()-1; ++i) {
        // i es el nodo actual.
        // g[i] es la lista de vecinos
        int minimoPesoLocal = INFTY;
        int candidato=0;
        for (int j = 0; j < g[nodoActual].size(); ++j) {
            // Se actualiza el peso minimo
            if (g[nodoActual][j].peso <= minimoPesoLocal && !estaAgregado(g[nodoActual][j].dst, s.ordenVertices)) {
                minimoPesoLocal = g[nodoActual][j].peso;
                candidato = g[nodoActual][j].dst;
            }
        }
        nodoActual=candidato;
        s.costoSol += minimoPesoLocal;
        s.ordenVertices.push_back(nodoActual);
    }

    // Aca es el ultimo nodo, entonces busca al inicio y cierra el ciclo
    for (int i = 0; i < g[nodoActual].size(); ++i) {
        if (g[nodoActual][i].dst == 1){
            s.costoSol += g[nodoActual][i].peso;
        }
    }

    return s;
}

Salida heurAGM(Grafo& grafo){

    vector<int> agm = PrimMST(grafo);
    Grafo T= aristasAGM(agm);
    vector<int> dfs = recorridoDFS(T);
    Salida salida;
    salida.ordenVertices = dfs;
    salida.N = dfs.size();

    int sumaOptima = costoSolucion(grafo, dfs);

    salida.costoSol = sumaOptima;
    return salida;

}

Salida busquedaLocal(Grafo& g){
    Salida sol= heurGolosaConstructiva(g);
    Salida opt=sol;
    Salida local=sol;
    int cambio=0;
    int costoLocal=0;
    bool hayMejora=true;
    while(hayMejora){
        for (int i = 0; i < sol.ordenVertices.size()-1; ++i) {
            //empieza con [i+1] [i+2] y swapea con [i+3] [i+4] -> [i+1][i+3]   [i+2][i+4]
            //sigue con [i+1] [i+2] y swapea con [i+4] [i+5]
            for (int j = i; j < sol.ordenVertices.size() - 2; ++j) {//AB CD -> AC BD
                cambio = local.ordenVertices[i + 1];
                local.ordenVertices[i + 1] = local.ordenVertices[j + 2];
                local.ordenVertices[j + 2] = cambio;
                costoLocal = costoSolucion(g, local.ordenVertices);
                if (costoLocal < opt.costoSol) {
                    opt.ordenVertices = local.ordenVertices;
                    opt.costoSol = costoLocal;
                    local = sol;
                }
            }
        }

        if(opt.costoSol>=sol.costoSol){
            hayMejora=false;
        }
        sol = opt;
    }
    return sol;
}

//cantIteraciones limita que tanto ejecuta, tamañoMemo porque piden memoria finita, tipoMemo porque puede ser de ciclo(0) o de swaps(1)
//subvecindad que vaya de 0 a 100 que sea el porcentaje a quedarse de los vecinos
Salida tabu(Grafo& g,int cantIteraciones, int tamanioMemo, int tipoMemo, int subvecindad){
    Salida sol= heurGolosaConstructiva(g);
   //Salida sol= heurGolosaConstructiva(g);
    Salida opt =sol;
    vector<vector<int>> vecinos;
    list<vector<int>> memo; // vamos pusheando hasta que el size llegue a tamanioMemo y ahí cada vez que pusheamos, borramos el más viejo(el que esté primero)
    for (int i = 0; i < cantIteraciones ; ++i) {
        vecinos=obtenerSubvecindad(sol,subvecindad);  // veo todos losvecinos y me quedo solo un % (indicado por subvecindad)
        vector<int>solAnterior=sol.ordenVertices;
        sol=obtenerMejor(vecinos,memo,tipoMemo,solAnterior, g,tamanioMemo);  // agarro el mejor vecino que no este ya en memoria (peso y orden vertices)
        //en caso de que obtenerMejor no pueda continuar(ya sea por que está en memo o algo) volvemos a la mejor sol que tengamos hasta el momento
        //agregarAMemo(sol,memo,tipoMemo); //agregaría lo que nos quedamos a memoria, en caso de estar llena borrar el más viejo
        if (sol.costoSol < opt.costoSol){
            opt=sol;
        }

    }

    return opt;
}


vector<int> tabuSoluciones(Grafo& g,int cantIteraciones, int tamanioMemo, int tipoMemo, int subvecindad){
    Salida sol= heurGolosaConstructiva(g);
    //Salida sol= heurGolosaConstructiva(g);
    Salida opt =sol;
    vector<int>solucionesXiteracion;
    vector<vector<int>> vecinos;
    list<vector<int>> memo; // vamos pusheando hasta que el size llegue a tamanioMemo y ahí cada vez que pusheamos, borramos el más viejo(el que esté primero)
    for (int i = 0; i < cantIteraciones ; ++i) {
        vecinos=obtenerSubvecindad(sol,subvecindad);  // veo todos losvecinos y me quedo solo un % (indicado por subvecindad)
        vector<int>solAnterior=sol.ordenVertices;
        sol=obtenerMejor(vecinos,memo,tipoMemo,solAnterior, g,tamanioMemo);  // agarro el mejor vecino que no este ya en memoria (peso y orden vertices)
        //en caso de que obtenerMejor no pueda continuar(ya sea por que está en memo o algo) volvemos a la mejor sol que tengamos hasta el momento
        //agregarAMemo(sol,memo,tipoMemo); //agregaría lo que nos quedamos a memoria, en caso de estar llena borrar el más viejo
        if (sol.costoSol < opt.costoSol){
            opt=sol;
        }
        solucionesXiteracion.push_back(sol.costoSol);
    }

    return solucionesXiteracion;
}


int main(int argc, char** argv) {

    map<string, string> algoritmos_implementados = {
        {"BG", "Busqueda Golosa"},
        {"AGM", "Heuristica AGM"},
        {"BL", "Busqueda Local"},
        {"TABU", "Busqueda Tabu"},
        {"TABUSOL", "Busqueda Tabu con return solXiteracion"}
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

    Salida s;
    vector<int>sol;
    int n = 0;
    int m = 0;

    int it = 0;
    int tm = 0;
    int qmemo = 0;
    int sv = 0;

    if(algoritmo == "TABU" || algoritmo=="TABUSOL"){
        cin >> it >> tm >> qmemo >> sv;
    }

    // Leemos el input.
    cin >> n >> m;
    s.N=n;
    Grafo g(n+1);

    for (int i = 0; i < m ; ++i) {
        int a = 0;
        int b = 0;
        int peso = 0;
        cin>> a >> b >> peso;

        Vecino va(b, peso);
        Vecino vb(a, peso);

        g[a].push_back(va);
        g[b].push_back(vb);
    }

    auto start = chrono::steady_clock::now();
    if (algoritmo == "BG") {
        s = heurGolosaConstructiva(g);
    }
    else if (algoritmo == "AGM") {
        s = heurAGM(g);
    }
    else if (algoritmo == "BL") {
        s = busquedaLocal(g);
    }
    else if (algoritmo == "TABU") {
        s = tabu(g,it,tm,qmemo,sv);
    }
    else if (algoritmo=="TABUSOL"){
        sol= tabuSoluciones(g,it,tm,qmemo,sv);
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    if (algoritmo=="TABUSOL"){
        for(int i = 0; i < sol.size(); i++){
            cout << sol[i] << " ";
        }
    }else{
        cout << s.N << " " << s.costoSol << "\n";
        for(int i = 0; i < s.ordenVertices.size(); i++){
            cout << s.ordenVertices[i] << " ";
        }
    }

/*
    //1->2 (10)  2->4 (25) 4->3 (30) 3->1 (15) total 80
    Grafo g={{},
        {Vecino(2,10), Vecino(3,15), Vecino(4,20)},
        {Vecino(1,10), Vecino(3,35), Vecino(4,25)},
        {Vecino(1,15), Vecino(2,35), Vecino(4,30)},
        {Vecino(1,20), Vecino(2,25), Vecino(3,30)}
    };

    Grafo g2={{},
         {Vecino(2,10), Vecino(3,900), Vecino(4,20)},
         {Vecino(3,35), Vecino(1,10), Vecino(4,25)},
         {Vecino(4,30), Vecino(2,35), Vecino(1,900)},
         {Vecino(1,20), Vecino(3,30), Vecino(2,25)}
    };

    Grafo g3={{},
             {Vecino(2,20), Vecino(3,15), Vecino(4,10)},
             {Vecino(1,20), Vecino(3,30), Vecino(4,25)},
             {Vecino(1,15), Vecino(2,30), Vecino(4,40)},
             {Vecino(1,10), Vecino(2,25), Vecino(3,40)}
    };


    Salida s = heurGolosaConstructiva(g3);
    cout << s.N << " " << s.costoSol << "\n";
    for(int i = 0; i < s.ordenVertices.size(); i++){
        cout << s.ordenVertices[i] << " ";
    }

    cout << "\n--------------------" << endl;

    Salida s2 = heurAGM(g3);
    cout << s2.N << " " << s2.costoSol << "\n";
    for(int i = 0; i < s2.ordenVertices.size(); i++){
        cout << s2.ordenVertices[i] << " ";
    }

    cout << "\n--------------------" << endl;
    
    Salida s3 = busquedaLocal(g3);
    cout << s3.N << " " << s3.costoSol << "\n";

    for(int i = 0; i < s3.ordenVertices.size(); i++){
        cout << s3.ordenVertices[i] << " ";
    }

    cout << "\n--------------------" << endl;

    // Limitamos la entrada desde 1 a 100, el 0 no es un numero valido(para subvecindad)
    // Como precondicion subvecindad >= 1
    // Tipo memo = 0 o 1
    Salida s4 = tabu(g3,1000,0,0,1);
    cout << s4.N << " " << s4.costoSol << "\n";

    for(int i = 0; i < s4.ordenVertices.size(); i++){
        cout << s4.ordenVertices[i] << " ";
    }
*/
    return 0;
}
