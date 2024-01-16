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
class queue
{

public:
     node *front,*rear;
    queue() {
        front=rear=NULL;
    }
    void enqueue(int d)
    {
        node *temp=new node(d);
        if (rear==NULL)
        {
            front=rear=temp;
            return;
        }
        rear->next=temp;
        rear=temp;
    }
    void dequeue()
    {
        if (front==NULL)
        {
            return;
        }
        node *temp=front;
        front=front->next;
        if (front==NULL)
        {
            rear=NULL;
        }
        delete temp;
        
    }
    void display()
    {
        node *temp=front;
        cout<<endl<<"Queue is as follows:"<<endl;
        while (temp!=NULL)
        {
            cout<<temp->data<<"\t";
            temp=temp->next;
        }
        
    }
};
int main()
{
   queue q;
   q.enqueue(1);
   q.enqueue(2);
   q.enqueue(3);
   q.enqueue(4);
   q.enqueue(5);
   q.enqueue(6);
   q.enqueue(7);
   q.display();
   q.dequeue();
   q.dequeue();
   q.display();
   cout<<endl<<"Front::"<<q.front->data<<"\t"<<"Rear::"<<q.rear->data;
 return 0;   
}