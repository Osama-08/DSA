#include<iostream>
using namespace std;
void merge(int *a,int s,int e){

	int mid=(s+e)/2;
	
	int len1=mid-s+1;
	int len2=e-mid;
	
	int *first=new int[len1];
	int *second=new int[len2];
	//coping values
	int k=s;
	for(int i=0;i<len1;i++)
	{
		first[i]=a[k++];
	}
	 k=mid+1;
	for(int i=0;i<len2;i++)
	{
		second[i]=a[k++];
	}
	//merge 2 arrays now
	int index1=0;
	int index2=0;
	 k=s;
	while(index1<len1 && index2<len2)
	{
		if(first[index1]<second[index2])
		{
			a[k++]=first[index1++];
		}
		else
		{
			a[k++]=second[index2++];
		}
	}
	while(index1<len1)
	{
		a[k++]=first[index1++];
	}
	
	while(index1<len2)
	{
		a[k++]=second[index2++];
	}
	
	delete first;
	delete second;
}
void merge_sort(int a[],int s,int e){
	
  if(s>=e){
  	return;
  }
  int mid=(s+e)/2;
  //left
  merge_sort(a,s,mid);
  //right
  merge_sort(a,mid+1,e);
  
  merge(a,s,e);
}
int main(){
	int a[5]={64,3245,22,54,23};
	int n=5;
	merge_sort(a,0,n-1);
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" "; 
	}
}
