
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
    ListNode * prev;
};


class LinkedListDoubly
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListDoubly()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertFirst(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;

        if(list==0) //inserting the first item
        {
            newNode->next = 0;
            newNode->prev = 0;
            list = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = list;
            list->prev = newNode;
            newNode->prev = 0;
            list = newNode;
        }
        length++;
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

    void printListForward()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf(" Length: %d\n",length);
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here

        if(tail!=NULL){
            ListNode *temp=new ListNode();
            temp->item=item;
            temp->next=NULL;
            temp->prev=tail;
            tail->next=temp;
            tail=temp;
        }
        else{
            tail=new ListNode();
            tail->next=NULL;
            tail->prev=NULL;
            list=tail;
        }
        length++;
    }

    int deleteLast()
    {

        if(tail!=NULL){
            ListNode *temp=tail;
            int val=tail->item;

            delete temp;

            if(length>1) {
                tail = tail->prev;
                tail->next=NULL;
            }
            else {
                list=NULL;
                tail=NULL;
            }

            length--;
            return val;
        }

        return NULL_VALUE;
    }

    void printListBackward()
    {
        //will print the list backward starting from the tail position

        ListNode * temp=tail;

        while(temp!=NULL){
            cout<<temp->item<<" ";
            temp=temp->prev;
        }
        cout<<"Length: "<<length<<endl;
    }

};

int main(void)
{
    LinkedListDoubly ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. InsertLast. 7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertFirst(item);
        }
        else if(ch==2)
        {
            int item = ll.deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            ll.printListForward();
        }
        else if(ch==5)
        {
            ll.printListBackward();
        }
        else if(ch==6){
            cout<<"Enter the value: ";
            int item;
            cin>>item;
            ll.insertLast(item);
        }

        else if(ch==7)
        {
            break;
        }
    }

}
