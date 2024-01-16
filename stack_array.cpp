#include<iostream>
using namespace std;
class stack
{
public:
  int *arr;
  int top;
  int size;
 stack(int size) {
    this->size=size;
    top=-1;
    arr=new int[size];
 }
     void push(int val){
        if (size-top >1)
        {
            top++;
            arr[top]=val;
        }
        else
        {
            cout<<"Overflow"<<endl;
        }
        
        
     }
     void pop(){
        if (top>=0)
        {
            int temp=arr[top];
            top--;
        }
        else
        {
            cout<<"Underflow"<<endl;
        }
        
     }
     void peek(){
        if (top>=0)
        {
            cout<<"TOP="<<arr[top]<<endl;
        }
        else
        {
            cout<<"Underflow"<<endl;
        }
        
        
     }
     int isempty(){
        if (top==-1)
        {
           return 0;
        }
        return 1;
        
     }
     void print()
     {
      while (top!=-1)
      {
        cout<<arr[top]<<endl;
        top--;
      }
        
     }
};
int main()
{

stack s(5);
s.push(1);
s.push(2);
s.push(3);
s.push(4);
s.push(5);
s.pop();
s.pop();
// s.peek<<endl();
s.pop();
s.pop();
s.pop();
s.peek();
s.print();
if (!s.isempty())
{
    cout<<"Stack is empty";
}

 return 0;   
}