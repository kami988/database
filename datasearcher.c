int search_DATA(){
	int i,j,k,l,m,p,flag;
	char c;
	int hit[256];
	unsigned char s_name_ruby[256];
	unsigned char s_name[256];
	char s_postal[256];
	unsigned char s_address[512];
	char r_mail[128];
	int born[3][256];

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
			printf("名字を入力(全角カナ)\n");
			scanf("%s",&c);
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				l=strcmp(c,DATA[j]->name_ruby[0]);
				if(l==0){
					hit[k]=j;
					k++;
					if(k>2) k=2;
					m++;
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				flag=1;
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
				printf("検索を中断し選択画面へ移動します");
				flag=2;
				break;
			}
			break;
		
		case 2:
		for(;;){
			printf("名前を入力(全角カナ)\n");
			scanf("%s",&c);
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				l=strcmp(c,DATA[j]->name[0]);
				if(l==0){
					hit[k]=j;
					k++;
					if(k>2) k=2;
					m++;
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				flag=1;
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
				printf("検索を中断し選択画面へ移動します");
				flag=2;
				break;
			}
			break;
		
		case 3:
		for(;;){
			printf("郵便番号を入力\n");
			scanf("%d",&p);
			k=0;
			flag=0;
			for(j=0;j<bucket_size;j++){
				if(p==DATA[j]->postal){
					hit[k]=j;
					k++;
					if(k>2) k=2;
					m++;
				}
			}
			switch(k){
			case 0:
				printf("該当する名簿が見つかりませんでした\n");
				flag=1;
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
				printf("検索を中断し選択画面へ移動します");
				flag=2;
				break;
			}
			break;

		case 5:
			printf("メールアドレスを入力\n");
			scanf("%s",&c);
			j=get_hashval(c);
			if(DATA[j]->mail==NULL){
				printf("該当するメールアドレスが見つかりませんでした\n");
				flag=1;
			}else{
				printf("該当する名簿が見つかりました");
				printf("%s %s %s %s %s %d %d %s %s %s %d年%d月%d日 %s %s\n",
                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal[0],chain->postal[1],
                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
				chain = chain->next;
			}
			break;
			
			

