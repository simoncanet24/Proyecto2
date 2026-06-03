#include <iostream>
#include <string>
#include <thread>
#include<windows.h>
#include "Archivos.h"
using namespace std;

auto jugador= Archivos::descargarJugador("jugador.txt");
auto enemigos = Archivos::descargarEnemigos("enemigos.txt");
auto objetos = Archivos::descargarObjetos("objetos.txt");


int main() {

    cout<<("Te despiertas en la calle en una ciudad mientras llueve");
    cout<<("No sabes quien eres ni donde estas");
    cout<<"\n";
    cout<<("Que deberia de hacer");
    cout<<(" [1] Gritar por ayuda");
    cout<<(" [2]Caminar por la calle");
    int choice;
    if (choice ==1)
    {
        cout<<("Parece que no hay nadie por las calles en este momento, solo se escuchan las gotas de lluvia");

    }
    else
    {
        cout<<("Caminas por las calles pero no ves a nadie, solo un gato el cual llevas a un lugar seguro donde no le caiga lluvia");
    }
    cout<<"Te has encontrado con un enemigo amenazandote"<<"\n";


    cout<<"\n Press ENTER para salir";
    cin.ignore();
    cin.get();
    return 0;

    /* ----------------------------------------------
     * PROYECTO 2
     * ----------------------------------------------
     * no es un juego gráfico
     * simulacion
     * estado del mundo cambia durante ejecuccion.
     * archivos de salida
     * puede ser cualquier tematica
     * cada vez que se corra el programa tiene que tirar
     * algo distinto.
     * Sistema de suerte si el jugador desea.
     * ----------------------------------------------
     * Temas de Progra 2 (no hay que usarlos todos):
     *
     *      1...OOP: Clases y responsabilidades claras.
     *
     *      2...Clases -Uso correcto de herencia, polimorfismo, relaciones entre clases.
     *
     *      3...Manejo responsable de memoria, con punteros, o memoria inteligente.
     *
     *      4...Programacion generica - Estructuras o Iteradores (templates e interfaces)
     *          iteradores (no se)
     *
     *      5...Sobrecarga de operadores, y excepciones
     *
     *      6...Manejo de archivos, errores, validaciones. -
     *          Archivos con formato claro.
     *          Archivos de entrada - Informacion necesaria para iniciar el juego
     *          Archivos de salida - Revisar el comportamiento y resultado final. Bitacora
     *
     *      7...Aplicacion de patrones de diseño, cuando sea necesario.
     *
     *      8...Solucion simple, clara. NO HAY NECESIDAD DE USAR TODOS LOS TEMAS.
     *
     * -----------------------------------------------
     * QUE HAY QUE HACER
     *
     *  una simulacion que cargue, haga
     *  Registros en archivos (juego).
     *  Reporte final de la aventura, y hechos relevantes
     *
     * ej. (enemigos.txt, estadodelpersonaje.txt)
     *
     * -----------------------------------------------
     * ESTRUCTURA DEL JUEGO
     *
     * Mundo:
     *
     * Personajes: Se realizo la clase jugador y enemigos la cual la clase base es la de SistemaGeneral
     *
     * Elementos: Inventario
     *
     * Eventos: Se esta realizando la bitacora,Reporte y archivos
     *
     * Progreso: Va de la mano con eventos
     *
     * Registro: En proceso
     *
     * Reporte: En proceso
     *
     * -----------------------------------------------
     * REQUERIMIENTOS
     * Modular, mantenible, bajo acoplamiento
     * en ingles
     * rutas relativas
     * la ejecucion debe poder reproducirse con los archivos entregados.
     * El sistema debe manejar errores
     * -----------------------------------------------
     *
     *
     *
     *
     */

    return 0;
}
