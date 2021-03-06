#ifndef __STACK_TEMPLATE_H__
#define __STACK_TEMPLATE_H__

#include <iostream>
using namespace std;
#include "stack.h"

template < class T >
class stack_template:public stack{
public:
	T& push(T a){
		T*p=new T(a);
		stack::push(p);
		return *p;
	}
	T pop(){

		T*p = (T*)stack::pop();
		T a(*p);
		delete p;
		return a;
	}
	T& get(int index=1){
		return *((T*)stack::get(index));
	}
	void unshift(T a){
		T*p=new T(a);
		stack::unshift(p);
	}
	bool inside(T a){
		for(int i=0;i<len();i++){
			if(get(i+1).isSame(a)) return true;
		}
		return false;
	}
	void display(){
		for(int i=0;i<len();i++){
			get(i+1).display();  cout<<"\t";
		}
	}
	int len(){
		return stack::len();
	}
};

#endif
