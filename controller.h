#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED



#endif // CONTROLLER_H_INCLUDED

int controller_loadFromText(LinkedList* pArrayListMovies);
int controller_ListMovie(LinkedList* pArrayListMovies);
int controller_movieDuration(LinkedList* pArrayMovie);
int controller_movieRating(LinkedList* pArrayMovie);
int controller_movieGenre(LinkedList* pArrayMovie);


int controller_genreFilter(LinkedList* pArrayPelicula);

int controller_saveAsText(char* path , LinkedList* pArrayMovies);

int controller_saveAsTextSort(LinkedList* pArrayMovies);
