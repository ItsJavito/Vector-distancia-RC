/*
 * Para correr el archivo se tiene que seguir los siguientes pasos:
 *
 * 1. Compilar con la sentencia "g++ -O3 ./BellmanFord.cpp -o BellmanFord"
 *    dara un ejecutable de nombre BellmanFord.exe.
 * 
 * 2. Ejecutar el .exe con 
 *    ./BellmanFord <ArchivoGrafo.txt> <nombreArchivoOutput> <Nodo> 
 * 
 * 3. Al ejecutar ese comando nos dara el archivo con la tabla de enrutamiento 
 *    al nodo que le indicamos. 
 *    
 *    EJEMPLO:
 * 
 *    Ejecutamos -> "./BellmanFord Topologia1.txt Output.txt 2"
 * 
 *    - Se está ejecutando con el archivo de "Topologia1.txt"
 *    - La tabla de enrutamiento se esta mandando a "Output.txt"
 *    - tabla de enrutamiento del nodo 2
 */

//importacion de la libreria bits/stdc++.h que cotiene la mayoria de librerias utiles
#include<bits/stdc++.h>
#include <windows.h>
//Declaramos el entorno en el que vamos a usar, en este caso el estandar
using namespace std;
// Algunas simplificaciones de algunas estructuras que usaremos recurrentemente 
// son simplificaciones de sintaxis mas que todo 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

//variables utilizadas para contar el tiempo 
double PCFreq = 0.0;
__int64 CounterStart = 0;

//Declaracion de N como un numero bastante grande, mas que todo para el algoritmo de bellman-ford
//Lo ponemos como const por que es una constante en todo el programa 
const int N = 3e5;

// ----------------- DECLARACION DE VARIABLES Y ALGORITMO --------------

// Declaracion de los vectores que almacenaran la distancia y las vias 
vi dist;
vi link;

//Declaracion de la lista de adyacencia 
vpii adj[N];

//Declaracion de las variables de la cantidad de nodos y cantidad de aristas
int CantNodos , CantAristas , nodo;

//Declaracion de funciones
int get_via(int n, int u);
void bellman_ford(int n);
void imprimirRespuesta();
void leerGrafo();
void StartCounter();
double GetCounter();
int calcMemory();
int ProcessMemory();

string center(const string s, const int w);


int main(int argc, char *argv[]){
    //Comenzamos a calcular el tiempo de duracion de nuestro algoritmo 
    //indicamos los archivos de texto tanto de salido como de entrada. 

    // validacion de argumentos 
    if(argc < 4){
        cout << "NO HAY SUFICIENTES ARGUMENTOS" << endl;
        return 0; 
    }

    freopen(argv[1], "r" , stdin);
    freopen(argv[2], "w" , stdout); 

    //input de los nodos y aristas del grafo
    cin >> CantNodos >> CantAristas;

    //asignamos memoria para el vector que contendra las distancias 
    // y el vector que contendra las vias donde tendra que pasar el nodo para llegar al otro nodo
    dist.resize(CantNodos, N);
    link.resize(CantNodos, -1);

    //leemos el grafo 
    leerGrafo();

    //asignamos el valor del argumnto que se refiere al nodo 
    //a la variable del nodo 
    nodo = stoi(argv[3]);

    //validacion del nodo 
    if(nodo >= CantNodos || nodo < 0){
        cout << "NO EXISTE NÚMERO DE NODO " << endl;
        return 0;
    }

    //Comenzamos a tomar el tiempo del algoritmo 
    StartCounter();
    // Ejecutamos el algoritmo de bellmand-ford
    bellman_ford(nodo); 
    //tomamos el tiempo en que termina el algoritmo 
    double time = GetCounter();

    //ponemos el ir por nodo 
    for(int i = 0; i < CantNodos ; i++){
        if(link[i] == nodo) link[i] = i;
    }
    //tomamos la diferencia como tiempo de runtime 
    // PRESENTACION DE LA TABLA DE ENRUTAMIENTO
    imprimirRespuesta();

    cout << "RUNTIME: " << setprecision(15) << time*100 << " ms" << endl; 
    cout << "MEMORY: " << calcMemory() << " bytes usados" << endl; 
    cout << "PROCESS MEMORY AVAILABLE: " << ProcessMemory() << " mb" << endl; 
    return 0;
}

//funcion para calcular la cantidad de memoria utilizada en el programa 
int calcMemory(){
    int res = sizeof(dist) + sizeof(link) + sizeof(CantNodos) + sizeof(CantAristas);
    for(int i = 0; i < CantNodos ; i++){
        res += sizeof(adj[i]) + sizeof(dist[i]) + sizeof(link[i]);
    }
    return res; 
}

int ProcessMemory(){
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    return (statex.ullTotalVirtual - statex.ullAvailVirtual) / (1048576);
}

// Funcion para obtener la via por la que tiene que ir el nodo para llegar al nodo por el camino más corto
// Ponemos como parametros el n que es el nodo al que estamos haciendo la tabla 
// el u es el nodo que está en el indice en la lista de adyacencia
int get_via(int n, int u)
{
    //si el valor de n está en link[u]
    //quiere decir que este nodo esta conectado
    //directamente con el nodo n, es decir son vecinos
    if(link[u] == n) 
    // en ese caso retornamos u porque son vecinos
        return u;
    else
    //caso contrario llamamos recursivamente a la funcion
    //pero esta vez llamamos al nodo que esta directamente enlazado 
    // con n y a la via de u 
        return get_via(n, link[u]);
}

//La complejidad de este algorimo es O(VE)
// donde V son los vertices y E son las aristas
void bellman_ford(int n) {
    
    //Declaramos la distancia hacia el mismo nodo como 0
    dist[n] = 0;
    //la via a traves como se llega a n es n 
    link[n] = n; 

    //asignamos el valor de n a todos los nodos que estan 
    //directamente conectados con n 

    for(int i = 0; i < adj[n].size() ; i++){
        link[adj[n][i].first] = n; 
    }

    //Esta es la parte del algoritmo de bellman Ford
    //el primer bucle se tiene que hacer el relax V - 1 veces
    for(int i = 0; i < CantNodos-1; i++) //Relax vertices-1 veces O(v)
        for(int u = 0; u < CantNodos; u++) // Relax O(E) los 2 loops con lista de adj.  
            for(int j = 0; j < adj[u].size() ; j++){
                //Asignamos al par v los valores de vertice y peso respectivamente 
                pii v = adj[u][j];
                //Si la distancia al vertice es mayor a la distancia de u + la distancia hacia ese vertice
                //Actualizamos el valor de la distancia, ya que se encontro una distancia menor
                if(dist[v.first] > dist[u] + v.second){
                    //Actualizamos la via 
                    link[v.first] = get_via(n , u);
                    //Actualizamos la distancia
                    dist[v.first] = dist[u] + v.second;
                }
            }
}


//imprimir en pantalla

void imprimirRespuesta(){
    int espacio = 13; 
    cout << "*** TABLA DE ENRUTAMIENTO DEL NODO " << nodo << " ***" << endl; 
    cout << "-------------------------------------------" << endl;
    cout << "|" << center("NODO",espacio)
         << "|" << center("DISTANCIA",espacio) 
         << "|" << center("IR POR NODO",espacio) << "|" << endl;
    cout << "-------------------------------------------" << endl;

    for(int i = 0; i < CantNodos ; i++){
        cout << "|" << center(to_string(i),espacio)  
         << "|" << center(to_string(dist[i]),espacio)
         << "|" << center(to_string(link[i]),espacio)
         << "|" << endl;
    }
    cout << "-------------------------------------------" << endl;
}

//leemos la lista de adyacencia

void leerGrafo(){
    for(int i = 0 ; i < CantAristas; i++){
            int n1, n2, peso; 
            cin >> n1 >> n2 >> peso;
            adj[n1].push_back({n2, peso});
            adj[n2].push_back({n1, peso});
        }

}
/*
    **Código para obtener el tiempo de runtime***

    la libreria de std::chrono::high_resolution_clock no está 
    bien implementada en windows, solamente en linux 
    es por ello que daba respuestas como 0 de runtime 
    para ello utilizamos otras funciones de la librería
    windows.h para obtener el tiempo de respuesta 
    extraido de 
    https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
*/

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

// Funcion para poner alinear al centro un string, dando como parametro
// el string y el tamaño que hay para poner el string

string center(const string s, const int w) {
    stringstream ss, spaces;
    int padding = w - s.size();                 
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();  
    if(padding>0 && padding%2!=0)               
        ss << " ";
    return ss.str();
}