#include<iostream>
using namespace std;
class node
{
public:
    int data;
    int priority;
    node *next;
    node(int d,int p) 
    {
       this->data=d;
       this->priority=p;
       this->next=NULL;   
    }
    ~node() {
        if (this->next==NULL)
        {
            delete next;
            this->next=NULL;
        }
        
    }
};
class Priorty_Queue
{

public:
    void push(node* &head,int d,int p)
    {
       node *start=head;
       node *temp=new node(d,p);

       if (head->priority > p)
       {
           temp->next=head;
           head=temp;
       }
       else
       {
         while (start->next!=NULL && start->next->priority < p)
         {
            start=start->next;
         }
         temp->next=start->next;
         start->next=temp;
       }
       

    }
    void pop(node* &head)
    {
         node *temp=head;
         head=head->next;
         temp->next=NULL;
         delete temp;
    }
    int peek(node* &head)
    {
        return head->data;
    }
    int isempty(node* &head)
    {
        return head==NULL;
    }

   void display(node* &head)
   {
    node *temp=head;
        cout<<endl<<"Priorty Queue is as Follows:"<<endl;
        while (temp!=NULL)
        {
            cout<<temp->data<<"\t";
            temp=temp->next;
        }
        
   }
};
int main()
{ 
    Priorty_Queue q;
    node *head= new node(8,1);
    q.push(head,5,2);
    q.push(head,6,3);
    q.push(head,7,4);
    q.display(head);
    q.pop(head);
    q.display(head);
    return 0;
}