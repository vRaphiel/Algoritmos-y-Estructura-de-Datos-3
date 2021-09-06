# Practica 1

## Ejercicio 2
## a
Cuantos cuadrados debo generar?
A ver, el cuadrado se mide por dos formas
Por cada cuadrado que genero de nxn dimensiones, yo coloco un solo item entre {1...n^2]
Entonces, yo tengo n^2 cuadrados para colocar
En el siguiente cuadrado, tengo n^2-1 valores para colocar
Despues de eso, si tomo todo como un arreglo, tengo n^2! valores posibles para colocar
Entonces, por fuerza bruta, si tengo que hacer esto, supongamos tengo un cuadrado con todos los valores ordenados de menor a mayor. Cada uno de los valores por fuerza bruta son distintos. Puedo decir que los posibles cuadrados magicos son todos permutaciones de aquel que esta ordenado
Si necesito saber cuantos cuadrados necesito generar, entonces tengo que generar n!*n^2! cuadrados por fuerza buta para poder encontrar los magicos

## b
_Solución Candidata_
Será un arreglo de n^2 y uan solucion es un a=[a1,...,an^2] con 1 <= i <= n^2

_Solución Válida_
Es una secuencia Sn de tamaño n^2 donde cada a_i con 1 <= i <= n^2 y para cada a_i, a_j con j != i, a_i != a_j
Es decir, no hay valores repetidos. Tambien, la suma de las filas, y las columnas, y las diagonales dan lo mismo

_Solución Parcial_
Es una secuencia Sk=(a_1,...a_i) con 0 <= i <= k con a_i perteneciente a [1....n^2]. Cada a_i es una secuencia con valores, cada uno de esos pertenece entre 0 y n^2
Esta secuencia llamada b_i. el primer elemento de b_i está definido mientras que las primeras a_i-1 estan todas definidas. Luego para los elementos restantes entonces deben estar colocados entre 1 y n^2 y estos a su vez no deben pertenecer a las b_i en cada uno de los a_i

Algoritmo
Comienzo con un I = {} y lo que hago es ir extendiendolo siguiendo el criterio de la extension para este metodo
Para cada fila, asumo que i-1 ya está completada y, desde 0 hasta j-1 está completa tambien

Si estoy en el caso de la fila 0. Entonces la completo, voy tomando valores
Una idea es que, si yo se que hay n^2 valores. Entonces mi suma va a ser como minimo n^2. Pues en alguna celda estará n^2 
Entonces, puedo decir que en cada celda coloco un valor entre 0 y n^2. 

Ahora. Yo elijo colocar un valor, entre 1 y n^2

Tengo que completar la primera fila. Entonces, escojo un valor entre los posibles y lo coloco
Luego, recursivamente, calculo todos los cuadrados. Siempre, colocando en cada posicion los posibles, teniendo en cuenta, todos los que falten
Cuando termino de completar una linea. Calculo la suma, y esa es mi suma parcial
Sigo a la siguiente columna
Mientras i no sea n, entonces completo j, en cada pos coloco de los posibles. Que son aquellos que no han sido colocados y faltan colocar. Y busco armar todos los posibles en esta fila
Finalizo la fila y me fijo que sea igual a la suma de la primera, si es asi sigo, si no, entonces retrocedo y vuelvo a armar
Hago lo mismo con las columnas
Al final de todo, pruebo las diagonales, si no vuelvo atras
Entonces, necesito mi cuadrado nxn. Necesito saber cuales faltan, necesito saber en que posicion estoy y en que no

Algoritmo:
```
BT(M, n, I, i, j, suma_nueva){+
    si suma_fila < suma_nueva
        si i = n
            si suma_filas = suma_columnas = suma_diagonal
                return
            si no
                retrocedo
        si j = n
            si suma_fila = suma_nueva
                BT(M, n, I, i+1, 0, suma_fila)
            si no
                retrocedo
        si no
            pos = posibles(i, j, n)
            para cada a' en pos
                M[i][j] = a'
                BT(M, n, Ag(I, a'), i, j, suma_nueva)
}   
```

### c
Si queremos demostrar la complejidad de este arbol, podemos ver lo siguiente:
Sabemos, que tengo en cada posicion n^2 posiciones posibles, de esas n^2 yo tengo que tomar 1. entonces tengo el C(n^2 1)
Luego, para el otro elemento. Yo tengo n^2-1 valores posibles que tomar, esto es C(n^2-1 1)
Esto es equivalente a tomar n^2*(n^2 - 1)
Y asi con todas, entonces tengo 
n^2*(n^2 -1)*(n^2 - 2)*.....*(n^2 - n^2-1) = n^2!
Esto demuestra entonces que la complejidad de este arbol tiene esta complejidad
Esto es pues una vez yo planto un valor, puedo armar un cuadrado magico siguiendo a ese camino
Si trato todo por referencia, los tiempos son constantes entonces tengo que la complejidad me queda O(n^2!) en peor caso

### d
Si ahora tenemos en cuenta que al elegir el valor consideramos que la suma parcial no supere el número mágico, tenemos otro caso

```
BT(M, n, I, i, j, suma_nueva){+
    si suma_fila < suma_nueva
        si i = n
            si suma_filas = suma_columnas = suma_diagonal
                return
            si no
                retrocedo
        si j = n
            si suma_fila = suma_nueva
                BT(M, n, I, i+1, 0, suma_fila)
            si no
                retrocedo
        si no
            pos = posibles(i, j, n)
            para cada a' en pos
                si suma_fila(M[i] + a' < suma_nueva)
                    M[i][j] = a'
                    BT(M, n, Ag(I, a'), i, j, suma_nueva)
}   
```

### e


## Ejercicio 4
### a
_Solución Candidata_
Será una secuencia a = (a_1,...,a_n) de tamaño n donde cada a_i con 1 <= i <= k sea una permutación de Pi

_Solución Válida_
Será aquella soluución candidata tal que, si SC=(a1,...,ak) y a_i es permitación de D entonces D pi(n)pi(i) + Sum^(n-1)_(i=0) D pi(i)pi(i+1) es minimal

_Solución Parcial_
Es aquella secuencia SP = (a1, ..., ai) con 0 <= i <= k siendo ai una permutación o una matriz incompleta, todos los elementos que ya estan pertenecen a D, y todos los elementos que faltan tambien pertenecen a D. y no hay mayor cantidad de elementos internos que esten en la matriz incompleta y no esten en D

_Extender una solucion parcial_
Dada un IP = (a1, ..., ai) como una solucion parcial, se extiende IP union {k} con todo k perteneciente a [1....n] tal que k sea una permutación de D no perteneciente ya al IP


El algoritmo
Comienzo con un I = {} lo que hago es ir extendiendolo siguiendo el criterio de extension

## Ejercicio 5
### a
Sea n = |C| la cantidad de elementos de C

Analizando un poco, se puede ver que ss(C, k) es una función de backtracking de ss', pues
ss(C,k) lo que hace es devolver V o F si existe un subconjunto de C cuyos valores den k
ss' serviria para decir si hasta ahora, la suma, excede o no a k
Entonces
Si yo me baso en ss(C,k) la complejidad de este algoritmo es 2^n porque recorre todos los caminos posibles del arbol de decisiones. Mas que nada el 2^n se refiere a que llamo recursivamente a ss' para resolver este problema
Si ss es una implementacion en backtrackintg de ss'. y ss resuelve el algoritmo en 2^n, transitivamente se concluye que hace falta llamar 2^n veces a ss' para poder resolver el problema

### b
n = 5
Entonces k << 2^5 / 5 = 32 / 5 => k << 6.4
O(5*6.4)
Si C={6, 12, 6, 6} k = 12
Entonces yo voy a tomar el {6}
Luego voy a tomar el {6, 12} y la suma es 18
Luego tomo {6, 6} y la suma es 12 me sirve
Pero tambien luego tomo {6, 6} que es 12
Entonces necesariamente estoy calculando esta instancia

### c
Sirve

### d
subset_sum resuelve el problema pues en la matriz M voy guardando los valores, entonces me ahorro el estar repitiendo sumas
El mejor algoritmo para ambos casos es el de programación Dinámica. Pues imaginemos k es chico, pero C tiene sus n valores siendo esos n repetidos
Entonces la complejidad es elevada
El algoritmo de programación dinámica me permite evitarme esos casos de grandes procesamientos siendo que almacena los valores y me dice que sirve y que no

### e
Claro, como me voy moviendo por i, j entonces yo se que el valor valor actual es igual al valor anterior o en tal caso la suma, de forma que yo pueda ir buscando quue valores me igualan a K

## Ejercicio 6
Multiconjunto B de valores de billetes
Producto de costo c
No hay vuelto

Necesitamos un subconjunto de billetes
Pagar con el minimo exceso posible a fin de minimizar la perdida
Queremos gastar el menor tiempo posible poniendo billetes en la maquina

_Solución Candidata_
Será una secuencia a = (a1,...,an) de tamaño n donde cada a_i con 1 <= i <= n pertenece a la secuencia B

_Solución Válida_
Será una subsecuencia Sn = (a1,...,an) de tamaño n donde cada a_i con 1 <= i <= n pertenece a la secuencia B. Que n sea minimal y, la suma de todos los a_i - c (precio) tambien sea minimal

_Solución Parcial_
Será una subsecuencia SP = (a1,...,ak) con 0 <= i <= k con k < n donde cada elemento de SP pertenezca a B. y que SP pueda extenderse a tamaño n, con n minimal, de forma que pueda reducir la diferencia se la suma SP y C. Equivalentemente todos los elementos de SP deben pertenecer a B

_Algoritmo_
Inicio con I={} tomo el maximo elemento en B. Hago la resta entre, sea C el costo, C y max(B). Si el max(B) es menor que el minimo listo, el resultado es ese
Si no, me quedo con la diferencia. Entonces, ahora como la diferencia es mas grande que el minimo, tomo el anterior al max(B). Reviso, C - valor
Si es menor al minimo entonces veo
En cada caso si es menor al minimo me refiero entre 0 y el minimo
Si es negativo, tomo valor absoluto y me fijo, si sigue siendo menor al minimo, si no, entonces se que puedo usar otro billete para acotar la diferencia, o mejor dicho, la perdida
Asumo que en cada iteracion la perdida tiene que ser minima, entonces mientras la perdida sea menor al minimo, no tengo problema
Si es justo el minimo y la perdida es 0, entonces estoy bien, esa cantidad de billetes es chica
Esto es minimal? En terminos de cantidad
Y esto me permite hacer minimal tambien la cantidad
Claramente, en cada iteracion me fijo si la diferencia negativa es mucha, entonces ese billete no me sirve, busco que la diferencia sea muy chica en negativo. Ej, C=10 y max(B) = 75. La diferencia es 65. No me sirve sabiendo que puedo tener algun billete
Es mas, puedo considerar el siguiente metodo
Me fijo si el precio esta en algun intervalo de 2 billetes, o si es algun billete
Si es un billete doy ese billete y listo
Si esta en algun intervalo, tomo hasta ese intervalo
Entonces, veo eso, si el precio es mayor al maximo entonces se que puedo usar el maximo
Si no, entonces acoto, de esa forma puedo medir que billetes usar y que billetes no para hacer no solo minimal la perdida si no la cantidad de billetes que deba usar

#### Algoritmo
```
cc(B, c)
    si #B = 0 retorno (c, 0)    // No tengo valores para calcular la diferencia
    si no
        // Aca tengo un problema. Tengo que ver si hago c - bn o no
        //Hago c - bn, es decir, considero bn
        A <- cc(B-{bn}, c - bn)  // Entonces resté bn. Ahora, que pasa con el numero? Es negativo? Es positivo?
                            // Me importa acaso? Yo busco un bn.
        
        // No hago c - bn
        B <- cc(B - {bn}, c)     // Entonces no reste bn. Sigo manteniendo C. Aca el minimo a sumar es 0
        // 
        si 0 <= |c - bn| <= min(B) || c - bn > min(B)
            // Está entre el 0 y el minimo, es una perdida aceptable+
            // Tambien es mayor al minimo entonces puedo seguir buscando billetes
            retorno (A.first + bn, A.second + 1)
        si no
            // Se entonces que ahora, estoy debajo de 0 y fuera del minimo
            // Entonces no me conviene agregar ese billete
            retorno (B.first, B.second)


```

Yo se que cc(B, c) me devuelve hasta el momento el valor minimo producto de las sumas de B que es mayor o igual a C
Como hago para encontrar eso?
Tambien tengo que pensar que pasa si el numero se hace negativo. Significa que hay una perdida, pero esa perdida está contemplada en el enunciado
Es decir, puedo permitirme esa perdida. Considerando claro que es menor al minimo. Por ejemplo, si el minimo es 2, entonces si la perdida es 1 no importa
Ahora si la perdida es 2, puedo considerar el colocar 1 billete mas y la perdida es 0
Es relativo
Tomo la segunda. Considero si el valor está entre 0 y el minimo
Entonces me arreglo con eso 

### d
Estructura de memoización
Tengo n billetes. Tengo c precio
Si considero i = 0....n donde b_i es el billete i-esimo
Y luego
j entre 0 y k. siendo K el valor actual de C
Entonces
Puedo pensar una matriz tal que
i represente al billete, k represente al valor que queda
Entonces tengo una matriz de dimensiones

B_ij =def B(B, j) = bottom

Entonces, el acceder a M[i][j] es O(1)
Luego, el metodo para esto, seria

Necesito esta estructura? Como puedo usarla?
Pensemos...
Necesitamos memoizar este problema?
Si es asi, porque?

Tengo un problema para esto

### Ejercicio 8

Me dicen que tengo que cortar una vara de madera en varios lugares predeterminados
Ok, el costo de cortar la madera de longitud l es l

Entonces tengo
(j - i) + ((j-c1+1) + (j-c1-c2+1) + ... + (j-c1-c2-...-cn+1))
