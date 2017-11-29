#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define bucket_size 103 //(素数)
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

int log_system(int mode, int root){
    char c,str[100],str_ln[100];
    FILE *fi;
    time_t timer;
    struct tm *t_st;
    int flag_first = 0;
    if(mode == 0){
        if((fi = fopen("log.txt","r")) == NULL){//ファイルが存在しない
            flag_first = 1;
        }
        else{//存在する
            if(fscanf(fi,"%s", str) == EOF) flag_first = 1; //中身が空
            else{
                do{
                    if(strcmp(str,"開始時刻:") == 0 || strcmp(str,"終了時刻:") == 0){
                        strcpy(str_ln,str);
                    }
                } while(fscanf(fi,"%s", str) != EOF);
                if(strcmp(str_ln,"開始時刻:") == 0){
                    printf("\n他のユーザーが現在実行しているか、前のユーザーが強制終了したため、実行できません。\n");
                    printf("他のユーザーが終了するのを待つか、誰も実行していない場合はlog.txtの最後の行を削除してください\n");
                    exit(0);
                }
            }
            fclose(fi);
        }
    }
    
    FILE *fo = fopen("log.txt","a");
    time(&timer); // 現在時刻の取得
    t_st = localtime(&timer);// 現在時刻を構造体に変換
    if(mode == 0){
        printf("\n開始時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒\n",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        if(flag_first == 1) fprintf(fo,"開始時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        else                fprintf(fo,"\n開始時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
    }else{
        printf("\n終了時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒\n",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        if(root == 1) fprintf(fo,"\n終了時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒 (root)",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        else         fprintf(fo,"\n終了時刻: %4d年 %2d月 %2d日 %2d時%2d分%2d秒 (user)",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
    }
    fclose(fo);
}

int root_system(int *root, int *rootval){
    char str[256],str2[256];
    int num;
    printf("\n管理者権限の有無を選んでください\n");
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
        strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
        while(get_passval(str) != *rootval){
            printf("パスワードが違います。もう1度入力してください。（管理者権限でログインしない：0）\n");
            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
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
            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
            while(strlen(str) < 4){
                printf("4字以上ではありません。もう1度入力してください。\n");
                strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
            }
            printf("確認のためもう1度入力してください。\n");
            strcpy(str2,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str2);
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
    FILE *fi;

    if((fi = fopen(".DATA.csv","r")) == NULL){
        char str_root[] = "root";
        *rootval = get_passval(str_root); //管理者権限のパスワードをrootにせってい
        return 1;
    }
    else if(fgetc(fi) == EOF){ //ファイルが空なら終わり
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
        do{
            c = fgetc(fi);
        } while (c != EOF && (c == '\n' || c == ' '));//ファイルの終わりで終了
        if(feof(fi)) break;
        fseek(fi, -1, SEEK_CUR);
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

int resister_DATA(node** DATA){
    char c;
    char str[256],str2[256];
    int num;
    int i,j,cmp;
    int ex_postal, ex_born[3], ex_sex;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    char *name[3] = {"男性","女性","その他の性別"};
    char *prefecture[47] ={"北海道","青森県","岩手県","宮城県","秋田県","山形県","福島県",
    "茨城県","栃木県","群馬県","埼玉県","千葉県","東京都","神奈川県",
    "新潟県","富山県","石川県","福井県","山梨県","長野県","岐阜県",
    "静岡県","愛知県","三重県","滋賀県","京都府","大阪府","兵庫県",
    "奈良県","和歌山県","鳥取県","島根県","岡山県","広島県","山口県",
    "徳島県","香川県","愛媛県","高知県","福岡県","佐賀県","長崎県",
    "熊本県","大分県","宮崎県","鹿児島県","沖縄県"
    };

    node *sample, *null_back, *chain;
    
    while(1){
    	printf("登録データを入力してください。\n");
    	printf("[名前を入力]\n");
    	printf("姓(カナ):");				scanf("%s",ex_name_ruby[0]);
    	printf("名(カナ):");				scanf("%s",ex_name_ruby[1]);
    	printf("姓(漢字):");				scanf("%s",ex_name[0]);
    	printf("名(漢字):");				scanf("%s",ex_name[1]);
    	printf("ニックネーム:");			scanf("%s",ex_nickname);
        while(1){
            printf("郵便番号を入力(ハイフンなし):");		
            if(scanf(" %d", &ex_postal) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else break;
        }
    	printf("住所(都道府県で並び替え可能です):");					scanf("%s",ex_address);
    	printf("電話番号(ハイフンなし):");    			scanf("%s",ex_tell);
        do{
            cmp = 1;
            printf("メールアドレス:");	    scanf("%s",ex_mail);
            for(i = 0; i < bucket_size; i++){ //ハッシュ‐チェイン-テーブルを巡回して同じメールアドレスを探す
                if(DATA[i] != NULL){
                    chain = DATA[i];
                    while(chain != NULL){
                        cmp = strcmp(ex_mail, chain->mail);
                        if(cmp == 0) break;
                        chain = chain->next;
                    }
                    if(cmp == 0) break;
                }
                if(cmp == 0) break;
            }
            if(cmp == 0) printf("そのメールアドレスは既に登録されています\n");       
        }while(cmp == 0);		    	
        while(1){
            printf("[生年月日を入力]\n");
            printf("西暦:");		
            if(scanf("%d",&ex_born[0]) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else break;
        }
    	while(1){
            printf("誕生月:");	
            if(scanf("%d",&ex_born[1]) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(ex_born[1] < 1 || ex_born[1] > 12){
                printf("入力が不適切です。\n");
            }
            else break;
        }
        while(1){
            printf("誕生日:");
            if(scanf("%d",&ex_born[2]) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(ex_born[2] < 1 || ex_born[2] > 31){
                printf("入力が不適切です。\n");
            }
            else break;
        }
    	printf("職業:");	    			scanf("%s",ex_job);
        while(1){
            printf("性別(男性=0, 女性=1, その他=2):");	
            if(scanf("%d",&ex_sex) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(ex_sex < 0 || ex_sex > 2){
                printf("入力が不適切です。\n");
            }
            else break;
        }
    	
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

		sample->prefecture = 48; //都道府県割り当て(48は住所に都道府県が無かった場合)
        for(i = 0; i < 47; i++){
            if(strstr(sample->address, prefecture[i]) != NULL) {
                sample->prefecture = i+1;
                break;
            }
        }
        
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
        
        printf("パスワードを登録しますか？\n");
        while(1){
            printf("1：はい　0：いいえ\n");
            if(scanf("%d",&num) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(num < 0 || num > 1){
                printf("入力が不適切です。\n");
            }
            else break;
        }
		if(num == 1){
			printf("パスワードを入力してください。(4字以上)\n");
			strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
			while(strlen(str) < 4){
			    printf("4字以上ではありません。もう1度入力してください。\n");
			    strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
			}
			printf("確認のためもう1度入力してください。\n");
			strcpy(str2,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str2);
			while(strcmp(str,str2)!=0){
				printf("パスワードが一致しませんでした。もう1度登録し直してください。\n");
				strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
				printf("確認のためもう1度入力してください。\n");
				strcpy(str2,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str2);
            }
            sample->passval = get_passval(str);
		    printf("登録が完了しました。\n");
		}
		
		printf("%s %s %s %s %s %d %s %s %s %d %d %d %s %s\n",ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,ex_postal,ex_address,ex_tell,ex_mail,ex_born[0],ex_born[1],ex_born[2],ex_job,name[ex_sex]);
		
        
        while(1){
            printf("住所登録を続行しますか？	Yes=1:  No=2:  (入力)：");
            if(scanf("%d",&i) != 1){
                printf("入力が不適切です。\n");
                scanf("%*s");
            }
            else if(i < 1 || i > 2){
                printf("入力が不適切です。\n");
            }
            else break;
        }
	    if(i==2){
		    break;
	    }
	}
}


int change_DATA(node **DATA,int root, int *rootval){
	int i,sw;
	int flag=0;

	int val,ex_passval;
    int ex_postal,ex_tell,ex_born,ex_sex;
	unsigned char str[500],str2[500];
	node *sample;
    char *name[3] = {"男性","女性","その他の性別"};
    char *prefecture[47] ={"北海道","青森県","岩手県","宮城県","秋田県","山形県","福島県",
    "茨城県","栃木県","群馬県","埼玉県","千葉県","東京都","神奈川県",
    "新潟県","富山県","石川県","福井県","山梨県","長野県","岐阜県",
    "静岡県","愛知県","三重県","滋賀県","京都府","大阪府","兵庫県",
    "奈良県","和歌山県","鳥取県","島根県","岡山県","広島県","山口県",
    "徳島県","香川県","愛媛県","高知県","福岡県","佐賀県","長崎県",
    "熊本県","大分県","宮崎県","鹿児島県","沖縄県"
    };

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
            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
            while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                printf("パスワードが違います。もう1度入力してください。（アクセスしない=0）\n");
                strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
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
        			printf("変更後の郵便番号(ハイフンなし)：");
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
                    
                    sample->prefecture = 48; //都道府県割り当て(48は住所に都道府県が無かった場合)
                    for(i = 0; i < 47; i++){
                        if(strstr(sample->address, prefecture[i]) != NULL) {
                            sample->prefecture = i+1;
                            break;
                        }
                    }
        			break;
            
                case 5: 
                    printf("\n現在の電話番号：%s\n",sample->tell);
        			printf("変更後の電話番号(ハイフンなし)：");
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
        			push_file(DATA, *rootval);
        			init_DATA(DATA); //DATAにNULLを代入
    				insert_DATA(DATA, rootval);//ファイルからDATAに代入
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
                        strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                            printf("パスワードが違います。もう1度入力してください。（アクセスしない=0）\n");
                            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
                        }
                        if(strcmp(str,"0") == 0) {
                            printf("中止しました。\n");
                            continue;
                        }
                    }
                    while(1){
                        printf("登録するパスワード(4文字以上)：");
                        strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
                        while(strlen(str) < 4){
                            printf("\n4字以上ではありません。もう1度入力してください。\n");
                            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
                        }
                        printf("\n確認のためもう1度入力してください\n");
                        strcpy(str2,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str2);
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
            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
            while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                printf("パスワードが違います。もう1度入力してください。（アクセスしない=0）\n");
                strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
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
               while(1){
                printf("以上の情報を削除しても本当によろしいですか？YES=1,NO=0\n");
              if (scanf("%d",&handan)!=1){
                  printf("入力が不適切です\n");
                  scanf("%*s");
              }
              else if (handan != 0 && handan != 1) {
                  printf("入力が不適切です\n");
              }
              else break;
          }
          if(handan==0){
              printf("中止しました。メールアドレス入力に戻ります\n");
              continue;
          }
          else if (handan == 1) {
              while(1){
                  printf("後悔しませんね？YES=1,NO=0\n");
                  if (scanf("%d",&handan)!=1){
                      printf("入力が不適切です\n");
                      scanf("%*s");
                  }
                  else if (handan != 0 && handan != 1) {
                      printf("入力が不適切です\n");
                  }
                  else break;
              }
            if (handan == 0) {
                printf("中止しました。メールアドレス入力画面に戻ります\n");
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

int search_DATA(node **DATA, int root){
    int i,j,k,l,m,p;
    char c[1000], str[1000], *ll;
    char chara;
    int born[3];
    char *name[3] = {"男性","女性","その他の性別"};
    node *sample, *chain;
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
                k = 0;//ヒット回数
                nocount = 0;//管理者権限が無く、はじかれた回数
                switch(i){
                    case 1:
                        printf("名字を入力(全角カナ)\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 2:
                        printf("名前を入力(全角カナ)\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 3:
                        printf("郵便番号を入力(ハイフンなし)\n");
                        printf("終了する場合は0を入力\n");
                        scanf("%d",&p);
                        break;
                    case 4:
                        printf("住所を入力してください\n");
                        printf("終了する場合は'end'と入力\n");
                        scanf("%s",c);
                        break;
                    case 5:
                        printf("電話番号を入力(ハイフンなし)\n");
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
                                ll = strstr(sample->address,c);
                                if(ll != NULL) l = 0;
                                else l = 1;
                                break;
                            case 5:
                                ll = strstr(sample->tell,c);
                                if(ll != NULL) l = 0;
                                else l = 1;
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
                        strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != chain->passval){
                            printf("パスワードが違います。入力し直してください。（アクセスしない=0）\n");
                            strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
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
                }
            }
        }
        else if(i == 0){       
                printf("名簿検索を終了します\n");
                break;
        }
    }
	return 0;
}

node *insert_DATA_tree(node *x, node *sample, int mode){ //全表示での、二分探索木に挿入
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

void treeprint(node *x, int updown){ //全表示での二分探索木の表示
    int i;
    char *name[3] = {"男性","女性","その他の性別"};
	if (x != NULL){
        if(updown == 1){
            treeprint(x->left, updown);
        }
        else{
            treeprint(x->right, updown);
        }
        printf("%20s %20s %10s %10s %20s %7d %s %s %s %d年%d月%d日 %s %s\n",
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
    printf("\n住所録プログラムを開始します。\n");
    log_system(0, 0);//開始時刻とファイルの状態確認
    node *DATA[bucket_size];
    init_DATA(DATA); //DATAにNULLを代入
    insert_DATA(DATA,&rootval);//ファイルからDATAに代入
    root_system(&root, &rootval);//管理者権限

    while(1){
        printf("\nモードを選択してください\n");
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
        else if(i==1) resister_DATA(DATA);
        else if(i==2) change_DATA(DATA,root,&rootval);
        else if(i==3) delete_DATA(DATA,root);
        else if(i==4) search_DATA(DATA,root);
        else if(i==5) show_DATA(DATA, root);
    }
    printf("終了します。\n");
    push_file(DATA,rootval);//ファイルに書き出し
    log_system(1,root);//終了時刻と権限の書き出し
    return 0;
}

