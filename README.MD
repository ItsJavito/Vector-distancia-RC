# Proyecto implementación Vector - Distancia

En el presente proyecto se ha implementado el algoritmo de vector distancia en C++. 

## Requisitos

Para poder compilar y correr el algoritmo se necesita el compilador de C++ [MinGW](https://sourceforge.net/projects/mingw/) , que es el GCC para windows. 

## Compilación y ejecución

Primeramente tenemos que clonar el repositorio en el cli de git con 
```shell
git clone https://github.com/ItsJavito/Vector-distancia-RC.git 
```
Después de descargar el repositorio y también al instalar el MinGW procedemos a el código con la sentencia

```shell
g++ -O3 ./BellmanFord.cpp -o BellmanFord
```
Un ejemplo de la ejecución de este comando es
![ImagenCompilacion](https://github.com/ItsJavito/Vector-distancia-RC/blob/main/Imagenes/Compilación.gif)

Despues de compilar procedemos a ajecutar con el siguiente formato

```shell
./BellmanFord <ArchivoTopologia> <ArchivoRespuesta> <Numero_Nodo>
```

## License
[MIT](https://choosealicense.com/licenses/mit/)