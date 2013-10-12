/*  stack();
 *  push(void* q)
 *  pop()
 *  get(int=1)
 *  len()   */

#ifndef __STACK_H__
#define __STACK_H__


#include <iostream>

class stack{
protected:
	stack *next;
	void*p;
public:
	stack(){
		next=NULL;
		p=NULL;
	}
	void* push(void* q){
		stack* tmp=new stack();
		tmp->next=next;
		tmp->p=q;
		next=tmp;
	}
	void* get(int index=1){  // start from position "1"
		void* q=NULL;
		if(index < 1 || index > len()) return q;

		stack *i=this;
		while((i=i->next) && (--index>0)){
		}
		q=i->p;
		return q;
	}
	void* pop(){
		void* q=NULL;
		if(next){
			q=next->p;
			stack* tmp=next;
			next=next->next;
			delete tmp;
		}
		return q;
	}
	int len(){
		int count=0;
		stack* q=this;
		while(q=q->next){ count++; }
		return count;
	}
};

#endif
