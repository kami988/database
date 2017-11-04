#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bucket_size 3 //(素数)
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

int resister_DATA(node** DATA, int root){}
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
    printf("1：あり　0：なし\n");
    scanf("%d",root);
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

    char *data_sample[] = {"タナカ3,ダイスケ,田中,大輔,ダイスキ,6511222,神戸市西区学園東町8-4,08012345235,r11130u1@g.kobe-kosen.co.jp,1998,5,2,名誉博士,0,0",
                           "タジマ2,ダイスケ,田島,大輔,アイツ,6511111,神戸市西区学園東町8-5,08012345343,r11130t1@gmail.com,1500,12,3,非常勤講師,2,11171859", //パスワード:kcct
                           "タナカ2,ダイスケ,田中,大輔,ダイスキ,6511222,神戸市西区学園東町8-4,08012345235,r11130e2@g.kobe-kosen.co.jp,1998,5,2,名誉博士,0,21533944", //パスワード:kobe1234
                           "タジマ,ダイスケ,田島,大輔,アイツ,6511111,神戸市西区学園東町8-5,08012345343,r11130r1@gmail.com,1500,12,3,非常勤講師,1,0",
                           "タナカ,タロウ,田中,太郎,タロノスケ,6511234,神戸市西区学園東町8-3,08012345678,r111301@g.kobe-kosen.com,1998,4,1,学生,0,0"};
    for(i = 0; i < 5; i++){
        sample = (node *)malloc(sizeof(node));

        sscanf(data_sample[i],"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%d,%d",
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
    }
}

int view_DATA(node **DATA, int root) {//管理者権限を考慮しない仮関数
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

int delete_DATA(node **DATA, int root) {
    char mail[128], str[256];
    int val, handan, first;
    node *sample;
    node *back;
    char *name[3] = {"男性","女性","その他の性別"};

    while(1){
        printf("削除したいユーザーのメールアドレスを入力してください（終了=0）\n");
        scanf( "%s", mail);
        if(strcmp(mail,"0") == 0) {
            printf("終了します。\n");
            break;
        }
        val = get_hashval(mail);
        sample = DATA[val];
        if (sample == NULL) {
            printf("そのメールアドレスは登録されていません。\n");
            continue;
        }
        else {
            if (strcmp(mail, sample->mail) == 0) {//線形リストの先頭を消したい
                first = 1;
            }else{
                first = 0;
                while (strcmp(mail, sample->mail) != 0) {
                    back = sample;
                    sample = sample->next;
                    if (sample == NULL) {
                        printf("そのメールアドレスは登録されていません。\n");
                        break;
                    }
                }
                if(sample == NULL) continue; //やり直し
            }
        }
        if(root == 0 && sample->passval != 0){ //管理者権限ではなく、パスワードがある
            printf("管理者権限がないため、登録されているパスワードを入力してください。（アクセスしない=0）\n");
            scanf("%s",str);
            while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                printf("パスワードが違います。もう1度入力してください。（アクセスしない=0）\n");
                scanf("%s",str);
            }
            if(strcmp(str,"0") == 0) {
                printf("中止しました。\n");
                continue;
            }
            printf("アクセスできました\n");
        }
        printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
               sample->name_ruby[0], sample->name_ruby[1], sample->name[0], sample->name[1], sample->nickname, sample->postal,
               sample->address, sample->tell, sample->mail, sample->born[0], sample->born[1], sample->born[2], sample->job, name[sample->sex]);
        printf("以上の情報を削除しても本当によろしいですか？YES=1,NO=0\n");
        scanf("%d", &handan);
        if (handan == 0) {
            printf("中止しました\n");
            continue;
        }
        else if (handan == 1) {
            printf("後悔しませんね？YES=1,NO=0\n");
            scanf("%d", &handan);
            if (handan == 0) {
                printf("中止しました\n");
                continue;
            }
            else if (handan == 1) {
                if(first == 1){//先頭を消す
                    DATA[val] = sample->next;
                    free(sample);
                }
                else{//間を消す
                    back->next = sample->next;
                    free(sample);
                }
                printf("削除しました\n");
            }
            else {
                printf("入力エラーです\n");
                continue;
            }
        }
        else {
            printf("入力エラーです\n");
            continue;
        }
    }
}
      

int main(int argc, char *argv[]) {
    int i;
    int root, rootval;

    node *DATA[bucket_size];
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(DATA,&rootval);//DATAに代入

    root_system(&root, &rootval);//管理者権限

    while(1){
        printf("モードを選択してください\n");
        printf("0：終了　１：登録　２：変更　３：削除　４：検索　５：全表示\n");
        scanf("%d",&i);
        if(i==0){
            printf("終了します。");
            break;
        }else if(i==1){
            //resister_DATA(DATA, root);
        }else if(i==2){
            //change_DATA(DATA,root);
        }else if(i==3){
            delete_DATA(DATA,root);
        }else if(i==4){
            //search_DATA(DATA,root);
        }else if(i==5){
            view_DATA(DATA, root);
        }else{
            printf("入力が不適切です。\n");
        }
    }
    return 0;
}