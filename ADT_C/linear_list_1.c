#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__


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
	// 删除线性表，清除空间
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
	// 删除线性表，并初始化分配空间
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
	// 判断表是否为空
	if(L.length<=0){
		return true;
	}
	else{
		return false;
	}
}
int ListLength(SqList L){
	// 返回表长度
	return L.length;
}
bool GetElem(SqList L,int i,ElemType& e){
	// 返回表的第i个元素，反馈给e
	if(i>=1 && i<=L.length){
		e = L.elem[i-1];
		return true;
	}
	return false;
}
int LocateElem(SqList L,ElemType e,bool (*compare)(ElemType a,ElemType b)){
	// 返回e元素的位置，不在则返回0
	int i;
	for(i=0;i<L.length;i++){
		if(compare(L.elem[i],e)==true){
			return i+1;
		}
	}
	return 0;
}
bool PriorElem(SqList L,ElemType cur_e,ElemType& pre_e){
	// 返回cur元素的前一位，给pre
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
	// 返回cur元素的下一位，给next
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
	// 在i位置插入元素e
	if(i>=1 && i<= L.length+1){
		int j;
		int newElem=0;
		ElemType* p=L.elem;
		if(L.length+1>L.listSize){
			// 若插入后长度大于所分配空间，增大空间
			newElem=1;
			L.elem = (ElemType*)malloc((L.listSize+LISTINCREMENT)*sizeof(ElemType));
			if(L.elem==NULL){
				L.elem=p;
				return OVERFLOW;
			}
			L.listSize=L.listSize+LISTINCREMENT;
		}
		
		i=i-1;
		for(j=L.length;j>=0;j--){
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
			// 删除以前遗留的空间
			free(p);
		}
		return OK;
	}
	else{
		return ERROR;
	}
}
bool ListDelete(SqList &L,int i,ElemType &e){
	if(i>=1 && i<=L.length){
		// 删除第i个元素
		int j;
		i--;
		e = L.elem[i];
		for(j=i;j<L.length-1;j++){
			L.elem[j] = L.elem[j+1];
		}
		L.length--;
		return true;
	}
	return false;
}
bool ListTraverse(SqList L, bool (*visit)(ElemType)){
	// 遍历表，执行visit，直到返回false
	int i;
	for(i=0;i<L.length;i++){
		if(visit(L.elem[i])==false){
			return false;
		}
	}
	return true;
}
bool compare_default(ElemType a,ElemType b){
	// 默认的比较函数
	if(a==b){
		return true;
	}
	return false;
}
	
#endif
