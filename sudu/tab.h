/* tab()
 * power(int,int)
 * match(int)
 * remove(int)
 * add(int)
 * int get() 
 * set(int)   */
#ifndef __TAB_H__
#define __TAB_H__


#include "stack.h"
#include <iostream>
using namespace std;

class tab{
public:
	int blank;
	bool change;
	int status;

	tab(){ 
		status=0;
		blank=0; 
		for(int i=0;i<9;i++){
			blank = blank | power(2,i+1) ;
		}
		change=false;
	}
	static int power(int a,int b){  // the b th power of a 
		int c=1;
		while(b-->0){
			c *= a;
		}
		return c;
	}
	bool match(int b){
		return blank & power(2,b);
	}
	bool remove(int b){
		change=false;
		int c = ~power(2,b);
		c= c& blank;
		if(c!=blank){
			blank=c;
			change=true;
		}
		return change;
	}
	bool add(int b){
		change=false;
		int c= power(2,b);
		c= c| blank;
		if(c!=blank){
			blank=c;
			change=true;
		}
		return change;
	}
	int get(){ 
		for(int i=0;i<9;i++){
			if(power(2,i+1)== blank) return i+1;
		}
		return 0;
	}
	bool set(int b){
		change = false;
		int c=power(2,b);
		if(c!=blank){
			blank=c;
			change=true;
		}
		return change;
	}
};

#endif
