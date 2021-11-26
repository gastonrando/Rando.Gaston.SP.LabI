#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "movies.h"
#include <time.h>


int main(void)
{
    char seguir = 's';

    int dataLoaded = 0;
    srand(time(NULL));
    int listMovieTest = 0;
    int banderaCarga =0;
    int banderaSort=0;
    int banderaGenero =0;
    int banderaRating=0;


    LinkedList* listaMovies = ll_newLinkedList();
    //LinkedList* listSalariesMin = NULL;
    LinkedList* sortLinkedList = NULL;


    if (listaMovies == NULL)
    {
        printf("No se pudo crear el linkedList\n");
        exit(1);
    }

    do
    {
        switch (menu())
        {
        case 1:
            if(ll_isEmpty(listaMovies) == 1)
            {
                if(!controller_loadFromText(listaMovies))
                {
                    printf("No se pudieron cargar los datos\n\n");
                }
                else
                {
                    banderaCarga=1;
                }
            }
            else
            {
                printf("No se puede cargar is empty.\n\n");
            }
            break;
        case 2:
            if(banderaCarga == 1)
            {

                if ( !controller_ListMovie(listaMovies) )
                {
                    printf("Error \n");
                }
            }
            else
            {
                printf("Debe de cargar un listado primero\n");
            }
            break;
        case 3:
            if  (banderaCarga == 1)
            {
                if ( !controller_movieRating(listaMovies))
                {
                    printf("Error \n");
                }
                else
                {
                    banderaRating=1;
                }
            }
            else
            {
                printf("Debe de cargar un listado primero\n");
            }
            break;
        case 4:
            if  (banderaCarga == 1)
            {
                if ( !controller_movieGenre(listaMovies))
                {
                    printf("Error \n");
                }
                else
                {
                    banderaGenero=1;
                }
            }
            else
            {
                printf("Debe de cargar un listado primero\n");
            }
            break;
        case 5:
            if(banderaCarga==1 && banderaRating==1 && banderaGenero ==1)
            {


                if ( !controller_genreFilter(listaMovies) )
                {
                    printf("Error \n");
                }
            }
            else
            {
                printf("Debe de cargar un listado, asignar genero y rating primero\n");
            }
            break;

        case 6:
            if(banderaCarga==1 && banderaGenero ==1 & banderaRating ==1)
            {

                if ( !controller_sortGenreRating(listaMovies))
                {

                    printf("Error \n");

                }
                else
                {
                    banderaSort=1;
                }
            }
            else
            {
                printf("Debe de cargar un listado, asignar genero y rating primero\n");
            }

            break;
        case 7:
            if(banderaSort==1)
            {


                if ( !controller_saveAsTextSort(listaMovies) )
                {
                    printf("Error \n");
                }
                else
                {
                    printf("Archivo exportado con exito! \n");
                    ll_deleteLinkedList(sortLinkedList);
                }
            }
            else
            {
                printf("Debe de aplicar el ordenamiento primero\n");
            }
            break;
        case 8:
            printf("Ha seleccionado salir\n");
            seguir='n';
            break;
        default:
            printf("Opcion invalida!!\n");
        }
        system("pause");
        system("cls");
    }
    while(seguir == 's');
    ll_deleteLinkedList(listaMovies);


    return 0;
}

