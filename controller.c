#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "parser.h"
#include "movies.h"
#include "controller.h"
#include "miBiblioteca.h"


int controller_loadFromText(LinkedList* pArrayListMovies)
{
	int todoOk = 0;
	FILE* pFile = NULL;
	char path[30];

	pedirString(path, "Ingrese el nombre del archivo:  ",30);
    strcat(path,".csv");

	if ( path != NULL && pArrayListMovies != NULL )
	{

		pFile = fopen( path, "r");
		if ( pFile == NULL )
		{
			printf("No se pudo abrir el archivo\n");
		}
		else
		{
			if ( parser_MovieFromText ( pFile, pArrayListMovies) )
			{
				printf( "Carga de archivo de texto exitosa\n" );
				todoOk = 1;
			}
		}
	}
	fclose(pFile);
	return todoOk;
}


int controller_ListMovie(LinkedList* pArrayListMovies)
{
	int todoOk = 0;
	Movies* auxMovie;
	if (pArrayListMovies != NULL)
	{
        printf("----------------------------------------------------\n");
		printf("              *** LISTA PELICULAS ***	\n");
		printf("----------------------------------------------------\n");
		printf(" ID      TITULO                         GENERO              RATING\n");
		for (int i = 0; i < ll_len(pArrayListMovies); i++)
		{
			auxMovie = (Movies*) ll_get( pArrayListMovies, i );
			showMovie(auxMovie);
		}
		todoOk = 1;
	}
	return todoOk;
}

int controller_movieRating(LinkedList* pArrayMovie)
{
    int todoOk = 0;

    pArrayMovie = ll_map(pArrayMovie, randomRating);

    if ( pArrayMovie != NULL  )
    {
        controller_ListMovie(pArrayMovie);

        todoOk = 1;
    }
    return todoOk;
}

int controller_movieGenre(LinkedList* pArrayMovie)
{
    int todoOk = 0;

    pArrayMovie = ll_map(pArrayMovie, randomGenre);

    if ( pArrayMovie != NULL  )
    {
        controller_ListMovie(pArrayMovie);

        todoOk = 1;
    }
    return todoOk;
}


int controller_genreFilter(LinkedList* pArrayMovies)
{
    int todoOk = 0;
    int opcion;
    char nombreArchivo[50];

    system("cls");
    printf("Filtrado por genero:\n");
    printf(" 1 - drama\n");
    printf(" 2 - comedia\n");
    printf(" 3 - accion\n");
    printf(" 4 - terror\n");

    validarInt(&opcion, "Ingrese el genero a filtrar (1-2-3-4): ", " ***ERROR*** ", 1,4,25);

    switch (opcion)
    {
    case 1:
        pArrayMovies = ll_filter(pArrayMovies, filterDrama);
        strcpy(nombreArchivo, "dataDrama.csv");
        break;
    case 2:
        pArrayMovies = ll_filter(pArrayMovies, filterComedia);
        strcpy(nombreArchivo, "dataComedia.csv");
        break;
    case 3:
        pArrayMovies = ll_filter(pArrayMovies, filterAccion);
        strcpy(nombreArchivo, "dataAccion.csv");
        break;
    case 4:
        pArrayMovies = ll_filter(pArrayMovies, filterTerror);
        strcpy(nombreArchivo, "dataTerror.csv");
        break;

    }

    if ( pArrayMovies != NULL  )
    {
        controller_ListMovie(pArrayMovies);
        controller_saveAsText(nombreArchivo, pArrayMovies);
        todoOk = 1;
    }
    return todoOk;
}

int controller_saveAsText(char* path , LinkedList* pArrayMovies)
{
	int todoOk = 0;
	FILE* pFile;
	int id;
	char title[80];
	char genre[80];
	float rating;

	Movies* auxMovie;

	if ( path != NULL && pArrayMovies != NULL )
	{
		pFile = fopen(path, "w");
		if ( pFile == NULL )
		{
			printf("ERROR,No se pudo abrir el archivo\n");

		}

		fprintf( pFile, "id,title,genre,rating\n" );

		for (int i = 0; i < ll_len(pArrayMovies); i++)
		{
			auxMovie = ll_get(pArrayMovies, i);
			if ( movie_getId(auxMovie, &id) &&
                 movie_getTitle(auxMovie, title) &&
                 movie_getGenre( auxMovie, genre) &&
				 movie_getRating(auxMovie, &rating)
			   )
			{
				fprintf(pFile, "%d,%s,%s,%.1f\n", id, title, genre, rating);
				todoOk = 1;
			}
		}
		fclose(pFile);
	}

	return todoOk;
}

int controller_sortGenreRating(LinkedList* pArrayMovies)
{
    system("cls");
    int todoOk = 0;

    if ( pArrayMovies != NULL )
    {
        LinkedList* sortLinkedList = NULL;
        sortLinkedList = ll_clone(pArrayMovies);
        todoOk = 1;
        ll_sort( sortLinkedList, compareGenreRating, 1 );
        controller_ListMovie(sortLinkedList);
        ll_deleteLinkedList(sortLinkedList);

    }
    return todoOk;

}



int controller_saveAsTextSort(LinkedList* pArrayMovies)
{
    system("cls");
    int todoOk = 0;

    if ( pArrayMovies != NULL )
    {
        LinkedList* sortLinkedList = NULL;
        sortLinkedList = ll_clone(pArrayMovies);
        todoOk = 1;
        ll_sort( sortLinkedList, compareGenreRating, 1 );
        controller_saveAsText("sortGenreRating.csv",sortLinkedList);
        ll_deleteLinkedList(sortLinkedList);

    }
    return todoOk;

}
