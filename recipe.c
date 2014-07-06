//! gcc -std=gnu99 -o recipe recipe.c -W -Wall
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* 全てのレシピを保存するコンテナの初期サイズ */
const int RECIPE_LINES_DEFAULT_SIZE = 4; /* 今回の課題では適切な大きさ */

void *mymalloc( size_t size ) {
  void *tmp = malloc( size );
  if ( tmp == NULL ) { perror("mymalloc"); exit(EXIT_FAILURE); }
  return tmp;
}

typedef struct _recipe_lines {
  char **lines;
  size_t size;
  size_t alloced;
} recipe_lines_t;

recipe_lines_t *recipe_lines_create( FILE *fp ) {
  /* lines[n]にはrecipe_idがn+1のものが入る点に注意 */
  char **lines = mymalloc( sizeof( char * ) * RECIPE_LINES_DEFAULT_SIZE );
  size_t lines_alloced = RECIPE_LINES_DEFAULT_SIZE;
  
  int id = 1;
  char *line;
  while ( fscanf( fp, "%ms", &line ) != EOF ) {
    if ( strlen( line ) == 0 ) continue;
    if ( (uint32_t) id >= lines_alloced ) {
      size_t new_size = lines_alloced * 2;
      char **new_lines = realloc( lines, sizeof( char * ) * new_size );
      if ( new_lines == NULL ) { perror( "realloc" ); exit( EXIT_FAILURE ); }
      lines = new_lines;
      lines_alloced = new_size;
    }
    lines[id - 1] = line;
    id++;
  }

  /* create object to return */
  recipe_lines_t *recipes = mymalloc( sizeof( recipe_lines_t ) );
  recipes->lines = lines;
  recipes->size = id-1;
  recipes->alloced = lines_alloced;
  return recipes;
}

void recipe_lines_free( recipe_lines_t *recipes ) {
  free( recipes->lines );
  recipes->lines = NULL;
  recipes->size = -1;
  recipes->alloced = 0;
}

/* idを指定して表示 */
/* id <= 0 のときは全てを表示 */
void recipe_lines_print( recipe_lines_t *recipes, int id ) {
  if ( id > 0 ) {
    if ( (uint32_t) id <= recipes->size ) 
      printf( "%d: %s\n", id, recipes->lines[id-1] );
    else
      printf( "ID: %d は存在しません。\n", id );
  } else {
    for ( uint32_t i = 0; i < recipes->size; i++ ) {
      printf( "%d: %s\n", i+1, recipes->lines[i] );
    }
  }
}

int main( int argc, char* argv[] ) {
  FILE *recipe_fp;

  /*** Usageの表示 ***/
  if ( argc < 2 ) {
    fprintf( stderr, "Usage: %s file_name [id]\n", argv[0] );
    return -1;
  }

  /*** 引数のリネーム ***/
  char *recipe_file_path = argv[1];
  int recipe_specified_id = ( argc >= 3 ) ? atoi(argv[2]) : -1;  /* -1だと全てを表示する */


  /*** ファイルを開く ***/
  if ( ( recipe_fp = fopen( recipe_file_path , "r" ) ) == NULL ) {
    fprintf( stderr, "ファイルが開けません\n" );
    return -1;
  }

  /* レシピの処理 */
  recipe_lines_t *recipes = recipe_lines_create( recipe_fp );
  recipe_lines_print(recipes, recipe_specified_id);
  
  fclose( recipe_fp );
  recipe_lines_free( recipes );
  
  return 0;
}
