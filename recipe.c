//! gcc -std=gnu99 -o recipe recipe.c -W -Wall
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* 全てのレシピを保存するコンテナの初期サイズ */
const size_t RECIPE_ARRAY_DEFAULT_SIZE = 4; /* 今回の課題では適切な大きさ */
const size_t RECIPE_ARRAY_FGETS_BUFFER_SIZE = 1024;

void *mymalloc( size_t size ) {
  void *tmp = malloc( size );
  if ( tmp == NULL ) { perror("mymalloc"); exit(EXIT_FAILURE); }
  return tmp;
}

typedef struct _recipe {
  char *name;
  char *url;
} recipe_t;

typedef struct _recipe_array {
  recipe_t **array;
  size_t size;
  size_t alloced;
} recipe_array_t;

/*** recipe_t ***/
/* name, urlはバッファが確保されてコピーされる */
recipe_t *recipe_create( char *name, char *url ) {
  recipe_t *r = mymalloc( sizeof( recipe_t ) );
  int rc = sscanf( name, "%ms", &r->name );
  if ( rc <= 0 ) { perror( "sscanf" ); exit( EXIT_FAILURE ); }
  rc = sscanf( url, "%ms", &r->url );
  if ( rc <= 0 ) { perror( "sscanf" ); exit( EXIT_FAILURE ); }
  return r;
}

/* TODO: 本当はIDはrecipeが保持すべきデータ */
void recipe_print( recipe_t *recipe, int id ) {
  printf( "%d: %s %s\n", id, recipe->name, recipe->url );
}

/*** recipe_array_t ***/
void recipe_array_append( recipe_array_t *this, recipe_t *recipe ) {
  static int id = 1;
  if ( (uint32_t) id >= this->alloced ) {
    size_t new_size = this->alloced * 2;
    recipe_t **new_recipes = realloc( this->array, sizeof( recipe_t * ) * new_size );
    if ( new_recipes == NULL ) { perror( "realloc" ); exit( EXIT_FAILURE ); }
    this->array = new_recipes;
    this->alloced = new_size;
  }
  this->array[id-1] = recipe;
  this->size++;
}

recipe_array_t *recipe_array_create( FILE *fp ) {
  /* array[n]にはrecipe_idがn+1のものが入る点に注意 */
  recipe_array_t *this = mymalloc( sizeof( recipe_array_t ) );
  this->array = mymalloc( sizeof( recipe_t ) * RECIPE_ARRAY_DEFAULT_SIZE );
  this->size = 0;
  this->alloced = RECIPE_ARRAY_DEFAULT_SIZE;

  /* テキストのパース */
  char *name, *url;
  while ( fscanf( fp, "%ms %ms", &name, &url ) != EOF ) {
    recipe_t *r = recipe_create( name, url );
    recipe_array_append( this, r );
  }
  return this;
}

void recipe_array_free( recipe_array_t *recipes ) {
  free( recipes->array );
  recipes->array = NULL;
  recipes->size = -1;
  recipes->alloced = 0;
}

/* idを指定して表示 */
/* id <= 0 のときは全てを表示 */
void recipe_array_print( recipe_array_t *recipes, int id ) {
  if ( id > 0 ) {
    if ( (uint32_t) id <= recipes->size )
      recipe_print( recipes->array[id-1], id );
    else
      printf( "ID: %d は存在しません。\n", id );
  } else {
    for ( uint32_t i = 0; i < recipes->size; i++ ) {
      recipe_print( recipes->array[i], i+1 );
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
  recipe_array_t *recipes = recipe_array_create( recipe_fp );
  recipe_array_print(recipes, recipe_specified_id);
  
  fclose( recipe_fp );
  recipe_array_free( recipes );
  
  return 0;
}
