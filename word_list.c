#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"

struct node {
	int kaisu;
	char *word;
	struct node *next;
};

struct node * makeNode(char *str){
    struct node * n;

    n = (struct node *)malloc(sizeof(struct node));
    n->word = (char *)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(n->word,str);
    n->kaisu = 1;
    n -> next = NULL;

    return n;
}

struct node *insert(struct node *x, char* str){
    int judge;
    struct node *add, *root = x, *back = x;
    while(1){
		if(x == NULL){//1回目、もしくは最後尾に挿入
        	free(x);
			if(back == NULL) root = makeNode(str);
        	else back->next = makeNode(str);
			break;
		}
        judge = Mystrcmp(x->word, str);
        if(judge == 0){//同じ単語
            x->kaisu++;
            break;
        }
	    else if(judge > 0){//降順
            add = makeNode(str);
            if(x == root){//先頭に挿入
                add->next = root;
                root = add;
            }
            else{//間に挿入
                back -> next = add;
                add  -> next = x;
            }
            break;
	    }
        else{
            back = x;
            x = x->next;
        }
    }
	return root;
}

void listprint(struct node *x, int long_len, int num_all){
	int i;
	if (x != NULL){
		printf("%s ",x->word);
		for(i = 0; i < long_len - strlen(x->word); i++) printf(" "); //最低限の空白
		printf("%4d回/%4d",x->kaisu,num_all); //出現回数表示
    	printf("%7.2f%%\n",(float)(x->kaisu)/num_all*100); //出現確立表示
		listprint(x->next, long_len, num_all);
	}
}

int main(int argc, char *argv[]){
	struct node *root;
	char str[256];
	int long_len = 0;
	int num_all = 0;
	root = NULL;
	
	while(1){
		strcpy(str,GetWord(str));
		if(str[0] == '\n') continue;
    	if(strcmp(str,"***END***") == 0) break;
		root = insert(root,str);
		if(long_len < strlen(str)) long_len = strlen(str); //最高文字数の更新
		num_all++; //確率用個数記憶
	}

	listprint(root, long_len, num_all);
	return 0;
}