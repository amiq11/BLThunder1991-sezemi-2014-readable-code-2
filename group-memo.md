# 見つけたコード BLThunder1991

## 1番
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

### 名前
コードのブロック化

## 2番
### コード
https://github.com/BLThunder1991/amiq11-sezemi-2014-readable-code-2/blob/master/recipe.h#L5

```C
    typedef struct _recipe
    {
        recipe_id_t id;
        char *name;
    } recipe_t;
```

### いいところ
* レシピがどんな情報を持っているかすぐわかる。
* 新しい情報を追加しやすい

### 見つけたきっかけ
* 仕様7を実装するとき
    * URLの追加を行う際に、どこに追加すればよいかすぐ思いついた。

### 名前
変数のカプセル化


## 1つ目
### コード
https://github.com/amiq11/amiq11-sezemi-2014-readable-code-2/blob/master/recipe.c#L111 - 113

```C
    const char *recipe_path = argv[1];
    recipe_list_t *recipe_list = read_recipe_from_file(recipe_path);
    print_recipes(recipe_list);
```

### いいところ
* main関数の中に、最低限の呼び出ししか置いていないことが良い。全体を通して、何をやりたいかが明確にわかる。

### 見つけたきっかけ
* 全体の処理の流れを見るために、main関数を参照した。

### 名前
ロジックの分割

## 2つ目
### コード
https://github.com/amiq11/amiq11-sezemi-2014-readable-code-2/blob/master/recipe.c#L76 - 77

```C
    FILE *fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen"); exit(EXIT_FAILURE); }
```

### いいところ
* 僕だったら、``if (( fp = fopen ( path, "r")) == NULL)`` と書いてしまうと思うけど、ポインタの生成ロジックと成否判定ロジックは別の処理なので、一行ずつ分けるほうがわかりやすいと思った。

### 見つけたきっかけ
* 実装前のコードリーディング

### 名前
一行に一つの意味

## 3つ目
### コード
https://github.com/amiq11/amiq11-sezemi-2014-readable-code-2/blob/master/recipe.c#L107
```C
    print_usage(argv[0]);
```

### いいところ
どんなふうにコンパイルしても、自分が生成したバイナリでUsageを表示するのがわかりやすくて良い。

### 見つけたきっかけ
* 実装前のコードリーティング

### 名前
ユーザビリティへの配慮

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

#見つけた箇所
##1つ目
ブロック単位で処理が区切られていたため、動作を読み取りやすかった。

##2つ目
実行時引数ではなく、printfとscanfを用いて対話型であるので、今何の情報を入力しているかがわかりやすかった。

##3つ目
変数の命名がわかりやすく、何を行っている変数かすぐに分かった。

# 良かった点
## 1つ目
定数がdefineで予め定義されていいる

## 2つ目
名前から定数の意味・役割がわかる
