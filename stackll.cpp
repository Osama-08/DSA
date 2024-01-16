#include<iostream>
using namespace std;
class node
{
public:
    int data;
    node *next;
    node(int data) {
        this->data=data;
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
class stack
{
public:
   node *top=NULL;
 void push(int d)
 {
    if (top==NULL)
    {
    node *temp=new node(d);
    top=temp;
    }
    
    else if (top!=NULL)
    {
        node *ptr=new node(d);
        ptr->next=top;
        top=ptr;
    }
    

 }  
 void pop()
 { 
    if (top==NULL)
    {
        cout<<"Underflow"<<endl;
        return;
    }
    else
    {
        node *temp=top;
        top=temp->next;
        temp->next=NULL;
        delete temp;
    }
    

 } 
 void peek()
 {
    if (top==NULL)
    {
        cout<<"Stack is empty";
        return;
    }
    else
    {
    cout<<"TOP ="<<top->data<<endl;
    }
    
    
 }
 bool empty()
 {
     if (top==NULL)
     {
        return true;
     }
     return false;
     
 }
 void display()
 {
    node *temp=top;
    while (temp!=NULL)
    {
         cout<<temp->data<<endl;
         temp=temp->next;
    }
    
 }
};
int main()
{
     stack s;
     s.push(1);
     s.push(2);
     s.push(3);
     s.push(4);
     s.push(5);
     s.pop();
     s.pop();
    //  s.pop();
    //  s.pop();
    //  s.pop();
    //  s.pop();
     s.peek();
    if (s.empty())
    {
        cout<<"Stack is  empty"<<endl;
    }
    else
    {
        cout<<"Stack is not  empty"<<endl;
    }
    
    
     s.display();

 return 0;   
}