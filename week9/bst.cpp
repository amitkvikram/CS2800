/*
  Name: Amit Vikram Singh
  Roll No: 111601001
  Date: 12 March, 2018
  Problem: Binary Search Tree
*/
#include<iostream>
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

bool insert_key(node *r, int key){
      if(r == nullptr){
            r = new node(key);
            return true;
      }
      if(r->key == key) return false;
      node *curr = r;
      while(curr!=nullptr){
            if(key>curr->key){
                  if(curr.right == nullptr){
                        curr->right = new node(key);
                        return true;
                  }
                  else if(curr->right->key == key)  return false;
                  else curr = r->right;
            }
            else{
                  if(curr->left == nullptr){
                        curr->left = new node(key);
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
      cout<<r->key<<' ';
      postorder_traversal(r->left);
      postorder_traversal(r->right)
}

void find_preeding_key(node *r){

}

int main(){
      node *r = new node;
      cout<<r->key<<endl;
}
