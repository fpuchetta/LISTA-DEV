#include <stdbool.h>
#include "cola.h"
#include "lista.h"

struct cola {
	lista_t *lista;
};

cola_t *cola_crear()
{
	cola_t *c = malloc(sizeof(cola_t));
	if (!c)
		return NULL;
	c->lista = lista_crear();
	if (!c->lista) {
		free(c);
		return NULL;
	}

	return c;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola)
		return false;
	bool insertado = lista_insertar(cola->lista, elemento);
	return insertado;
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola)
		return NULL;
	void *sacado = lista_sacar_de_posicion(cola->lista, 0);
	return sacado;
}

bool cola_vacia(cola_t *cola)
{
	if (!cola)
		return false;
	return (lista_tamanio(cola->lista) == 0);
}

size_t cola_tamanio(cola_t *cola)
{
	if (!cola)
		return 0;
	return (lista_tamanio(cola->lista));
}

void *cola_frente(cola_t *cola)
{
	if (!cola)
		return NULL;
	void *elemento = lista_obtener_elemento(cola->lista, 0);
	return elemento;
}

void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;
	lista_destruir(cola->lista);
	free(cola);
}