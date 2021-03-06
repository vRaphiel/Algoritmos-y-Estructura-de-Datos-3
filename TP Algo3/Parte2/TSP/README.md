# Trabajo Practico - TSP 

_Este trabajo fue realizado por alumnos de Algoritmos y Estructura de datos 3_

## Despliegue 馃摝

El codigo que resuelve el problema se encuentra en la carpeta /codigo del directorio fuente, en el archivo main.cpp

Para correr los experimentos es necesario primero compilar el codigo fuente de las implementaciones de los algoritmos. Para esto ejecutar los siguientes comandos desde el directorio del proyecto:

```
./codigo/g++ -o tsp main.cpp extras.cpp

./codigo/mv ./tsp ../python
```

Al ejecutarlo se le debe pasar un par谩metro que indique cu谩l algoritmo se desea utilizar entre las siguientes opciones:
* BG: Busqueda Golosa
* AGM: Arbol Generador Minimo
* BL: Busqueda Local
* TABU: Busqueda TABU.
* TABUSOL: Busqueda Tabu con devoluci贸n de solucion por iteraci贸n

A demas, se le debe pasar la instancia por entrada est谩ndar. Por ejemplo, para ejecutar BUSQUEDA GOLOSA solamente con poda por factiblidad en una instancia INST1.TXT se debe correr el siguiente comando:
```
cat INST1.txt | tsp BG
```
La salida del programa es doble. Por la salida est谩ndar se devuelve lo pedido por el anunciado. Por la STDERR se devuelve el tiempo de ejecuci贸n del algoritmo

### Importante
Si el algoritmo elegido es TABU o TABUSOL entonces, elegido el algoritmo, como primeros parametros se le pasa:
* Cantidad de iteraciones
* Tama帽o de memoria
* Tipo de memoria: 0 o 1
* Subvecindad porcentaje como numero entero
```
tsp TABU
1000 1000 0 10

tsp TABU
1000 1000 1 10
```

Si se va a correr una instancia .txt entonces se agrega al principio del .txt estos parametros y luego se ejecuta
```
// Caso TABU
cat INST1.txt | tsp TABU

// Caso TABUSOL
cat INST1.exe | tsp TABUSOL
```

La generacion de instancias y corrida de los experimentos de manera secuencial se program贸 en Python utilizando Jupyter Lab. Para ver los notebooks se debe tener instalado Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalaci贸n utilizando pip3.

Una vez instalado Jupyter Lab, abrir una consola en la carpeta python y correr el comando:
	jupyter lab

All铆, existen dos archivos:
* lectura_instancia.ipynb: toma los resultados de las ejecuciones y genera todos los gr谩ficos correspondientes.
* experimentos.ipynb: corre los experimentos del trabajo y deja el resultado de todas las ejecuciones en un CSV en la carpeta python/resultados

Por otro lado, la generaci贸n de graficos se realiz贸 utilizando R. Para ejecutar el archivo se debe tener instalado el lenguaje R siguiendo las instrucciones en su web.
Tambien se puede utilizar Rstudio para hacer una visualizaci贸n mucho mejor del archivo

* codigograficos.rmd: genera los gr谩ficos en relaci贸n a los experimentos. Este c贸digo esta realizado en R

_Herramientas utilizadas para el proyecto_

* [Jupyter Lab](https://jupyter.org/) - Los Notebooks
* [CLion](https://www.jetbrains.com/es-es/clion/) - IDE utilizado para el desarrollo
* [CMake](https://cmake.org/) - Herramienta utilizada para compilar el codigo
* [R](https://www.r-project.org/) - Lenguaje R para generar los gr谩ficos
* [RStudio](https://www.rstudio.com/) - IDE para visualizar mejor el documento y generar notebooks si hace falta
