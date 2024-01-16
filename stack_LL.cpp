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
};
class stack
{

public:
   node *top;
   stack(){this->top=NULL;}
    void push(int val){
        node *temp=new node(val);
        if (!temp)
        {
            cout<<"Overflow";
        }
        
        temp->data=val;
        temp->next=top;
        top=temp;
    }
    void pop(){
        if (top == NULL)
        {
            cout<<"Underflow";
        }
        else
        {
        node *temp=top;
        top=temp->next;
        temp->next=NULL;
        delete temp;
        if (top==NULL)
        {
            cout<<"Stack is empty";
        }
        
        }
        
    }
    void peek(){
        cout<<"Top="<<top->data<<endl;
    }
int isempty() {
    return (top == NULL) ? 1 : 0;
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
//    s.pop();
//    s.pop();
//    s.pop();
//    s.pop();
   s.display();
   s.peek();
   if (!s.isempty())
   {
      cout<<"Stack is not empty";
   }
 
   
   
return 0;    
}