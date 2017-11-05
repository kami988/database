#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define bucket_size 103 //(�f��)
#define bucket_pass 32749391 //32,749,391(�f��)

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

int init_DATA(node **DATA) {// �n�b�V���e�[�u����NULL�ŏ�����
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
        if((fi = fopen("log_windows.txt","r")) == NULL){//�t�@�C�������݂��Ȃ�
            flag_first = 1;
        }
        else{//���݂���
            if(fscanf(fi,"%s", str) == EOF) flag_first = 1; //���g����
            else{
                do{
                    if(strcmp(str,"�J�n����:") == 0 || strcmp(str,"�I������:") == 0){
                        strcpy(str_ln,str);
                    }
                } while(fscanf(fi,"%s", str) != EOF);
                if(strcmp(str_ln,"�J�n����:") == 0){
                    printf("\n���̃��[�U�[�����ݎ��s���Ă��邩�A�O�̃��[�U�[�������I���������߁A���s�ł��܂���B\n");
                    printf("���̃��[�U�[���I������̂�҂��A�N�����s���Ă��Ȃ��ꍇ��log.txt�̍Ō�̍s���폜���Ă�������\n");
                    exit(0);
                }
            }
            fclose(fi);
        }
    }
    
    FILE *fo = fopen("log_windows.txt","a");
    time(&timer); // ���ݎ����̎擾
    t_st = localtime(&timer);// ���ݎ������\���̂ɕϊ�
    if(mode == 0){
        printf("�J�n����: %4d�N %2d�� %2d�� %2d��%2d��%2d�b\n",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        if(flag_first == 1) fprintf(fo,"�J�n����: %4d�N %2d�� %2d�� %2d��%2d��%2d�b",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        else                fprintf(fo,"\n�J�n����: %4d�N %2d�� %2d�� %2d��%2d��%2d�b",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
    }else{
        printf("�I������: %4d�N %2d�� %2d�� %2d��%2d��%2d�b\n",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        if(root == 1) fprintf(fo,"\n�I������: %4d�N %2d�� %2d�� %2d��%2d��%2d�b (root)",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
        else         fprintf(fo,"\n�I������: %4d�N %2d�� %2d�� %2d��%2d��%2d�b (user)",1900+t_st->tm_year,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
    }
    fclose(fo);
}

int root_system(int *root, int *rootval){
    char str[256],str2[256];
    int num;
    printf("�Ǘ��Ҍ����̗L����I��ł�������\n");
    while(1){
        printf("�P�F����@�O�F�Ȃ�\n");
        if(scanf(" %d", root) != 1){
            printf("���͂��s�K�؂ł��B\n");
            scanf("%*s");
        }
        else if(*root != 0 && *root != 1){
            printf("���͂��s�K�؂ł��B\n");
        }
        else break;
    }
    if(*root == 1){
        printf("�p�X���[�h����͂��Ă��������B(�����p�X���[�h�Froot)\n");
        scanf("%s",str);
        while(get_passval(str) != *rootval){
            printf("�p�X���[�h���Ⴂ�܂��B����1�x���͂��Ă��������B�i�Ǘ��Ҍ����Ń��O�C�����Ȃ��F0�j\n");
            scanf("%s",str);
            if(strcmp(str,"0") == 0) {
                *root = 0;
                return 1;
            }
        }
        printf("�p�X���[�h��ύX���܂����H\n");
        while(1){
            printf("�P�F����@�O�F���Ȃ�\n");
            if(scanf(" %d", &num) != 1){
                printf("���͂��s�K�؂ł��B\n");
                scanf("%*s");
            }
            else if(num != 0 && num != 1){
                printf("���͂��s�K�؂ł��B\n");
            }
            else break;
        }
        while(num == 1){
            printf("�V�����p�X���[�h����͂��Ă��������B(4���ȏ�)\n");
            scanf("%s",str);
            while(strlen(str) < 4){
                printf("4���ȏ�ł͂���܂���B����1�x���͂��Ă��������B\n");
                scanf("%s",str);
            }
            printf("�m�F�̂��߂���1�x���͂��Ă��������B\n");
            scanf("%s",str2);
            if(strcmp(str,str2)!=0){
                printf("�p�X���[�h����v���܂���ł����B�o�^�������Ă��������B\n");
            }
            else{
            	*rootval = get_passval(str);
            	printf("�o�^���������܂����B\n");
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
    char *prefecture[47] ={"�k�C��","�X��","��茧","�{�錧","�H�c��","�R�`��","������",
    "��錧","�Ȗ،�","�Q�n��","��ʌ�","��t��","�����s","�_�ސ쌧",
    "�V����","�x�R��","�ΐ쌧","���䌧","�R����","���쌧","�򕌌�",
    "�É���","���m��","�O�d��","���ꌧ","���s�{","���{","���Ɍ�",
    "�ޗǌ�","�a�̎R��","���挧","������","���R��","�L����","�R����",
    "������","���쌧","���Q��","���m��","������","���ꌧ","���茧",
    "�F�{��","�啪��","�{�茧","��������","���ꌧ"
    };

    FILE *fi = fopen("DATA_windows.csv","r");
    if(fgetc(fi) == EOF){ //�t�@�C������Ȃ�I���
        char str_root[] = "root";
        *rootval = get_passval(str_root); //�Ǘ��Ҍ����̃p�X���[�h��root�ɂ����Ă�
        return 1;
    }
    else fseek(fi, 0, SEEK_SET);

    fscanf(fi,"%d",rootval);
    fgetc(fi);//���s�ǂ�
    if(fgetc(fi) == EOF){ //�o�^�f�[�^���Ȃ���ΏI���
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

        sample->prefecture = 48; //�s���{�����蓖��(48�͏Z���ɓs���{�������������ꍇ)
        for(i = 0; i < 47; i++){
            if(strstr(sample->address, prefecture[i]) != NULL) {
                sample->prefecture = i+1;
                break;
            }
        }

        num = get_hashval(ex_mail); //���[���A�h���X����n�b�V���l�𐶐�
        if(DATA[num] == NULL) {//�Փ˂Ȃ�
            DATA[num] = sample;
        }
        else{//�Փ˗L��
            null_back = DATA[num];//NULL��������|�C���^
            while(null_back->next != NULL){ //NULL��������܂Ő��`���X�g�𑖍�
                null_back = null_back->next;
            }
            null_back->next = sample;//NULL�������|�C���^�̎�O��next(�܂�NULL)�ɑ��
        }
        if (fgetc(fi) == EOF) break;//�t�@�C���̏I���ŏI��
    }
    fclose(fi);
}

int push_file(node **DATA, int rootval){
    int i;
    node *chain;
    FILE *fo = fopen("DATA_windows.csv","w");
    char str[] = "root";
    fprintf(fo,"%d",rootval); //�Ǘ��Ҍ����̃p�X���[�h
    for(i = 0; i < bucket_size; i++){
        if(DATA[i] != NULL){
            chain = DATA[i];
            // ���X�g�����𑖍����ďo�͂���
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
    int i,j;
    int ex_postal, ex_born[3], ex_sex;
    unsigned char ex_name_ruby[2][256], ex_name[2][128], ex_nickname[128], ex_address[512];
	char ex_tell[20], ex_mail[128];
    unsigned char ex_job[512];
    char *name[3] = {"�j��","����","���̑��̐���"};

    node *sample, *null_back;
    
    while(1){
    	printf("�o�^�f�[�^����͂��Ă��������B\n");
    	printf("[���O�����]\n");
    	printf("��(�J�i):");				scanf("%s",ex_name_ruby[0]);
    	printf("��(�J�i):");				scanf("%s",ex_name_ruby[1]);
    	printf("��(����):");				scanf("%s",ex_name[0]);
    	printf("��(����):");				scanf("%s",ex_name[1]);
    	printf("�j�b�N�l�[��:");			scanf("%s",ex_nickname);
    	printf("�X�֔ԍ������:");		scanf("%d",&ex_postal);
    	printf("�Z��:");					scanf("%s",ex_address);
    	printf("�d�b�ԍ�:");    			scanf("%s",ex_tell);
    	printf("���[���A�h���X:");	    scanf("%s",ex_mail);
    	printf("[���N���������]\n");
    	printf("����:");			    	scanf("%d",&ex_born[0]);
    	printf("�a����:");    			scanf("%d",&ex_born[1]);
    	printf("�a����:");		    	scanf("%d",&ex_born[2]);
    	printf("�E��:");	    			scanf("%s",ex_job);
    	printf("����(�j��=0, ����=1, ���̑�=2):");	scanf("%d",&ex_sex);
    	
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

		num = get_hashval(ex_mail); //���[���A�h���X����n�b�V���l�𐶐�
        //printf("%d\n",num);
        if(DATA[num] == NULL) {//�Փ˂Ȃ�
            DATA[num] = sample;
        }
        else{//�Փ˗L��
            null_back = DATA[num];//NULL��������|�C���^
            while(null_back->next != NULL){ //NULL��������܂Ő��`���X�g�𑖍�
                null_back = null_back->next;
            }
            null_back->next = sample;//NULL�������|�C���^�̎�O��next(�܂�NULL)�ɑ��
        }
        
        printf("�p�X���[�h��o�^���܂����H");
		printf("1�F�͂��@0�F������\n");
		scanf("%d",&num);
		if(num == 1){
			printf("�p�X���[�h����͂��Ă��������B(4���ȏ�)\n");
			scanf("%s",str);
			while(strlen(str) < 4){
			    printf("4���ȏ�ł͂���܂���B����1�x���͂��Ă��������B\n");
			    scanf("%s",str);
			}
			printf("�m�F�̂��߂���1�x���͂��Ă��������B\n");
			scanf("%s",str2);
			while(strcmp(str,str2)!=0){
				printf("�p�X���[�h����v���܂���ł����B����1�x�o�^�������Ă��������B\n");
				scanf("%s",str);
				printf("�m�F�̂��߂���1�x���͂��Ă��������B\n");
				scanf("%s",str2);
            }
            sample->passval = get_passval(str);
		    printf("�o�^���������܂����B\n");
		}
		
		printf("%s %s %s %s %s %d %s %s %s %d %d %d %s %s\n",ex_name_ruby[0],ex_name_ruby[1],ex_name[0],ex_name[1],ex_nickname,ex_postal,ex_address,ex_tell,ex_mail,ex_born[0],ex_born[1],ex_born[2],ex_job,name[ex_sex]);
		
	    printf("�Z���o�^�𑱍s���܂����H	Yes=1:  No=2:  (����)�F");
	    scanf("%d",&i);
	    if(i==2){
		    break;
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
    char *name[3] = {"�j��","����","���̑��̐���"};

    while(1){
    	printf("���e��ύX���������[�U�[�̃��[���A�h���X����͂��Ă������� (�I��=0)\n");
        scanf( "%s", str);
        if(strcmp(str,"0") == 0) {
            printf("�I�����܂��B\n");
            break;
        }
        val = get_hashval(str);
        sample = DATA[val];
        if (sample == NULL) {
            printf("���̃��[���A�h���X�͓o�^����Ă��܂���B\n");
            continue;
        }
        else {
            while (strcmp(str, sample->mail) != 0) {
                sample = sample->next;
                if (sample == NULL) {
                    printf("���̃��[���A�h���X�͓o�^����Ă��܂���B\n");
                    break;
                }
            }
            if(sample == NULL) continue;
    	}
    	 if(root == 0 && sample->passval != 0){ //�Ǘ��Ҍ����ł͂Ȃ��A�p�X���[�h������
            printf("�Ǘ��Ҍ������Ȃ����߁A�o�^����Ă���p�X���[�h����͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
            scanf("%s",str);
            while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                printf("�p�X���[�h���Ⴂ�܂��B����1�x���͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
                scanf("%s",str);
            }
            if(strcmp(str,"0") == 0) {
                printf("���~���܂����B\n");
                continue;
            }
            printf("�A�N�Z�X�ł��܂���\n");
    	}

        while(1){
        	printf("\n�ύX���������e�̔ԍ�����͂��Ă�������\n");
        	printf("�����@�@�@�@�@�F1\n");
        	printf("�Ăі��@�@�@�@�F2\n");
        	printf("�X�֔ԍ��@�@�@�F3\n");
        	printf("�Z���@�@�@�@�@�F4\n");
        	printf("�d�b�ԍ��@�@�@�F5\n");
        	printf("���[���A�h���X�F6\n");
        	printf("���N�����@�@�@�F7\n");
        	printf("�E�Ɓ@�@�@�@�@�F8\n");
            printf("����          �F9\n");
            printf("�p�X���[�h    �F10\n");
        	printf("�I��          �F0\n");
            scanf("%d",&sw);
            if(sw==0)break;

        	switch(sw){
                case 1: 
                    printf("\n���݂̐����F%s %s\n",sample->name[0],sample->name[1]);
        			printf("\n�ύX��̐��F");
        			scanf("%s",str);
        			sample->name[0]=(char*)realloc(sample->name[0],sizeof(char)*(strlen(str)+1));//���₵���茸�炵����
        			strcpy(sample->name[0],str);
            
        			printf("�t���K�i�F");
        			scanf("%s",str);
        			sample->name_ruby[0]=(char*)realloc(sample->name_ruby[0],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name_ruby[0],str);
            
        			printf("\n�ύX��̖��F");
        			scanf("%s",str);
        			sample->name[1]=(char*)realloc(sample->name[1],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name[1],str);
            
        			printf("�t���K�i�F");
        			scanf("%s",str);
        			sample->name_ruby[1]=(char*)realloc(sample->name_ruby[1],sizeof(char)*(strlen(str)+1));
        			strcpy(sample->name_ruby[1],str);
            
        			printf("\n������ %s %s ( %s %s )�ɕύX����܂���\n",sample->name[0],sample->name[1]
        																				,sample->name_ruby[0],sample->name_ruby[1]);
        			break;
            
                case 2: 
                    printf("\n���݂̌Ăі��F%s\n",sample->nickname);
        			printf("�ύX��̌Ăі��F");
        			scanf("%s",str);
        			sample->nickname=(char*)realloc(sample->nickname,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->nickname,str);
        			printf("\n�Ăі��� %s �ɕύX����܂���\n",sample->nickname);
        			break;
            
                case 3: 
                    printf("\n���݂̗X�֔ԍ��F%d\n",sample->postal);
        			printf("�ύX��̗X�֔ԍ��F");
        			scanf("%d",&ex_postal);
        			sample->postal = ex_postal;
        			printf("\n�X�֔ԍ��� %d �ɕύX����܂���\n",sample->postal);
        			break;
            
                case 4: 
                    printf("\n���݂̏Z���F%s\n",sample->address);
        			printf("�ύX��̏Z���F");
        			scanf("%s",str);
        			sample->address=(char*)realloc(sample->address,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->address,str);
        			printf("\n�Z���� %s �ɕύX����܂���\n",sample->address);
        			break;
            
                case 5: 
                    printf("\n���݂̓d�b�ԍ��F%s\n",sample->tell);
        			printf("�ύX��̓d�b�ԍ��F");
        			scanf("%s",str);
        			sample->tell=(char*)realloc(sample->tell,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->tell,str);
        			printf("\n�d�b�ԍ��� %s �ɕύX����܂���\n",sample->tell);
        			break;
            
                case 6: 
                    printf("\n���݂̃��[���A�h���X�F%s\n",sample->mail);
        			printf("�ύX��̃��[���A�h���X�F");
        			scanf("%s",str);
        			sample->mail=(char*)realloc(sample->mail,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->mail,str);
        			printf("\n���[���A�h���X�� %s �ɕύX����܂���\n",sample->mail);
        			break;
            
                case 7: 
                    printf("\n���݂̐��N�����F%d�N %d�� %d��\n",sample->born[0],sample->born[1],sample->born[2]);
        			printf("\n�ύX��̐���F");
        			scanf("%d",&ex_born);
        			sample->born[0]=ex_born;
            
        			printf("\n�ύX��̌��F");
        			scanf("%d",&ex_born);
        			sample->born[1]=ex_born;
            
        			printf("\n�ύX��̓��F");
        			scanf("%d",&ex_born);
        			sample->born[2]=ex_born;
        			printf("\n���N������ %d�N %d�� %d�� �ɕύX����܂���\n",sample->born[0],sample->born[1],sample->born[2]); 
        			break;
            
                case 8:
                    printf("\n���݂̐E�ƁF%s\n",sample->job);
        			printf("�ύX��̐E�ƁF");
        			scanf("%s",str);
        			sample->job=(char*)realloc(sample->job,sizeof(char)*(strlen(str)+1));
        			strcpy(sample->job,str);
        			printf("\n�E�Ƃ� %s �ɕύX����܂���\n",sample->job);
        			break;
            
                case 9: 
                    printf("\n���݂̐��ʁF%s\n",name[sample->sex]);
        			printf("�ύX��̐���(�j��=0, ����=1, ���̑��̐���=2)�F");
        			scanf("%d",&ex_sex);
        			sample->sex=ex_sex;
        			printf("\n���ʂ� %s �ɕύX����܂���\n",name[sample->sex]);
                    break;
                case 10:
                    if(sample->passval == 0){
                        printf("\n�V�K�o�^�ɂȂ�܂�\n");
                    }
                    else if(root == 0){
                        printf("\n���݂̃p�X���[�h����͂��Ă�������\n");
                        scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                            printf("�p�X���[�h���Ⴂ�܂��B����1�x���͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
                            scanf("%s",str);
                        }
                        if(strcmp(str,"0") == 0) {
                            printf("���~���܂����B\n");
                            continue;
                        }
                    }
                    while(1){
                        printf("�o�^����p�X���[�h(4�����ȏ�)�F");
                        scanf("%s",str);
                        while(strlen(str) < 4){
                            printf("\n4���ȏ�ł͂���܂���B����1�x���͂��Ă��������B\n");
                            scanf("%s",str);
                        }
                        printf("\n�m�F�̂��߂���1�x���͂��Ă�������\n");
                        scanf("%s",str2);
                        if(strcmp(str,str2)!=0){
                            printf("\n�p�X���[�h����v���܂���ł����B�o�^�������Ă�������\n");//�J��Ԃ�
                            continue;
                        }
                        else{
                            sample->passval = get_passval(str);
                            printf("\n�o�^���������܂����B\n");
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
    char *name[3] = {"�j��","����","���̑��̐���"};

    while(1){
        printf("�폜���������[�U�[�̃��[���A�h���X����͂��Ă��������i�I��=0�j\n");
        scanf( "%s", mail);
        if(strcmp(mail,"0") == 0) {
            printf("�I�����܂��B\n");
            break;
        }
        val = get_hashval(mail);
        sample = DATA[val];
        if (sample == NULL) {
            printf("���̃��[���A�h���X�͓o�^����Ă��܂���B\n");
            continue;
        }
        else {
            if (strcmp(mail, sample->mail) == 0) {//���`���X�g�̐擪����������
                first = 1;
            }else{
                first = 0;
                while (strcmp(mail, sample->mail) != 0) {
                    back = sample;
                    sample = sample->next;
                    if (sample == NULL) {
                        printf("���̃��[���A�h���X�͓o�^����Ă��܂���B\n");
                        break;
                    }
                }
                if(sample == NULL) continue; //��蒼��
            }
        }
        if(root == 0 && sample->passval != 0){ //�Ǘ��Ҍ����ł͂Ȃ��A�p�X���[�h������
            printf("�Ǘ��Ҍ������Ȃ����߁A�o�^����Ă���p�X���[�h����͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
            scanf("%s",str);
            while(strcmp(str,"0") != 0 && get_passval(str) != sample->passval){
                printf("�p�X���[�h���Ⴂ�܂��B����1�x���͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
                scanf("%s",str);
            }
            if(strcmp(str,"0") == 0) {
                printf("���~���܂����B\n");
                continue;
            }
            printf("�A�N�Z�X�ł��܂���\n");
        }
        printf("%s %s %s %s %s %d %s %s %s %d�N%d��%d�� %s %s\n",
               sample->name_ruby[0], sample->name_ruby[1], sample->name[0], sample->name[1], sample->nickname, sample->postal,
               sample->address, sample->tell, sample->mail, sample->born[0], sample->born[1], sample->born[2], sample->job, name[sample->sex]);
        printf("�ȏ�̏����폜���Ă��{���ɂ�낵���ł����HYES=1,NO=0\n");
        scanf("%d", &handan);
        if (handan == 0) {
            printf("���~���܂���\n");
            continue;
        }
        else if (handan == 1) {
            printf("������܂���ˁHYES=1,NO=0\n");
            scanf("%d", &handan);
            if (handan == 0) {
                printf("���~���܂���\n");
                continue;
            }
            else if (handan == 1) {
                if(first == 1){//�擪������
                    DATA[val] = sample->next;
                    free(sample);
                }
                else{//�Ԃ�����
                    back->next = sample->next;
                    free(sample);
                }
                printf("�폜���܂���\n");
            }
            else {
                printf("���̓G���[�ł�\n");
                continue;
            }
        }
        else {
            printf("���̓G���[�ł�\n");
            continue;
        }
    }
}

int search_DATA(node **DATA, int root){
    int i,j,k,l,m,p;
    char c[1000], str[1000];
    char chara;
    int born[3];
    char *name[3] = {"�j��","����","���̑��̐���"};
    node *sample, *chain;
    node *keep;//��Ŗ߂�next�̃|�C���^
    node *DATA_search = NULL;//��������
    int nocount = 0;

    int flag = 2;//�p������
	for(;;){
	    DATA_search = NULL;
        printf("�������e��I��\n");
        printf("0:�I��\n");
        printf("1:����(�S�p�J�i)\n");
        printf("2:���O(�S�p�J�i)\n");
        printf("3:�X�֔ԍ�\n");
        printf("4:�Z��\n");
        printf("5:�d�b�ԍ�\n");
        printf("6:���N����\n");
        printf("7:���[���A�h���X\n");
        printf("�����S���v�̂ݕ\\�����܂�\n");
        scanf("%d",&i);
        if(1 <= i && i <= 6){
            for(;;){
                born[0] = 1;        //������
                p = 1;              //������
                strcpy(c,"\n");     //������
                DATA_search = NULL; //������
                switch(i){
                    case 1:
                        printf("���������(�S�p�J�i)\n");
                        printf("�I������ꍇ��'end'�Ɠ���\n");
                        scanf("%*c%*c%s",c);
                        printf("%s",c);
                        break;
                    case 2:
                        printf("���O�����(�S�p�J�i)\n");
                        printf("�I������ꍇ��'end'�Ɠ���\n");
                        scanf("%s\n",c);
                        break;
                    case 3:
                        printf("�X�֔ԍ������\n");
                        printf("�I������ꍇ��0�����\n");
                        scanf("%d",&p);
                        break;
                    case 4:
                        printf("�Z������͂��Ă�������\n");
                        printf("�I������ꍇ��'end'�Ɠ���\n");
                        scanf("%s",c);
                        break;
                    case 5:
                        printf("�d�b�ԍ������\n");
                        printf("�I������ꍇ��'end'�Ɠ���\n");
                        scanf("%s",c);
                        break;
                    case 6:
                        printf("���N��������͂��Ă��������B\n");
                        printf("�I������ꍇ��'0'�Ɠ���\n");
                        printf("�N:"); scanf("%d",&born[0]);
                        if(born[0] == 0) break;
                        printf("��:"); scanf("%d",&born[1]);
                        printf("��:"); scanf("%d",&born[2]);
                        break;
                }
                if(p == 0) break;
                else if(born[0] == 0) break;
                else if(strcmp(c,"end") == 0) break;
                //�Y���T��
                k = 0;//�q�b�g��
                nocount = 0;//�Ǘ��Ҍ����������A�͂����ꂽ��
                for(j = 0; j < bucket_size; j++){
                    sample = DATA[j];
                    while(sample != NULL){

                        switch(i){ //��v�̌���
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

                        if(l == 0){//��v�����ꍇ
                            k++;
                            if(root == 0 && sample->passval != 0){
                                nocount++;
                            }
                            else if(DATA_search == NULL){
                                DATA_search = sample;
                                DATA_search->right = NULL; //������
                            }
                            else{
                                chain = DATA_search;
                                while(chain->right != NULL){
                                    chain = chain->right;
                                }
                                chain->right = sample;
                                chain->right->right = NULL; //������
                            }
                        }
                        sample = sample->next;
                    }
                }
                

                //�������ʕ\\��
                if(k == 0){
                    printf("�Y�����閼�낪������܂���ł���\n");
                }
                else if(k == 1){
                    printf("�Y�����閼�낪������܂���\n");
                    if(nocount == 0){
                        chain = DATA_search;
                        printf("%s %s %s %s %s %d %s %s %s %d�N%d��%d�� %s %s\n",
                                chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                                chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                        DATA_search->next = keep;//�߂�
                        DATA_search = NULL;//�ė��p���邽�ߏ�����
                    }
                    else{
                        printf("�Ǘ��Ҍ������Ȃ����߁A%d���̃f�[�^�̓p�X���[�h�ɂ��\\���ł��܂���ł����B\n",nocount);
                    }
                }
                else if(k > 1){
                    printf("�Y�����閼�낪%d��������܂���\n",k);
                    printf("�ꊇ�ŕ\\�����܂�\n");
                    /* ���X�g�����𑖍����ďo�͂��� */
                    chain = DATA_search;
                    while(chain != NULL){
                        printf("%s %s %s %s %s %d %s %s %s %d�N%d��%d�� %s %s\n",
                        chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                        chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                        chain = chain->right;
                    }
                    if(nocount != 0){
                        printf("�Ǘ��Ҍ������Ȃ����߁A%d���̃f�[�^�̓p�X���[�h�ɂ��\\���ł��܂���ł����B\n",nocount);
                    }
                }else{
                    printf("�G���[\n");
                    printf("�����𒆒f���I����ʂֈړ����܂�\n");
                }
            }
        }
        else if(i == 7){
            for(;;){
                printf("���[���A�h���X�����\n");
                printf("�I������ꍇ��'end'�Ɠ���\n");
                scanf("%s",c);
                if(strcmp(c,"end")==0) break;
                j = get_hashval(c);
                if(DATA[j] == NULL){
                    printf("�Y�����郁�[���A�h���X��������܂���ł���\n");
                    printf("�����𒆎~���I����ʂֈړ����܂�\n");
                    break;
                }
                else{
                    chain = DATA[j];
                    while(chain != NULL){
                        if(strcmp(c,chain->mail) == 0) break;
                        chain = chain->next;
                    }
                    if(chain == NULL){
                        printf("�Y�����郁�[���A�h���X��������܂���ł���\n");
                        printf("�����𒆎~���I����ʂֈړ����܂�\n");
                        break;
                    }
                    printf("�Y�����閼�낪������܂���\n");
                    if(root == 0 && chain->passval != 0){ //�Ǘ��Ҍ����ł͂Ȃ��A�p�X���[�h������
                        printf("�Ǘ��Ҍ������Ȃ����߁A�o�^����Ă���p�X���[�h����͂��Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
                        scanf("%s",str);
                        while(strcmp(str,"0") != 0 && get_passval(str) != chain->passval){
                            printf("�p�X���[�h���Ⴂ�܂��B���͂������Ă��������B�i�A�N�Z�X���Ȃ�=0�j\n");
                            scanf("%s",str);
                        }
                        if(strcmp(str,"0") == 0) {
                            printf("���~���܂���\n");
                            break;
                        }
                        printf("�A�N�Z�X�ł��܂���\n");
                    }
                    printf("%s %s %s %s %s %d %s %s %s %d�N%d��%d�� %s %s\n",
                    chain->name_ruby[0],chain->name_ruby[1],chain->name[0],chain->name[1],chain->nickname,chain->postal,
                    chain->address,chain->tell,chain->mail,chain->born[0],chain->born[1],chain->born[2],chain->job,name[chain->sex]);
                    chain = chain->next;
                }
            }
        }
        else if(i == 0){
            printf("���댟�����I�����܂���?\n");
            printf("yes:y or no:n\n");
            scanf("%*c%c",&chara);
            if(chara=='y') flag=0;
            else if(chara=='n') flag=2;
            else flag=1;
            if(flag==0){
                printf("���댟�����I�����܂�\n");
                break;
            }
            if(flag==2){
                printf("���댟�����p�����܂�\n");
            }
            if(flag==1){
                printf("�G���[\n");
                printf("���댟�����I�����܂�\n");
            }
        }
    }
	return 0;
}

node *insert_DATA_tree(node *x, node *sample, int mode){ //�S�\\���ł́A�񕪒T���؂ɑ}��
    int judge;
    int i;
    

	if(x == NULL){
        x = sample;
        x->right = NULL;
        x->left = NULL;
	}
	else{
        if     (mode == 1) judge = strcmp(x->name_ruby[0], sample->name_ruby[0]);//��
        else if(mode == 2) judge = strcmp(x->name_ruby[1], sample->name_ruby[1]);//��
        else if(mode == 3) judge = strcmp(x->nickname, sample->nickname);//�Ăі�
        else if(mode == 4) {//�X�֔ԍ�
            if(x->postal > sample->postal) judge = 1;
            else judge = -1;
        }
        else if(mode == 5) {//�s���{��
            if(x->prefecture > sample->prefecture) judge = 1;
            else judge = -1;
        }
        else if(mode == 6) judge = strcmp(x->tell, sample->tell);//�d�b�ԍ�
        else if(mode == 7) judge = strcmp(x->mail, sample->mail);//���[���A�h���X
        else if(mode == 8) {//���N����
            if(x->born[0] > sample->born[0]) judge = 1;//�N
            else if(x->born[0] < sample->born[0])judge = -1;
            else{
                if(x->born[1] > sample->born[1]) judge = 1;//��
                else if(x->born[1] < sample->born[1])judge = -1;
                else{
                    if(x->born[2] > sample->born[2]) judge = 1;//��
                    else judge = -1;
                }
            }
        }
        else if(mode == 9) judge = strcmp(x->job, sample->job);//�E��
        else if(mode == 10) {//����
            if(x->sex > sample->sex) judge = 1;
            else judge = -1;
        }
        if     (judge > 0)   x->left  = insert_DATA_tree(x->left,sample,mode);
        else if(judge <= 0)   x->right = insert_DATA_tree(x->right,sample,mode);
    }
	return x;
}

void treeprint(node *x, int updown){ //�S�\\���ł̓񕪒T���؂̕\\��
    int i;
    char *name[3] = {"�j��","����","���̑��̐���"};
	if (x != NULL){
        if(updown == 1){
            treeprint(x->left, updown);
        }
        else{
            treeprint(x->right, updown);
        }
        printf("%s %s %s %s %s %d %s %s %s %d�N%d��%d�� %s %s\n",
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

    printf("\n���ёւ��̊�ɂ�����e�̔ԍ�����͂��Ă�������\n");
    while(1){
        printf("��  �@�@�@�@�@�F1\n");
        printf("��            �F2\n");
        printf("�Ăі�        �F3\n");
        printf("�X�֔ԍ��@�@�@�F4\n");
        printf("�s���{���@�@�@�F5\n");
        printf("�d�b�ԍ��@�@�@�F6\n");
        printf("���[���A�h���X�F7\n");
        printf("���N�����@�@�@�F8\n");
        printf("�E�Ɓ@�@�@�@�@�F9\n");
        printf("����          �F10\n");
        if(scanf(" %d", &mode) != 1){
            printf("���͂��s�K�؂ł��B\n");
            scanf("%*s");
        }
        else if(mode > 10 || mode < 1){
            printf("���͂��s�K�؂ł��B\n");
        }
        else break;
    }

    printf("�������~�����I��ł�������  ");
    while(1){
        if     (mode == 1 || mode == 2) printf("(50����)\n");
        else if(mode == 3) printf("(50�����Ŋ����̓����_��)\n");
        else if(mode == 4) printf("(0 < 9)\n");
        else if(mode == 5) printf("(�k�C�� < ����@< ���̑�)\n");
        else if(mode == 6) printf("(0 < 9)\n");
        else if(mode == 7) printf("(0 < 9 < A < z)\n");
        else if(mode == 8) printf("(0 < 9)\n");
        else if(mode == 9) printf("(50�����Ŋ����̓����_��)\n");
        else if(mode == 10) printf("(�j�� < ���� < ���̑��̐���)\n");
        printf("�P�F�����@�Q�F�~��\n");
        if(scanf(" %d", &updown) != 1){
            printf("���͂��s�K�؂ł��B\n");
            scanf("%*s");
        }
        else if(updown != 1 && updown != 2){
            printf("���͂��s�K�؂ł��B\n");
        }
        else break;
    }

    for(i = 0; i < bucket_size; i++){ //�n�b�V���]�`�F�C��-�e�[�u�������񂵂ăf�[�^��T��
        if(DATA[i] != NULL){
            chain = DATA[i];
            while(chain != NULL){ 
                if(root == 1 || chain->passval == 0){
                    DATA_tree = insert_DATA_tree(DATA_tree,chain,mode); //�񕪒T���؂ɑ}��
                    chain = chain->next;
                }
                else{
                    nocount++;
                    chain = chain->next;
                }
            }
        }
    }

    treeprint(DATA_tree, updown); //�o��
    if(nocount != 0){
        printf("\n�Ǘ��Ҍ������Ȃ����߁A%d�l�̃f�[�^�̓p�X���[�h�ɂ��\\���ł��܂���ł����B\n",nocount);
    }
    printf("�I�����܂��B\n");
}

int main() {
    int i;
    int root, rootval;
    log_system(0, 0);//�J�n�����ƃt�@�C���̏�Ԋm�F
    node *DATA[bucket_size];
    init_DATA(DATA); //DATA��NULL����
    insert_DATA(DATA,&rootval);//�t�@�C������DATA�ɑ��
    root_system(&root, &rootval);//�Ǘ��Ҍ���

    while(1){
        printf("���[�h��I�����Ă�������\n");
        while(1){
            printf("0�F�I���@�P�F�o�^�@�Q�F�ύX�@�R�F�폜�@�S�F�����@�T�F�S�\\��\n");
            if(scanf(" %d", &i) != 1){
                printf("���͂��s�K�؂ł��B\n");
                scanf("%*s");
            }
            else if(i < 0 || i > 5){
                printf("���͂��s�K�؂ł��B\n");
            }
            else break;
        }
        
        if     (i==0) {break;}
        else if(i==1) resister_DATA(DATA);
        else if(i==2) change_DATA(DATA,root);
        else if(i==3) delete_DATA(DATA,root);
        else if(i==4) search_DATA(DATA,root);
        else if(i==5) show_DATA(DATA, root);
    }
    printf("�I�����܂��B\n");
    push_file(DATA,rootval);//�t�@�C���ɏ����o��
    log_system(1,root);//�I�������ƌ����̏����o��
    return 0;
}