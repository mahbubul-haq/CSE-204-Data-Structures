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

        while(length>=2&&temp->next->next!=NULL) {
            temp=temp->next;
        }

        if(length==1){
            delete tail;
            delete list;
            list=NULL;
            tail=NULL;
            length--;
        }

        else {

            delete temp->next;
            temp->next = NULL;

            tail = temp;
            length--;
        }
    }
};

int main(void)
{
    LinkedListWithTail ll;

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

            printf("7. insertLast. 8. getItemAt. 9. deleteLast\n");
            printf("0. Break");

            int choice;
            cin>>choice;

            if(choice==7){
                printf("Enter value: ");
                int item;
                cin>>item;
                ll.insertLast(item);
            }
            else if(choice==8){
                int pos;
                printf("Enter position: ");
                cin>>pos;

                ListNode *temp=ll.getItemAt(pos);

                if(temp==NULL)cout<<"Invalid Position"<<endl;
                else cout<<"Value: "<<temp->item<<endl;

            }
            else if(choice==9){
                ll.deleteLast();
            }
            else if(choice==0){

            }


        }
    }

}
