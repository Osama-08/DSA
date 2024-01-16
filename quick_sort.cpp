#include<iostream>
using namespace std;
int partition(int *a,int s,int e)
{
	int pivot=a[s];
	int count=0;
	for(int i=s+1;i<=e;i++)
	{
		if(a[i]<=pivot)
		{
			count++;
		}
	}
	int pivotindex=s+count;
	//swaping
	swap(a[s],a[pivotindex]);
	//sorting
	int i=s,j=e;
	while(i<pivotindex && j>pivotindex)
	{
		while(a[i]<pivotindex)
		{
			i++;
		}
		while(a[j]>pivotindex)
		{
			j--;
		}
		//swapping
		if(i<pivotindex && j>pivotindex)
		{
			swap(a[i++],a[j--]);
			
		}
		
		
		
	}
	
	return pivotindex;
}
void quicksort(int *a,int s,int e)
{
	//base case
	if(s>=e)
	{
		return;
	}
	int p=partition(a,s,e);
//	left part
    quicksort(a,s,p-1);
    //	right part
    quicksort(a,p+1,e);
}
int main()
{
	int a[5]={5,4,3,2,1};
	int n=5;
	quicksort(a,0,n-1);
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
}
