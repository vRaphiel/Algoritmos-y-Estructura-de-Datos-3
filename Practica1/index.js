function ejercicio1(n){
    var i = 0;
    var j = 0;
    var suma_linea = 0;
    var solucion = [];
    var valores_usados = [];
    
    for(let i = 0; i < n; i++){
        solucion[i] = [0];
    }

    function posibles(i, j){
        var posibles_valores = [];
        // No tienen que haber numeros repetidos en ningun lado

        //Reviso la columna
        var suma_parcial = 0;
        for(var k = 0; k < i; k++){
            suma_parcial += solucion[k][j];
        }
        
        // Reviso en la columna
    }

    function BK(n, suma_parcial){
        if(i == n){
            
        }else{
            // para cada valor posible, hago BK
            for(var k = 0; k < n*n; k++){



            }
                        
        }
    }

}

function ejercicio6(){
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
        if(a[0] < b[0]) {
            return a;
        }
        return b;
    } 

    var abs = (a) => {
        if(a < 0) return (-1)*a;
        return a;
    }

    var cc = (B, c) => {
        if (B.length == 0) {
            return [0, 0];
        } else {
            var minor = B.pop();

            // Si c > minor no tengo alternativa, le resto el bn
            if (c > minor){
                var tomoMenosBn = cc(B, c - minor);
                return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
            }else{
                if((abs(c - minor) > 0 && abs(c-minor) < B[0])){
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
            if (c > minor){
                var tomoMenosBn = cc(B, c - minor, i-1);
                return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
            }else{
                if((abs(c - minor) > 0 && abs(c-minor) < B[0])){
                    var tomoMenosBn = cc(B, c - minor, i - 1);
                    return [tomoMenosBn[0] + minor, tomoMenosBn[1] + 1];
                }
                var noTomoMenosBn = cc(B, c, i - 1);
                return [noTomoMenosBn[0], noTomoMenosBn[1]];
            }
        }
    }

    var billetes = [2,3,5,10,20,20];
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

function ejercicio8(longitud, cortesNivel){
    
    const min = (a, b) => {
        if (a < b) return a;
        return b;
    }
    
    var storage = new Array(longitud);
    
    const cortarMadera = (i, j, cortes) => {

        var corteMinimo = 0;
        var cortesRestantes = 0;
        
        if(storage[i-j] == undefined){
            for(let k = 0; k < cortes.length; k++){
                if (cortes[k] > i && cortes[k] < j){
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
            if(cortesRestantes == 0){
                storage[i-j] = 0;
            }else if(cortesRestantes == 1){
                storage[i-j] = j - i;
            }else{
                storage[i-j] = j - i + corteMinimo;
            }
        }
        
        return storage[i-j];
    }

    return cortarMadera(0, longitud, cortesNivel)
}

console.log(ejercicio8(10, [2,4,7]));