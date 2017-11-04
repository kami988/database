#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define bucket_size 3 //(素数)
#define bucket_pass 32749391 //32,749,391(素数)

typedef struct _node{
    unsigned char *name_ruby[2];
    unsigned char *name[2];
    unsigned char *nickname;
    int postal;
    unsigned char *address;
    int prefecture;
	char *tell;
    char *mail;
    int born[3];
    unsigned char *job;
    int sex;
    int passval;
    struct _node *next;
    struct _node *right;
    struct _node *left;
} node;

int resister_DATA(node** DATA, int root){}
int delete_DATA(node** DATA, int root){}
int change_DATA(node** DATA, int root){}
int search_DATA(node** DATA, int root){}

int get_hashval(char *key) {
    int hashval = 0;

    while(*key){
        hashval = (hashval * 137 + *key++) % bucket_size;
    }
    return hashval;
}

int get_passval(char *key) {
    int hashval = 0;

    while(*key){
        hashval = hashval * hashval * 137 + *key++;
    }
    return abs(hashval) % bucket_pass + 1;
}

int init_DATA(node **DATA) {// ハッシュテーブルをNULLで初期化
    int i;
    for(i = 0; i < bucket_size; i++){
        DATA[i] = NULL;
    }
}

int root_system(int *root, int *rootval){
    char str[256],str2[256];
    int num;
    printf("管理者権限の有無を選んでください\n");
    while(1){
        printf("１：あり　０：なし\n");
        if(scanf(" %d", root) != 1){
            printf("入力が不適切です。\n");
            scanf("%*s");
        }
        else if(*root != 0 && *root != 1){
            printf("入力が不適切です。\n");
        }
        else break;
    }
    if(*root == 1){
        printf("パスワードを入力してください。(初期パスワード：root)\n");
        scanf("%s",str);
        while(get_passval(str) != *rootval){
            printf("パスワードが違います。もう1度入力してください。（管理者権限でログインしない：0）\n");
            scanf("%s",str);
            if(strcmp(str,"0") == 0) {
                *root = 0;
                return 1;
            }
        }
        printf("パスワードを変更しますか？\n");
        while(1){
            printf("１：する　０：しない\n");
            if(scanf(" %d", &num) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(num != 0 && num != 1){
                printf("入力が不適切です。\n");
            }
            else break;
        }
        while(num == 1){
            printf("新しいパスワードを入力してください。(4字以上)\n");
            scanf("%s",str);
            while(strlen(str) < 4){
                printf("4字以上ではありません。もう1度入力してください。\n");
                scanf("%s",str);
            }
            printf("確認のためもう1度入力してください。\n");
            scanf("%s",str2);
            if(strcmp(str,str2)!=0){
                printf("パスワードが一致しませんでした。登録し直してください。\n");
            }
            else{
            	*rootval = get_passval(str);
            	printf("登録が完了しました。\n");
            	num = 0;
            }
        }
    }
}

int insert_DATA(node **DATA, int *rootval) {
    char c;
    int num;
    int i,j;
    int ex_postal, ex_born[3], ex_sex, ex_passval;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    node *sample, *null_back;
    char *prefecture[47] ={"北海道","青森県","岩手県","宮城県","秋田県","山形県","福島県",
    "茨城県","栃木県","群馬県","埼玉県","千葉県","東京都","神奈川県",
    "新潟県","富山県","石川県","福井県","山梨県","長野県","岐阜県",
    "静岡県","愛知県","三重県","滋賀県","京都府","大阪府","兵庫県",
    "奈良県","和歌山県","鳥取県","島根県","岡山県","広島県","山口県",
    "徳島県","香川県","愛媛県","高知県","福岡県","佐賀県","長崎県",
    "熊本県","大分県","宮崎県","鹿児島県","沖縄県"
    };

    FILE *fi = fopen("DATA.csv","r");
    if(fgetc(fi) == EOF){ //ファイルが空なら終わり
        char str_root[] = "root";
        *rootval = get_passval(str_root); //管理者権限のパスワードをrootにせってい
        return 1;
    }
    else fseek(fi, 0, SEEK_SET);

    fscanf(fi,"%d",rootval);
    fgetc(fi);//改行読み
    if(fgetc(fi) == EOF){ //登録データがなければ終わり
        return 1;
    }
    else fseek(fi, -1, SEEK_CUR);

    while(1){
        sample = (node *)malloc(sizeof(node));
        fscanf(fi,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%d,%d",
                ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,&sample->postal,
                ex_address,ex_tell,ex_mail,&sample->born[0],&sample->born[1],&sample->born[2],ex_job,&sample->sex,&sample->passval);
        
        sample->name_ruby[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[0]) + 1));
        sample->name_ruby[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[1]) + 1));
        sample->name[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[0]) + 1));
        sample->name[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[1]) + 1));
        sample->nickname = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_nickname) + 1));
        sample->address = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_address) + 1));
        sample->tell = (char *)malloc(sizeof(char) * (strlen(ex_tell) + 1));
        sample->mail = (char *)malloc(sizeof(char) * (strlen(ex_mail) + 1));
        sample->job = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_job) + 1));
        sample->next = NULL;

        strcpy(sample->name_ruby[0], ex_name_ruby[0]);
        strcpy(sample->name_ruby[1], ex_name_ruby[1]);
        strcpy(sample->name[0], ex_name[0]);
        strcpy(sample->name[1], ex_name[1]);
        strcpy(sample->nickname, ex_nickname);
        strcpy(sample->address, ex_address);
        strcpy(sample->tell, ex_tell);
        strcpy(sample->mail, ex_mail);
        strcpy(sample->job, ex_job);

        sample->prefecture = 48; //都道府県割り当て(48は住所に都道府県が無かった場合)
        for(i = 0; i < 47; i++){
            if(strstr(sample->address, prefecture[i]) != NULL) {
                sample->prefecture = i+1;
                break;
            }
        }

        num = get_hashval(ex_mail); //メールアドレスからハッシュ値を生成
        if(DATA[num] == NULL) {//衝突なし
            DATA[num] = sample;
        }
        else{//衝突有り
            null_back = DATA[num];//NULLを見つけるポインタ
            while(null_back->next != NULL){ //NULLが見つかるまで線形リストを走査
                null_back = null_back->next;
            }
            null_back->next = sample;//NULLだったポインタの手前のnext(つまりNULL)に代入
        }
        if (fgetc(fi) == EOF) break;//ファイルの終わりで終了
    }
    fclose(fi);
}

int push_file(node **DATA, int rootval){
    int i;
    node *chain;
    FILE *fo = fopen("DATA.csv","w");
    char str[] = "root";
    fprintf(fo,"%d",rootval); //管理者権限のパスワード
    for(i = 0; i < bucket_size; i++){
        if(DATA[i] != NULL){
            chain = DATA[i];
            // リスト内部を走査して出力する
            while(chain != NULL){
                fprintf(fo,"\n");
                fprintf(fo,"%s,%s,%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%s,%d,%d",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,chain->sex,chain->passval);
                chain = chain->next;
            }
        }
    }
    fclose(fo);
}

node *insert_DATA_tree(node *x, node *sample, int mode){
    int judge;
    int i;
    

	if(x == NULL){
        x = sample;
        x->right = NULL;
        x->left = NULL;
	}
	else{
        if     (mode == 1) judge = strcmp(x->name_ruby[0], sample->name_ruby[0]);//姓
        else if(mode == 2) judge = strcmp(x->name_ruby[1], sample->name_ruby[1]);//名
        else if(mode == 3) judge = strcmp(x->nickname, sample->nickname);//呼び名
        else if(mode == 4) {//郵便番号
            if(x->postal > sample->postal) judge = 1;
            else judge = -1;
        }
        else if(mode == 5) {//都道府県
            if(x->prefecture > sample->prefecture) judge = 1;
            else judge = -1;
        }
        else if(mode == 6) judge = strcmp(x->tell, sample->tell);//電話番号
        else if(mode == 7) judge = strcmp(x->mail, sample->mail);//メールアドレス
        else if(mode == 8) {//生年月日
            if(x->born[0] > sample->born[0]) judge = 1;//年
            else if(x->born[0] < sample->born[0])judge = -1;
            else{
                if(x->born[1] > sample->born[1]) judge = 1;//月
                else if(x->born[1] < sample->born[1])judge = -1;
                else{
                    if(x->born[2] > sample->born[2]) judge = 1;//日
                    else judge = -1;
                }
            }
        }
        else if(mode == 9) judge = strcmp(x->job, sample->job);//職業
        else if(mode == 10) {//性別
            if(x->sex > sample->sex) judge = 1;
            else judge = -1;
        }
        if     (judge > 0)   x->left  = insert_DATA_tree(x->left,sample,mode);
        else if(judge <= 0)   x->right = insert_DATA_tree(x->right,sample,mode);
    }
	return x;
}

void treeprint(node *x, int updown){
    int i;
    char *name[3] = {"男性","女性","その他の性別"};
	if (x != NULL){
        if(updown == 1){
            treeprint(x->left, updown);
        }
        else{
            treeprint(x->right, updown);
        }
        printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
                x->name_ruby[0],x->name_ruby[1],x->name[0],x->name[1],x->nickname,x->postal,
                x->address,x->tell,x->mail,x->born[0],x->born[1],x->born[2],x->job,name[x->sex]);
        if(updown == 1){
            treeprint(x->right, updown);
        }
        else{
            treeprint(x->left, updown);
        }
	}
}

int show_DATA(node **DATA, int root) {
    int i,mode,updown;
    node *chain;
    node *DATA_tree = NULL;
    int nocount = 0;

    printf("\n並び替えの基準にする内容の番号を入力してください\n");
    while(1){
        printf("姓  　　　　　：1\n");
        printf("名            ：2\n");
        printf("呼び名        ：3\n");
        printf("郵便番号　　　：4\n");
        printf("都道府県　　　：5\n");
        printf("電話番号　　　：6\n");
        printf("メールアドレス：7\n");
        printf("生年月日　　　：8\n");
        printf("職業　　　　　：9\n");
        printf("性別          ：10\n");
        if(scanf(" %d", &mode) != 1){
            printf("入力が不適切です。\n");
            scanf("%*s");
        }
        else if(mode > 10 || mode < 1){
            printf("入力が不適切です。\n");
        }
        else break;
    }

    printf("昇順か降順か選んでください  ");
    while(1){
        if     (mode == 1 || mode == 2) printf("(50音順)\n");
        else if(mode == 3) printf("(50音順で漢字はランダム)\n");
        else if(mode == 4) printf("(0 < 9)\n");
        else if(mode == 5) printf("(北海道 < 沖縄　< その他)\n");
        else if(mode == 6) printf("(0 < 9)\n");
        else if(mode == 7) printf("(0 < 9 < A < z)\n");
        else if(mode == 8) printf("(0 < 9)\n");
        else if(mode == 9) printf("(50音順で漢字はランダム)\n");
        else if(mode == 10) printf("(男性 < 女性 < その他の性別)\n");
        printf("１：昇順　２：降順\n");
        if(scanf(" %d", &updown) != 1){
            printf("入力が不適切です。\n");
            scanf("%*s");
        }
        else if(updown != 1 && updown != 2){
            printf("入力が不適切です。\n");
        }
        else break;
    }

    for(i = 0; i < bucket_size; i++){ //ハッシュ‐チェイン-テーブルを巡回してデータを探す
        if(DATA[i] != NULL){
            chain = DATA[i];
            while(chain != NULL){ 
                if(root == 1 || chain->passval == 0){
                    DATA_tree = insert_DATA_tree(DATA_tree,chain,mode); //二分探索木に挿入
                    chain = chain->next;
                }
                else{
                    nocount++;
                    chain = chain->next;
                }
            }
        }
    }

    treeprint(DATA_tree, updown); //出力
    if(nocount != 0){
        printf("\n管理者権限がないため、%d人のデータはパスワードにより表示できませんでした。\n",nocount);
    }
    printf("終了します。\n");
}

int main() {
    int i;
    int root, rootval;

    node *DATA[bucket_size];
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(DATA,&rootval);//ファイルからDATAに代入
    root_system(&root, &rootval);//管理者権限

    while(1){
        printf("モードを選択してください\n");
        while(1){
            printf("0：終了　１：登録　２：変更　３：削除　４：検索　５：全表示\n");
            if(scanf(" %d", &i) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(i < 0 || i > 5){
                printf("入力が不適切です。\n");
            }
            else break;
        }
        
        if     (i==0) {break;}
        else if(i==1) resister_DATA(DATA, root);
        else if(i==2) change_DATA(DATA,root);
        else if(i==3) delete_DATA(DATA,root);
        else if(i==4) search_DATA(DATA,root);
        else if(i==5) show_DATA(DATA, root);
    }
    printf("終了します。");
    push_file(DATA,rootval);//ファイルに書き出し
    return 0;
}
