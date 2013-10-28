#include <stdio.h>
#include "encode.h"
#include "decode.h"
			


int main(int argc,char*argv[]){
	int enc_dec=0;   // 0: enc   1: dec
	char* input="hello";  // default input file name
	char* dec=0;            
	char* output=0;
	char* helpMessage="usage:\n %s -enc -tf input.enc input -o output\n %s -dec -tf input.enc input.hf -o output\n";
	int i;
	if(argc>1){
		input=argv[1];
		for(i=1;i<argc;i++){
			if(argv[i][0] == '-'){
				if(strcmp(argv[i],"-o")==0){
					i++;
					output=argv[i];
				}
				else if(strcmp(argv[i],"-tf")==0){
					i++;
					dec = argv[i];
				}
				else if(strcmp(argv[i],"-enc")==0){
					enc_dec=0;
				}
				else if(strcmp(argv[i],"-dec")==0){
					enc_dec=1;
				}
				else if(strcmp(argv[i],"-h")==0){
					printf(helpMessage,argv[0],argv[0]);
					return 0;
				}
			}
			else{
				input = argv[i];
			}
		}
	}
	else{
		printf(helpMessage,argv[0],argv[0]);
		return 0;
	}
	int len=strlen(input);
	if(dec==0){
		/* 编码所生成的中间文件，解码所依赖的文件  */
	       	dec=(char*)malloc(sizeof(char)*(len+5));
		strcpy(dec,input);
		if(strcmp(dec+len-3,".hf")==0){
			strcpy(dec+len-3,".enc");
		}
		else{
			strcpy(dec+len,".enc");
		}
	}
	if(output==0){
	       	output=(char*)malloc(sizeof(char)*(len+5));
		strcpy(output,input);
		/* 解码，输出文件  */
		if(enc_dec){
			strcpy(output+len,".out");
		}
		/*   编码，输出文件            */
		else{
			strcpy(output+len,".hf");
		}
	}
	if(enc_dec){
		decode_tree(dec);
		decode(input,output);
	}
	else{
		encode_tree(input,dec);
		encode(input,output);
	}
	return 0;
}
