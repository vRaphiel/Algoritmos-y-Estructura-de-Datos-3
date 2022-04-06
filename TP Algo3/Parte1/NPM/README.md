# Trabajo Practico - Negocios por Medio

_Este trabajo fue realizado por alumnos de Algoritmos y Estructura de datos 3_

## Despliegue 📦

El codigo que resuelve el problema se encuentra en la carpeta /codigo del directorio fuente, en el archivo negociospormedio.cpp

Para correr los experimentos es necesario primero compilar el codigo fuente de las implementaciones de los algoritmos. Para esto ejecutar los siguientes comandos desde el directorio del proyecto:

```
./codigo/g++ -o negociospormedio main.cpp

./codigo/mv ./negociospormedio ../python
```


Al ejecutarlo se le debe pasar un parámetro que indique cuál algoritmo se desea utilizar entre las siguientes opciones:
* FB: Fuerza bruta
* BT: Backtracking solamente con poda por factibilidad.
* BT-O: Backtracking con poda por factibilidad y optimalidad
* DP: Programación dinámica.

A demas, se le debe pasar la instancia por entrada estándar. Por ejemplo, para ejecuutar backtracking solamente con poda por factiblidad en una instancia INST1.TXT se debe correr el siguiente comando:
```
cat INST1.txt | negociospormedio BT
```
La salida del programa es doble. Por la salida estándar se devuelve lo pedido por el anunciado. Por la STDERR se devuelve el tiempo de ejecución del algoritmo

La generacion de instancias y corrida de los experimentos de manera secuencial se programó en Python utilizando Jupyter Lab. Para ver los notebooks se debe tener instalado Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalación utilizando pip3.

Una vez instalado Jupyter Lab, abrir una consola en la carpeta python y correr el comando:
	jupyter lab

Allí, existen tres archivos:
* generar-instancias.ipynb: genera las instancias descriptas en el trabajo y las ubica en la carpeta python/instancias.
* experimentos.ipynb: corre los experimentos del trabajo y deja el resultado de todas las ejecuciones en un CSV en la carpeta python/resultados
* analysis.ipynb: toma los resultados de las ejecuciones y genera todos los gráficos correspondientes.

_Herramientas utilizadas para el proyecto_

* [Jupyter Lab](https://jupyter.org/) - Los Notebooks
* [CLion](https://www.jetbrains.com/es-es/clion/) - IDE utilizado para el desarrollo
* [CMake](https://cmake.org/) - Herramienta utilizada para compilar el codigo