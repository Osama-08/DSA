#include<iostream>
#include<string>
#include<cmath>
#include<queue>
using namespace std;

class bst_node
{
public:
       int book_id,isbn_no;
       double book_price;
       string book_name;
       bst_node *left;
       bst_node *right;
    bst_node(int book_id,int isbn_no,double book_price,string book_name) {
             this->isbn_no=isbn_no;
             this->book_price=book_price;
             this->book_name=book_name;
             this->book_id=book_id;
             this->left=NULL;
             this->right=NULL;
    }
};
bst_node* insert(bst_node* &root,int d,int is,double p,string n){
      if (root==NULL)
      {
        root=new bst_node(d,is,p,n);
        return root;
      }
      if (d <= root->book_id)
      {
        root->left=insert(root->left,d,is,p,n);
      }
      else if(d >= root->book_id)
      {
        root->right=insert(root->right,d,is,p,n);
      }
      return root; 
}

bool search(bst_node* &root,int d)
{
    if (root==NULL)
    {
        return false;
    }
    else if(root->book_id == d)
    {
        return true;
    }
    else if (d <=root->book_id)
    {
        search(root->left,d);
    }
    else
    {
        search(root->right,d);
    }   
}
bst_node* maxval(bst_node* &root)
{
    bst_node *temp=root;
    while (temp->right!=NULL)
    {
        temp=temp->right;
    }
    return temp;
    
}
bst_node* minval(bst_node* &root)
{
    bst_node *temp=root;
    while (temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
    
}
bst_node* deletion(bst_node* &root,int d)
{
    if (root==NULL)
    {
        return root;
    }
    if (root->book_id == d)
    {
        //0 child
        if (root->left==NULL && root->right==NULL)
        {
            delete root;
            return NULL;
        }
        //1 Child
        if (root->left!=NULL && root->right==NULL)
        {
            bst_node *temp=root->left;
            delete root;
            return temp;
        }
        if (root->left==NULL && root->right!=NULL)
        {
            bst_node *temp=root->right;
            delete root;
            return temp;
        }
        //2 child
        if (root->left!=NULL && root->right!=NULL)
        {
            int mini=minval(root->right)->book_id;
            root->book_id=mini;
            root->right=deletion(root->right,mini);
            return root;
        }
        
        
    }
    else if(root->book_id > d)
    {
        root->left=deletion(root->left,d);
        return root;
    }
    else
    {
        root->right=deletion(root->right,d);
        return root;
    }
    
    
}
void printSpace(double n,bst_node* &root)
{

    for (; n > 0; n--) {

        cout << "\t";

    }

    if (root == nullptr) {

        cout << " ";

    }

    else {

        cout <<"Id::"<<root->book_id<<endl;
        cout <<"Isbn::"<<root->isbn_no<<endl;
        cout <<"Name::"<<root->book_name<<endl;
        cout <<"Price::"<<root->book_price<<endl;
        

    }
}
 

int heightOfTree(bst_node* &root)
{

    if (root == nullptr) {

        return 0;

    }

    return 1

           + max(heightOfTree(root->left),

                 heightOfTree(root->right));
}
 

void printBinaryTree(bst_node* &root)
{

    queue<bst_node*> treeLevel, temp;

    treeLevel.push(root);

    int counter = 0;

    int height = heightOfTree(root) - 1;

    double numberOfElements = pow(2, (height + 1)) - 1;

    while (counter <= height) {

        bst_node* removed = treeLevel.front();

        treeLevel.pop();

        if (temp.empty()) {

            printSpace(numberOfElements

                           / pow(2, counter + 1),

                       removed);

        }

        else {

            printSpace(numberOfElements / pow(2, counter),

                       removed);

        }

        if (removed == nullptr) {

            temp.push(nullptr);

            temp.push(nullptr);

        }

        else {

            temp.push(removed->left);

            temp.push(removed->right);

        }

        if (treeLevel.empty()) {

            cout << endl << endl;

            treeLevel = temp;

            while (!temp.empty()) {

                temp.pop();

            }

            counter++;

        }

    }
}
int main()
{
    bst_node *root=NULL;
    cout<<"Librar Managment System\n"<<endl;
    cout<<"After Inserting in the Binary Tree\n";
    //Inserting in the Tree
    insert(root,15,01,1000,"Thomas Calculus");
    insert(root,10,02,2000,"Programming Book");
    insert(root,16,03,3000,"DLD Concept");
    insert(root,13,04,4000,"Discrete Structure");
    insert(root,9,05,5000,"COAL by Josh");
    insert(root,7,06,6000,"English");
    insert(root,12,07,7000,"Urdu");
    insert(root,6,10,9000,"Physics");
    printBinaryTree(root);

    //Searching the tree with Book_id
    int a;
    cout<<"\nEnter the Book_id you want to Search:";
    cin>>a;
    if (search(root,a))
    {
        cout<<"\nThe Book is Present";
    }
    else
    {
        cout<<"\nThe Book is not Present";
    }
    
    //Deleting the certain book with book_id
     int b;
    cout<<"\nEnter the Book_id you want to Delete:";
    cin>>b;
    deletion(root,b);
    cout<<"\nAfter Deleting the Certain Book Tree is as Follows\n";
    printBinaryTree(root);

 return 0;   
}