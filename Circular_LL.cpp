#include<iostream>
#include<map>
using namespace std;
class node
{

public:
int data;
node *next;
    node(int data)
    {
        this->data=data;
        this->next=NULL;

    }
    ~node()
    {
        if (this->next!=NULL)
        {
            delete next;
            next=NULL;
        }
        
    }
};
void insertion(node* &tail,int ele,int d)
{
    if (tail==NULL)
    {
        node *temp=new node(d);
        tail=temp;
        temp->next=temp;
    }
    else
    {
        node *curr=tail;
        while (curr->data!=ele)
        {
             curr=curr->next;
        }
        node *temp=new node(d);
        temp->next=curr->next;
        curr->next=temp;
    }
   
}

void del(node* &tail,int ele)
{
    if(tail==NULL)
    {
        cout<<"Empty LL";
        return;
    }
    else
    {
    
        node *pev=tail;
        node *curr=pev->next;
        while (curr->data!=ele)
        {
            pev=curr;
            curr=curr->next;
        }
        pev->next=curr->next;

        if (curr==pev)
        {
            tail=NULL;
        }

       else if (tail==curr)
        {
            tail=pev;
        }

        curr->next=NULL;
        delete curr;
        
        
    }
    
} 
void print(node* &tail)
{
    node *temp=tail;
    do
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    } while (temp!=tail);
}
int main()
{
   node *tail=NULL;
   insertion(tail,5,3);
   insertion(tail,3,5);
   insertion(tail,5,7);
   insertion(tail,7,9);
   insertion(tail,9,11);
   del(tail,3);
//    del(tail,5);
//    del(tail,11);
   print(tail);

 return 0;   
}
