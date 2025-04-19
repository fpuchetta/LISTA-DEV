#include <stdbool.h>
#include "pila.h"
#include "lista.h"

struct pila {
	lista_t *lista;
};

pila_t *pila_crear()
{
	pila_t *p = malloc(sizeof(pila_t));
	if (!p)
		return NULL;
	p->lista = lista_crear();
	if (!p->lista) {
		free(p);
		return NULL;
	}

	return p;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila)
		return false;
	bool insertado = lista_insertar_en_posicion(pila->lista, 0, elemento);
	return insertado;
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila || lista_tamanio(pila->lista) == 0)
		return NULL;
	void *sacado = lista_sacar_de_posicion(pila->lista, 0);
	return sacado;
}

bool pila_vacia(pila_t *pila)
{
	if (!pila)
		return false;
	return (lista_tamanio(pila->lista) == 0);
}

size_t pila_tamanio(pila_t *pila)
{
	if (!pila)
		return 0;
	return lista_tamanio(pila->lista);
}

void *pila_tope(pila_t *pila)
{
	if (!pila)
		return NULL;
	void *elemento = lista_obtener_elemento(pila->lista, 0);
	return elemento;
}

void pila_destruir(pila_t *pila)
{
	if (!pila)
		return;
	lista_destruir(pila->lista);
	free(pila);
}