#include "bigInt.h"
#include "huffuman.h"
#include <stdio.h>

typedef struct swp{
	char *s;
}swp;

swp* Swp;
typedef unsigned int _bits;
unsigned char len;

void encode(char* input,char* output){
	FILE* fp=fopen(input,"rb");
	FILE* fq=fopen(output,"wb");
	int i,size;
	char *p;
	unsigned char s[10];
	unsigned char j=0;
	len=0;
	while((size=fread(s,1,10,fp))>0){
		for(i=0;i<size;i++){
			p=Swp[s[i]].s;
			while(*p){
				if(*p=='0'){
					j=j<<1;
				}
				else if(*p=='1'){
					j=((j<<1) | 1);
				}
				len++;
				p++;
				if(len==8){
					fwrite(&j,1,1,fq);
					j=0;
					len=0;
				}
			}
		}
	}
	if(len !=0){
		j=j<<(8-len);
		fwrite(&j,1,1,fq);
	}
	fclose(fp);
	fclose(fq);
}
			
void get(swp* Swp,node*p,node**q,char*s){
	if(p->left){
		int l=strlen(s);
		s[l]='0';
		s[l+1]='\0';
		char* sp=(char*)malloc(sizeof(char)*100);
		strcpy(sp,s);
		sp[l]='1';
		get(Swp,p->left,q,s);
		get(Swp,p->right,q,sp);
	}
	else{
		int i=0;
		for(;i<256;i++){
			if(p==q[i]){
				Swp[i].s=s;
				print_b(p->sum);
				printf(": %s\n",s);
				break;
			}
		}
	}
}
int encode_tree(char*filename,char*output){
	Swp=(swp*)malloc(sizeof(swp)*256);
	int i,j,count;
	FILE* fp=fopen(filename,"rb");
	FILE* fq=fopen(output,"wb");

	if(fp==0 || fq==0){
		printf("sorry to open \n");
		return -1;
	}
	unsigned char r[10];
	size_t size;
	count=256;
	node **p=(node**)malloc(sizeof(node*)*count);
	node **q=(node**)malloc(sizeof(node*)*count);
	for(i=0;i<count;i++){
		p[i]=(node*)malloc(sizeof(node));
		q[i]=p[i];
		init(p[i]);
	}
	while((size=fread(r,1,10,fp))>0){
		for(i=0;i<size;i++)
			plusplus(&(p[r[i]]->sum));
	}

	huffuman(p,count);
	char* s=(char*)malloc(sizeof(char)*100);
	s[0]=0;
//	display(p[0],s);
	s=(char*)malloc(sizeof(char)*100);
	s[0]=0;
	get(Swp,p[0],q,s);
	for(i=0;i<256;i++){
		fwrite(Swp[i].s,100,1,fq);
	}
	fclose(fq);
	fclose(fp);
	return 0;
}
#define LOOK
int main(int argc,char*argv[]){
#ifdef LOOK
	char *input="test.cpp";
	char *output=0;
	char *output_enc=0;
	if(argc>1){
		if(argc>2){
			output=argv[2];
		}
		input=argv[1];
	}
	int input_len=strlen(input);
	if(!output){
		output=(char*)malloc(input_len+4);
		strcpy(output,input);
		strcpy(output+input_len,".hf");
	}
	output_enc=(char*)malloc(input_len+5);
	strcpy(output_enc,input);
	strcpy(output_enc+input_len,".enc");

	encode_tree(input,output_enc);
	encode(input,output);
#else
	int i;
	char s[100];
	FILE*p=fopen(output_enc,"rb");
	for(i=0;i<256;i++){
		fread(s,100,1,p);
		printf("%s\n",s);
	}
	fclose(p);
#endif
	return 0;
}
