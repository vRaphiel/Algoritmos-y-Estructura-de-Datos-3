function ejercicio1(n) {
    var i = 0;
    var j = 0;
    var suma_linea = 0;
    var solucion = [];
    var valores_usados = [];

    for (let i = 0; i < n; i++) {
        solucion[i] = [0];
    }

    function posibles(i, j) {
        var posibles_valores = [];
        // No tienen que haber numeros repetidos en ningun lado

        //Reviso la columna
        var suma_parcial = 0;
        for (var k = 0; k < i; k++) {
            suma_parcial += solucion[k][j];
        }

        // Reviso en la columna
    }

    function BK(n, suma_parcial) {
        if (i == n) {

        } else {
            // para cada valor posible, hago BK
            for (var k = 0; k < n * n; k++) {



            }

        }
    }

}

function ejercicio6() {
    /**
     * Solución Candidato: Es un arreglo A = [a1, ..., an] donde ai es una tupla (c', q), c' es el minimo costo mayor o igual
     * alcanzable con los billetes de B y q el minimo de billetes usables
     * 
     * Solución Válida: Es aquella solución Sn = (c', q) tal que c' es el minimo mayor o igual de C que se puede conseguir con la 
     * suma de billetes de B, y, q tiene que ser minimal
     * 
     * Solución Parcial:
     */

    const min = (a, b) => {
        if (a[0] < b[0]) {
            return a;
        }
        return b;
    }

    var abs = (a) => {
        if (a < 0) return (-1) * a;
        return a;
    }

    var cc = (B, c) => {
        if (B.length == 0) {
            return [0, 0];
        } else {
            var minor = B.pop();

            // Si c > minor no tengo alternativa, le resto el bn
            if (c > minor) {
                var tomoMenosBn = cc(B, c - minor);
                return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
            } else {
                if ((abs(c - minor) > 0 && abs(c - minor) < B[0])) {
                    var tomoMenosBn = cc(B, c - minor);
                    return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
                }
                var noTomoMenosBn = cc(B, c);
                return [noTomoMenosBn[0], noTomoMenosBn[1]];
            }
        }
    }

    var ccPrim = (B, c, i) => {
        if (B.length == 0) {
            return [0, 0];
        } else {
            var minor = B[i];

            // Si c > minor no tengo alternativa, le resto el bn
            if (c > minor) {
                var tomoMenosBn = cc(B, c - minor, i - 1);
                return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
            } else {
                if ((abs(c - minor) > 0 && abs(c - minor) < B[0])) {
                    var tomoMenosBn = cc(B, c - minor, i - 1);
                    return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
                }
                var noTomoMenosBn = cc(B, c, i - 1);
                return [noTomoMenosBn[0], noTomoMenosBn[1]];
            }
        }
    }

    var billetes = [2, 3, 5, 10, 20, 20];
    var costo = 14;

    //result = cc(billetes, costo);
    result = ccPrim(billetes, costo, billetes.length - 1);

    console.log(result);

}

// La complejidad de esto es:
/**
 * Tengo varias ramas. Entonces puedo tomar yo muchas cosas
 * Tengo 3 llamados recursivos
 * No obstante, considero 1 caso para cada uno
 * Pero esto se basa en tener por cada caso 2 nodos
 * Entonces la complejidad de esto es 2^n porque tengo 2^n notos finales. Por otro lado,
 */

/**
 * Ejercicio 7
 *  */

function ejercicio7(p) {

    var maxAsteroides = ((p.length % 2 == 0) ? p.length : p.length - 1) / 2;
    console.log("Max Asteroid at:", maxAsteroides);

    const max = (a) => {
        var res = 0;
        for (let i = 0; i < a.length; i++) {
            if (a[i] > res) {
                res = a[i];
            }
        }
        return res;
    }

    // P es el arreglo de los valores de asteroides (numeros solamente)
    // I es el dia
    // C es la cantidad de asteroides
    // Ganancia obtenida

    const maxAsteroid = (p, i, c, g) => {

        //console.log(`Ingreso con p: ${p}, indice: ${i}, asteroides: ${c}, ganancia: ${g} y elemento en pos i: ${p[i]}`);
        var resultado = 0;
        // Caso base
        if (c < 0 || c > i) return resultado; // Si la cantidad de asteroides es negativa o es mayor al dia entonces devuelvo 0
        if (i == p.length) return g;

        if (i == p.length - 1) {
            if (c == 0) return g;
            if (c == 1) return g + p[i];
            return 0;
        }

        if (c == 0) return (resultado + maxAsteroid(p, i + 1, c + 1, g - p[i]));

        // Vendo uno el dia j-1
        var caso1 = max([0, maxAsteroid(p, i + 1, c - 1, g + p[i])]);

        var caso2 = 0;

        // Compro un asteroide
        if (c + 1 <= maxAsteroides) caso2 = max([0, maxAsteroid(p, i + 1, c + 1, g - p[i])]);

        // No hago nada
        var caso3 = max([0, maxAsteroid(p, i + 1, c, g)]);

        // Si la cantidad de asteroides hasta el elemento del medio. Es decir, al dia del medio, es menor o igual a la cantidad de dias. Entonces puedo seguir comprando, si no restando

        resultado = max([0, caso1, caso2, caso3]);

        return resultado

    }

    return maxAsteroid(p, 0, 0, 0);
}

function ejercicio8(longitud, cortesNivel) {

    const min = (a, b) => {
        if (a < b) return a;
        return b;
    }

    var storage = new Array(longitud);

    const cortarMadera = (i, j, cortes) => {

        var corteMinimo = 0;
        var cortesRestantes = 0;

        if (storage[i - j] == undefined) {
            for (let k = 0; k < cortes.length; k++) {
                if (cortes[k] > i && cortes[k] < j) {
                    cortesRestantes++;
                    let sumaDesdeIC = cortarMadera(i, cortes[k], cortes);
                    let sumaDesdeCJ = cortarMadera(cortes[k], j, cortes);
                    let sumaIJ = sumaDesdeIC + sumaDesdeCJ;
                    if (corteMinimo == 0) {
                        corteMinimo = sumaIJ;
                    } else {
                        corteMinimo = min(corteMinimo, sumaIJ);
                    }
                }
            }
            if (cortesRestantes == 0) {
                storage[i - j] = 0;
            } else if (cortesRestantes == 1) {
                storage[i - j] = j - i;
            } else {
                storage[i - j] = j - i + corteMinimo;
            }
        }

        return storage[i - j];
    }

    return cortarMadera(0, longitud, cortesNivel)
}

// Ejercicio 9
/**
 * Terreno de m filas y n columnas
 * Ir desde (0,0) hasta (m-1, n-1). Movimiento derecha o abajo
 * Cada numero suma o resta vida
 * Minimo nivel de vida con tal que haya un camino posible tal que nuestro nivel de vida sea mayor a 1
 */

function ejercicio9(M) {
    // Seteo mis iniciales
    var maxX = M.length;
    var maxY = M[0].length;

    var recorridos = [];

    const max = (a, b) => {
        if (a > b) return a;
        return b;
    }

    const abs = (a) => {
        if (a < 0) return (-1) * a;
        return a
    }


    // Recibo la matriz, una i, una j
    // i se mueve en X
    // j se mueve en Y
    const recorrerTablero = (M, i, j) => {

        resultado = 0;
        console.log(`En pos i: ${i} y j: ${j} es ${M[i][j]}`);

        if (i == maxX - 1 && j == maxY - 1) return M[i][j];
        
        if(i == maxX - 1) return recorrerTablero(M, i, j+1) - M[i][j];
        if(j == maxY - 1) return recorrerTablero(M, i+1, j) - M[i][j];

        minimoDer = recorrerTablero(M, i, j+1);
        minimoAba = recorrerTablero(M, i+1, j);

        if(minimoDer < minimoAba){
            resultado = minimoDer;
            recorridos.push({a: i, b: j+1});
        } else {
            resultado = minimoAba;
            recorridos.push({a: i+1, b: j});
        }
        
        console.log(`En pos i: ${i} y j: ${j} es ${M[i][j]} y el resultado es ${resultado}`);
        return resultado - M[i][j];

    }

    console.log(recorrerTablero(M, 0, 0));
}

// P son los pesos w
// S son los soportes
function ejercicio10(pesos, soportes){
    // Solo puede haber una caja apoyada sobre otra
    // Las cajas de la pila deben estar ordenadas crecientemente por numero
    // Cada caja i tiene peso w y soporte s_i
    // El peso de las cajas que estan arriba de otra no deben exceder el soporte de la otra

    //  Buscamos la maxima cantidad de cajas posibles a apilar
    const max = (a) => {
        var res = 0;
        for (let i = 0; i < a.length; i++) {
            if (a[i] > res) {
                res = a[i];
            }
        }
        return res;
    }

    // W son los pesos
    // S son los soportes
    // i es el indice actual
    // p_sum es la suma de los pesos
    // s_sum es la suma de los soportes
    const BT = (W, S, i, j, p_sum, first) => {

        var result = 0;
        
        if ( i == W.length ) return 0;
        
        // Aca tengo los pesos, tengo los soportes, tengo el inidice
        // Tambien tengo, la suma del peso + peso de caja agregada
        // Tengo el soporte del peso - el peso aceptado
        for(let k = i; k < W.length; j++){
            // Para cada caja

            // Si es la primera caja a agregar
            if(first){
                /* Busco el maximo entre 0 y BT de W, S, la siguiente caja, porque se que
                al entrar a la siguiente caja entonces yo voy a ver si agrego o no esa caja
                Entonces, considero esta caja actual, el principio de todo 
                Otra cosa es que no me importa el peso de la primera caja para la operacion final, 
                porque esta puede ser la que mas pese entre todas y cambiarme el resultado final */
                
                result = max([result, BT(W, S, i+1, k, 0, false)]);
            }else{
                /** 
                 * Se que no es la primera caja, ya hay una caja previa. Por lo tanto s_sum ya no es 0
                 * A su vez, caso recursivo, tengo que repetir para todas las posibilidades
                 * Como no se cuantos soportes van a haber, entonces tengo que hacer esto
                 * 
                 * */
            }


        }

        return 1 + result;
        
    }

    return BT(p, s, 0, 0, -1, true)

}

function ejercicio10Aux(pesos, soportes){

    const max = (a, b) => {
        if (a < b) return b;
        return a;
    }

    const apilar = (i, p, W, S) => {
        if (i == 0 && p > S[i]) {
            return 0;
        }
        if(i == 0 && p <= S[i]){
            return 1;
        }

        return max(1 + apilar(i+1, p + p[i], W, S), apilar(i-1, p, W, S));

    }

    return apilar(pesos.length, 0, pesos, soportes);

}

var p = [19, 7, 5, 6, 1];
var s = [15, 13, 7, 8, 2];
console.log(ejercicio10Aux(p, s));