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
	lista_t *lista = lista_crear();
	void *elemento = lista_sacar_de_posicion(lista, 1000);
	pa2m_afirmar(
		elemento == NULL,
		"Sacar elemento en posición inválida de lista vacia devuelve NULL");
	lista_destruir(lista);
}

void buscar_elemento_en_lista_vacia_devuelve_menos_uno()
{
	lista_t *lista = lista_crear();
	int elemento = 123;
	int posicion = lista_buscar_posicion(lista, &elemento);
	pa2m_afirmar(posicion == -1,
		     "Buscar un elemento en lista vacía devuelve -1");
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
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "El tamaño se incrementa tras insertar NULL");

	lista_destruir(lista);
}

void lista_insertar_devuelve_false_lista_nula()
{
	lista_t *lista = NULL;
	bool resultado = lista_insertar(lista, "Elemento");
	pa2m_afirmar(resultado == false,
		     "Insertar en lista nula devuelve false");
}

void lista_insertar_suma_cantidad_elementos()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La lista tiene 3 elementos tras 3 inserciones");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "El primer elemento es el primero insertado");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b,
		     "El segundo elemento es el segundo insertado");
	pa2m_afirmar(lista_obtener_elemento(lista, 2) == &c,
		     "El tercer elemento es el tercero insertado");
	lista_destruir(lista);
}

void insertar_en_posicion_final_equivale_a_lista_insertar()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	bool exito = lista_insertar_en_posicion(lista, 1, &b);
	pa2m_afirmar(exito, "Insertar en posición igual al tamaño funciona");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b,
		     "Elemento se insertó al final correctamente");
	lista_destruir(lista);
}

void insertar_en_posicion_cero_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	int a = 42;
	bool exito = lista_insertar_en_posicion(lista, 0, &a);
	pa2m_afirmar(exito, "Insertar en posición 0 en lista vacía funciona");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "El elemento está en la posición 0");
	lista_destruir(lista);
}

void insertar_en_posicion_cero_en_lista_con_elementos()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar_en_posicion(lista, 0, &b);
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b,
		     "Elemento insertado al principio es accesible");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &a,
		     "Elemento original se desplazó a la posición 1");
	lista_destruir(lista);
}

void insertar_en_posicion_intermedia()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar_en_posicion(lista, 1, &b);

	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "Primer elemento es correcto");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b,
		     "Elemento intermedio insertado correctamente");
	pa2m_afirmar(lista_obtener_elemento(lista, 2) == &c,
		     "Tercer elemento desplazado correctamente");

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
	pa2m_afirmar(!exito,
		     "Insertar en posición mayor al tamaño devuelve false");
	lista_destruir(lista);
}

void insertar_elemento_null_actualiza_cantidad_y_lo_guarda()
{
	lista_t *lista = lista_crear();

	bool exito = lista_insertar_en_posicion(lista, 0, NULL);

	pa2m_afirmar(exito, "Insertar NULL devuelve true");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La lista tiene 1 elemento luego de insertar NULL");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == NULL,
		     "El elemento en posición 0 es NULL");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_unico_elemento_devuelve_elemento_y_lista_vacia()
{
	lista_t *lista = lista_crear();
	int a = 999;
	lista_insertar(lista, &a);
	void *sacado = lista_sacar_de_posicion(lista, 0);
	pa2m_afirmar(sacado == &a, "Sacar único elemento devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La lista queda vacía luego de sacar el único elemento");
	lista_destruir(lista);
}

void lista_sacar_de_posicion_elemento_principio_mueve_puntero()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	void *sacado = lista_sacar_de_posicion(lista, 0);
	pa2m_afirmar(sacado == &a,
		     "Sacar elemento en posición 0 devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La lista queda con un solo elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b,
		     "El nuevo primer elemento es el segundo original");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_elemento_intermedio_reordena_lista()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	void *sacado = lista_sacar_de_posicion(lista, 1);

	pa2m_afirmar(sacado == &b,
		     "Sacar elemento intermedio devuelve el correcto");
	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"El tamaño se reduce despues de sacar elemento tamanio: %u",
		lista_tamanio(lista));
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "El primer elemento sigue siendo el mismo");
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &c,
		     "El tercero se desplaza a la posición 1");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_ultimo_elemento_actualiza_final()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	void *sacado = lista_sacar_de_posicion(lista, 1);

	pa2m_afirmar(sacado == &b,
		     "Sacar ultimo elemento devuelve el correcto");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La lista queda con un elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "El elemento restante es el primero");

	lista_destruir(lista);
}

void lista_sacar_de_posicion_y_elemento_de_lista_nula_devuelve_null()
{
	lista_t *lista = NULL;
	int a = 1;
	pa2m_afirmar(lista_sacar_de_posicion(lista, 0) == NULL,
		     "Sacar elemento de lista nula devuelve null con posicion");
	pa2m_afirmar(lista_sacar_elemento(lista, &a) == NULL,
		     "Sacar elemento de lista nula devuelve null con elemento");
}

void lista_sacar_de_posicion_y_elemento_de_lista_vacia_devuelve_null()
{
	lista_t *lista = lista_crear();
	int a = 1;
	pa2m_afirmar(lista != NULL, "Lista creada correctamente");
	pa2m_afirmar(lista_tamanio(lista) == 0, "Lista con 0 elementos");
	pa2m_afirmar(!lista_sacar_de_posicion(lista, 0),
		     "Lista sacar de posicion devuelve null por estar vacia");
	pa2m_afirmar(!lista_sacar_elemento(lista, &a),
		     "Lista sacar elemento devuelve null por estar vacia");
	lista_destruir(lista);
}

void lista_sacar_de_posicion_y_elemento_invalida_devuelve_null()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 5;
	pa2m_afirmar(lista_insertar(lista, &a), "Inserto un elemento");
	pa2m_afirmar(lista_insertar(lista, &b), "Inserto otro elemento");
	pa2m_afirmar(
		!lista_sacar_de_posicion(lista, 10),
		"Lista sacar de posicion devuelve null por posicion invalida");
	pa2m_afirmar(
		!lista_sacar_elemento(lista, &c),
		"Lista sacar elemento devuelve null por elemento invalido");
	lista_destruir(lista);
}

void lista_obtener_funcionamiento_esperado()
{
	lista_t *lista = lista_crear();
	int a = 0, b = 1;
	pa2m_afirmar(!lista_obtener_elemento(lista, 0),
		     "Devuelve null al obtener elemento en lista vacia");
	lista_insertar(lista, &a);
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "Obtengo el elemento en la posicion cero");
	lista_insertar(lista, &b);
	pa2m_afirmar(lista_obtener_elemento(lista, 1) == &b,
		     "Obtengo el elemento en la posicion 1");
	lista_destruir(lista);
}

void lista_obtener_funcionamiento_incorrecto()
{
	lista_t *lista = lista_crear();
	int a = 1;
	pa2m_afirmar(!lista_obtener_elemento(NULL, 0),
		     "Lista obtener devuelve null en lista nula");
	pa2m_afirmar(!lista_obtener_elemento(lista, -1),
		     "Lista obtener devuelve null en posicion invalida");
	pa2m_afirmar(lista_insertar(lista, &a),
		     "Elemento insertado correctamente");
	pa2m_afirmar(!lista_obtener_elemento(lista, 100),
		     "Lista obtener devuelve null en posicion fuera de rango");
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
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	void *sacado = lista_sacar_elemento(lista, &b);

	pa2m_afirmar(
		sacado == &b,
		"Se devuelve el puntero correcto al eliminar un elemento existente");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "El tamaño se reduce luego de eliminar un elemento");

	lista_destruir(lista);
}

void lista_sacar_primer_elemento_funciona()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	void *sacado = lista_sacar_elemento(lista, &a);

	pa2m_afirmar(
		sacado == &a,
		"Sacar el primer elemento devuelve correctamente el puntero");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &b,
		     "El segundo elemento se desplaza a la primera posición");

	lista_destruir(lista);
}

void lista_sacar_ultimo_elemento_funciona()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

	void *sacado = lista_sacar_elemento(lista, &b);

	pa2m_afirmar(
		sacado == &b,
		"Sacar el último elemento devuelve correctamente el puntero");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La lista queda con un solo elemento");
	pa2m_afirmar(lista_obtener_elemento(lista, 0) == &a,
		     "El elemento restante es el primero");

	lista_destruir(lista);
}

void lista_sacar_elemento_null_insertado_funciona()
{
	lista_t *lista = lista_crear();
	int a = 1;
	lista_insertar(lista, &a);
	lista_insertar(lista, NULL); // insertamos NULL

	void *sacado = lista_sacar_elemento(lista, NULL);

	pa2m_afirmar(sacado == NULL,
		     "Se puede sacar un elemento NULL si fue insertado");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La lista queda con un elemento después de sacar NULL");

	lista_destruir(lista);
}

void lista_buscar_posicion_encuentra_pos_correcta(){
	lista_t* lista=lista_crear();
	int a=1,b=2,c=3;
	lista_insertar(lista,&a);
	lista_insertar(lista,&b);
	lista_insertar(lista,&c);
	int posicion_a=lista_buscar_posicion(lista,&a);
	int posicion_b=lista_buscar_posicion(lista,&b);
	int posicion_c=lista_buscar_posicion(lista,&c);
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_a)==&a,"Posicion primer elemento correcta");
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_b)==&b,"Posicion segundo elemento correcta");
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_c)==&c,"Posicion tercer elemento correcta");
	lista_destruir(lista);
}
void lista_buscar_posicion_encuentra_null(){
	lista_t* lista=lista_crear();
	void* a=NULL;
	lista_insertar(lista,&a);
	lista_insertar(lista,&a);
	lista_insertar(lista,&a);
	int posicion_a=lista_buscar_posicion(lista,&a);
	int posicion_b=lista_buscar_posicion(lista,&a);
	int posicion_c=lista_buscar_posicion(lista,&a);
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_a)==&a,"Primer elemento null posicion correcta");
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_b)==&a,"Segundo elemento null posicion correcta");
	pa2m_afirmar(lista_obtener_elemento(lista,posicion_c)==&a,"Tercer elemento null posicion correcta");
	lista_destruir(lista);
}

void lista_buscar_posicion_no_encuentra_pos(){
	lista_t* lista=lista_crear();
	int a=1;
	lista_insertar(lista,&a);
	int posicion=lista_buscar_posicion(lista,NULL);
	pa2m_afirmar(posicion==-1,"Posicion invalida por elemento invalido");
	lista_destruir(lista);
}

void lista_buscar_posicion_lista_invalida(){
	lista_t* lista=NULL;
	int a=1;
	int posicion=lista_buscar_posicion(lista,&a);
	pa2m_afirmar(posicion==-1,"Buscar posicion en lista invalida devuelve NULL");
}

void lista_buscar_posicion_lista_vacia(){
	lista_t* lista=lista_crear();
	int a=1;
	int posicion=lista_buscar_posicion(lista,&a);
	pa2m_afirmar(posicion==-1,"Buscar posicion en lista vacia devuelve NULL");
	lista_destruir(lista);
}

bool es_igual_a(void* elemento, void* contexto)
{
	return *((int*)elemento) == *((int*)contexto);
}

bool iterar_hasta_encontrar(void* elemento, void* contexto)
{
	if (*((int*)elemento) == *((int*)contexto)) return false;
	return true;
}

void lista_buscar_e_iterar_encuentran_elementos()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	int objetivo = 2;
	void* encontrado = lista_buscar(lista, es_igual_a, &objetivo);
	pa2m_afirmar(encontrado == &b, "lista_buscar encuentra el elemento buscado");

	int iterados = lista_iterar(lista, iterar_hasta_encontrar, &objetivo);
	pa2m_afirmar(iterados == 2, "lista_iterar se detiene cuando encuentra el objetivo");

	lista_destruir(lista);
}

void lista_buscar_e_iterar_iterados_correctos()
{
	lista_t* lista = lista_crear();
	int a = 10, b = 20, c = 30;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	int no_presente = 99;
	void* encontrado = lista_buscar(lista, es_igual_a, &no_presente);
	pa2m_afirmar(encontrado == NULL, "lista_buscar devuelve NULL si no encuentra el elemento");

	int iterados = lista_iterar(lista, iterar_hasta_encontrar, &no_presente);
	pa2m_afirmar(iterados == 3, "lista_iterar recorre todos los elementos si no encuentra el objetivo");

	lista_destruir(lista);
}

void lista_buscar_e_iterar_funcion_nula()
{
	lista_t* lista = lista_crear();
	int a = 1;
	lista_insertar(lista, &a);

	void* encontrado = lista_buscar(lista, NULL, &a);
	pa2m_afirmar(encontrado == NULL, "lista_buscar con función nula devuelve NULL");
	int iterados = lista_iterar(lista, NULL, &a);
	pa2m_afirmar(iterados == 0, "lista_iterar con función nula no recorre elementos");

	lista_destruir(lista);
}

void lista_buscar_e_iterar_lista_nula()
{
	int contexto = 1;
	void* encontrado = lista_buscar(NULL, es_igual_a, &contexto);
	pa2m_afirmar(encontrado == NULL, "lista_buscar con lista NULL devuelve NULL");

	int iterados = lista_iterar(NULL, iterar_hasta_encontrar, &contexto);
	pa2m_afirmar(iterados == 0, "lista_iterar con lista NULL devuelve 0");
}

void lista_buscar_e_iterar_lista_vacia()
{
	lista_t* lista = lista_crear();
	int objetivo = 5;

	void* encontrado = lista_buscar(lista, es_igual_a, &objetivo);
	pa2m_afirmar(encontrado == NULL, "lista_buscar en lista vacía devuelve NULL");

	int iterados = lista_iterar(lista, iterar_hasta_encontrar, &objetivo);
	pa2m_afirmar(iterados == 0, "lista_iterar en lista vacía devuelve 0");

	lista_destruir(lista);
}

void destruir_lista_vacia_no_genera_errores()
{
	lista_t* lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Lista vacía creada correctamente");
	lista_destruir(lista);
	pa2m_afirmar(true, "Destruir lista vacía no genera errores");
}

void destruir_lista_nula_no_genera_errores()
{
	lista_t* lista = NULL;
	lista_destruir(lista);
	pa2m_afirmar(true, "Destruir lista NULL no genera errores");
}

void destruir_lista_con_elementos_no_genera_errores()
{
	lista_t* lista = lista_crear();
	int a = 1, b = 2, c = 3;
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	pa2m_afirmar(lista_tamanio(lista) == 3, "Lista tiene 3 elementos");

	lista_destruir(lista);
	pa2m_afirmar(true, "Destruir lista con elementos no genera errores");
}

void lista_iterar_itera_correctamente()
{
	lista_t* l = lista_crear();
	int a = 10, b = 20, c = 30, d = 40, e = 50;
	lista_insertar(l, &a);
	lista_insertar(l, &b);
	lista_insertar(l, &c);
	lista_insertar(l, &d);
	lista_insertar(l, &e);
	int* esperados[] = {&a, &b, &c, &d, &e};
	int posicion = 0;

	lista_iterador_t* li = NULL;
	for (li = lista_iterador_crear(l);
	     lista_iterador_quedan_elementos_por_recorrer(li);
	     lista_iterador_proxima_iteracion(li)) {
		int* elemento = lista_iterador_obtener_elemento(li);
		pa2m_afirmar(elemento == esperados[posicion],
		             "Elemento en iterador externo coincide con el esperado (esperado:%i | obtenido:%i)", *esperados[posicion], *elemento);
		posicion++;
	}
	pa2m_afirmar(posicion == 5, "Se recorrieron los 5 elementos con el iterador externo");
	lista_iterador_destruir(li);
	lista_destruir(l);
}

void probar_iterador_externo_con_parametros_invalidos()
{
	lista_iterador_t* it_null = NULL;
	pa2m_afirmar(!lista_iterador_quedan_elementos_por_recorrer(it_null), "iterador NULL no tiene elementos por recorrer");
	pa2m_afirmar(lista_iterador_obtener_elemento(it_null) == NULL, "iterador NULL devuelve NULL al obtener elemento");
	lista_iterador_proxima_iteracion(it_null);
	pa2m_afirmar(true, "iterador NULL no ocasiona comportamiento indeterminado al avanzar iteración");
	lista_iterador_destruir(NULL);
	pa2m_afirmar(true, "Destruir iterador NULL no ocasiona comportamiento indeterminado");
}

void correr_pruebas_lista(){
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
	lista_buscar_posicion_encuentra_pos_correcta();
	lista_buscar_posicion_encuentra_null();

	pa2m_nuevo_grupo("Parametros invalidos");
	lista_buscar_posicion_no_encuentra_pos();
	lista_buscar_posicion_lista_invalida();
	lista_buscar_posicion_lista_vacia();

	pa2m_nuevo_grupo("Pruebas iterar y buscar lista");
	lista_buscar_e_iterar_encuentran_elementos();
	lista_buscar_e_iterar_iterados_correctos();

	pa2m_nuevo_grupo("Parametros invalidos");
	lista_buscar_e_iterar_funcion_nula();
	lista_buscar_e_iterar_lista_nula();
	lista_buscar_e_iterar_lista_vacia();

	pa2m_nuevo_grupo("Pruebas de lista_destruir");
	destruir_lista_vacia_no_genera_errores();
	destruir_lista_con_elementos_no_genera_errores();
	destruir_lista_nula_no_genera_errores();

	pa2m_nuevo_grupo("Pruebas iterador externo");
	lista_iterar_itera_correctamente();

	pa2m_nuevo_grupo("Pruebas invalidas iterador externo");
	probar_iterador_externo_con_parametros_invalidos();
}

void pila_apilar_funcionamiento_correcto(pila_t* pila){
	int a = 10, b = 20, c = 30;
	int* nuevo_tope=NULL;
	pa2m_afirmar(pila_apilar(pila, &a), "Elemento 10 apilado correctamente");
	nuevo_tope=pila_tope(pila);
	pa2m_afirmar(nuevo_tope== &a, "El tope es elemento esperado (esperado: %i | obtenido: %i)",a,*nuevo_tope);
	pa2m_afirmar(pila_apilar(pila, &b), "Elemento 20 apilado correctamente");
	nuevo_tope=pila_tope(pila);
	pa2m_afirmar(nuevo_tope == &b, "El tope es elemento esperado (esperado: %i | obtenido: %i)",b,*nuevo_tope);
	pa2m_afirmar(pila_apilar(pila, &c), "Elemento 30 apilado correctamente");
	nuevo_tope=pila_tope(pila);
	pa2m_afirmar(nuevo_tope == &c, "El tope es elemento esperado (esperado: %i | obtenido: %i)",c,*nuevo_tope);

	pa2m_afirmar(pila_tamanio(pila) == 3, "La pila tiene 3 elementos");
}

void pila_desapilar_funcionamiento_correcto()
{
	int a = 10, b = 20, c = 30;
	pila_t* pila=pila_crear();
	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);
	int* valores_esperados[] = {&c, &b, &a};
	int posicion = 0;
	while (!pila_vacia(pila)) {
		int* desapilado = pila_desapilar(pila);
		pa2m_afirmar(desapilado != NULL && *desapilado == *valores_esperados[posicion],
		             "Desapilar devuelve elemento esperado (esperado: %i)", *valores_esperados[posicion]);
		int* tope = pila_tope(pila);
		if (!pila_vacia(pila)) {
			pa2m_afirmar(tope != NULL && *tope == *valores_esperados[posicion + 1],
			             "Nuevo tope es el esperado (esperado: %i)", *valores_esperados[posicion + 1]);
		}
		posicion++;
	}
	pa2m_afirmar(pila_vacia(pila), "La pila está vacía después de desapilar todo");
	pa2m_afirmar(pila_desapilar(pila) == NULL, "Desapilar en pila vacía devuelve NULL");
	pa2m_afirmar(pila_tope(pila) == NULL, "Tope en pila vacía devuelve NULL");
	pila_destruir(pila);
}

void pruebas_pila_completa()
{
	pila_t* pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Crear una pila devuelve una pila válida");
	pa2m_afirmar(pila_vacia(pila), "La pila está vacía al crearse");
	pila_apilar_funcionamiento_correcto(pila);
	pila_desapilar_funcionamiento_correcto();
	pila_destruir(pila);
}

void correr_pruebas_pila(){
	pa2m_nuevo_grupo("Pruebas pila completa");
	pruebas_pila_completa();
}

void cola_encolar_funcionamiento_correcto(cola_t* cola){
	int a = 10, b = 20, c = 30;
	int* nuevo_frente=NULL;
	pa2m_afirmar(cola_encolar(cola, &a), "Elemento 10 encolado correctamente");
	nuevo_frente=cola_frente(cola);
	pa2m_afirmar(*nuevo_frente==a,"Frente no cambia al encolar elemento");
	pa2m_afirmar(cola_encolar(cola, &b), "Elemento 20 encolado correctamente");
	nuevo_frente=cola_frente(cola);
	pa2m_afirmar(*nuevo_frente==a,"Frente no cambia al encolar elemento");
	pa2m_afirmar(cola_encolar(cola, &c), "Elemento 30 encolado correctamente");
	nuevo_frente=cola_frente(cola);
	pa2m_afirmar(*nuevo_frente==a,"Frente no cambia al encolar elemento");

	pa2m_afirmar(cola_tamanio(cola) == 3, "La cola tiene 3 elementos");
}

void cola_desencolar_funcionamiento_correcto() {
	int a = 10, b = 20, c = 30;
	int esperados[] = {a, b, c};
	cola_t* cola = cola_crear();
	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);
	int posicion = 0;
	while (!cola_vacia(cola)) {
		int* frente = cola_frente(cola);
		pa2m_afirmar(*frente == esperados[posicion], "Frente es el esperado (esperado: %i | obtenido: %i)", esperados[posicion], *frente);
		int* desencolado = cola_desencolar(cola);
		pa2m_afirmar(*desencolado == esperados[posicion], "Desencolado es el esperado (esperado: %i | obtenido: %i)", esperados[posicion], *desencolado);
		posicion++;
	}

	pa2m_afirmar(cola_vacia(cola), "La cola está vacía después de desencolar todo");
	pa2m_afirmar(cola_desencolar(cola) == NULL, "Desencolar en cola vacía devuelve NULL");
	pa2m_afirmar(cola_frente(cola) == NULL, "Frente en cola vacía devuelve NULL");

	cola_destruir(cola);
}

void pruebas_cola_completa(){
	cola_t* cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Crear una cola devuelve una cola válida");
	pa2m_afirmar(cola_vacia(cola), "La cola está vacía al crearse");
	cola_encolar_funcionamiento_correcto(cola);
	cola_desencolar_funcionamiento_correcto();
	cola_destruir(cola);
}

void correr_pruebas_cola(){
	pa2m_nuevo_grupo("Pruebas cola completa");
	pruebas_cola_completa();
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas lista ===============");
	correr_pruebas_lista();

	pa2m_nuevo_grupo("============== Pruebas pila y cola ===============");
	correr_pruebas_pila();
	correr_pruebas_cola();
	//pruebas cola y pila invalida
	return pa2m_mostrar_reporte();
}
