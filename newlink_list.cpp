#include<iostream>
using namespace std;
///  making a node 
class node
{
public:
// contains data & address of some next node
    int data;
	node *next;
//passing value to the node & giving the next loc to null
	node(int data){
        this->data=data;
		this->next=NULL;
	}
//for deleting the data	
   ~node()
   {
	int val=this->data;
	if(this->next==NULL)
	{
		delete next;
		this->next=NULL;
	}
   }
};
//inserting at the begning of the list 
void inset_at_begining(node* &head,node* &tail,int d)
{
	if(head==NULL)
   {
    node *temp=new node(d);
    head=temp;
    tail=temp;
   }
      else {node *temp=new node(d);
	  temp->next=head;
	  head=temp;}
}
//inserting at the end of the list
void insert_at_end(node* &head,node* &tail,int d)
{
	 if(tail==NULL)
   {
    node *temp=new node(d);
    head=temp;
    tail=temp;
   }
   else{

      node* temp=new node(d);
	  tail->next=temp;
	  tail=temp;
   }
}
//for inserting at any position
void insert_at_position(node* &head,node* &tail,int pos,int d)
{
      if(pos==1)
	  {
		inset_at_begining(head,tail,d);
		return;
	  }
	  node* temp=head;
	  int count=1;
	  while (count<pos-1)
	  {
	     temp=temp->next;
		 count++;
	  }
	  if(temp->next==NULL)
     {
         insert_at_end(tail,tail,d);
		 return;
       }
     node* current=new node(d);
	 current->next=temp->next;
    temp->next=current;
	     
}
//Deletion of Node by position
void delete_node(node* &head,node* &tail,int pos)
{ 
	//deleting first node
    if(pos==1)
	{
		node* temp=head;
     head=head->next;
	//  freeing the memory
	 temp->next=NULL;
	 delete temp;
	 return;		    
	}
	else
	{
		//deleting any middle or last node
		node *pev=NULL;
		node *curr=head;
		int count=1;
		while (count<pos)
		{
			pev=curr;
			curr=curr->next;
			// for adjusting the tail pointer
			tail=pev;
			count++;
		}
		pev->next=curr->next;
		curr->next=NULL;
		delete curr;
		return;
	}
}


//for printing the list
void display(node *head)
{
      node* temp=head;
	  while (temp!=NULL)
	  {
		cout<<temp->data<<" ";
        temp=temp->next;
	  }
	  cout<<endl;
}
int main()
{
   
    node* head=NULL;
	node* tail=NULL;
	inset_at_begining(head,tail,0);
	insert_at_end(head,tail,1);
	insert_at_end(head,tail,2);
	insert_at_end(head,tail,3);
	insert_at_end(head,tail,4);
	insert_at_position(head,tail,6,5);
	display(head);
  // delete_node(head,tail,1);
//   delete_node(head,tail,3);
//   delete_node(head,tail,5);
  delete_node(head,tail,6);
  display(head);
  cout<<"Tail="<<tail->data;

return 0;	
}