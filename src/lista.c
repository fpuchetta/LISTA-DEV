#include "lista.h"

typedef struct {
    void* elemento;
    nodo_t* siguiente;
}nodo_t;

struct lista {
    nodo_t* principio;
    nodo_t* final;
    size_t cantidad_elementos;
};

lista_t* lista_crear(){
    lista_t* lista_creada=malloc(sizeof(lista_t));
    if (!lista_creada){
        return NULL;
    }
    lista_creada->principio=NULL;
    lista_creada->final=NULL;
    lista_creada->cantidad_elementos=0;
    return lista_creada;
}

bool lista_insertar(lista_t *lista, void *elemento){
    if(!lista) return false;
    nodo_t* nodo_a_agregar=malloc(sizeof(nodo_t));
    if (nodo_a_agregar==NULL) return false;
    nodo_a_agregar->elemento=elemento;
    nodo_a_agregar->siguiente=NULL;
    if(lista->final==NULL){
        lista->final=nodo_a_agregar;
        lista->principio=lista->final;
    }else{
        lista->final->siguiente=nodo_a_agregar;
    }
    lista->cantidad_elementos+=1;
    return true;
}

size_t lista_tamanio(lista_t *lista){
    (!lista) ? 0 : lista->cantidad_elementos;
}
void *lista_obtener_elemento(lista_t *lista, int posicion){
    if (!lista || posicion < 0 || posicion >= lista->cantidad_elementos) return NULL;
    int iterando=0;
    nodo_t* actual=lista->principio;
    while(iterando!=posicion){
        actual=actual->siguiente;
        iterando+=1;
    }
    return actual->elemento;
}

void lista_destruir(lista_t *lista){
    if (!lista) return;
    nodo_t* a_destruir=lista->principio;
    nodo_t* siguiente_a_destruir;
    while(a_destruir!=NULL){
        siguiente_a_destruir=a_destruir->siguiente;
        free(a_destruir);
        a_destruir=siguiente_a_destruir;
    }
    free(lista);
}