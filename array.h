#include <iostream>
using namespace std;
#define SIZ 50
class node{
public:
	void *p;
	node* before;
	node* next;
	node(){ before=NULL; next=NULL;p=NULL;}
};

class array{
public:
	node* begin;
	node* last;
	int length;

	array(){length=0;begin=NULL;last=NULL;}

	~array(){
		node*p = begin;
		while(length-->0){
			begin=begin->next;
			delete p;
			p = begin;
		}
	}

	void* operator [](int i){
		if(i<length&&i>=0){
			node* p=begin;
			while(i-->0){
				p = p->next;
			}
			return p->p;
		}
		return NULL;
	}

	void unshift(void*p){
		node* q=new node();
		length++;
		q->p=p;
		q->next=begin;
		q->before=NULL;
		if(!last) last=q;
		if(begin) begin->before = q;
		begin=q;
	}
	void push(void*p){
		node*q=new node();
		length++;
		q->p=p;
		q->next=NULL;
		q->before=last;
		if(!begin) begin = q;
		if(last) last->next = q;
		last=q;
	}

	void* shift(){
		if(!begin) return NULL;

		void *p=begin->p;
		node* t=begin;
		begin = begin->next;
		if(begin) begin -> before = NULL;
		delete t;
		length--;
		if(length<=0) last=NULL;
		return p;
	}

	void* pop(){
		if(!last) return NULL;

		void* p=last->p;
		node* t=last;
		last = last->before;
		if(last) last -> next = NULL;
		delete t;
		length--;
		if(length<=0) begin=NULL;
		return p;
	}

};
