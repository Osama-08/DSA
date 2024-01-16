#include<iostream>
using namespace std;
class CircularQueue{
    int *arr;
    int front;
    int rear;
    int size;
    
    public:
   
    CircularQueue(int n){
        size = n;
        arr = new int[size];
        front = rear = -1;
    }

    
    bool enqueue(int value){
       
        if( (front == 0 && rear == size-1) || (rear == (front-1)%(size-1) ) )
         {
            cout << "Queue is Full";
            return false;
        }
        else if(front == -1) 
        {
			front = rear = 0;
            
        }
        else if(rear == size-1 && front != 0) {
            rear = 0; 
        }
        else
        {
            rear++;
        }
        arr[rear] = value;
        
        return true;
    }

   
    int dequeue(){
        if(front == -1){
            cout << "Queue is Empty " << endl;
            return -1;
        }
        int ans = arr[front];
        arr[front] = 0;
        if(front == rear) { 
            front = rear = -1;
        }
        else if(front == size - 1) {
            front = 0;
        }
        else
        {
            front++;
        }
        return ans;
    }
     void display()
    {
        cout<<endl<<"Values in Queue are"<<endl;
        for (int i = 0; i < size; i++)
        {
            cout<<arr[i]<<"\t";
        }
        
    }
};

int main()
{
  CircularQueue q(5);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(4);
  q.enqueue(5);
  q.display();
  q.dequeue(); 
  q.dequeue();
  q.display(); 

    return 0;
}