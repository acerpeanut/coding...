#include <unistd.h>
#include "stack_template.h"
#include "tab.h"
#include "position.h"
#include <iostream>

using namespace std;
position nine(int a,int b){
	int x=a/3*3+b/3;
	int y=(a%3)*3+b%3;
	return position(x,y);
}
void display(tab a[9][9]){
	cout<<"/////////"<<endl;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<a[i][j].get()<<'\t';
		}
		cout<<endl;
	}
}

int unnine(int x,int y){
	return x/3*3+y/3;
}
int complete(tab a[9][9]){ // error: -1; complete: 1; uncomplete: 0;
	int ret=1;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j].status==1){
				ret!=-1?(ret=0):0;
			}
			if(a[i][j].blank==0){
				ret=-1;
			}
		}
	}
	return ret;
}

int main(){
	int init[9][9]={ 
		0,0,0,4,0,6,0,3,0,
		0,0,0,0,0,0,8,2,9,
		5,8,3,0,0,1,4,0,0,
		0,7,8,0,1,0,0,5,0,
		0,0,4,0,0,0,7,0,0,
		0,1,0,0,4,0,2,8,0,
		0,0,2,5,0,0,3,1,6,
		8,5,1,0,0,0,0,0,0,
		0,6,0,1,0,2,0,0,0
	};

//	stack_position yes;

//	stack_position no_line[9];
//	stack_position no_row[9];
//	stack_position no_nine[9];

	stack_position prepare;
	tab a[9][9];
	cout<<"0"<<endl;
	int i,j,k;	

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			int tmp;
			tmp=init[i][j];
//			cout<<i<<","<<j<<"\t";
			position tmp2(i,j);
			if(tmp!=0){
				a[i][j].set(tmp);
				a[i][j].status=1;
				prepare.push(tmp2);
			}
			else{ 
//				no_line[i].push(tmp2);
//				no_row[j].push(tmp2);
//				no_nine[i/3*3+j/3].push(tmp2);
			}
		}
	}

	do{
		while(prepare.len()){
			position tmp=prepare.pop();
			int x=tmp.x, y=tmp.y;

			for(j=0;j<9;j++){
				if(a[x][j].status==0){
					a[x][j].remove(a[x][y].get());
					//  cout<<x<<","<<j<<"\t"<<a[x][j].blank<<endl;
					if(a[x][j].get()){ 
						prepare.push(position(x,j));
						a[x][j].status=1;
					}
				}
				if(a[j][y].status==0){
					a[j][y].remove(a[x][y].get());
					//  cout<<j<<","<<y<<"\t"<<a[j][y].blank<<endl;
					if(a[j][y].get()){
						prepare.push(position(j,y));
						a[j][y].status=1;
					}
				}
				int t0=unnine(x,y);
				position t1(nine(t0,j));
				if(a[t1.x][t1.y].status==0){
					a[t1.x][t1.y].remove(a[x][y].get());
					//  cout<<t1.x<<","<<t1.y<<"\t"<<a[t1.x][t1.y].blank<<endl;
					if(a[t1.x][t1.y].get()){
						prepare.push(t1);
						a[t1.x][t1.y].status=1;
					}
				}
				
			}
			a[tmp.x][tmp.y].status=2;
		}
		if(complete(a)==-1){
			cout<<"error!"<<endl;
			return(-1);
		}
		else break;
	}while(true);
	
	for(i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j].get()) cout<<a[i][j].get()<<"\t";
			else cout<<a[i][j].blank<<"\t";
		}
		cout<<endl;
	}
	return 0;
}
