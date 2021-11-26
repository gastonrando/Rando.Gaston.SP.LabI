#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

typedef struct
{
    int id;
    char title[80];
    char genre[80];
    float rating;

}Movies;


#endif // MOVIES_H_INCLUDED

Movies* movie_new();
Movies* movie_newParametros(char* idStr,char* titleStr,char* genreStr, char* ratingStr);
void movie_delete(Movies* pMovies);

int movie_setId(Movies* this,int id);
int movie_getId(Movies* this,int* id);

int movie_setTitle(Movies* this,char* title);
int movie_getTitle(Movies* this,char* title);

int movie_setGenre(Movies* this,char* genre);
int movie_getGenre(Movies* this,char* genre);

int movie_setRating(Movies* this,float rating);
int movie_getRating(Movies* this,float* rating);
int menu();

int showMovie(Movies* movie);
int randomRating(void* elemento);
int randomGenre(void* elemento);
int filterDrama(void* movie);
int filterComedia(void* movie);
int filterAccion(void* movie);
int filterTerror(void* movie);


int compareGenreRating( void* movieA, void* movieB);
