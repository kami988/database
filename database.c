#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bucket_size 103 //(素数)
#define bucket_pass 32749391 //32,749,391(素数)

typedef struct _node{
    unsigned char *name_ruby[2];
    unsigned char *name[2];
    unsigned char *nickname;
    int postal;
    unsigned char *address;
	char *tell;
    char *mail;
    int born[3];
    unsigned char *job;
    int sex;
    int passval;
    struct _node *next;
} node;

typedef struct _node_tree{
    unsigned char *name_ruby[2];
    unsigned char *name[2];
    unsigned char *nickname;
    int postal;
    unsigned char *address;
	char *tell;
    char *mail;
    int born[3];
    unsigned char *job;
    int sex;
    int passval;
    struct _node_tree *left;
    struct _node_tree *right;
} node_tree;

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

int insert_DATA(node **DATA, int *rootval) {
    char c;
    int num;
    int i,j;
    int ex_postal, ex_born[3], ex_sex, ex_passval;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    node *sample, *sample_next, *sample_back;
    FILE *fi = fopen("DATA.csv","r");
    if(fgetc(fi) == EOF){ //ファイルが空なら終わり
        char str_root[] = "root";
        *rootval = get_passval(str_root);
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
        fscanf(fi,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%d,%d",
                ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,&ex_postal,
                ex_address,ex_tell,ex_mail,&ex_born[0],&ex_born[1],&ex_born[2],&ex_job,&ex_sex,&ex_passval);
        
        sample = (node *)malloc(sizeof(node));
        sample->name_ruby[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[0]) + 1));
        sample->name_ruby[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[1]) + 1));
        sample->name[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[0]) + 1));
        sample->name[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[1]) + 1));
        sample->nickname = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_nickname) + 1));
        sample->postal = ex_postal;
        sample->address = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_address) + 1));
        sample->tell = (char *)malloc(sizeof(char) * (strlen(ex_tell) + 1));
        sample->mail = (char *)malloc(sizeof(char) * (strlen(ex_mail) + 1));
        sample->born[0] = ex_born[0];
        sample->born[1] = ex_born[1];
        sample->born[2] = ex_born[2];
        sample->job = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_job) + 1));
        sample->sex = ex_sex;
        sample->next = NULL;
        sample->passval = ex_passval;

        strcpy(sample->name_ruby[0], ex_name_ruby[0]);
        strcpy(sample->name_ruby[1], ex_name_ruby[1]);
        strcpy(sample->name[0], ex_name[0]);
        strcpy(sample->name[1], ex_name[1]);
        strcpy(sample->nickname, ex_nickname);
        strcpy(sample->address, ex_address);
        strcpy(sample->tell, ex_tell);
        strcpy(sample->mail, ex_mail);
        strcpy(sample->job, ex_job);

        num = get_hashval(ex_mail); //メールアドレスからハッシュ値を生成
        if(DATA[num] == NULL) {//衝突なし
            DATA[num] = sample;
        }
        else{//衝突有り
            sample_next = DATA[num]->next;//NULLを見つけるポインタ
            sample_back = DATA[num];//NULLを見つけるポインタの手前
            while(sample_next != NULL){ //NULLが見つかるまで線形リストを走査
                sample_back = sample_next;
                sample_next = sample_next->next;
            }
            sample_back->next = sample;//NULLだったポインタの手前のnext(つまりNULL)に代入
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
    fprintf(fo,"%d",rootval);
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

int print_DATA(node **DATA, int root, int rootval) {
    int i;
    node *chain;
    char *name[3] = {"男性","女性","その他の性別"};
    for(i = 0; i < bucket_size; i++){
        if(DATA[i] != NULL){
            chain = DATA[i];
            /* リスト内部を走査して出力する */
            while(chain != NULL){
                printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                chain = chain->next;
            }
        }
    }
}

int root_system(int *root, int *rootval){
    char str[256],str2[256];
    int num;
    printf("管理者権限の有無を選んでください\n");
    printf("1：あり　0：なし\n");
    scanf("%d",root);
    if(*root == 1){
        printf("パスワードを入力してください。(初期パスワード：root)\n");
        scanf("%s",str);
        if(get_passval(str) != *rootval){
            printf("パスワードが違います。もう1度入力してください。（管理者権限でログインしない：0）\n");
            scanf("%s",str);
            if(strlen(str)==1 && str[0]=='0') {
                *root = 0;
                return 1;
            }
        }
        printf("パスワードを変更しますか？");
        printf("1：はい　0：いいえ\n");
        scanf("%d",&num);
        if(num == 1){
            printf("新しいパスワードを入力してください。(4字以上)\n");
            scanf("%s",str);
            while(strlen(str) < 4){
                printf("4字以上ではありません。もう1度入力してください。\n");
                scanf("%s",str);
            }
            printf("確認のためもう1度入力してください。\n");
            scanf("%s",str2);
            while(strcmp(str,str2)!=0){
                printf("パスワードが違います。もう1度入力してください。\n");
                scanf("%s",str);
                printf("確認のためもう1度入力してください。\n");
                scanf("%s",str2);
            }
            *rootval = get_passval(str);
            printf("登録が完了しました。\n");
        }
    }
}

int main(int argc, char *argv[]) {
    int i;
    int root, rootval;

    node *DATA[bucket_size];
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(DATA,&rootval);//ファイルからDATAに代入

    root_system(&root, &rootval);

    while(1){
        printf("モードを選択してください\n");
        printf("0：終了　１：登録　２：変更　３：削除　４：検索　５：全表示\n");
        scanf("%d",&i);
        if(i==0){
            printf("終了します。");
            break;
        }else if(i==1){
            
        }else if(i==0){
            
        }else if(i==1){
            
        }else if(i==2){
            
        }else if(i==3){
            
        }else if(i==4){
            
        }else if(i==5){
            print_DATA(DATA, root, rootval);
        }else{
            printf("入力が不適切です。\n");
        }
    }
    push_file(DATA,rootval);
    return 0;
}