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
    struct _node *right;
} node;

int resister_DATA(node** DATA, int root){}
int change_DATA(node** DATA, int root){}
int view_DATA(node** DATA, int root){}

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
    char *tok;

    char *data_sample[] = {"タナカ,ダイスケ,田中,大輔,ダイスキ,6511222,神戸市西区学園東町8-4,08012345235,r11130u1@g.kobe-kosen.co.jp,1998,5,2,名誉博士,0,0",
                           "タジマ2,ダイスケ,田島,大輔,アイツ,6511111,神戸市西区学園東町8-5,08012345343,r11130t1@gmail.com,1500,12,3,非常勤講師,2,11171859", //パスワード:kcct
                           "タナカ,ダイスケ,田中,大輔,ダイスキ,6511222,神戸市西区学園東町8-4,08012345235,r11130e2@g.kobe-kosen.co.jp,1998,5,2,名誉博士,0,21533944", //パスワード:kobe1234
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

int search_DATA(node **DATA, int root){
    int i,j,k,l,m,p;
    char c[1000], str[1000];
    char chara;
    int born[3];
    char *name[3] = {"男性","女性","その他の性別"};
    node *sample, *chain;
    node *keep;//後で戻すnextのポインタ
    node *DATA_search = NULL;//検索結果
    int nocount = 0;

    int flag = 2;//継続条件
	for(;;){
	    DATA_search = NULL;
        printf("検索内容を選択\n");
        printf("0:終了\n");
        printf("1:名字(全角カナ)\n");
        printf("2:名前(全角カナ)\n");
        printf("3:郵便番号\n");
        printf("4:住所\n");
        printf("5:電話番号\n");
        printf("6:生年月日\n");
        printf("7:メールアドレス\n");
        printf("※完全合致のみ表示します\n");
        scanf("%d",&i);
        if(1 <= i && i <= 6){
            for(;;){
                born[0] = 1;        //初期化
                p = 1;              //初期化
                strcpy(c,"\n");     //初期化
                DATA_search = NULL; //初期化
                switch(i){
                    case 1:
                        printf("名字を入力(全角カナ)\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 2:
                        printf("名前を入力(全角カナ)\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s\n",c);
                        break;
                    case 3:
                        printf("郵便番号を入力\n");
                        printf("終了する場合は0を入力\n");
                        scanf("%d",&p);
                        break;
                    case 4:
                        printf("住所を入力してください\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 5:
                        printf("電話番号を入力\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 6:
                        printf("生年月日を入力してください。\n");
                        printf("終了する場合は'0'と入力\n");
                        printf("年:"); scanf("%d",&born[0]);
                        if(born[0] == 0) break;
                        printf("月:"); scanf("%d",&born[1]);
                        printf("日:"); scanf("%d",&born[2]);
                        break;
                }
                if(p == 0) break;
                else if(born[0] == 0) break;
                else if(strcmp(c,"end") == 0) break;
                //該当探索
                k = 0;//ヒット回数
                nocount = 0;//管理者権限が無く、はじかれた回数
                for(j = 0; j < bucket_size; j++){
                    sample = DATA[j];
                    while(sample != NULL){

                        switch(i){ //一致の検査
                            case 1:
                                l = strcmp(c,sample->name_ruby[0]);
                                break;
                            case 2:
                                l = strcmp(c,sample->name_ruby[1]);
                                break;
                            case 3:
                                if(p == sample->postal) l = 0;
                                else l = 1;
                                break;
                            case 4:
                                l = strcmp(c,sample->address);
                                break;
                            case 5:
                                l = strcmp(c,sample->tell);
                                break;
                            case 6:
                                if(born[0] == sample->born[0] && born[1] == sample->born[1] && born[2] == sample->born[2]) l = 0;
                                else l = 1;
                                break;
                        }

                        if(l == 0){//一致した場合
                            k++;
                            if(root == 0 && sample->passval != 0){
                                nocount++;
                            }
                            else if(DATA_search == NULL){
                                DATA_search = sample;
                                DATA_search->right = NULL; //初期化
                            }
                            else{
                                chain = DATA_search;
                                while(chain->right != NULL){
                                    chain = chain->right;
                                }
                                chain->right = sample;
                                chain->right->right = NULL; //初期化
                            }
                        }
                        sample = sample->next;
                    }
                }
                

                //検索結果表示
                if(k == 0){
                    printf("該当する名簿が見つかりませんでした\n");
                }
                else if(k == 1){
                    printf("該当する名簿が見つかりました\n");
                    if(nocount == 0){
                        chain = DATA_search;
                        printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
                                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                    }
                    else{
                        printf("管理者権限がないため、%d件のデータはパスワードにより表示できませんでした。\n",nocount);
                    }
                }
                else if(k > 1){
                    printf("該当する名簿が%d件見つかりました\n",k);
                    printf("一括で表示します\n");
                    /* リスト内部を走査して出力する */
                    chain = DATA_search;
                    while(chain != NULL){
                        printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
                        chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                        chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                        chain = chain->right;
                    }
                    if(nocount != 0){
                        printf("管理者権限がないため、%d件のデータはパスワードにより表示できませんでした。\n",nocount);
                    }
                }else{
                    printf("エラー\n");
                    printf("検索を中断し選択画面へ移動します\n");
                }
            }
        }
        else if(i == 7){
            for(;;){
                printf("メールアドレスを入力\n");
                printf("終了する場合は'end'と入力\n");
                scanf("%s",c);
                if(strcmp(c,"end")==0) break;
                j = get_hashval(c);
                if(DATA[j] == NULL){
                    printf("該当するメールアドレスが見つかりませんでした\n");
                    printf("検索を中止し選択画面へ移動します\n");
                    break;
                }
                else{
                    chain = DATA[j];
                    while(chain != NULL){
                        if(strcmp(c,chain->mail) == 0) break;
                        chain = chain->next;
                    }
                    if(chain == NULL){
                        printf("該当するメールアドレスが見つかりませんでした\n");
                        printf("検索を中止し選択画面へ移動します\n");
                        break;
                    }
                    printf("該当する名簿が見つかりました\n");
                    if(root == 0 && chain->passval != 0){ //管理者権限ではなく、パスワードがある
                        printf("管理者権限がないため、登録されているパスワードを入力してください。（アクセスしない=0）\n");
                        scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != chain->passval){
                            printf("パスワードが違います。入力し直してください。（アクセスしない=0）\n");
                            scanf("%s",str);
                        }
                        if(strcmp(str,"0") == 0) {
                            printf("中止しました\n");
                            break;
                        }
                        printf("アクセスできました\n");
                    }
                    printf("%s %s %s %s %s %d %s %s %s %d年%d月%d日 %s %s\n",
                    chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                    chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                    chain = chain->next;
                }
            }
        }
        else if(i == 0){
            printf("名簿検索を終了しますか?\n");
            printf("yes:y or no:n\n");
            scanf("%*c%c",&chara);
            if(chara=='y') flag=0;
            else if(chara=='n') flag=2;
            else flag=1;
            if(flag==0){
                printf("名簿検索を終了します\n");
                break;
            }
            if(flag==2){
                printf("名簿検索を継続します\n");
            }
            if(flag==1){
                printf("エラー\n");
                printf("名簿検索を終了します\n");
            }
        }
    }
	return 0;
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
            printf("終了します。\n");
            break;
        }else if(i==1){
            //resister_DATA(DATA, root);
        }else if(i==2){
            //change_DATA(DATA,root);
        }else if(i==3){
            //delete_DATA(DATA,root);
        }else if(i==4){
            search_DATA(DATA,root);
        }else if(i==5){
            //view_DATA(DATA, root);
        }else{
            printf("入力が不適切です。\n");
        }
    }
    return 0;
}
