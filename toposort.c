#include <stdio.h>
#include <stdlib.h>
#define LIMIT 21
#define NUL -1
#define RECORDLIMIT (LIMIT-1)*(LIMIT-2)/2+1

typedef int outputarray[LIMIT];
typedef int countcollection[LIMIT];
typedef int listpointer;
typedef listpointer succ_collection[LIMIT];
typedef struct{
	int succobj;
	listpointer link;
}listrecords,recordsarray[RECORDLIMIT];

typedef struct{
	outputarray rank;
	int next;
}rankingrecord;
rankingrecord ranking;
recordsarray lists;

void predinitialization(int n, countcollection count){
	int i;
	for (i=1;i<=n;i++) count[i]=0;
}

void increase(int j, countcollection count){
	count[j] += 1;
}

void decrease(int j,countcollection count){
	count[j] -= 1;
}

int iszero(int i, countcollection count){
	return (count[i]==0);
}


void setinfo(listpointer pointer, int value){
	lists[pointer].succobj = value;
}

void setlink(listpointer pointer1, listpointer pointer2){
	lists[pointer1].link = pointer2;
}
listpointer avail(){
	static listpointer t=0;
	t++;
	return t;
}

void insert(int i, int j, succ_collection succ){
	listpointer pointer;
	pointer = avail();
	setinfo(pointer,j);
	setlink(pointer,succ[i]);
	succ[i] = pointer;
}
void succinitialization(int n,succ_collection succ){
	int i;
	for (i=1;i<=n;i++) succ[i] = NUL;
}

listpointer access_succ(int i,succ_collection succ){
	return (succ[i]);
}

void copy(int n, outputarray topologicalsort, rankingrecord ranking){
	int i;
	for(i=1;i<=n;i++){
		topologicalsort[i] = ranking.rank[i];
	}
}
typedef int bagcollection;

void baginitialization(bagcollection* pbag, int n, countcollection count){
	int i;
	ranking.next = 1;
	*pbag = 1;
	for (i=1;i<=n;i++){
		if (iszero(i,count)){
			ranking.rank[*pbag] = i;
			*pbag += 1;
		}
	}
}
int emptybag(bagcollection bag){
	return (bag==ranking.next);
}

void remove_from_bag(bagcollection* pbag, int* pobj){
	*pobj = ranking.rank[ranking.next];
	ranking.next += 1;
}

void process(listpointer listname, listpointer recordpointer, bagcollection * pbag, countcollection count){
	int currentsucc;
	currentsucc = lists[recordpointer].succobj;
	decrease(currentsucc,count);
	if (iszero(currentsucc,count)){
		ranking.rank[*pbag] = currentsucc;
		*pbag += 1;
	}
}

listpointer next(listpointer recordpointer){
	return (lists[recordpointer].link);
}
int nextpair(int* pi, int* pj){
	printf("\n enter a pair \n");
	scanf("%d %d",pi,pj);
	return (!((*pi==0)&&(*pj==0)));
}

int anotherrecord(listpointer recordpointer){
	return (recordpointer!=NUL);
}
void update(succ_collection succ,int obj, bagcollection *pbag, countcollection count){
	listpointer listname,recordpointer;
	listname = access_succ(obj,succ);
	recordpointer = listname;
	while(anotherrecord(recordpointer)){
		process(listname,recordpointer,pbag,count);
		recordpointer = next(recordpointer);
	}
}
void toposort(int* pn, outputarray topologicalsort){
	countcollection count;
	succ_collection succ;
	bagcollection bag;
	int i,j,obj;
	printf("\n enter n between 1 and %d \n",LIMIT-1);
	scanf("%d",pn);
	
	predinitialization(*pn,count);
	succinitialization(*pn,succ);
	
	while(nextpair(&i,&j)){
		increase(j,count);
		insert(i,j,succ);
	}
	baginitialization(&bag,*pn,count);
	while(!emptybag(bag)){
		remove_from_bag(&bag,&obj);
		update(succ,obj,&bag,count);
	}
	copy(*pn,topologicalsort,ranking);
}
int main(){
	int n,i;
	outputarray topologicalsort;
	toposort(&n,topologicalsort);
	printf("\n A topological SORT IS:\n");
	for (i=1;i<n;i++){
		printf("%d -> ",topologicalsort[i]);
	}
	printf("%d\n",topologicalsort[i]);
	return 0;
}