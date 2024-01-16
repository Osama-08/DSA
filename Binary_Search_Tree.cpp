#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
class bst_node
{
public:
       int data;
       bst_node *left;
       bst_node *right;
    bst_node(int data) {
             this->data=data;
             this->left=NULL;
             this->right=NULL;
    }
};
bst_node* insert(bst_node* &root,int d){
      if (root==NULL)
      {
        root=new bst_node(d);
        return root;
      }
      if (d <= root->data)
      {
        root->left=insert(root->left,d);
      }
      else if(d >= root->data)
      {
        root->right=insert(root->right,d);
      }
      return root; 
}
void level_order(bst_node* &root)
{
queue<bst_node*> q;
  q.push(root);
  q.push(NULL);
  while (!q.empty())
  {
    bst_node *temp=q.front();
    q.pop();
      if (temp==NULL)
      {
        cout<<endl;
        if (!q.empty())
        {
            q.push(NULL);
        }
        
      }
      else
      {
        cout<<temp->data<<"  ";
        if (temp->left)
        {
            q.push(temp->left);
        }
        if (temp->right)
        {
            q.push(temp->right);
        }
        
      }
      
  }
  
}
void preorder(bst_node* &root)
{
   if (root==NULL)
   {
    return;
   }
   cout<<root->data<<" ";
   preorder(root->left);
   preorder(root->right);
   
}

void postorder(bst_node* &root)
{
   if (root==NULL)
   {
    return;
   }
   postorder(root->left);
   postorder(root->right);
   cout<<root->data<<" ";
   
}
void inorder(bst_node* &root)
{
   if (root==NULL)
   {
    return;
   }
   inorder(root->left);
   cout<<root->data<<" ";
   inorder(root->right);
   
}
bool search(bst_node* &root,int d)
{
    if (root==NULL)
    {
        return false;
    }
    else if(root->data == d)
    {
        return true;
    }
    else if (d <=root->data)
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
    if (root->data == d)
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
            int mini=minval(root->right)->data;
            root->data=mini;
            root->right=deletion(root->right,mini);
            return root;
        }
        
        
    }
    else if(root->data > d)
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

        cout <<" ";

    }

    else {

        cout<<root->data;
        

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
    insert(root,50);
    insert(root,40);
    insert(root,30);
    insert(root,20);
    insert(root,10);
    insert(root,60);
    insert(root,70);
    insert(root,80);
    insert(root,90);
    insert(root,45);
    insert(root,35);
    insert(root,65);
    insert(root,75);
    insert(root,85);
    insert(root,95);
    level_order(root);
    cout<<"Pre-Order=>";preorder(root);cout<<endl;
    cout<<"Post-Order=>";postorder(root);cout<<endl;
    cout<<"In-Order=>";inorder(root);cout<<endl;
    
    if (search(root,30))
    {
       cout<<"The Node is Found";
    }
    else
    {
        cout<<"The Node is not Found";
    }
    
    // root=deletion(root,50);
    // root=deletion(root,10);
    root=deletion(root,35);
    // level_order(root);
    printBinaryTree(root);
 return 0;   
}