var memo = new Array();
const fillMemo = (X, Y) => {
    // Una matriz de n filas y m columnas
    for(let i = 0; i < X.length; i ++){
        memo.push(new Array(Y.length).fill(0));
    }
}

/* X, Y son las palabras independientes. Z es la palabra mezcla*/
const isShuffle = (X, Y, Z) => {
    var n = X.length;
    var m = Y.length;
    var r = Z.length;
    memo[0][0] = 1;
    if(r != n + m) return false;
    for(let i = 1; i < n; i++){
        memo[i][0] = memo[i-1][0] && (Z[i-1] == X[i-1]);
    }
    for(let j = 1; j < m; j++){
        memo[0][j] = memo[0][j-1] && (Z[j-1] == Y[j-1]);
    }
    for(let i = 1; i < n; i++){
        for(let j = 1; j < m; j++){
            memo[i][j] = ((Z[i+j-1] == X[i-1]) && memo[i-1][j]) || ((Z[i+j-1] == Y[j-1]) && memo[i][j-1]);
        }
    }
    return memo[n-1][m-1];  
}

const PD = (X, Y, Z) => {
    fillMemo(X, Y);
    var res = isShuffle(X, Y, Z);
    console.log(res);
}