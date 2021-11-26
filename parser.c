#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "movies.h"


int parser_MovieFromText(FILE* pFile , LinkedList* pArrayListMovies)
{
	int todoOk = 0;
	int cant;
	char id[50];
	char title[50];
	char genre[50];
	char duration[50];

	Movies* auxMovie;

	if (pFile != NULL && pArrayListMovies != NULL  )
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, title, genre, duration);
		do
		{
			cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, title, genre, duration);
			if (cant < 4)
			{
				break;
			}

			auxMovie = movie_newParametros( id, title, genre, duration );
			if (auxMovie != NULL)
			{
				ll_add( pArrayListMovies, auxMovie );
				todoOk = 1;
				auxMovie = NULL;
			}
		}
		while (!feof(pFile));
	}
	return todoOk;
}

