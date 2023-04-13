#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void inicializar (Tarea* arreglo[], int cant); // Tarea* arreglo[] = Tarea** arreglo
void liberar (Tarea** arreglo, int cant);
void descripcion (Tarea** arreglo);
void cargarTareas (Tarea** arreglo, int cant);

int main () {
    int cant;
    srand(time(NULL)); 
    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cant);
    Tarea **tareasPendientes = (Tarea **) malloc(sizeof(Tarea*)* cant);
    inicializar(tareasPendientes,cant);
    cargarTareas(tareasPendientes);
    Tarea **tareasRealizadas = (Tarea **) malloc(sizeof(Tarea*)* cant);
    return 0;
}

void inicializar(Tarea** arreglo, int cant) {
    for (int i = 0; i < cant; i++) {
        arreglo[i] = NULL;
    }
}

void liberar(Tarea** arreglo, int cant) {
    for (int i = 0; i < cant; i++) {
        free(arreglo[i]);
    }
    free(arreglo);
}

void descripcion(Tarea** arreglo) {
    char aux[100];
    printf("Ingrese la descripcion: ");
    gets(aux);
    arreglo = malloc(sizeof(char) * ((strlen(aux)) + 1));
    strcpy(arreglo,aux);
}

void cargarTareas (Tarea** arreglo, int cant) {
    for (int i = 0; i < cant; i++) {
        arreglo[i] = malloc(sizeof(Tarea));
        arreglo[i]->TareaID = i;
        descripcion(arreglo[i]->Descripcion);
        arreglo[i]->Duracion = 10 + rand() % 91;
    }
}