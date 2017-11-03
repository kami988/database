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
    char *tok;

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


int change_DATA(node **DATA,int root){
	int i,sw;
	int flag=0;

	int val,ex_passval;
    int ex_postal,ex_tell,ex_born,ex_sex;
	unsigned char str[500],str2[500];
	node *sample;
    char *name[3] = {"男性","女性","その他の性別"};

    while(1){
    	printf("内容を変更したいユーザーのメールアドレスを入力してください (終了=0)\n");
        scanf( "%s", str);
        if(strcmp(str,"0") == 0) {
            printf("終了します。\n");
            break;
        }
        val = get_hashval(str);
        sample = DATA[val];
        if (sample == NULL) {
            printf("そのメールアドレスは登録されていません。\n");
            continue;
        }
        else {
            while (strcmp(str, sample->mail) != 0) {
                sample = sample->next;
                if (sample == NULL) {
                    printf("そのメールアドレスは登録されていません。\n");
                    break;
                }
            }
            if(sample == NULL) continue;
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

        while(1){
        	printf("\n変更したい内容の番号を入力してください\n");
        	printf("姓名　　　　　：1\n");
        	printf("呼び名　　　　：2\n");
        	printf("郵便番号　　　：3\n");
        	printf("住所　　　　　：4\n");
        	printf("電話番号　　　：5\n");
        	printf("メールアドレス：6\n");
        	printf("生年月日　　　：7\n");
        	printf("職業　　　　　：8\n");
            printf("性別          ：9\n");
            printf("パスワード    ：10\n");
        	printf("終了          ：0\n");
            scanf("%d",&sw);
            if(sw==0)break;

        	switch(sw){
                case 1: 
                    printf("\n現在の姓名：%s %s\n",sample->name[0],sample->name[1]);
        			printf("\n変更後の姓：");
        			scanf("%s",str);
        			sample->name[0]=(char*)realloc(sample->name[0],sizeof(char)*(strlen(str)+1));//増やしたり減らしたり
        			strcpy(sample->name[0],str);
            
        			printf("フリガナ：");
        			scanf("%s",str);
        			sample->name_ruby[0]=(char*)realloc(sample->name_ruby[0],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name_ruby[0],str);
            
        			printf("\n変更後の名：");
        			scanf("%s",str);
        			sample->name[1]=(char*)realloc(sample->name[1],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name[1],str);
            
        			printf("フリガナ：");
        			scanf("%s",str);
        			sample->name_ruby[1]=(char*)realloc(sample->name_ruby[1],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name_ruby[1],str);
            
        			printf("\n姓名が %s %s ( %s %s )に変更されました\n",sample->name[0],sample->name[1]
        																				,sample->name_ruby[0],sample->name_ruby[1]);
        			break;
            
                case 2: 
                    printf("\n現在の呼び名：%s\n",sample->nickname);
        			printf("変更後の呼び名：");
        			scanf("%s",str);
        			sample->nickname=(char*)realloc(sample->nickname,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->nickname,str);
        			printf("\n呼び名が %s に変更されました\n",sample->nickname);
        			break;
            
                case 3: 
                    printf("\n現在の郵便番号：%d\n",sample->postal);
        			printf("変更後の郵便番号：");
        			scanf("%d",&ex_postal);
        			sample->postal = ex_postal;
        			printf("\n郵便番号が %d に変更されました\n",sample->postal);
        			break;
            
                case 4: 
                    printf("\n現在の住所：%s\n",sample->address);
        			printf("変更後の住所：");
        			scanf("%s",str);
        			sample->address=(char*)realloc(sample->address,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->address,str);
        			printf("\n住所が %s に変更されました\n",sample->address);
        			break;
            
                case 5: 
                    printf("\n現在の電話番号：%s\n",sample->tell);
        			printf("変更後の電話番号：");
        			scanf("%s",str);
        			sample->tell=(char*)realloc(sample->tell,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->tell,str);
        			printf("\n電話番号が %s に変更されました\n",sample->tell);
        			break;
            
                case 6: 
                    printf("\n現在のメールアドレス：%s\n",sample->mail);
        			printf("変更後のメールアドレス：");
        			scanf("%s",str);
        			sample->mail=(char*)realloc(sample->mail,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->mail,str);
        			printf("\nメールアドレスが %s に変更されました\n",sample->mail);
        			break;
            
                case 7: 
                    printf("\n現在の生年月日：%d年 %d月 %d日\n",sample->born[0],sample->born[1],sample->born[2]);
        			printf("\n変更後の西暦：");
        			scanf("%d",&ex_born);
        			sample->born[0]=ex_born;
            
        			printf("\n変更後の月：");
        			scanf("%d",&ex_born);
        			sample->born[1]=ex_born;
            
        			printf("\n変更後の日：");
        			scanf("%d",&ex_born);
        			sample->born[2]=ex_born;
        			printf("\n生年月日が %d年 %d月 %d日 に変更されました\n",sample->born[0],sample->born[1],sample->born[2]); 
        			break;
            
                case 8:
                    printf("\n現在の職業：%s\n",sample->job);
        			printf("変更後の職業：");
        			scanf("%s",str);
        			sample->job=(char*)realloc(sample->job,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->job,str);
        			printf("\n職業が %s に変更されました\n",sample->job);
        			break;
            
                case 9: 
                    printf("\n現在の性別：%s\n",name[sample->sex]);
        			printf("変更後の性別(男性=0, 女性=1, その他の性別=2)：");
        			scanf("%d",&ex_sex);
        			sample->sex=ex_sex;
        			printf("\n性別が %s に変更されました\n",name[sample->sex]);
                    break;
                case 10:
                    if(sample->passval == 0){
                        printf("\n新規登録になります\n");
                    }
                    else if(root == 0){
                        printf("\n現在のパスワードを入力してください\n");
                        scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                            printf("パスワードが違います。もう1度入力してください。（アクセスしない=0）\n");
                            scanf("%s",str);
                        }
                        if(strcmp(str,"0") == 0) {
                            printf("中止しました。\n");
                            continue;
                        }
                    }
                    while(1){
                        printf("登録するパスワード(4文字以上)：");
                        scanf("%s",str);
                        while(strlen(str) < 4){
                            printf("\n4字以上ではありません。もう1度入力してください。\n");
                            scanf("%s",str);
                        }
                        printf("\n確認のためもう1度入力してください\n");
                        scanf("%s",str2);
                        if(strcmp(str,str2)!=0){
                            printf("\nパスワードが一致しませんでした。登録し直してください\n");//繰り返し
                            continue;
                        }
                        else{
                            sample->passval = get_passval(str);
                            printf("\n登録が完了しました。\n");
                            break;
                        }
                    }
                    break;
        	}
        }
    }
}

int main(int argc, char *argv[]) {
    int i;
    int root, rootval;

    node *DATA[bucket_size];
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(DATA,&rootval);//DATAに代入(仮)

    root_system(&root, &rootval);//管理者権限（仮）

    while(1){
        printf("モードを選択してください\n");
        printf("0：終了　１：登録　２：変更　３：削除　４：検索　５：全表示\n");
        scanf("%d",&i);
        if(i==0){
            printf("終了します。\n");
            break;
        }else if(i==1){
            //resister_DATA(DATA);
        }else if(i==2){
            change_DATA(DATA,root);
        }else if(i==3){
            //delete_DATA(DATA,root);
        }else if(i==4){
            //search_DATA(DATA,root);
        }else if(i==5){
            view_DATA(DATA, root);//（仮）
        }else{
            printf("入力が不適切です。\n");
        }
    }
    return 0;
}

