#include <iostream>
using namespace std;
void swap(int &a,int &b){
	int tmp=a;
	a=b;
	b=tmp;
}
int sort(int a[],int size){
	int *p=&a[0];
	int *q=&a[size-1];
	int flag=1;
		while(p!=q){
			if(*p>*q){
				swap(*p,*q);
				flag=((~flag) & 1);
			}
			if(flag) q--;
			else p++;
		}
	if(p-a>=2)
		sort(a,p-a);
	if(size+a-p>=2)
		sort(p+1,size-(p-a)-1);
	return 0;
}	

int main(){
	int a[]={ 4,2,7,3,5,1,10,9,8,0,15,5 };
	sort(a,12);
	for(int i=0;i<12;i++) cout<<a[i]<< "  ";
	cout<<endl;
	return 0;
}
