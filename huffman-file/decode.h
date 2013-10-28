#include "huffuman.h"
#include <stdio.h>

typedef struct huffmantr{    // build a tree through encode-file
	unsigned char c;
	struct huffmantr *left,*right;
}huffmantr;

huffmantr root;

void decode_tree(char* input){
	root.c=0;
	root.left=root.right=0;
	
	char**s=(char**)malloc(sizeof(char*)*256);
	int i=0;
	FILE* fp=fopen(input,"rb");
	for(i=0;i<256;i++){
		s[i]=(char*)malloc(sizeof(char)*100);
		fread(s[i],1,100,fp);
	}
	fclose(fp);
	for(i=0;i<256;i++){
		huffmantr *pt=&root;
		char* p=s[i];
		while(*p){
			if(*p=='0'){
				if(pt->left==0){
					pt->left=(huffmantr*)malloc(sizeof(huffmantr));
					pt = pt->left;
					pt->left=pt->right=0;
				}
				else{
					pt = pt->left;
				}
			}
			else if(*p=='1'){
				if(pt->right==0){
					pt->right=(huffmantr*)malloc(sizeof(huffmantr));
					pt = pt->right;
					pt->left=pt->right=0;
				}
				else{
					pt = pt->right;
				}
			}
			p++;
		}
		pt->c=i;
	}
}	
	
void decode(char* input,char* output){
	FILE* fp=fopen(input,"rb");
	FILE* fq=fopen(output,"wb");
	int i,j,size;
	huffmantr* p=&root;
	unsigned char s[10];
	unsigned char c;
	while((size=fread(s,1,10,fp))>0){
		for(i=0;i<size;i++){
			for(j=0;j<8;j++){
				if((s[i]>>(7-j))&1){
					p=p->right;
				}
				else{
					p=p->left;
				}
				if(!(p->left)){
					c=p->c;
					p=&root;
					fwrite(&c,1,1,fq);
				}
			}
		}
	}
	fclose(fp);
	fclose(fq);
}
			


