#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));

    if(newList != NULL)
    {
        newList->size = 0;
        newList->pFirstNode = NULL;
    }

    return newList;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int size = -1;

    if(this != NULL)
    {
        size = this->size;
    }

    return size;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* aux = NULL;

    if ( this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this) )
    {
        aux = this->pFirstNode;
        while( nodeIndex > 0 )
        {
            aux = aux->pNextNode;
            nodeIndex--;
        }
    }

    return aux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;

    Node* nuevoNodo = NULL;
    Node* previousNode = NULL;

    if (this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        nuevoNodo = (Node*)malloc(sizeof(Node));//creo nuevo y pido espacion en memoria
        if (nuevoNodo != NULL)//verifico que se haya conseguido espacio en memoria
        {
            nuevoNodo->pElement = pElement; //al nuevo le cargo lo que recibo
            nuevoNodo->pNextNode = NULL; //seguro
            if (nodeIndex == 0) //si es igual a 0 la direccion del anterior es el linkedlist
            {
                nuevoNodo->pNextNode = this->pFirstNode;
                this->pFirstNode = nuevoNodo;
            }
            else
            {
                previousNode = getNode(this, nodeIndex-1);
                nuevoNodo->pNextNode = previousNode->pNextNode;
                previousNode->pNextNode = nuevoNodo;
            }
            this->size++; // actualizo el tam del linkedlist
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{

    return addNode(this, ll_len(this), pElement);

}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;

    auxNode = getNode(this, index); // no valida porque ya lo hace getnode()
    if (auxNode != NULL)
    {
        returnAux = auxNode->pElement;
    }

    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)//piso la carga, es un setter
{
    int returnAux  = -1;
    Node* aux;

    if(this != NULL && index < ll_len(this) && index >= 0)
    {
        aux = getNode(this, index);

        if(aux != NULL)
        {
            aux->pElement = pElement;// no hago un free porque si tuviese otro linkedlist apuntandole a eso lo pierdo. si quiero hacer el free no lo hago por linkedlist
            returnAux  = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* previousNode = NULL;

    if (this != NULL && index >= 0 && index < ll_len(this))
    {

        if (index == 0)
        {

            this->pFirstNode = this->pFirstNode->pNextNode;
        }
        else
        {
            previousNode = getNode(this, index-1);
            if (previousNode != NULL)
            {
                previousNode->pNextNode = previousNode->pNextNode->pNextNode;
            }
        }
        this->size--;
        returnAux = 0;

    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if (this != NULL)
    {
        while ( !ll_isEmpty(this) )
        {
            ll_remove(this, 0);
        }

        /*OPCION 2
        voy yendo desde el final hacia adelante
        for ( int i = ll_len(this)-1; i >= 0; i-- )
        {
            ll_remove(this, i);
        }*/

        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    /*     OPCION A
        if (this != NULL)
        {
            if (ll_clear(this) == 0) // borramos todos los vagones antes de explotar la locomotora
            {
                free(this);
                returnAux = 0;
            }
        }*/

    returnAux = ll_clear(this);
    if ( !returnAux )
    {
        free(this);
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int status = -1;
    int i;
    Node* aux;

    if(this != NULL)
    {
        int tam = ll_len(this);
        for(i = 0; i < tam ; i++)
        {
            aux = getNode(this, i);
            if(aux != NULL)
            {
                if(pElement == aux->pElement)
                {
                    status = i;
                    break;
                }
            }
        }
    }

    return status;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
        returnAux = 1;
        if ( ll_len(this) )
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement  );
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */

void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    returnAux = ll_get(this, index);
    ll_remove(this, index);

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if ( this != NULL )
    {
        returnAux = 0;
        if (ll_indexOf(this, pElement) >= 0 )
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    if (this != NULL && this2 != NULL)
    {
        returnAux = 1;

        int tam = ll_len(this2);

        for (int i = 0; i < tam; i++)
        {
            if ( !ll_contains(this, ll_get(this2, i)) )
            {
                returnAux = 0;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    if (this != NULL && from >= 0 && to <= ll_len(this) && to > from )
    {
        cloneArray = ll_newLinkedList();
        if (cloneArray != NULL)
        {
            for (int i = from; i < to; i++)
            {
                ll_add(cloneArray, ll_get(this, i));
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{

    return ll_subList(this, 0, ll_len(this));

}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;

    int tam = ll_len(this);
    void* aux;

    if (this != NULL && pFunc != NULL && order >= 0 && order <= 1)
    {
        for (int i =0; i < tam-1; i++)
        {
            for (int j = i+1; j<tam; j++)
            {
                if ( ( pFunc( ll_get(this, i), ll_get(this, j) ) > 0 && order ) ||
                        ( pFunc( ll_get(this, i), ll_get(this, j) ) < 0 && !order ) )
                {
                    aux = ll_get(this, i);
                    ll_set(this, i, ll_get(this, j));
                    ll_set(this, j, aux);
                }
            }
        }
        returnAux = 0;
    }

    return returnAux;

}

LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*))
{
    LinkedList* filterList = NULL;
    void* aux = NULL;

    if(this != NULL && pFunc != NULL)
    {
        filterList = ll_newLinkedList();

        if(filterList != NULL)
        {
            int tam = ll_len(this);
            for(int i = 0; i < tam; i++)
            {
                aux = ll_get(this, i);

                if(pFunc(aux)) //retorna 1 si la carga a la filter list, 0 sino cumple los requisitos
                {
                    if(ll_add(filterList, aux)) //en caso de que no se pueda cargar
                    {
                        ll_deleteLinkedList(filterList);
                        filterList = NULL;
                        break;
                    }
                }
            }
        }
    }

    return filterList;
}

/*LinkedList* ll_filter(LinkedList* this, int (pFunc)(void) )
{
    LinkedList* filterList = NULL;
    void* elemento = NULL;
    int tam;

    if (this != NULL && pFunc != NULL)
    {
        filterList = ll_newLinkedList();
        if (filterList != NULL)
        {
            tam = ll_len(this);
            for (int i=0; i<tam; i++)
            {
                elemento = ll_get(this, i);
                if ( pFunc(elemento) )
                {
                    if(ll_add(filterList, elemento))
                    {
                        ll_deleteLinkedList(filterList);
                        filterList = NULL;
                        break;
                    }
                }
            }
        }
    }
    return filterList;
}*/

/*void ll_random
int numeroAleatorio()
{

    int numero;
    int max =240;
    int min= 100
             srand(time(NULL));
    numero =rand() % (max - min + 1) + min;


    return 0;


}
*/
/*LinkedList* ll_map(LinkedList* this,void*(*pFunc) (void* element))
{
    inkedList newList = NULL;
    int tam;
    void* aux;
    int i;

    int numero;
    int max =240;
    int min= 100

    srand(time(NULL));
    //numero =rand() % (max - min + 1) + min;


    if(this!=NULL && pFunc != NULL)
    {
        newList = ll_newLinkedList();
        tam = ll_len(this);
        for(i=0; i<tam; i++)
        {
            pFunc(this)
            aux = ll_get(this, i);
            pFunc(aux);
            ll_add(newList,aux);
        }
    }
    return newList;
}*/

LinkedList* ll_map(LinkedList* lista, void* (*pFunc) (void*))
{
    LinkedList* newList = NULL;
    void* aux =NULL;
    int tam;

    if( lista != NULL && pFunc != NULL)
    {
        newList = ll_newLinkedList();
        tam = ll_len(lista);
        for(int i=0; i < tam; i++)
        {
            aux = ll_get(lista, i);
                if ( pFunc( aux ) )
                {
                    if (  ll_add(newList, aux)  )
                    {
                        ll_deleteLinkedList(newList);
                        newList = NULL;
                        break;
                    }
                }
        }
    }


    return newList;
}
