#include<iostream>
using namespace std;
void insertion_sort(int a[],int n)
{
	int key,j;
	for(int i=1;i<n;i++)
	{
		key=a[i];
		j=i-1;
		while(j>=0 && a[j]>key)
		{
			a[j+1]=a[j];
			j=j-1;
		}
		a[j+1]=key;
	}
}

int binary_search(int array[], int x, int low, int high) {
  
  int mid;
  while (low <= high) 
  {
     mid = low + (high - low) / 2;

    if (array[mid] == x)
    {
	
      return mid;
    }
    if (array[mid] < x)
    {
	
      low = mid + 1;
    }
    else
    {
	
      high = mid - 1;
	}
	
    }

  return -1;
}
void display(int s[],int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<s[i]<<"\t";
	}	
}
int main()
{
	int arr[5]={5,2,4,6,1};
	int n,res;
	insertion_sort(arr,5);
    display(arr,5);
    cout<<endl<<"Enter the Element you want to search in the sorted array::";
    cin>>n;
    res=binary_search(arr,n,0,4);
    if(res==-1)
    {
    	cout<<"Element Not Found.";
	}
	else
	{
		cout<<"Element Found at Index ["<<res<<"]";
	}
    
}
