#include <iostream>
using namespace std;

void binarysearch(int arr[], int lb,int ub,int val)
{
	int mid = 0;

	while ( lb <= ub )
	{
		mid = lb + (ub - lb) / 2;

		if (arr[mid] == val)
		{
			cout << "Value found at index number : " << mid << endl;
		}

		if (arr[mid] < val)
		{
			lb = mid + 1;
		}
		else
		{
			ub = mid - 1;
		}
	}

}

struct node
{
public:

	int LID;
	int books;
	string name;
	node* next;

	node()
	{
		LID = 0;
		books = 0;
		name = "";
	}
};

class linkList
{

public:
	node* head, * tail;


	void insert(int id, int book, string nam)
	{

		if (searchuser(id))
		{
			cout << endl << "The User ID " << id << " is already registered" << endl;
		}
		else
		{
			node* temp = head;
			node* user = new node;
			user->LID = id;
			user->books = book;
			user->name = nam;
			user->next = NULL;

			if (temp == NULL)// 1st node
			{
				head = user;
				tail = user;
			}
			else
			{

				tail->next = temp;
				tail = temp;
				temp->next = user;
			}
		}
	}

	void insertatstart(int id, int books, string nam)
	{
		if (searchuser(id))
		{
			cout << endl << "The User ID "<< id <<" is already registered" << endl;
		}
		else
		{
			node* user = new node;
			user->LID = id;
			user->books = books;
			user->name = nam;
			user->next = head;
			head = user;
		}
	}

	bool searchuser(int id)
	{
		bool flag = false;

		node* temp = head;

		while (temp != NULL)
		{
			if (temp->LID == id)
			{
				flag = true;
				break;
			}
			temp = temp->next;
		}

		return flag;
	}

	void search(int id)
	{
		node* temp = head;

		while (temp != NULL)
		{
			if (temp->LID == id)
			{
				break;
			}
			temp = temp->next;
		}

		cout << endl;
		cout << "Printing Searched ID Data " << endl;
		cout << "User name = " << temp->name << endl;
		cout << "User id = " << temp->LID << endl;
		cout << "Books issued by User = " << temp->books << endl;
		cout << endl;

	}

	void print()
	{

		node* temp = head;

		cout << endl << "User Data" << endl;

		while (temp != NULL)
		{
			cout << endl;
			cout << "User name = " << temp->name << endl;
			cout << "User id = " << temp->LID << endl;
			cout << "User books = " << temp->books << endl;
			cout << endl;
			temp = temp->next;
		}
	}

	~linkList()
	{
		node* currNode = head, * nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			// destroy the current node
			delete currNode;
			currNode = nextNode;
		}
		cout << "List Destroyed" << endl;
	}

};



int main()
{

	int arr[5] = { 5,2,4,6,1 };

	int key = 0, mid = 0;

	for (int i = 0; i < 5; i++)
	{
		key = arr[i];
  		int j = i;
		
		while (j > 0 && key < arr[j - 1])
		{
			arr[j] = arr[j - 1];
			j = j - 1;
		}

		arr[j] = key;
	
	}

	for (int j = 0; j < 5; j++)
	{
		cout << arr[j] << " ";
	}
	cout << endl;

	binarysearch(arr, 0, 4, 6);


	linkList l1;
	l1.insert(1234, 3, "Umair");
	l1.insert(2345, 1, "Awais");
	l1.insertatstart(5678, 2, "Khayam");
	l1.insert(1234, 10, "Ossama");
	
	l1.print();

	cout << endl;

	l1.search(1234);

}
