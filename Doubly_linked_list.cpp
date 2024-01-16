#include<iostream>
using namespace std;
class node
{
public:
   int data;
   node *prev;
   node *next;
    node(int data)
    {
      this->data=data;
      this->prev=NULL;
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
void display(node* &head){
    node *temp=head;
    while (temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
    
}
void insert_start(node* &head,node* &tail,int d)
{
   if(head==NULL)
   {
    node *temp=new node(d);
    head=temp;
    tail=temp;
   }
   else
   {
    node *temp=new node(d);
    temp->next=head;
    head->prev=temp;
    head=temp;
   }
}
void insert_end(node* &head,node* &tail,int d)
{
   if(tail==NULL)
   {
    node *temp=new node(d);
    tail=temp;
    head=temp;
   }
   else
   {
    node *temp=new node(d);
    tail->next=temp;
    temp->prev=tail;
    tail=temp;
   }
   
}
void insert_position(node* &head,node* &tail,int pos,int d)
{
  if(pos==1)
  {
    insert_start(head,tail,d);
    return;
  }
  node *temp=head;
  int count=1;
  while (count<pos-1)
  {
    temp=temp->next;
    count++;
  }
  if (temp->next==NULL)
  {
    insert_end(head,tail,d);
    return;
  }
  node *node_to_insert=new node(d);
  node_to_insert->next=temp->next;
  temp->next->prev=node_to_insert;
  temp->next=node_to_insert;
  node_to_insert->prev=temp;
  
  
}
int getlen(node* &head)
{
    int count;
    node *temp=head;
    while (temp->next!=NULL)
    {
        count++;
        temp=temp->next;
    }
    return count;
}
void delete_node(node* &head,node* &tail,int pos)
{ 
	
    if(pos==1)
	{
	node* temp=head;
    temp->next->prev=NULL;
    head=temp->next;
	 temp->next=NULL;
	 delete temp;
	 return;		    
	}
	else
	{
		
		node *pev=NULL;
		node *curr=head;
		int count=1;
		while (count<pos)
		{
			pev=curr;
			curr=curr->next;
			tail=pev;
			count++;
		}
        if(pos==getlen(head))
        {

        
        node* temp=head;
         while (temp->next!=NULL)
         {
            tail=temp->next;
            temp=temp->next;
         }
        }
		curr->prev=NULL;
        pev->next=curr->next;
        curr->next=NULL;
		delete curr;
		return;
	}
}
int main()
{

node *head=NULL;
node *tail=NULL;
insert_start(head,tail,20);
insert_start(head,tail,10);
insert_end(head,tail,30);
insert_end(head,tail,40);
insert_position(head,tail,3,25);
insert_position(head,tail,5,35);
// delete_node(head,tail,1);
// delete_node(head,tail,3);
delete_node(head,tail,6);
display(head);
cout<<head->data<<" "<<tail->data;
return 0;
}