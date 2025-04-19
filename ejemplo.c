#include <stdlib.h>
#include <stdio.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

bool mostrar_int(void *elemento, void *contexto)
{
	int *posicion = contexto;

	int *n = (int *)elemento;
	printf("Elemento en posicion %i: %i\n", *posicion, *n);
	(*posicion)++;
	return true;
}

int main(int argc, char *argv[])
{
	//Este es el ejemplo que armamos en clase
	//Notar que no incluye ejemplos de cola y pila
	//Si la implementación es correcta, se deberían mostrar correctamente 3 veces
	//todos los elementos de la lista en el orden en que fueron insertados

	int uno = 1;
	int dos = 2;
	int tres = 3;

	lista_t *l = lista_crear();
	if (lista_tamanio(l) == 0) {
		printf("Lista vacia!\n");
	}
	if (lista_sacar_de_posicion(l, 0) == NULL) {
		printf("Lista sacar de posicion devuelve null porque esta vacia\n");
	}
	lista_insertar(l, &uno);
	lista_insertar(l, &dos);
	lista_insertar(l, &tres);

	lista_insertar_en_posicion(l, 0, &uno);
	printf("tamanio lista: %lu\n", lista_tamanio(l));
	printf("Muestro los elementos usando el iterador interno:\n");
	int posicion = 0;
	lista_iterar(l, mostrar_int, &posicion);

	printf("\nMuestro los elementos usando lista_obtener_elemento:\n");
	for (int i = 0; i < lista_tamanio(l); i++) {
		int *n = lista_obtener_elemento(l, i);
		printf("Elemento en posicion %i: %i\n", i, *n);
	}

	int *recuperado = lista_sacar_de_posicion(l, 3);
	printf("\nSaque el elemento %i\n", *(recuperado));
	printf("tamanio lista: %lu\n", lista_tamanio(l));
	int *eliminado = (int *)lista_sacar_elemento(l, &uno);
	printf("\nSaque el elemento %i\n", *(eliminado));
	printf("tamanio lista: %lu\n", lista_tamanio(l));
	printf("\nMuestro los elementos usando lista_obtener_elemento:\n");
	for (int i = 0; i < lista_tamanio(l); i++) {
		int *n = lista_obtener_elemento(l, i);
		printf("Elemento en posicion %i: %i\n", i, *n);
	}
	lista_insertar_en_posicion(l, 1, &dos);
	lista_insertar_en_posicion(l, 2, &tres);
	printf("\nMuestro los elementos usando el iterador externo:\n");
	posicion = 0;
	lista_iterador_t *li;
	for (li = lista_iterador_crear(l);
	     lista_iterador_quedan_elementos_por_recorrer(li);
	     lista_iterador_proxima_iteracion(li)) {
		int *n = lista_iterador_obtener_elemento(li);
		printf("Elemento en posicion %i: %i\n", posicion, *n);
		posicion++;
	}
	lista_iterador_destruir(li);

	lista_destruir(l);
	cola_t *cola = cola_crear();

	int a = 100, b = 200, c = 300;

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);

	printf("Frente: %d\n",
	       *(int *)cola_frente(cola)); // Debería mostrar 100

	while (!cola_vacia(cola)) {
		int *x = (int *)cola_desencolar(cola);
		int *frente = (int *)cola_frente(cola);
		if (frente)
			printf("Frente: %d\n", *frente);
		else
			printf("Frente: (cola vacía)\n");
		printf("Desencolado: %d\n", *x);
	}

	cola_destruir(cola);

	return 0;
}
