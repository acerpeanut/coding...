#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__


#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType ;
typedef struct{
	ElemType* elem;
	int length;
	int listSize;
}SqList;
typedef int Status ;

const int OK=1;
const int OVERFLOW=-1;


Status InitList(SqList &L);
void DestroyList(SqList &L);
Status ClearList(SqList &L);
bool ListEmpty(SqList L);
int ListLength(SqList L);
bool GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e,bool (*compare)(ElemType,ElemType));
bool compare_default(ElemType,ElemType);
bool PriorElem(SqList L,ElemType cur_e,ElemType &pre_e);
bool NextElem(SqList L,int i,ElemType e);
Status ListInsert(SqList &L,int i,ElemType e);
bool ListDelete(SqList &L,int i,ElemType &e);
bool ListTraverse(SqList L,bool (*visit)(ElemType));

Status InitList(SqList &L){
	// 构造空的线性链表
	L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if(L.elem==NULL){   // 分配失败
		return OVERFLOW;
	}
	L.length=0;    // 长度为0
	L.listSize=LIST_INIT_SIZE;   //初始存储容量
	return OK;
}
void DestroyList(SqList &L){
	if(L.listSize>0){
		free(L.elem);
	}
	L.length=0;
	L.listSize=0;
}
Status ClearList(SqList &L){
	if(L.length>0){
		L.length=0;
	}
	if(L.listSize>LIST_INIT_SIZE){
		free(L.elem);
		L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
		if(L.elem==NULL){
			return OVERFLOW;
		}
		L.listSize=LIST_INIT_SIZE;
	}
	return OK;
}
bool ListEmpty(SqList L){
	if(L.length<=0){
		return true;
	}
	else{
		return false;
	}
}
int ListLength(SqList L){
	return L.length;
}
bool GetElem(SqList L,int i,ElemType& e){
	if(i>=1 && i<=L.length){
		e = L.elem[i-1];
		return true;
	}
	return false;
}
int LocateElem(SqList L,ElemType e,bool (*compare)(ElemType a,ElemType b)){
	for(int i=0;i<L.length;i++){
		if(compare(L.elem[i],e)==true){
			return i+1;
		}
	}
	return 0;
}
bool PriorElem(SqList L,ElemType cur_e,ElemType& pre_e){
	int ret = LocateElem(L, cur_e,compare_default);
	if(ret > 1){
		pre_e = L.elem[ret-2];
		return true;
	}
	else{
		return false;
	}
}
bool NextElem(SqList L,ElemType cur_e,ElemType& next_e){
	int ret = LocateElem(L, cur_e,compare_default);
	if(ret > 0 && ret < L.length){
		next_e = L.elem[ret];
		return true;
	}
	else{
		return false;
	}
}
Status ListInsert(SqList& L, int i,ElemType e){
	if(i>=1 && i<= L.length+1){
		int newElem=0;
		ElemType* p=L.elem;
		if(L.length+1>L.listSize){
			newElem=1;
			L.elem = (ElemType*)malloc((L.listSize+LISTINCREMENT)*sizeof(ElemType));
			if(L.elem==NULL){
				L.elem=p;
				return OVERFLOW;
			}
			L.listSize=L.listSize+LISTINCREMENT;
		}
		
		i=i-1;
		for(int j=L.length;j>=0;j--){
			if(j<i){
				L.elem[j]=p[j];
			}
			else if(j==i){
				L.elem[j]=e;
			}
			else{
				L.elem[j]=p[j-1];
			}
		}
		L.length=L.length+1;
		if(newElem==1){
			free(p);
		}
		return OK;
	}
	else{
		return false;
	}
}
bool ListDelete(SqList &L,int i,ElemType &e){
	if(i>=1 && i<=L.length){
		i--;
		e = L.elem[i];
		for(int j=i;j<L.length-2;j++){
			L.elem[j] = L.elem[j+1];
		}
		L.length--;
		return true;
	}
	return false;
}
bool ListTraverse(SqList L, bool (*visit)(ElemType)){
	for(int i=0;i<L.length;i++){
		if(visit(L.elem[i])==false){
			return false;
		}
	}
	return true;
}
bool compare_default(ElemType a,ElemType b){
	if(a==b){
		return true;
	}
	return false;
}
	
#endif
