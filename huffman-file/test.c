#include "bigInt.h"
#include "huffuman.h"
#include <stdio.h>
char filename[]="filetest";
char output[]="";
int main(){
	int i;
	FILE* fp=fopen(filename,"wb");
	unsigned char c;
	for(i=0;i<256;i++){
		c=i;
		fwrite(&c,1,1,fp);
	}
	fclose(fp);
	return 0;
}
