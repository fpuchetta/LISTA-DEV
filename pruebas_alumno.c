#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void lista_crear_crea_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar((int)lista_tamanio(lista) == 0, "Lista creada esta vacia");
	pa2m_afirmar(lista_sacar_de_posicion(lista, 0) == NULL,
		     "Lista sacar de posicion devuelve null porque esta vacia");
	lista_destruir(lista);
}

void lista_crear_devuelve_una_lista_valida()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se crea una lista no nula");
	lista_destruir(lista);
}

void sacar_elemento_de_lista_vacia_devuelve_null()
{
	lista_t* lista = lista_crear();
	void* elemento = lista_sacar_de_posicion(lista, 1000);
	pa2m_afirmar(elemento == NULL, "Sacar elemento en posición inválida de lista vacia devuelve NULL");
	lista_destruir(lista);
}

void buscar_elemento_en_lista_vacia_devuelve_menos_uno()
{
	lista_t* lista = lista_crear();
	int elemento = 123;
	int posicion = lista_buscar_posicion(lista, &elemento);
	pa2m_afirmar(posicion == -1, "Buscar un elemento en lista vacía devuelve -1");
	lista_destruir(lista);
}

void lista_insertar_elemento_inserta_correctamente()
{
	int uno = 1;
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_insertar(lista, &uno),
		     "Elemento insertado correctamente");
	pa2m_afirmar((int)lista_tamanio(lista),
		     "La lista tiene un elemento al insertar");
	int *obtenido = lista_obtener_elemento(lista, 0);
	pa2m_afirmar(
		*obtenido == 1,
		"Devuelve el elemento esperado (esperado : %i) | (devuelto: %i)",
		uno, *obtenido);
	lista_destruir(lista);
}

void lista_insertar_inserta_elemento_null()
{
	lista_t *lista = lista_crear();
	bool resultado = lista_insertar(lista, NULL);
	pa2m_afirmar(resultado == true, "Se puede insertar un elemento NULL");
	pa2m_afirmar(lista_tamanio(lista) == 1, "El tamaño se incrementa tras insertar NULL");
	
	lista_destruir(lista);
}

void lista_insertar_devuelve_false_lista_nula()
{
	lista_t *lista = NULL;
	bool resultado = lista_insertar(lista, "Elemento");
	pa2m_afirmar(resultado == false, "Insertar en lista nula devuelve false");
}

void lista_insertar_suma_cantidad_elementos()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	pa2m_afirmar(lista_tamanio(lista) == 3, "La lista tiene 3 elementos tras 3 inserciones");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "El primer elemento es el primero insertado");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b, "El segundo elemento es el segundo insertado");
	pa2m_afirmar(lista_obtener_elemento(lista, 2) == &c, "El tercer elemento es el tercero insertado");
	lista_destruir(lista);
}

void insertar_en_posicion_final_equivale_a_lista_insertar()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	bool exito = lista_insertar_en_posicion(lista, 1, &b);
	pa2m_afirmar(exito, "Insertar en posición igual al tamaño funciona");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b, "Elemento se insertó al final correctamente");
	lista_destruir(lista);
}

void insertar_en_posicion_cero_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	int a = 42;
	bool exito = lista_insertar_en_posicion(lista, 0, &a);
	pa2m_afirmar(exito, "Insertar en posición 0 en lista vacía funciona");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "El elemento está en la posición 0");
	lista_destruir(lista);
}

void insertar_en_posicion_cero_en_lista_con_elementos()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar_en_posicion(lista, 0, &b);
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b, "Elemento insertado al principio es accesible");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &a, "Elemento original se desplazó a la posición 1");
	lista_destruir(lista);
}

void insertar_en_posicion_intermedia()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar_en_posicion(lista, 1, &b);

	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "Primer elemento es correcto");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b, "Elemento intermedio insertado correctamente");
	pa2m_afirmar(lista_obtener_elemento(lista, 2) == &c, "Tercer elemento desplazado correctamente");

	lista_destruir(lista);
}

void insertar_en_lista_nula_devuelve_false()
{
	bool exito = lista_insertar_en_posicion(NULL, 0, "A");
	pa2m_afirmar(!exito, "Insertar en lista NULL devuelve false");
}

void insertar_en_posicion_negativa_devuelve_false()
{
	lista_t *lista = lista_crear();
	bool exito = lista_insertar_en_posicion(lista, -1, "A");
	pa2m_afirmar(!exito, "Insertar en posición negativa devuelve false");
	lista_destruir(lista);
}

void insertar_en_posicion_fuera_de_rango_devuelve_false()
{
	lista_t *lista = lista_crear();
	int a = 1;
	lista_insertar(lista, &a);
	bool exito = lista_insertar_en_posicion(lista, 5, "B");
	pa2m_afirmar(!exito, "Insertar en posición mayor al tamaño devuelve false");
	lista_destruir(lista);
}

void insertar_elemento_null_actualiza_cantidad_y_lo_guarda()
{
	lista_t* lista = lista_crear();

	bool exito = lista_insertar_en_posicion(lista, 0, NULL);

	pa2m_afirmar(exito, "Insertar NULL devuelve true");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista tiene 1 elemento luego de insertar NULL");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == NULL, "El elemento en posición 0 es NULL");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_unico_elemento_devuelve_elemento_y_lista_vacia()
{
	lista_t* lista = lista_crear();
	int a = 999;
	lista_insertar(lista, &a);
	void* sacado = lista_sacar_de_posicion(lista, 0);
	pa2m_afirmar(sacado == &a, "Sacar único elemento devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista queda vacía luego de sacar el único elemento");
	lista_destruir(lista);
}

void lista_sacar_de_posicion_elemento_principio_mueve_puntero()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	void* sacado = lista_sacar_de_posicion(lista, 0);
	pa2m_afirmar(sacado == &a, "Sacar elemento en posición 0 devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista queda con un solo elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b, "El nuevo primer elemento es el segundo original");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_elemento_intermedio_reordena_lista()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	void* sacado = lista_sacar_de_posicion(lista, 1);

	pa2m_afirmar(sacado == &b, "Sacar elemento intermedio devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño se reduce despues de sacar elemento tamanio: %u",lista_tamanio(lista));
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "El primer elemento sigue siendo el mismo");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &c, "El tercero se desplaza a la posición 1");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_ultimo_elemento_actualiza_final()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	void* sacado = lista_sacar_de_posicion(lista, 1);

	pa2m_afirmar(sacado == &b, "Sacar ultimo elemento devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista queda con un elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "El elemento restante es el primero");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_y_elemento_de_lista_nula_devuelve_null(){
	lista_t* lista=NULL;
	int a=1;
	pa2m_afirmar(lista_sacar_de_posicion(lista,0)==NULL,"Sacar elemento de lista nula devuelve null con posicion");
	pa2m_afirmar(lista_sacar_elemento(lista,&a)==NULL,"Sacar elemento de lista nula devuelve null con elemento");
}

void lista_sacar_de_posicion_y_elemento_de_lista_vacia_devuelve_null(){
	lista_t* lista=lista_crear();
	int a=1;
	pa2m_afirmar(lista!= NULL,"Lista creada correctamente");
	pa2m_afirmar(lista_tamanio(lista)==0,"Lista con 0 elementos");
	pa2m_afirmar(!lista_sacar_de_posicion(lista,0),"Lista sacar de posicion devuelve null por estar vacia");
	pa2m_afirmar(!lista_sacar_elemento(lista,&a),"Lista sacar elemento devuelve null por estar vacia");
	lista_destruir(lista);
}

void lista_sacar_de_posicion_y_elemento_invalida_devuelve_null(){
	lista_t* lista=lista_crear();
	int a=1,b=2,c=5;
	pa2m_afirmar(lista_insertar(lista,&a),"Inserto un elemento");
	pa2m_afirmar(lista_insertar(lista,&b),"Inserto otro elemento");
	pa2m_afirmar(!lista_sacar_de_posicion(lista,10),"Lista sacar de posicion devuelve null por posicion invalida");
	pa2m_afirmar(!lista_sacar_elemento(lista,&c),"Lista sacar elemento devuelve null por elemento invalido");
	lista_destruir(lista);
}

void lista_obtener_funcionamiento_esperado(){
	lista_t* lista=lista_crear();
	int a=0,b=1;
	pa2m_afirmar(!lista_obtener_elemento(lista,0),"Devuelve null al obtener elemento en lista vacia");
	lista_insertar(lista,&a);
	pa2m_afirmar(lista_obtener_elemento(lista,0)==&a,"Obtengo el elemento en la posicion cero");
	lista_insertar(lista,&b);
	pa2m_afirmar(lista_obtener_elemento(lista,1)==&b,"Obtengo el elemento en la posicion 1");
	lista_destruir(lista);
}

void lista_obtener_funcionamiento_incorrecto(){
	lista_t* lista=lista_crear();
	int a=1;
	pa2m_afirmar(!lista_obtener_elemento(NULL,0),"Lista obtener devuelve null en lista nula");
	pa2m_afirmar(!lista_obtener_elemento(lista,-1),"Lista obtener devuelve null en posicion invalida");
	pa2m_afirmar(lista_insertar(lista,&a),"Elemento insertado correctamente");
	pa2m_afirmar(!lista_obtener_elemento(lista,100),"Lista obtener devuelve null en posicion fuera de rango");
	lista_destruir(lista);
}

void lista_sacar_elemento_saca_correctamente()
{
	int uno = 1;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &uno);
	int *obtenido = lista_sacar_elemento(lista, &uno);
	pa2m_afirmar(
		*obtenido == 1,
		"Lista_sacar_elemento devuelve el valor esperado (esperado: %i) | (devuelto: %i)",
		uno, *obtenido);
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La lista achica su tamanio luego de sacar un elemento");
	lista_destruir(lista);
}

void lista_sacar_elemento_existente_devuelve_elemento_y_reduce_tamanio()
{
	lista_t* lista = lista_crear();
	int a = 10, b = 20, c = 30;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	void* sacado = lista_sacar_elemento(lista, &b);

	pa2m_afirmar(sacado == &b, "Se devuelve el puntero correcto al eliminar un elemento existente");
	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño se reduce luego de eliminar un elemento");

	lista_destruir(lista);
}

void lista_sacar_primer_elemento_funciona()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	void* sacado = lista_sacar_elemento(lista, &a);

	pa2m_afirmar(sacado == &a, "Sacar el primer elemento devuelve correctamente el puntero");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b, "El segundo elemento se desplaza a la primera posición");

	lista_destruir(lista);
}

void lista_sacar_ultimo_elemento_funciona()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	void* sacado = lista_sacar_elemento(lista, &b);

	pa2m_afirmar(sacado == &b, "Sacar el último elemento devuelve correctamente el puntero");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista queda con un solo elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a, "El elemento restante es el primero");

	lista_destruir(lista);
}

void lista_sacar_elemento_null_insertado_funciona()
{
	lista_t* lista = lista_crear();
	int a = 1;
	lista_insertar(lista, &a);
	lista_insertar(lista, NULL);  // insertamos NULL

	void* sacado = lista_sacar_elemento(lista, NULL);

	pa2m_afirmar(sacado == NULL, "Se puede sacar un elemento NULL si fue insertado");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista queda con un elemento después de sacar NULL");

	lista_destruir(lista);
}


int main()
{
	pa2m_nuevo_grupo("============== Pruebas lista ===============");
	pa2m_nuevo_grupo("Pruebas lista_crear");
	lista_crear_devuelve_una_lista_valida();
	lista_crear_crea_lista_vacia();
	sacar_elemento_de_lista_vacia_devuelve_null();
	buscar_elemento_en_lista_vacia_devuelve_menos_uno();

	pa2m_nuevo_grupo("Pruebas lista_insertar");
	lista_insertar_elemento_inserta_correctamente();
	lista_insertar_suma_cantidad_elementos();
	lista_insertar_inserta_elemento_null();

	pa2m_nuevo_grupo("Pruebas lista_insertar_posicion");
	pa2m_nuevo_grupo("Parametros validos");
	insertar_en_posicion_final_equivale_a_lista_insertar();
	insertar_en_posicion_cero_en_lista_vacia();
	insertar_en_posicion_cero_en_lista_con_elementos();
	insertar_en_posicion_intermedia();

	pa2m_nuevo_grupo("Parametros invalidos");
	insertar_en_lista_nula_devuelve_false();
	insertar_en_posicion_negativa_devuelve_false();
	insertar_en_posicion_fuera_de_rango_devuelve_false();
	insertar_elemento_null_actualiza_cantidad_y_lo_guarda();

	pa2m_nuevo_grupo("Pruebas lista_sacar_de_posicion y sacar_elemento");
	pa2m_nuevo_grupo("Parametros validos");
	lista_sacar_de_posicion_unico_elemento_devuelve_elemento_y_lista_vacia();
	lista_sacar_de_posicion_elemento_principio_mueve_puntero();
	lista_sacar_de_posicion_elemento_intermedio_reordena_lista();
	lista_sacar_de_posicion_ultimo_elemento_actualiza_final();
	lista_sacar_elemento_saca_correctamente();
	lista_sacar_elemento_existente_devuelve_elemento_y_reduce_tamanio();
	lista_sacar_primer_elemento_funciona();
	lista_sacar_ultimo_elemento_funciona();
	lista_sacar_elemento_null_insertado_funciona();
	
	pa2m_nuevo_grupo("Parametros invalidos");
	lista_sacar_de_posicion_y_elemento_de_lista_nula_devuelve_null();
	lista_sacar_de_posicion_y_elemento_de_lista_vacia_devuelve_null();
	lista_sacar_de_posicion_y_elemento_invalida_devuelve_null();

	pa2m_nuevo_grupo("Pruebas lista_obtener_elemento");
	lista_obtener_funcionamiento_esperado();
	lista_obtener_funcionamiento_incorrecto();

	pa2m_nuevo_grupo("Pruebas lista_buscar_posicion");
	return pa2m_mostrar_reporte();
}
