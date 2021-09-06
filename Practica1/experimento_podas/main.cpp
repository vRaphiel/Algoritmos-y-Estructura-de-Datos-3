#include <bits/stdc++.h>

using namespace std;

int n = 9;
int sqrt_n = 3;
int nodos_visitados = 0;
vector<vector<int>> sudoku(n,vector<int>(n));
vector<vector<int>> solucion;

void leer_sudoku(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin>>sudoku[i][j];
}
void escribir_sudoku(){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout<<solucion[i][j]<<' ';
        cout<<'\n';
    }
}

vector<int> posibles(int i, int j){
    if(sudoku[i][j] != 0)
        return {sudoku[i][j]};
    vector<bool> vale(n+1,true);
    for(int k = 0; k < n; k++) vale[sudoku[i][k]] = false;
    for(int k = 0; k < n; k++) vale[sudoku[k][j]] = false;
    i -= (i%sqrt_n);
    j -= (j%sqrt_n);
    for(int k1 = 0; k1 < sqrt_n; k1++) for(int k2 = 0; k2 < sqrt_n; k2++) vale[sudoku[i+k1][j+k2]] = false;

    vector<int> res;
    for(int x = 1; x <= n; x++) if(vale[x]) res.push_back(x);
    return res;
}

void sudoku_solver(int i = 0, int j = 0){
    nodos_visitados++;
    if(!solucion.empty()) return;

    if(i == n) {
        solucion = sudoku;
        return;
    }

    int ip = i;
    int jp = j+1;
    if(jp == n) ip++, jp = 0;

    if(sudoku[i][j] == 0){
        vector<int> s = posibles(i,j);
        for(auto x : s) {
            sudoku[i][j] = x;
            sudoku_solver(ip,jp);
            if(!solucion.empty()) return;
        }
        sudoku[i][j] = 0;
    }
    else sudoku_solver(ip,jp);
}

bool vale(int i, int j){
    for(int k = 0; k < n; k++) if(posibles(i,k).empty()) return false;
    for(int k = 0; k < n; k++) if(posibles(k,j).empty()) return false;
    i -= (i%sqrt_n);
    j -= (j%sqrt_n);
    for(int k1 = 0; k1 < sqrt_n; k1++) for(int k2 = 0; k2 < sqrt_n; k2++) if(posibles(i+k1,j+k2).empty()) return false;
    return true;
}

//chequea al poner un numero si no deja sin candidatos a otra celda
void sudoku_solver_2(int i = 0, int j = 0){
    nodos_visitados++;
    if(!solucion.empty()) return;

    if(i == n) {
        solucion = sudoku;
        return;
    }

    int ip = i;
    int jp = j+1;
    if(jp == n) ip++, jp = 0;

    if(sudoku[i][j] == 0){
        vector<int> s = posibles(i,j);
        for(int x : s){
            sudoku[i][j] = x;
            if(vale(i,j)){
                sudoku_solver_2(ip,jp);
                if(!solucion.empty()) return;
            }
        }
        sudoku[i][j] = 0;
    }
    else sudoku_solver_2(ip,jp);
}

bool completo(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(sudoku[i][j] == 0) return false;
    return true;
}

//empiezo decidiendo por la celda con menor cantidad de candidatos
void sudoku_solver_3(){
    nodos_visitados++;
    if(!solucion.empty()) return;

    if(completo()) {
        solucion = sudoku;
        return;
    }

    int x = -1,y = -1;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(sudoku[i][j] != 0) continue;
        if(x == -1 or posibles(i,j) < posibles(x,y)) x = i, y = j;
    }

    vector<int> s = posibles(x,y);
    for(int c : s){
        sudoku[x][y] = c;
        sudoku_solver_3();
        if(!solucion.empty()) return;
    }
    sudoku[x][y] = 0;
}

int main(){
    leer_sudoku();
    sudoku_solver_3();
    cout<<'\n';
    escribir_sudoku();
    cout<<nodos_visitados<<'\n';
}