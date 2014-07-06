# 開発言語

C

# プログラムの説明
現状満たしている仕様: 仕様5まで

## ファイルフォーマット recipe-data.txt

    % cat recipe-data.txt
    オムライス
    親子丼
    杏仁豆腐


## プログラムのコンパイルと実行
gccを使用してビルドする

    % gcc recipe.c -o recipe

プログラムの使用方法

    % ./recipe ファイル名 [ID]

プログラムの実行

    % ./recipe recipe-data.txt
    1: オムライス
    2: 親子丼
    3: 杏仁豆腐

    % ./recipe recipe-data.txt 2
    2: 親子丼

    % ./recipe recipe-data.txt -1
    1: オムライス
    2: 親子丼
    3: 杏仁豆腐
