/* 
chars()
chars(char*)
chars(int)
insert(char*,int index)
clear()
unsignedtochar(int)
*/

#ifndef __CHARS_H_
#define __CHARS_H_



#include <iostream>
#include <cstring>
using namespace std;

class chars{
public:
	char* c;
	int length;

	chars(int a){
		char*p = unsignedtochar(a);
		length = strlen(p);
		c = new char[length+1];
		strcpy(c,p);
	}
	chars(){ c=NULL; length=0; }
	chars(char *p){
		if(p){
			length = strlen(p);
			c=new char[length+1];
			strcpy(c,p);
		}
		else{ c=NULL; length=0; }
	}
	char(){	return c;	}
	void insert(char *p,int index){   // insert from "0" position
		if(p){
			char* t=c;
			if(length>=index){
				length = strlen(p)+length;
				c = new char [1+length];
				int i=0;
				for(i=0;i<index;i++){
					c[i] = t[i];
				}
				while(*p){
					c[i++] = *p;
					p++;
				}
				if(index<0) index=0;
				for(;i<length;){
					c[i++] = t[index++];
				}
				c[i] = '\0';
				delete [] t;
			}
			else{}
		}
	}
	void append(char*p){
		insert(p,length);
	}
	void clear(){
		if(length){
			length=0;
			delete [] c;
		}
	}
protected:
public:

	static char* unsignedtochar(long a){
		static char ac[100];
		ac[100-1]='\0';
		int i=2;
		while(ac[100-i++]=a%10+'0'){ 
			if(!(a=a/10)){ i--; break; }
		}
		return ac+100-i;
	}
	static char* unsignedtochar(int a){
		static char ac[100];
		ac[100-1]='\0';
		int i=2;
		while(ac[100-i++]=a%10+'0'){ 
			if(!(a=a/10)){ i--; break; }
		}
		return ac+100-i;
	}
};


#endif
