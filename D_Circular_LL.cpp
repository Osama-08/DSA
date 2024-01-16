#include<iostream>
#include<map>
using namespace std;
class node
{
public:
   int data;
   node *next;
   node *prev;
    node(int data)
    {
        this->data=data;
       this->prev=NULL;
       this->next=NULL;
    }
    ~node()
    {
        if(this->next!=NULL)
        {
            delete next;
            next=NULL;
        }
    }

};
void insertion(node* &tail, int d, int ele)
{
    if (tail == NULL)
    {
        node *newnode = new node(d);
        newnode->prev = newnode;
        newnode->next = newnode;
        tail = newnode;
    }
    else
    {
        node *curr = tail;
        while (curr->data != ele)
        {
            curr = curr->next;
        }

        node *temp = new node(d);
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        temp->prev = curr;
    }
}

void display(node* &tail)
{
    node *temp=tail;
    do
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    } while (temp!=tail);
    cout<<endl;
}
void deletion(node* &tail,int d)
{
       if (tail==NULL)
       {
        cout<<"Empty List";
        return;
       }
       else
       {
        node *pev=tail;
        node *curr=pev->next;
        while (curr->data!=d)
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
            tail=curr->next;
        }
        curr->next->prev=pev;
        curr->next=NULL;
        curr->prev=NULL;
        delete curr;

       }
       
       
}
int main()
{
    node *tail=NULL;
    insertion(tail,1,0);
    insertion(tail,2,1);
    insertion(tail,3,2);
    insertion(tail,4,3);
    insertion(tail,5,4);
    insertion(tail,6,5);
    // deletion(tail,4);
    deletion(tail,6 );
    deletion(tail,1);
    display(tail);
    
}
