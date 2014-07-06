## 1つ目
### コード
https://github.com/amiq11/BLThunder1991-sezemi-2014-readable-code-2/blob/master/recipe.c#L99

```C
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
```

### いいところ
* コードがブロックごとにわかれている
* ぱっと見て仕事の流れが分かれている

### 見つけたきっかけ
* グループ無いでコードを交換したタイミング

## 2つ目
### コード
```C
  if ( ( recipe_fp = fopen( recipe_file_path , "r" ) ) == NULL ) {
    fprintf( stderr, "ファイルが開けません\n" );
    return -1;
  }
```
### いいところ
* エラーをちゃんとstderrを用いて出力することで、明らかにエラーのprintだということを明確にする

### 見つけたきっかけ
* コードを交換したタイミングで
