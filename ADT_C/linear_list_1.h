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
const int ERROR=0;
const int OK=1;
const int OVERFLOW=-1;

Status InitList(SqList& L);
void DestroyList(SqList& L);
Status ClearList(SqList& L);
bool ListEmpty(SqList L);
int ListLength(SqList L);
bool GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e,bool (*compare)(ElemType,ElemType));
bool compare_default(ElemType,ElemType);
bool PriorElem(SqList L,ElemType cur_e,ElemType& pre_e);
bool NextElem(SqList L,int i,ElemType& e);
Status ListInsert(SqList& L,int i,ElemType e);
bool ListDelete(SqList& L,int i,ElemType& e);
bool ListTraverse(SqList L,bool (*visit)(ElemType));
