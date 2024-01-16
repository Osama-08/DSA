#include<iostream>
using namespace std;
class node
{
public:

    int data;
	node *next;

	node(int data){
        this->data=data;
		this->next=NULL;
	}	
   ~node()
   {
	if(this->next==NULL)
	{
		delete next;
		this->next=NULL;
	}
   }
};
 
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
void recursive(node* &head,node* curr,node* prev)
{
    if (curr==NULL)
    {
        head=prev;
        return;
    }
    
    node *forward=curr->next;
    recursive(head,forward,curr);
    curr->next=prev;
}
node* reverse1(node* &head)
{
    if (head==NULL || head->next==NULL)
    {
        return head;
    }
    node *temp=reverse1(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
}
void reverse(node* &head)
{
  node *prev=NULL;
  node *curr=head;
//  through recursion
  //recursive(head,curr,prev);
    //through another method
    if (head==NULL || head->next==NULL)
    {
        cout<<"Already Reversed";
    }
    else{

    
     node *prev=NULL;
     node *curr=head;
     node *forward=NULL;
     while (curr!=NULL)
     {
        forward=curr->next;
        curr->next=prev;
        prev=curr;
        curr=forward;
     }
     head= prev;
    }
    
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
    reverse(head);

	display(head);
 return 0;   
}