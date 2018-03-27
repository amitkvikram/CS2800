/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 12 March, 2018
  Problem: Binary Search Tree
*/
#include<iostream>
#include<limits.h>

using namespace std;

//class for each node of bst
class node{
public:
      node *parent = nullptr;
      node *left = nullptr;
      node *right = nullptr;
      int key = 0;
      node(int x){
            key = x;
      }
};

//head of bst
class bst{
public:
      node *root;       //pointer to root node of bst
      int sz  = 0;      //no of nodes in bst
};

//returns pointer to node with given key value
node* search(node *r, int key){
      if(r == nullptr || r->key==key) return r;       //if curr node doesn't exist or current node containes the key
      if(key<r->key) return search(r->left, key);     //if key can be found in left subtree
      else return search(r->right, key);              //if key can be found in right subtree
}

//Insert a node with given key value without creating duplicates
bool insert_key(bst *T, int key){
      if(T->root == nullptr){       //If bst is empty
            T->root = new node(key);      //create a node and make it as root
            T->sz++;                //increment the size of bst
            return true;            //if element was successfully inserted return true
      }
      if(T->root->key == key) return false;     //element with given key already in the bst
      node *curr = T->root;
      while(curr!=nullptr){
            if(key>curr->key){                  //key should be inserted in right subtree
                  if(curr->right == nullptr){
                        curr->right = new node(key);
                        curr->right->parent = curr;
                        T->sz++;                //increment the size of bst
                        return true;
                  }
                  else if(curr->right->key == key)  return false;       //duplicate found
                  else curr = curr->right;      //Search in right subtree of curr
            }
            else{                               //key should be inserted in left subtree
                  if(curr->left == nullptr){
                        curr->left = new node(key);
                        curr->left->parent = curr;
                        T->sz++;                //increment the size of bst
                        return true;
                  }
                  else if(curr->left->key == key) return false;         //duplicate found
                  else curr = curr->left;       //Search in left subtree of curr
            }
      }
}

//function returns pointer to the node with smallest key value
node* find_min(node *r){
      if(r == nullptr) return r;    //if bst is empty return nil
      else if(r->left== nullptr) return r;   //if left child is null r is the node with  smallest key value
      else return find_min(r->left);           //Search in the left subtree
}

//print tree in inorder
void inorder_traversal(node *r){
      if(r == nullptr) return;
      inorder_traversal(r->left);   //print left subtree
      cout<<r->key<<' ';            //print current node
      inorder_traversal(r->right);  //print right subtree
}

//print tree in postorder
void postorder_traversal(node *r){
      if(r == nullptr) return;
      postorder_traversal(r->left); //print left subtree
      postorder_traversal(r->right); //print right subtree
      cout<<r->key<<' ';            //print current node
}

//returns preceding key for a given node; preceding key is max element in left subtree if left subtree is present
node* find_preceding_key(node *r){
      if(r == nullptr){
            return nullptr;
      }
      if(r->left == nullptr){
            if(r->parent == nullptr) return nullptr;
            while(r->parent!=nullptr && r->parent->right!=r){
                  r= r->parent;
            }
            return r->parent;
      }
      node *curr = r->left;
      while(curr->right!=nullptr){
            curr = curr->right;
      }
      return curr;
}

//delete a give node
void deleteKey(bst *T, node* curr){
      if(curr == nullptr) return;

      //if current node doesn't have any children
      if(curr->left == nullptr && curr->right == nullptr){
            if(curr->parent == nullptr){
                  T->root = nullptr;
            }
            else if(curr->parent->left == curr) curr->parent->left = nullptr;
            else curr->parent->right = nullptr;
            delete curr;
            T->sz--;
            return;
      }

      //if current node doesn't have any left child
      else if(curr->left == nullptr){
            if(curr->parent == nullptr){  //if current node is root of bst
                  T->root = curr->right;
                  curr->right->parent = nullptr;
            }
            else{
                  curr->right->parent = curr->parent;
                  if(curr->parent->left == curr) curr->parent->left = curr->right;
                  else curr->parent->right = curr->right;
            }
            T->sz--;
            delete curr;
      }

      //if current node doesn't have any right child
      else if(curr->right == nullptr){
            if(curr->parent == nullptr){  //if current node is root of bst
                  T->root = curr->left;
                  curr->left->parent = nullptr;
            }
            else{
                  curr->left->parent = curr->parent;
                  if(curr->parent->left == curr) curr->parent->left = curr->left;
                  else curr->parent->right = curr->left;
            }
            T->sz--;
            delete curr;
      }

      else{
            node* y = find_preceding_key(curr);
            curr->key = y->key;     //make key of node equal to its preceding key
            deleteKey(T, y);        //delete predecessor
      }
}

//print tree
void print(node *r, int level){
      if(r == nullptr){
            printf("\n");
            return;
      }
      print(r->right, level+8);     //print right subtree
      printf("%*s", level, " ");
      printf("%03d\n",r->key);     //print current node's key
      print(r->left, level+8);      //print left subtree
}

//main begins here
int main(){
      bst T = bst();
      int choice, key;
      do{
            cout<<"------------MENU------------\n";
            cout<<"1. Search Key\n"<<"2. Insert Key\n"<<"3. Find Min Key\n"<<"4. InOrder traversal\n";
            cout<<"5. Post Order Traversal\n"<<"6. Find Preeding Key\n"<<"7. Delete Key\n"<<"8. Print Key\n";
            cout<<"Enter Your Choice: ";
            cin>>choice;
            if(choice == 1){
                  cout<<"Enter Key: ";
                  cin>>key;
                  node *temp = search(T.root, key);
                  if(temp == nullptr) cout<<"not found";
                  else cout<<"found";
            }
            else if(choice == 2){
                  cout<<"Enter Key: ";
                  cin>>key;
                  bool flag = insert_key(&T, key);
            }
            else if(choice == 3){
                  node* x = find_min(T.root);
                  if(x!=nullptr) cout<<"Minimum Key: "<<x->key;
            }
            else if(choice == 4){
                  cout<<"Inorder Traversal: ";
                  inorder_traversal(T.root);
            }
            else if(choice == 5){
                  cout<<"Post Order Traversal: ";
                  postorder_traversal(T.root);
            }
            else if(choice == 6){
                  cout<<"Enter Key: ";
                  cin>>key;
                  node *r = search(T.root, key);
                  r = find_preceding_key(r);
                  if(r == nullptr) cout<<"no predecessor";
                  else cout<<"Preceding Key: "<<r->key;
            }
            else if(choice == 7){
                  cout<<"Enter Key: ";
                  cin>>key;
                  node *r = search(T.root, key);
                  deleteKey(&T, r);
            }
            else if(choice == 8){
                  print(T.root, 0);
            }
            else{
                  cout<<"Exiting...";
            }
            cout<<endl;
      }while(choice>0 && choice <=8);
}
//main ends here
