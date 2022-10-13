


#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        if(list==NULL){
            list=new ListNode();
            list->item=item;
            list->next=NULL;
            tail=list;
            length++;
        }

        else {
            ListNode *newNode;
            newNode = new ListNode();
            newNode->item = item;
            newNode->next = list; //point to previous first node
            list = newNode; //set list to point to newnode as this is now the first node
            length++;
            return SUCCESS_VALUE;
        }
    }

    //add required codes to set up tail pointer
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
            delete temp ;
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

    //add required codes to set up tail pointer
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
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        ///write your codes here
        if(tail==NULL||list==NULL){
            list=new ListNode();
            list->item=item;
            list->next=NULL;
            tail=list;
            length++;
        }

        else if(tail!=NULL){
            ListNode *newNode=new ListNode();
            newNode->item=item;
            newNode->next=NULL;
            tail->next=newNode;
            tail=newNode;
            length++;
        }

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

    int deleteLast()
    {
        //write your codes here

        if(tail==NULL||list==NULL){
            return NULL_VALUE;
        }

        ListNode *temp=list;
        int val=tail->item;

        while(length>=2&&temp->next->next!=NULL) {
            temp=temp->next;
        }

        if(length==1){
            delete tail;
            delete list;
            list=NULL;
            tail=NULL;
            length--;
            return val;
        }

        else {

            delete temp->next;
            temp->next = NULL;

            tail = temp;
            length--;
            return val;
        }
    }
};


class Queue
{
    LinkedListWithTail ll;
public:
    Queue()
    {

    }

    void enqueue(int item)
    {
        //write your codes here

        ll.insertItem(item);

    }

    int dequeue()
    {
        //write your codes here

        int val=ll.deleteLast();
        return val;

    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

}