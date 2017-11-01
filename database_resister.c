#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <wchar.h>

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

int resister_DATA(node** DATA){
    char c;
    char str[256],str2[256];
    int num;
    int i,j;
    int ex_postal, ex_born[3], ex_sex;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    node *sample, *null_back;
    
    while(1){
    	printf("登録データを入力してください。\n");
    	printf("[名前を入力]\n");
    	printf("姓(カナ):");				scanf("%s",ex_name_ruby[0]);
    	printf("名(カナ):");				scanf("%s",ex_name_ruby[1]);
    	printf("姓(漢字):");				scanf("%s",ex_name[0]);
    	printf("名(漢字):");				scanf("%s",ex_name[1]);
    	printf("ニックネーム:");			scanf("%s",ex_nickname);
    	printf("郵便番号を入力:");		scanf("%d",&ex_postal);
    	printf("住所:");					scanf("%s",ex_address);
    	printf("電話番号:");    			scanf("%s",ex_tell);
    	printf("メールアドレス:");	    scanf("%s",ex_mail);
    	printf("[生年月日を入力]\n");
    	printf("西暦:");			    	scanf("%d",&ex_born[0]);
    	printf("誕生月:");    			scanf("%d",&ex_born[1]);
    	printf("誕生日:");		    	scanf("%d",&ex_born[2]);
    	printf("職業:");	    			scanf("%s",ex_job);
    	printf("性別(男性=0, 女性=1, その他=2):");	scanf("%d",&ex_sex);
    	
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
        //printf("%d\n",num);
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
        
        printf("パスワードを登録しますか？");
		printf("1：はい　0：いいえ\n");
		scanf("%d",&num);
		if(num == 1){
			printf("パスワードを入力してください。(4字以上)\n");
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
		    printf("登録が完了しました。\n");
		}
		
		printf("%s %s %s %s %s %d %s %s %s %d %d %d %s %d\n",ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,ex_postal,ex_address,ex_tell,ex_mail,ex_born[0],ex_born[1],ex_born[2],ex_job,ex_sex);
		
	    printf("住所登録を続行しますか？	Yes=1:  No=2:  (入力)：");
	    scanf("%d",&i);
	    if(i==2){
		    break;
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
            resister_DATA(DATA);
        }else if(i==2){
            //change_DATA(DATA,root);
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
