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
Lista controlarTarea(Lista L1, Lista *L2, Lista *L3);
Lista buscaTareaPorId(Lista L1, int id);
Lista buscaTareaPorNombre(Lista L1, Lista L2);
void eliminarTarea(struct Nodo* nodo);
struct Nodo* quitarNodoPorId(Lista *L, int id);
void insertarNodo(Lista *L, struct Nodo* nodo);

int main () {
    Lista TPendientes, TRealizadas, TProceso, aux;
    int id, list, resp, yes = 1;
    srand(time(NULL));
    TPendientes = crearLista();
    TRealizadas = crearLista();
    TProceso = crearLista();
    cargarTareas(&TPendientes);
    // mostrarTodasLasTareas(TPendientes);
    // TPendientes = controlarTarea(TPendientes,&TRealizadas,&TProceso);
    // printf("\nTareas pendientes:\n");
    // mostrarTodasLasTareas(TPendientes);
    // printf("\nTareas realizadas:\n");
    // mostrarTodasLasTareas(TRealizadas);
    // mostrarTarea(&(buscaTareaPorId(TPendientes,TRealizadas))->T);
    // mostrarTarea(&(buscaTareaPorNombre(TPendientes,TRealizadas))->T);
    // eliminarTarea(&TPendientes,2);
    // mostrarTodasLasTareas(TPendientes);
    while (yes == 1) {
        printf("\n-----TAREAS PENDIENTES-----\n");
        mostrarTodasLasTareas(TPendientes);
        printf("\n-----TAREAS EN PROCESO-----\n");
        mostrarTodasLasTareas(TProceso);
        printf("\n-----TAREAS REALIZADAS-----\n");
        mostrarTodasLasTareas(TRealizadas);
        printf("\nElija el id de la tarea que quiere seleccionar\n");
        scanf("%d", &id);
        if (buscaTareaPorId(TPendientes,id)) {
            list = 1;
        } else {
            if (buscaTareaPorId(TProceso,id)) {
                list = 2;
            } else {
                if (buscaTareaPorId(TRealizadas,id)) {
                    list = 3;
                } else {
                    list = 0;
                }
            }
        }
        switch (list) {
            case 1:
                printf("Donde desea mover la tarea?\n");
                printf("Realizadas:1\n");
                printf("En Proceso:2\n");
                printf("No mover:3\n");
                scanf("%d",&resp);
                fflush(stdin);
                switch (resp) {
                    case 1:
                        aux = quitarNodoPorId(&TPendientes,resp);
                        insertarNodo(&TRealizadas,aux);
                    break;
                    case 2:
                        aux = quitarNodoPorId(&TPendientes,resp);
                        insertarNodo(&TProceso,aux);
                    break;
                }
            break;
            case 2:
                printf("Donde desea mover la tarea?\n");
                printf("Pendientes:1\n");
                printf("Realizadas:2\n");
                printf("No mover:3\n");
                scanf("%d",&resp);
                fflush(stdin);
                switch (resp) {
                    case 1:
                        aux = quitarNodoPorId(&TProceso,resp);
                        insertarNodo(&TPendientes,aux);
                    break;
                    case 2:
                        aux = quitarNodoPorId(&TProceso,resp);
                        insertarNodo(&TRealizadas,aux);
                    break;
                }
            break;
            case 3:
                printf("Donde desea mover la tarea?\n");
                printf("Pendientes:1\n");
                printf("En Proceso:2\n");
                printf("No mover:3\n");
                scanf("%d",&resp);
                fflush(stdin);
                switch (resp) {
                    case 1:
                        aux = quitarNodoPorId(&TRealizadas,resp);
                        insertarNodo(&TPendientes,aux);
                    break;
                    case 2:
                        aux = quitarNodoPorId(&TRealizadas,resp);
                        insertarNodo(&TProceso,aux);
                    break;
                }
            break;
            default:
                printf("No existe la tarea");
            break;
        }
        printf("Quiere mover otra tarea? (Si:1/No:0)\n");
        scanf("%d", &yes);
    }
    printf("\n-----TAREAS PENDIENTES-----\n");
    mostrarTodasLasTareas(TPendientes);
    printf("\n-----TAREAS EN PROCESO-----\n");
    mostrarTodasLasTareas(TProceso);
    printf("\n-----TAREAS REALIZADAS-----\n");
    mostrarTodasLasTareas(TRealizadas);
    liberarLista(&TPendientes);
    liberarLista(&TRealizadas);
    liberarLista(&TProceso);
    return 0;
}

Lista crearLista() {
    return NULL;
}

Lista crearNodo(int id) {
    struct Nodo *nodo = malloc(sizeof(struct Nodo));
    printf("-----TAREA N%d-----\n", id);
    nodo->T.TareaID = id;
    descripcion(&nodo->T.Descripcion);
    nodo->T.Duracion = 10 + rand() % 91;
    nodo->Siguiente = NULL;
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
    int suma = 0;
    if (L == NULL) {
        puts("No hay tareas que mostrar");
    }
    while (L != NULL) {
        mostrarTarea(&L->T);
        suma = suma + L->T.Duracion;
        L = L->Siguiente;
    }
    printf("La suma total de tiempo es %d\n", suma);
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

Lista controlarTarea(Lista L1, Lista *L2, Lista *L3) {
    Lista aux, LP;
    int num;
    LP = crearLista();
    puts("\n-----CONTROLAR TAREAS-----");
    while (L1 != NULL) {
        mostrarTarea(&L1->T);
        printf("\nA donde desea mover la tarea?\n(Pendientes:0/EnProceso:1/Realizadas:2)");
        scanf("%d", &num);
        if (num == 1) {
            aux = quitarNodo(&L1);
            aux->Siguiente = (*L2);
            *L2 = aux;
        } else {
            if (num == 2) {
                aux = quitarNodo(&L1);
                aux->Siguiente = (*L3);
                *L3 = aux;
            } else {
                aux = quitarNodo(&L1);
                aux->Siguiente = LP;
                LP = aux;
            }
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

Lista buscaTareaPorId(Lista L1, int id) {
    while (L1 != NULL) {
        if (L1->T.TareaID == id) {
            return (L1);
        }
        L1 = L1->Siguiente;
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

// void eliminarTarea(Lista *L, int id) {
//     struct Nodo *aux = *L;
//     struct Nodo *anterior = NULL;
//     while (aux != NULL) {
//         if (aux->T.TareaID == id) {
//             if (anterior == NULL) {
//                 (*L) = aux->Siguiente;
//             } else {
//                 anterior->Siguiente = aux->Siguiente;
//             }
//             free(aux->T.Descripcion);
//             free(aux);
//             return;
//         }
//         anterior = aux;
//         aux = aux->Siguiente;
//     }
// }

void eliminarTarea(struct Nodo* nodo) {
    free(nodo->T.Descripcion);
    free(nodo);
}

struct Nodo* quitarNodoPorId(Lista *L, int id) {
    struct Nodo *auxSiguiente, *auxAnterior;
    if ((*L) != NULL) {
        if ((*L)->Siguiente == NULL){
            if ((*L)->T.TareaID == id) {
                auxAnterior = (*L);
                (*L) = NULL;
                return (auxAnterior);
            }   
        } else {
            auxAnterior = (*L);
            auxSiguiente = (*L)->Siguiente;
            while (auxSiguiente->Siguiente != NULL && auxSiguiente->T.TareaID != id) {
                auxAnterior = auxSiguiente;
                auxSiguiente = auxSiguiente->Siguiente;
            }
            if (auxSiguiente->T.TareaID == id) {
                auxAnterior->Siguiente = auxSiguiente->Siguiente;
                return (auxSiguiente);
            }
        }
    }
    printf("No se encontro el nodo\n");
    return NULL;
}

void insertarNodo(Lista *L, struct Nodo* nodo) {
    nodo->Siguiente = (*L); 
    (*L) = nodo;
}