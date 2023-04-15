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
void descripcion (char** arreglo);
void cargarTareas (Tarea** arreglo, int cant);
void mostrarTarea(Tarea* arreglo);
void controlarTarea(Tarea** arreglo1,Tarea** arreglo2, int cant);
void mostrarTodo(Tarea** arreglo, int cant);
Tarea* buscarTarea(Tarea** arreglo1,Tarea** arreglo2, int cant);

int main () {
    int cant;
    srand(time(NULL)); 
    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cant);
    fflush(stdin);
    Tarea **tareasPendientes = (Tarea **) malloc(sizeof(Tarea*)* cant);
    inicializar(tareasPendientes,cant);
    cargarTareas(tareasPendientes,cant);
    Tarea **tareasRealizadas = (Tarea **) malloc(sizeof(Tarea*)* cant);
    inicializar(tareasRealizadas,cant);
    controlarTarea(tareasPendientes,tareasRealizadas,cant);
    mostrarTodo(tareasPendientes,cant);
    mostrarTodo(tareasRealizadas,cant);
    mostrarTarea(buscarTarea(tareasPendientes,tareasRealizadas,cant));
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

void descripcion(char** arreglo) {
    char aux[100];
    printf("Ingrese la descripcion: ");
    gets(aux);
    *arreglo = malloc(sizeof(char) * ((strlen(aux)) + 1));
    strcpy(*arreglo,aux);
}

void cargarTareas (Tarea** arreglo, int cant) {
    for (int i = 0; i < cant; i++) {
        arreglo[i] = malloc(sizeof(Tarea));
        arreglo[i]->TareaID = i + 1;
        printf("\nTAREA N%d\n\n", i + 1);
        descripcion(&arreglo[i]->Descripcion);
        arreglo[i]->Duracion = 10 + rand() % 91;
    }
}

void mostrarTarea(Tarea* arreglo) {
    printf("ID Tarea: %d\n", arreglo->TareaID);
    printf("Tarea descripcion: %s\n", arreglo->Descripcion);
    printf("Tarea duracion: %d\n", arreglo->Duracion);
}

void controlarTarea(Tarea** arreglo1,Tarea** arreglo2, int cant) {
    int num;
    int j = 0;
    for (int i = 0; i < cant; i++) {
        printf("Si se completo la siguiente tarea, escriba 1. Caso contrario escriba 0\n\n");
        mostrarTarea(arreglo1[i]);
        printf("Su respuesta: \n");
        scanf("%d", &num);
        if (num == 1) {
            arreglo2[j] = arreglo1[i];
            arreglo1[i] = NULL;
            j++;
        }
    }
}

void mostrarTodo(Tarea** arreglo, int cant) {
    for (int i = 0; i < cant; i++) {
        if (arreglo[i] != NULL) {
            printf("\nTAREA N%d\n\n", i + 1);
            mostrarTarea(arreglo[i]);
        }
    }
}

Tarea* buscarTarea(Tarea** arreglo1,Tarea** arreglo2, int cant) {
    char palabra[100];
    printf("\nIngrese la palabra clave de la tarea que quiere buscar:\n");
    fflush(stdin);
    gets(palabra);
    fflush(stdin);
    for (int i = 0; i < cant; i++) {
        if (arreglo1[i] != NULL) {
            if (strstr(arreglo1[i]->Descripcion,palabra) != NULL) {
                puts("\nLa tarea esta en pendientes\n");
                return (arreglo1[i]);
            }
        }
        if (arreglo2 != NULL) {
            if (strstr(arreglo2[i]->Descripcion,palabra) != NULL) {
                puts("\nLa tarea esta en realizadas\n");
                return (arreglo2[i]);
            }
        }
    }
    return NULL;
}