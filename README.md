# database

#変更点 (10/26)\n
ファイル管理を考えなくてよくなった(FILE *fi がいらない)。\n
郵便番号が配列ではなく、1つの数字になった。\n
パスワード(不可逆ハッシュ, なしで0)機能が追加された。\n
管理者権限(初期パス：root, 不可逆ハッシュ, 引数にrootを持つべき)機能が追加された。\n

衝突の探査には探査するsampleを用いてsample->nextがNULLになるまでwhileで探す\n
