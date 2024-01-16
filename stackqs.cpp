#include<iostream>
using namespace std;

class node
{

public:
    char data;
    node *next;
    node(char data) {
        this->data=data;
        this->next=NULL;
    }        
};
class stack
{

public:
   node *top;
   stack(){this->top=NULL;}
    void push(char val){
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
   s.push('o');
   s.push('s');
   s.push('a');
   s.push('m');
   s.push('a');
//    s.pop();
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