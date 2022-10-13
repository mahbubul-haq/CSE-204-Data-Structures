#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }


    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",length);
    }

    //------------write code for the functions below-----------

    int insertLast(int item)
    {
        //write your codes here

        if(list==NULL){
            list=new ListNode();
            list->item=item;
            list->next=NULL;
            length++;
            return SUCCESS_VALUE;
        }

        ListNode *temp;
        temp=list;

        while(temp->next!=NULL){
            temp=temp->next;
        }
        ListNode *temp1=new ListNode();
        temp1->item=item;
        temp1->next=NULL;

        temp->next=temp1;
        length++;

        return SUCCESS_VALUE;

    }

    int insertAfter(int oldItem, int newItem)
    {
        //write your codes here

        ListNode *temp;
        temp=list;

        while(temp!=NULL&&temp->item!=oldItem){
            temp=temp->next;
        }
        if(temp!=NULL&&temp->item==oldItem){

            ListNode *item1=new ListNode();
            item1->item=newItem;
            item1->next=temp->next;
            temp->next=item1;
            length++;
        }
        return SUCCESS_VALUE;

    }

    ListNode * getItemAt(int pos)
    {
        //write your codes here

        if(pos>length||pos<1) return NULL;
        else {

            ListNode * temp;
            temp=list;

            int i=2;

            while(i<=pos){
                temp=temp->next;
                i++;
            }

            return temp;

        }


    }

    int deleteFirst()
    {
        //write your codes here

        if(length==0) return NULL_VALUE;
        else {
            ListNode *temp=list;
            list=list->next;
            delete temp;
            length--;
            return SUCCESS_VALUE;

        }

    }


    ~LinkedList()
    {
        //write your codes here

        while(length!=0){

            ListNode * temp;
            temp=list;

            while(temp->next!=NULL){
                temp=temp->next;
            }
            delete temp;
            length--;

        }
        delete list;
        list=NULL;

    }

};

int main(void)
{
    LinkedList ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. My added features. 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==5)
        {
            ll.printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==4){
            printf("1. InsertLast. 2. InsertAfter. 0. Break.\n");
            printf("3. getItemAt. 4. deleteFirst. 5. Destructor.\n");
            int x;
            cin>>x;

            if(x==1){
                printf("Enter number: ");
                int item;
                cin>>item;
                ll.insertLast(item);
            }
            else if(x==2){

                printf("Enter oldItem and newItem: ");
                int oi,ni;
                cin>>oi>>ni;

                ll.insertAfter(oi,ni);

            }

            else if(x==3){
                printf("Enter Position: ");
                int pos;
                cin>>pos;
                ListNode *temp=ll.getItemAt(pos);
                if(temp==NULL) printf("Invalid Position\n");
                else cout<<"Item is: "<<temp->item<<endl;
            }

            else if(x==4){
                ll.deleteFirst();
            }

            else if(x==5){
                ll.~LinkedList();
            }

            else if(x==0){
            }

        }
    }

}
