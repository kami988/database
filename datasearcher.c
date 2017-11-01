int search_DATA(node **DATA, int root){
	int i,j,k,l,m,p,flag;
	char c[1000];
	char chara;
	int hit[256];
	unsigned char s_name_ruby[256];
	unsigned char s_name[256];
	char s_postal[256];
	unsigned char s_address[512];
	char r_mail[128];
	int born[3][256];
	node *sample;
	
	start:; //最終手段goto文用flag
	printf("検索内容を選択\n");
	printf("1:名字(全角カナ)\n");
	printf("2:名前(全角カナ)\n");
	printf("3:郵便番号\n");
	printf("4:住所\n");
	printf("5:電話番号\n");
	printf("6:生年月日\n");
	printf("7:終了\n");
	printf("※完全合致のみ表示します\n");
	scanf("%d",&i);
	switch(i){
	case 1:
		for(;;){
			//name_ruby:;
			printf("名字を入力(全角カナ)\n");
			printf("終了する場合は'end'と入力\n");
			scanf("%s",c);
			if(strcmp(c,"end")==0) break;
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				if(DATA[j] != NULL){
					sample = DATA[j];
					l=strcmp(c,sample->name_ruby[0]);
					while(sample->next != NULL){
						l=strcmp(c,sample->name_ruby[0]);
						sample = sample->next;
						if(l==0)break;
					}
					if(l==0){
						hit[k]=j;
						k++;
						if(k>2) k=2;
						m++;
					}
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				flag=0;
				//goto name_ruby;
				break;
			case 1:
				printf("該当する名簿が見つかりました\n");
				j=hit[0];
				chain=DATA[j];
				printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
				chain = chain->next;
				break;
			case 2:
				printf("該当する名簿が%d件見つかりました\n",m);
				printf("一括で表示します\n");
				for(j=0;j<m;j++){
					l=hit[j]
					chain=DATA[l];
					printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
					chain = chain->next;
				}
				break;
			default:
				printf("エラー\n");
				printf("検索を中断し選択画面へ移動します\n");
				flag=2;
				//goto start;
				break;
			}
			break;
		
		case 2:
		for(;;){
			printf("名前を入力(全角カナ)\n");
			printf("終了する場合は'end'と入力\n");
			scanf("%s",&c);
			if(strcmp(c,"end")==0) break;
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				if(DATA[j] != NULL){
					sample = DATA[j];
					l=strcmp(c,sample->name[0]);
					while(sample->next != NULL){
						l=strcmp(c,sample->name[0]);
						sample = sample->next;
						if(l==0)break;
					}
					if(l==0){
						hit[k]=j;
						k++;
						if(k>2) k=2;
						m++;
					}
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				break;
			case 1:
				printf("該当する名簿が見つかりました\n");
				j=hit[0];
				chain=DATA[j];
				printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
				chain = chain->next;
				break;
			case 2:
				printf("該当する名簿が%d件見つかりました\n",m);
				printf("一括で表示します\n");
				for(j=0;j<m;j++){
					l=hit[j]
					chain=DATA[l];
					printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
					chain = chain->next;
				}
				break;
			default:
				printf("エラー\n");
				printf("検索を中断し選択画面へ移動します\n");
				flag=2;
				//goto start;
				break;
			}
			break;
		}
		
		case 3:
		for(;;){
			printf("郵便番号を入力\n");
			printf("終了する場合は0を入力\n")
			scanf("%d",&p);
			if(p==0) break;
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				if(DATA[j] != NULL){
					sample = DATA[j];
					while(sample->next != NULL){
						sample = sample->next;
						if(p==sample->postal)break;
					}
					if(l==0){
						hit[k]=j;
						k++;
						if(k>2) k=2;
						m++;
					}
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				break;
			case 1:
				printf("該当する名簿が見つかりました\n");
				j=hit[0];
				chain=DATA[j];
				printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
				chain = chain->next;
				break;
			case 2:
				printf("該当する名簿が%d件見つかりました\n",m);
				printf("一括で表示します\n");
				for(j=0;j<m;j++){
					l=hit[j]
					chain=DATA[l];
					printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
					chain = chain->next;
				}
				break;
			default:
				printf("エラー\n");
				printf("検索を中断し選択画面へ移動します\n");
				flag=2;
				//goto start;
				break;
			}
			break;
		case 4:
			//住所
		case 5:
			printf("メールアドレスを入力\n");
			printf("終了する場合は'end'と入力\n");
			scanf("%s",&c);
			if(strcmp(c,"end")==0) break;
			j=get_hashval(c);
			if(DATA[j]->mail==NULL){
				printf("該当するメールアドレスが見つかりませんでした\n");
				printf("検索を中止し選択画面へ移動します\n");
				flag=2;
				//goto start;
			}else{
				printf("該当する名簿が見つかりました");
				printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
				chain = chain->next;
			}
			break;
		case 6:
			//生年月日
		case 7:
			printf("名簿検索を終了しますか?\n");
			printf("yes:y or no:n\n");
			scanf("%c",&chara);
			if(chara=='y') flag=2;
			else if(chara=='n') flag=0;
			else flag=1;
			if(flag==0){
				printf("名簿検索を終了します\n");
				//goto start;
			}
			if(flag==2){
				printf("名簿検索を継続します\n");
				//goto name_ruby;
			}
			if(flag==1){
				printf("エラー\n");
				printf("名簿検索を終了します\n");
				//goto start;
			}
			if(flag==1) break;
			else flag=2;
			break;
	}
	if(flag!=2) goto start;
	return 0;
}
			
			

