
#include "stack_template.h"
#include "tab.h"
#include "position.h"
#include <iostream>

using namespace std;


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

	stack_position yes;

	stack_position no_line[9];
	stack_position no_row[9];
	stack_position no_nine[9];

	stack_position prepare;
	tab a[9][9];
	cout<<"0"<<endl;
	int i,j,k;	
	int test=0;

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			int tmp;
			tmp=init[i][j];
			cout<<i<<","<<j<<"\t";
			position tmp2(i,j);
			if(tmp!=0){
				a[i][j].set(tmp);
				prepare.push(tmp2);
				test++;
			}
			else{ 
				no_line[i].push(tmp2);
				no_row[j].push(tmp2);
				no_nine[i/3*3+j/3].push(tmp2);
			}
		}
	}
	cout<<test<<endl;
	int x=prepare.len();
	cout<<x<<endl;

	while(prepare.len()){
		position tmp=prepare.pop();
		int length=no_line[tmp.x].len();
		for(j=0;j<length;j++){
			position tmp2(no_line[tmp.x].pop());
			if(prepare.inside(tmp2)) continue;

			a[tmp2.x][tmp2.y].remove(a[tmp.x][tmp.y].get());
			if(a[tmp2.x][tmp2.y].get()){
				prepare.unshift(tmp2);
			}
			else{	no_line[tmp.x].unshift(tmp2); }
		}
		for(j=no_row[tmp.y].len();j>0;j--){
			position tmp2(no_row[tmp.y].pop());
			if(prepare.inside(tmp2)) continue;

			a[tmp2.x][tmp2.y].remove(a[tmp.x][tmp.y].get());
			if(a[tmp2.x][tmp2.y].get()){
				prepare.unshift(tmp2);
			}
			else{	no_row[tmp.y].unshift(tmp2); }
		}
		for(j=no_nine[(tmp.x)/3*3+(tmp.y)/3].len();j>0;j--){
			position tmp2(no_nine[(tmp.x)/3*3+(tmp.y)/3].pop());
			if(prepare.inside(tmp2)) continue;
			
			a[tmp2.x][tmp2.y].remove(a[tmp.x][tmp.y].get());
			if(a[tmp2.x][tmp2.y].get()){
				prepare.push(tmp2);
			}
			else{	no_nine[tmp.x/3*3+tmp.y/3].unshift(tmp2); }
		}
		yes.push(tmp);
	}

	for(i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(a[i][j].get()) cout<<a[i][j].get()<<"\t";
			else cout<<a[i][j].blank<<"\t";
		}
		cout<<endl;
	}
	return 0;
}
