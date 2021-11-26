#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "movies.h"

Movies* movie_new()
{
    Movies* newMovie = (Movies*) malloc(sizeof(Movies));
    if(newMovie != NULL)
    {
        newMovie->id = 0;
        strcpy(newMovie->title, "");
        strcpy(newMovie->genre, "");
        newMovie->rating = 0;
    }
    return newMovie;
}

Movies* movie_newParametros(char* idStr,char* titleStr,char* genreStr, char* ratingStr)
{
    Movies* newMovie = movie_new();
    if(newMovie != NULL)
    {
        if(!(movie_setId(newMovie, atoi(idStr)) &&
                movie_setTitle(newMovie,titleStr) &&
                movie_setGenre(newMovie,genreStr) &&
                movie_setRating(newMovie,atof(ratingStr) ) ))
        {
            free(newMovie);
            newMovie = NULL;
        }
    }

    return newMovie;
}

void movie_delete(Movies* pMovies)
{

    if(pMovies != NULL)
    {
        free(pMovies);

    }
}


int movie_setId(Movies* this,int id)
{
    int todoOk =0;

    if(this != NULL && id > 0 )
    {
        this->id = id;
        todoOk =1;
    }

    return todoOk;
}

int movie_getId(Movies* this,int* id)
{
    int todoOk = 0;
    if(this != NULL && id != NULL )
    {
        *id = this->id;
        todoOk = 1;
    }

    return todoOk;
}

int movie_setTitle(Movies* this,char* title)
{
    int todoOk =0;
    char auxCadena[80];

    if(this != NULL && title != NULL && strlen(title) >= 3 && strlen(title) < 80 )
    {
        strcpy(auxCadena, title);
        strlwr(auxCadena);
        auxCadena[0]= toupper(auxCadena[0]);
        strcpy(this->title,auxCadena);
        todoOk =1;
    }

    return todoOk;
}

int movie_getTitle(Movies* this,char* title)
{
    int todoOk = 0;
    if(this != NULL && title != NULL )
    {
        strcpy(title,this->title);
        todoOk = 1;
    }

    return todoOk;
}

int movie_setGenre(Movies* this,char* genre)
{
    int todoOk =0;
    char auxCadena[80];

    if(this != NULL && genre != NULL && strlen(genre) >= 3 && strlen(genre) < 80 )
    {
        strcpy(auxCadena, genre);
        strlwr(auxCadena);
        auxCadena[0]= toupper(auxCadena[0]);
        strcpy(this->genre,auxCadena);
        todoOk =1;
    }

    return todoOk;
}

int movie_getGenre(Movies* this,char* genre)
{
    int todoOk = 0;
    if(this != NULL && genre != NULL )
    {
        strcpy(genre,this->genre);
        todoOk = 1;
    }

    return todoOk;
}

int movie_setRating(Movies* this,float rating)
{
    int todoOk =0;

    if(this != NULL &&  rating >= 0)
    {
        this->rating = rating;
        todoOk =1;
    }

    return todoOk;
}

int movie_getRating(Movies* this,float* rating)
{
    int todoOk = 0;
    if(this != NULL && rating != NULL )
    {
        *rating = this->rating;
        todoOk = 1;
    }

    return todoOk;
}

int menu()
{
    int opcion;

    printf("     **************************\n");
    printf("     **     ABM PELICULAS    **\n");
    printf("     **************************\n");
    printf("  1- Ingrese el nombre del archivo sin el .csv (ejemplo en existencia: ""movies"")\n");
    printf("  2- Listar peliculas\n");
    printf("  3- Asignar rating random\n");
    printf("  4- Asignar genero random\n");
    printf("  5- Filtrar por genero\n");
    printf("  6- Mostrar listado ordenado por genero y rating descendente\n");
    printf("  7- Exportar listado ordenado por genero y rating descendente\n");
    printf("  8- SALIR\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

int showMovie(Movies* movie)
{
    int todoOk = 0;
    int id;
    char title[80];
    char genre[80];
    float rating;

    if (movie != NULL)
    {
        if ( movie_getId( movie, &id ) &&
                movie_getTitle( movie, title ) &&
                movie_getGenre( movie, genre ) &&
                movie_getRating(movie, &rating)
           )
        {
            printf ("  %-5d  %-25s        %-10s        %-5.1f\n", id, title, genre, rating);
            todoOk = 1;
        }
    }
    return todoOk;
}

int randomRating(void* elemento)
{
    int todoOk = 0;
    Movies* aux = NULL;
    float rating;
    int max =100;
    int min= 10;
    if (elemento != NULL)
    {
        todoOk = 1;
        aux = (Movies*) elemento;
        rating = (float)(rand() % (max - min + 1) + min)/10;
        movie_setRating(aux, rating);
    }
    return todoOk;
}

int randomGenre(void* elemento)
{
    int todoOk = 0;
    Movies* aux = NULL;
    int opcion;
    char genre [20];
    int max =4;
    int min= 1;
    if (elemento != NULL)
    {
        todoOk = 1;
        aux = (Movies*) elemento;
        opcion = rand() % (max - min + 1) + min;

        switch(opcion)
    {
    case 1:
        strcpy(genre, "drama");
        break;
    case 2:
        strcpy(genre, "comedia");
        break;
    case 3:
        strcpy(genre, "accion");
        break;
    case 4:
        strcpy(genre, "terror");
        break;
    }

    movie_setGenre(aux, genre);
}
return todoOk;
}


int filterDrama(void* movie)
{
    int todoOk = 0;
    Movies* aux = NULL;

    if ( movie!= NULL)
    {
        aux = (Movies*) movie;
        if ( strcmp( aux->genre, "Drama"  ) == 0  )
        {
            todoOk = 1;
        }
    }
    return todoOk;
}

int filterComedia(void* movie)
{
    int todoOk = 0;
    Movies* aux = NULL;

    if ( movie!= NULL)
    {
        aux = (Movies*) movie;
        if ( strcmp( aux->genre, "Comedia"  ) == 0  )
        {
            todoOk = 1;
        }
    }
    return todoOk;
}

int filterAccion(void* movie)
{
    int todoOk = 0;
    Movies* aux = NULL;

    if ( movie!= NULL)
    {
        aux = (Movies*) movie;
        if ( strcmp( aux->genre, "Accion"  ) == 0  )
        {
            todoOk = 1;
        }
    }
    return todoOk;
}

int filterTerror(void* movie)
{
    int todoOk = 0;
    Movies* aux = NULL;

    if ( movie!= NULL)
    {
        aux = (Movies*) movie;
        if ( strcmp( aux->genre, "Terror"  ) == 0  )
        {
            todoOk = 1;
        }
    }
    return todoOk;
}


int compareGenreRating( void* movieA, void* movieB)
{
    int todoOk = 0;

    if(  ( strcmp( ((Movies*)movieA)->genre,  ((Movies*)movieB)->genre )  > 0 ) ||
            ( ( strcmp( ((Movies*)movieA)->genre,  ((Movies*)movieB)->genre )  == 0 ) &&
              ((Movies*)movieA)->rating < ((Movies*)movieB)->rating )
      )
    {
        todoOk = 1;
    }
    if(  ( strcmp( ((Movies*)movieA)->genre,  ((Movies*)movieB)->genre )  < 0 ) ||
            ( ( strcmp( ((Movies*)movieA)->genre,  ((Movies*)movieB)->genre )  == 0 ) &&
              ((Movies*)movieA)->rating > ((Movies*)movieB)->rating )
      )
    {
        todoOk = -1;
    }
    return todoOk;
}

