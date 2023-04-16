#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
};

typedef struct Nodo *Lista;

Lista crearLista();
Lista crearNodo(int id);
Lista quitarNodo(Lista *L);
void cargarTareas(Lista *L);
void descripcion (char** L);
void mostrarTarea(Tarea *T);
void mostrarTodasLasTareas(Lista L);
void liberarLista(Lista *L);
Lista controlarTarea(Lista L1, Lista *L2);
Lista buscaTareaPorId(Lista L1, Lista L2);
Lista buscaTareaPorNombre(Lista L1, Lista L2);

int main () {
    Lista TPendientes, TRealizadas;
    srand(time(NULL));
    TPendientes = crearLista();
    TRealizadas = crearLista();
    cargarTareas(&TPendientes);
    mostrarTodasLasTareas(TPendientes);
    TPendientes = controlarTarea(TPendientes,&TRealizadas);
    printf("\nTareas pendientes:\n");
    mostrarTodasLasTareas(TPendientes);
    printf("\nTareas realizadas:\n");
    mostrarTodasLasTareas(TRealizadas);
    mostrarTarea(&(buscaTareaPorId(TPendientes,TRealizadas))->T);
    mostrarTarea(&(buscaTareaPorNombre(TPendientes,TRealizadas))->T);
    liberarLista(&TRealizadas);
    liberarLista(&TPendientes);
    return 0;
}

Lista crearLista() {
    return NULL;
}

Lista crearNodo(int id) {
    struct Nodo *nodo = malloc(sizeof(struct Nodo));
    printf("-----TAREA N%d-----\n", id);
    nodo->T.TareaID = id;
    nodo->T.Duracion = 10 + rand() % 91;
    descripcion(&nodo->T.Descripcion);
    return nodo;
}

void cargarTareas(Lista *L) {
    int num, id = 1;
    Lista nodo;
    printf("\nDesea cargar tarea? (Si:1/No:0): ");
    scanf("%d", &num);
    fflush(stdin);
    while (num == 1) {
        nodo = crearNodo(id);
        nodo->Siguiente = (*L);
        (*L) = nodo;
        id++;
        printf("\nDesea cargar tarea? (Si:1/No:0): ");
        scanf("%d", &num);
        fflush(stdin);
    }
}

void descripcion(char** L) {
    char aux[100];
    printf("Ingrese la descripcion: ");
    gets(aux);
    *L = malloc(sizeof(char) * ((strlen(aux)) + 1));
    strcpy(*L,aux);
}

void mostrarTarea(Tarea *T) {
    if (T != NULL) {
        printf("\nID Tarea: %d\n", T->TareaID);
        printf("Tarea descripcion: %s\n", T->Descripcion);
        printf("Tarea duracion: %d\n", T->Duracion);
    } else {
        printf("La tarea no existe");
    }
}

void mostrarTodasLasTareas(Lista L) {
    while (L != NULL) {
        mostrarTarea(&L->T);
        L = L->Siguiente;
    }
}

void liberarLista(Lista *L) {
    struct Nodo *aux;
    while ((*L) != NULL) {
        aux = *L;
        (*L) = (*L)->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }   
}

Lista controlarTarea(Lista L1, Lista *L2) {
    Lista aux, LP;
    int num;
    LP = crearLista();
    puts("\n-----CONTROLAR TAREAS-----");
    while (L1 != NULL) {
        mostrarTarea(&L1->T);
        printf("\nSe completo la tarea? (Si:1/No:0)");
        scanf("%d", &num);
        if (num == 1) {
            aux = quitarNodo(&L1);
            aux->Siguiente = (*L2);
            *L2 = aux;
        } else {
            aux = quitarNodo(&L1);
            aux->Siguiente = LP;
            LP = aux;
        }
    }
    return LP;
}

Lista quitarNodo(Lista *L) {
    struct Nodo *nodo = NULL;
    if ((*L) != NULL) {
        nodo = (*L);
        *L = (*L)->Siguiente;
    }
    return (nodo);
}

Lista buscaTareaPorId(Lista L1, Lista L2) {
    int id;
    printf("\nIngrese el ID de la tarea que quiere buscar:\n");
    scanf("%d",&id);
    fflush(stdin);
    while (L1 != NULL) {
        if (L1->T.TareaID == id) {
            puts("\nLa tarea esta en pendientes");
            return (L1);
        }
        L1 = L1->Siguiente;
    }
    while (L2 != NULL) {
        if (L2->T.TareaID == id) {
            puts("La tarea esta en realizadas");
            return (L2);
        }
        L2 = L2->Siguiente;
    }
    return NULL;
}

Lista buscaTareaPorNombre(Lista L1, Lista L2) {
    char palabra[100];
    printf("\nIngrese la palabra clave de la tarea que quiere buscar:\n");
    fflush(stdin);
    gets(palabra);
    fflush(stdin);
    while (L1 != NULL) {
        if (strstr(L1->T.Descripcion,palabra) != NULL) {
            puts("La tarea esta en pendientes");
            return (L1);
        }
        L1 = L1->Siguiente;
    }
    while (L2 != NULL) {
        if (strstr(L2->T.Descripcion,palabra) != NULL) {
            puts("La tarea esta en realizadas");
            return (L2);
        }
        L2 = L2->Siguiente;
    }
    return NULL;
}