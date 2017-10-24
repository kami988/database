#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bucket_size 103

typedef struct _node{
    unsigned char *name_ruby[2];
    unsigned char *name[2];
    unsigned char *nickname;
    int postal[2];
    unsigned char *address;
	char *tell;
    char *mail;
    int born[3];
    unsigned char *job;
    int sex;
    struct _node *next;
} node;

typedef struct _node_tree{
    unsigned char *name_ruby[2];
    unsigned char *name[2];
    unsigned char *nickname;
    int postal[2];
    unsigned char *address;
	char *tell;
    char *mail;
    int born[3];
    unsigned char *job;
    int sex;
    struct _node_tree *left;
    struct _node_tree *right;
    struct _node_tree *same;
} node_tree;

int resister_DATA();
int delete_DATA();
int change_DATA();
int search_DATA();
int view_DATA();

int get_hashval(char *key) {
    int hashval = 0;

    while(*key){
        hashval = (hashval * 137 + *key++) % bucket_size;
    }
    return hashval;
}

int init_DATA(node **DATA) {// ハッシュテーブルをNULLで初期化
    int i;
    for(i = 0; i < bucket_size; i++){
        DATA[i] = NULL;
    }
}

int insert_DATA(FILE *fi, node **DATA) {
    char c;
    int num;
    int i,j;
    int ex_postal[2], ex_born[3], ex_sex;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    node *sample, *sample_next, *sample_back;

    if(fgetc(fi) == EOF){ //ファイルが空なら終わり
        return 1;
    }
    else fseek(fi, 0, SEEK_SET);

    while(1){
        fscanf(fi,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%d",
                ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,&ex_postal[0],&ex_postal[1],
                ex_address,ex_tell,ex_mail,&ex_born[0],&ex_born[1],&ex_born[2],&ex_job,&ex_sex);
        
        sample = (node *)malloc(sizeof(node));
        sample->name_ruby[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[0]) + 1));
        sample->name_ruby[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name_ruby[1]) + 1));
        sample->name[0] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[0]) + 1));
        sample->name[1] = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_name[1]) + 1));
        sample->nickname = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_nickname) + 1));
        sample->postal[0] = ex_postal[0];
        sample->postal[1] = ex_postal[1];
        sample->address = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_address) + 1));
        sample->tell = (char *)malloc(sizeof(char) * (strlen(ex_tell) + 1));
        sample->mail = (char *)malloc(sizeof(char) * (strlen(ex_mail) + 1));
        sample->born[0] = ex_born[0];
        sample->born[1] = ex_born[1];
        sample->born[2] = ex_born[2];
        sample->job = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ex_job) + 1));
        sample->sex = ex_sex;
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

        num = get_hashval(ex_mail); //メールアドレスからハッシュ値を生成
        printf("%d\n",num);
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
}

int print_DATA(node **DATA) {
    int i,j;
    node *chain;
    char *name[3] = {"男性","女性","その他の性別"};
    for(i = 0; i < bucket_size; i++){
        if(DATA[i] != NULL){
            chain = DATA[i];
            /* リスト内部を走査して出力する */
            while(chain != NULL){
                printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                chain = chain->next;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int i;
    int num_all = 0;//登録数 (配列番号+1)
    int root,mode;
    FILE *fi;
    fi = fopen("DATA.csv","r+"); //読み込み＋書き込み

    node *DATA[bucket_size];
    node *DATA_str;
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(fi, DATA);//ファイルからDATAに代入
    printf("管理者権限の有無を選んでください\n");
    printf("０：あり　１：なし");
    //scanf();
    printf("モードを選択してください\n");
    printf("0：終了　１：登録　２：変更　３：削除　４：検索　５：全表示\n");
	print_DATA(DATA);
    fclose(fi);
    return 0;
}