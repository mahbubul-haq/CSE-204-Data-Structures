#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
using namespace std;
#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;

//********************************added by me

int getLength(){
	return length;
}

void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

//************************************added by me

int insertItemAt(int pos, int item){

	int *tempList;
	int val=0;
	int posval=-1;

	if(pos>=length)
		return NULL_VALUE;

	if(length== listMaxSize){
		listMaxSize=2*listMaxSize;
		tempList=(int*) malloc(listMaxSize*sizeof(int));
		int i;


		for(i=0;i<length;i++){
			if(i==pos){
				tempList[i]=item;
				val=list[i];
				posval=0;
			}
			else tempList[i]=list[i];
		}

		free(list);
		list=tempList;
	}
	else{
		tempList=(int*)malloc(listMaxSize*sizeof(int));
		int i;

		for(i=0;i<length;i++){
			if(i==pos){
				tempList[i]=item;
				val=list[i];
				posval=0;
			}
			else tempList[i]=list[i];
		}

		free(list);
		list=tempList;
	}


	if(posval==0){
		list[length]=val;
		length++;
	}
	return SUCCESS_VALUE;


}

int insertItem(int newitem)
{
	if(listMaxSize==0){
		listMaxSize=LIST_INIT_SIZE;
		list=(int*)malloc(listMaxSize*sizeof(int));
	}

	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}

////************************************added by me

void shrink(){

	if(length==0&&listMaxSize>LIST_INIT_SIZE){
		listMaxSize=LIST_INIT_SIZE;
		list=(int*)malloc(sizeof(int)*listMaxSize);
		return;
	}

	if(listMaxSize != LIST_INIT_SIZE){
		if(length*2==listMaxSize){
			int * tempList ;
			//allocate new memory space for tempList
			listMaxSize = length ;
			tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
			int i;
			for( i = 0; i < length ; i++ )
			{
				tempList[i] = list[i] ; //copy all items from list to tempList
			}
			free(list) ; //free the memory allocated before
			list = tempList ; //make list to point to new memory
		}
	}
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;

	shrink();

	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	return SUCCESS_VALUE ;
}

////*********************************added by me

int deleteLast(){
	if(length>=1){
		length--;
		shrink();
		return SUCCESS_VALUE;
	}
	else return NULL_VALUE;

}

////**********************************************added by me

void clear(){
	free(list);
	length=0;
	listMaxSize=0;
}

//****************************added by me

void deleteAll(){
	length=0;
	if(listMaxSize>LIST_INIT_SIZE){
		shrink();
	}

}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}
///************************************function for postfix


int postfix(string s){

    int len=s.length();
    for(int i=0;i<len;i++){

        if((s[i]-48)<10&&(s[i]-48)>-1){
			insertItem((s[i]-48));
		}
		
		else{
			
			if(s[i]=='+'){
				
				if(length<2)
					return INT_MAX;
				
				int a=list[length-1];
				int b=list[length-2];
				deleteLast();
				deleteLast();

				int x=a+b;
				insertItem(x);
			}
			else if(s[i]=='-'){
				
				if(length<2)
					return INT_MAX;
				
				int a=list[length-1];
				int b=list[length-2];
				deleteLast();
				deleteLast();

				int x=b-a;
				insertItem(x);
			}
			
			else if(s[i]=='*'){
				
				if(length<2)
					return INT_MAX;
				
				int a=list[length-1];
				int b=list[length-2];
				deleteLast();
				deleteLast();

				int x=a*b;
				insertItem(x);
			}
			else if(s[i]=='/'){
				
				if(length<2)
					return INT_MAX;
				
				int a=list[length-1];
				int b=list[length-2];
				deleteLast();
				deleteLast();

				int x;
				if(a!=0){
					x=b/a;
					insertItem(x);
				}
				else return INT_MAX;

			}
		}


    }
	
	if(length==1){
		int val=list[length-1];
		length=0;
		return val;
	}
	else {
		length=0;
		return INT_MAX;
	}

}

///*************************************main for postfix

int main(void){

	initializeList();


	string s;
	cin>>s;

	if(postfix(s)==INT_MAX) cout<<"Invalid Input"<<endl;
	else cout<<postfix(s)<<endl;
	
	clear();

	return 0;

}

/*int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. My Added functions . 5. Print. 6. exit.\n\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
		else if(ch==4){
			int choice;

			printf("1. Insert item at. 2. getLength. 0. Break\n");
			printf("3. DeleteLast. 4. clear. 5. deleteAll.\n\n");
			scanf("%d",&choice);



			if(choice==1){
				printf("Enter the value of pos and value: ");
				int pos,val;
				scanf("%d %d",&pos,&val);
				insertItemAt(pos,val);
			}
			else if(choice==2){
				printf("Length: %d\n",getLength());
			}

			else if(choice==3){
				deleteLast();
			}
			else if(choice==4){
				clear();
			}
			else if(choice==5){
				deleteAll();
			}
		}
    }

}*/
