# Trabajo Practico - TSP 

_Este trabajo fue realizado por alumnos de Algoritmos y Estructura de datos 3_

## Despliegue 📦

El codigo que resuelve el problema se encuentra en la carpeta /codigo del directorio fuente, en el archivo main.cpp

Para correr los experimentos es necesario primero compilar el codigo fuente de las implementaciones de los algoritmos. Para esto ejecutar los siguientes comandos desde el directorio del proyecto:

```
./codigo/g++ -o tsp main.cpp extras.cpp

./codigo/mv ./tsp ../python
```

Al ejecutarlo se le debe pasar un parámetro que indique cuál algoritmo se desea utilizar entre las siguientes opciones:
* BG: Busqueda Golosa
* AGM: Arbol Generador Minimo
* BL: Busqueda Local
* TABU: Busqueda TABU.
* TABUSOL: Busqueda Tabu con devolución de solucion por iteración

A demas, se le debe pasar la instancia por entrada estándar. Por ejemplo, para ejecutar BUSQUEDA GOLOSA solamente con poda por factiblidad en una instancia INST1.TXT se debe correr el siguiente comando:
```
cat INST1.txt | tsp BG
```
La salida del programa es doble. Por la salida estándar se devuelve lo pedido por el anunciado. Por la STDERR se devuelve el tiempo de ejecución del algoritmo

### Importante
Si el algoritmo elegido es TABU o TABUSOL entonces, elegido el algoritmo, como primeros parametros se le pasa:
* Cantidad de iteraciones
* Tamaño de memoria
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

La generacion de instancias y corrida de los experimentos de manera secuencial se programó en Python utilizando Jupyter Lab. Para ver los notebooks se debe tener instalado Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalación utilizando pip3.

Una vez instalado Jupyter Lab, abrir una consola en la carpeta python y correr el comando:
	jupyter lab

Allí, existen dos archivos:
* lectura_instancia.ipynb: toma los resultados de las ejecuciones y genera todos los gráficos correspondientes.
* experimentos.ipynb: corre los experimentos del trabajo y deja el resultado de todas las ejecuciones en un CSV en la carpeta python/resultados

Por otro lado, la generación de graficos se realizó utilizando R. Para ejecutar el archivo se debe tener instalado el lenguaje R siguiendo las instrucciones en su web.
Tambien se puede utilizar Rstudio para hacer una visualización mucho mejor del archivo

* codigograficos.rmd: genera los gráficos en relación a los experimentos. Este código esta realizado en R

_Herramientas utilizadas para el proyecto_

* [Jupyter Lab](https://jupyter.org/) - Los Notebooks
* [CLion](https://www.jetbrains.com/es-es/clion/) - IDE utilizado para el desarrollo
* [CMake](https://cmake.org/) - Herramienta utilizada para compilar el codigo
* [R](https://www.r-project.org/) - Lenguaje R para generar los gráficos
* [RStudio](https://www.rstudio.com/) - IDE para visualizar mejor el documento y generar notebooks si hace falta
