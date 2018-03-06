/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 12 March, 2018
  Problem: Binary Search Tree
*/
#include<iostream>
#include<limits.h>

using namespace std;

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

class bst{
public:
      node *root;
      int sz  = 0;
};

node* search(node *r, int key){
      if(r == nullptr || r->key==key) return r;
      node *temp;
      if(key<=r->key) return search(r->left, key);
      else return search(r->right, key);
}

bool insert_key(bst *T, int key){
      if(T->root == nullptr){
            T->root = new node(key);
            T->sz++;
            return true;
      }
      if(T->root->key == key) return false;
      node *curr = T->root;
      while(curr!=nullptr){
            if(key>curr->key){
                  if(curr->right == nullptr){
                        curr->right = new node(key);
                        curr->right->parent = curr;
                        T->sz++;
                        return true;
                  }
                  else if(curr->right->key == key)  return false;
                  else curr = curr->right;
            }
            else{
                  if(curr->left == nullptr){
                        curr->left = new node(key);
                        curr->right->parent = curr;
                        T->sz++;
                        return true;
                  }
                  else if(curr->left->key == key) return false;
                  else curr = curr->left;
            }
      }
}

node* find_min(node *r){
      if(r == nullptr) return r;
      else if(r->left== nullptr) return r->left;
      else return find_min(r->left);
}

void inorder_traversal(node *r){
      if(r == nullptr) return;
      inorder_traversal(r->left);
      cout<<r->key<<' ';
      inorder_traversal(r->right);
}

void postorder_traversal(node *r){
      if(r == nullptr) return;
      postorder_traversal(r->left);
      postorder_traversal(r->right);
      cout<<r->key<<' ';
}

node* find_preeding_key(node *r, int key){
      node *r = search(r, key);
      if(r == nullptr || r->left ==nullptr){
            cout<<"no predecessor\n";
            return nullptr;
      }
      node *curr = r->left;
      while(curr->right!=nullptr){
            curr = curr->right;
      }
      return curr;
}

void deleteKey(bst *T, int key){
      node *curr = search(T->root, key);
      // printf("%p\n",curr);
      if(curr == nullptr) return;
      if(curr->left == nullptr && curr->right == nullptr){
            if(curr->parent == nullptr){
                  T->root = nullptr;
            }
            else if(curr->parent->left == curr) curr->parent->left = nullptr;
            else curr->parent->right = nullptr;
            delete curr;
            return;
      }

      else if(curr->left == nullptr){
            if(curr->parent == nullptr){
                  T->root = curr->right;
                  curr->right->parent = nullptr;
            }
            else{
                  curr->right->parent = curr->parent;
                  if(curr->parent->left == curr) curr->parent->left = curr->right;
                  else curr->parent->right = curr->right;
            }
            delete curr;
      }

      else if(curr->right == nullptr){
            if(curr->parent == nullptr){
                  T->root = curr->left;
                  curr->left->parent = nullptr;
            }
            else{
                  curr->left->parent = curr->parent;
                  if(curr->parent->left == curr) curr->parent->left = curr->left;
                  else curr->parent->right = curr->left;
            }
      }

      else{
            int y = find_preeding_key(node *curr);
            curr->key = y;
            delete(T, y);
      }
}

void print(node *r){
      if(r == nullptr) return;
      printf(" ");
      print(node->right);
      cout<<r.key<<endl;
      print(node->left);
}

int main(){
      bst T = bst();
      int choice;
      d0{
            cout<<"Enter Your Choice\n";
            cout<<"1. Serach Key\n"<<"2. Insert Key\n"<<"3. Find Min Key\n"<<"4. InOrder traversal\n";
            cout<<"5. Post Order Traversal\n"<<"6. Find Preeding Key\n"<<"Delete Key\n"<<"Print Key\n";
            cin>>choice;
            if(choice == 1){
                  cout<<"Enter Key: ";
                  int key;
                  cin>>key;
                  node *temp = search(key);
                  if(temp == nullptr) cout<<"not found";
                  else cout<<"found";
            }
            else if(choice == 2){
                  cout<<"Enter Key: ";
                  int key;
                  cin>>key;
                  bool flag = insert(&T, key);
            }
            else if(choice == 3){
                  int x = find_min(T.root);
                  cout<<"Minimum Key: "<<x;
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
                  int key;
                  cin>>key;
                  node *r = find_preeding_key(T.root, key);
                  if(r == nullptr) cout<<"no predecessor";
                  else cout<<r->key;
            }
            else if(choice == 7){
                  cout<<"Enter Key: ";
                  int key;
                  cin>>key;
                  deleteKey(&T, key);
            }cout<<"Enter Key: ";
                  int key;
                  cin>>key;
            else if(choice == 8){
                  print(T);
            }
            cout<<endl;
      }while(choice>0 && choice <8);
}
