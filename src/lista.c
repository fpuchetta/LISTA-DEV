#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *principio;
	nodo_t *final;
	size_t cantidad_elementos;
};

struct lista_iterador {
	nodo_t *nodo_actual;
	bool seguir;
};

nodo_t *iterar_hasta_posicion(lista_t *lista, int posicion)
{
	if (!lista)
		return NULL;
	if (posicion > lista->cantidad_elementos)
		return NULL;
	int iterando = 0;
	nodo_t *actual = lista->principio;
	if (posicion == 0) {
		return actual;
	}
	while (iterando < posicion) {
		actual = actual->siguiente;
		iterando += 1;
	}
	return actual;
}

lista_t *lista_crear()
{
	lista_t *lista_creada = calloc(1,sizeof(lista_t));
	if (!lista_creada) {
		return NULL;
	}
	return lista_creada;
}

bool lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return false;
	nodo_t *nodo_a_agregar = calloc(1,sizeof(nodo_t));
	if (nodo_a_agregar == NULL)
		return false;
	nodo_a_agregar->elemento = elemento;
	if (lista->final == NULL) {
		lista->final = nodo_a_agregar;
		lista->principio = lista->final;
	} else {
		lista->final->siguiente = nodo_a_agregar;
		lista->final = nodo_a_agregar;
	}
	lista->cantidad_elementos += 1;
	return true;
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
	if (!lista || posicion < 0 ||
	    (posicion > lista->cantidad_elementos &&
	     lista->cantidad_elementos != 0))
		return false;
	if (posicion == lista->cantidad_elementos)
		return lista_insertar(lista, elemento);
	nodo_t *nodo_nuevo = calloc(1,sizeof(nodo_t));
	if (!nodo_nuevo)
		return false;
	nodo_nuevo->elemento = elemento;
	if (posicion == 0 && lista->cantidad_elementos == 0) {
		lista->principio = nodo_nuevo;
		lista->final = nodo_nuevo;
	} else if (posicion == 0) {
		nodo_nuevo->siguiente = lista->principio;
		lista->principio = nodo_nuevo;
	} else {
		nodo_t *anterior = iterar_hasta_posicion(lista, posicion - 1);
		nodo_nuevo->siguiente = anterior->siguiente;
		anterior->siguiente = nodo_nuevo;
		if (nodo_nuevo->siguiente == NULL)
			lista->final = nodo_nuevo;
	}
	lista->cantidad_elementos += 1;
	return true;
}

size_t lista_tamanio(lista_t *lista)
{
	return (!lista) ? 0 : lista->cantidad_elementos;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (!lista || posicion < 0 || posicion >= lista->cantidad_elementos)
		return NULL;
	nodo_t *actual = iterar_hasta_posicion(lista, posicion);
	return actual->elemento;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
	if (!lista || posicion > lista->cantidad_elementos || posicion < 0)
		return NULL;
	nodo_t *nodo_anterior;
	nodo_t *aux;
	void *retorno;
	if (lista->cantidad_elementos == 0)
		return NULL;
	if (posicion == 0) {
		aux = lista->principio;
		lista->principio = aux->siguiente;
		if (lista->cantidad_elementos == 1)
			lista->final = NULL;
	} else {
		nodo_anterior = iterar_hasta_posicion(lista, posicion - 1);
		if (!nodo_anterior->siguiente)
			return NULL;

		aux = nodo_anterior->siguiente;

		nodo_anterior->siguiente = aux->siguiente;
		if (!nodo_anterior->siguiente)
			lista->final = nodo_anterior;
	}
	retorno = aux->elemento;
	free(aux);
	lista->cantidad_elementos -= 1;
	return retorno;
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;
	int posicion = lista_buscar_posicion(lista, elemento);
	if (posicion == -1)
		return NULL;
	void* retorno=lista_sacar_de_posicion(lista,posicion);
	return retorno;
}

int lista_buscar_posicion(lista_t *lista, void *elemento)
{
	if (!lista)
		return -1;
	bool encontrado = false;
	nodo_t *actual = lista->principio;
	int posicion = 0;
	while (!encontrado && actual != NULL) {
		if (actual->elemento == elemento) {
			encontrado = true;
		} else {
			actual = actual->siguiente;
			posicion++;
		}
	}
	return (encontrado) ? posicion : -1;
}

void *lista_buscar(lista_t *lista, bool (*criterio)(void *, void *),
		   void *contexto)
{
	if (!lista || !criterio)
		return NULL;
	bool encontrado = false;
	nodo_t *actual = lista->principio;
	while (actual != NULL && !encontrado) {
		encontrado = criterio(actual->elemento, contexto);
		if (!encontrado)
			actual = actual->siguiente;
	}
	return (encontrado) ? actual->elemento : NULL;
}

int lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *contexto)
{
	if (!lista || !f)
		return 0;
	int iterados = 0;
	bool continuar = true;
	nodo_t *actual = lista->principio;
	while (actual != NULL && continuar) {
		continuar = f(actual->elemento, contexto);
		actual = actual->siguiente;
		iterados++;
	}
	return iterados;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;
	nodo_t *a_destruir = lista->principio;
	nodo_t *siguiente_a_destruir;
	while (a_destruir != NULL) {
		siguiente_a_destruir = a_destruir->siguiente;
		free(a_destruir);
		a_destruir = siguiente_a_destruir;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;
	lista_iterador_t *li = malloc(sizeof(lista_iterador_t));
	if (!li)
		return NULL;
	li->nodo_actual = lista->principio;
	li->seguir = (!li->nodo_actual) ? false : true;
	return li;
}

bool lista_iterador_quedan_elementos_por_recorrer(lista_iterador_t *iterador)
{
	return (!iterador) ? false : iterador->seguir;
}

void lista_iterador_proxima_iteracion(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->seguir)
		return;
	iterador->nodo_actual = iterador->nodo_actual->siguiente;
	iterador->seguir = (!iterador->nodo_actual) ? false : true;
}

void *lista_iterador_obtener_elemento(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->seguir)
		return NULL;
	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return;
	free(iterador);
}