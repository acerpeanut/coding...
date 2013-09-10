#include "array.h"

int main(){
	array a;
	int b[10]={1,2,3,4,5,6,7,8,9,0};
	int i;
	for(i=0;i<10;i++) a.unshift(b+i);
	for(i=0;i<10;i++) cout<<*(int*)a[i]<<endl;
	for(i=0;i<10;i++) a.push(b+i);
	// for(i=0;i<24;i++) cout<<*(int*)(a.pop())<<endl;
	int *p=NULL;
	cout<<*p<<endl;
	return 0;
}
