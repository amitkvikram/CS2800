/*
 Name: Amit Vikram Singh
 Roll No.:111601001
 Date: 15March, 2018
 Problem: B-Tree
*/

#include<iostream>
using namespace std;

class b_tree_node{
public:
      b_tree_node **child;
      int* key;
      int n;
      bool leaf;
      int  t= 3;

      b_tree_node(bool lf){
            key = new int[2*t - 1];
            child = new b_tree_node* [2*t];
            n = 0;
            leaf = lf;
      }
};

class b_tree{
public:
      b_tree_node *root;
      int t = 3;
      b_tree(int x){
            root = nullptr;
            t = x;
      }
};

void print(b_tree_node *r, int sz){
       for(int i = r->n-1; i>=0; i--){
            if(r->leaf == false) print(r->child[i+1], sz+8);
            printf("%*s", sz, " ");
            cout<<r->key[i]<<endl;
      }
      if(r->leaf == false) print(r->child[0],sz+8);
}

int search(b_tree_node *r, int key){
      if(r == nullptr) return -1;
      int i = 0;
      while(i<r->n && r->key[i] < key){
            i++;
      }

      if(i<r->n && r->key[i] == key){
            cout<<"Index"<<i;
            return i;
      }
      else if(r->leaf == true) return -1;
      else if(search(r->child[i], key) != -1){
            cout<<" <--child"<<i;
            return i;
      }
      return -1;
}

void split_child(b_tree_node *r, int c_i){
      int i = 2*r->t-1;
      b_tree_node *s = new b_tree_node(r->child[c_i]->leaf);
      s->n = r->t-1;
      while(i-->r->t){
            s->key[i - (r->t)] = r->child[c_i]->key[i];
            s->child[i-(r->t)+1] = r->child[c_i]->child[i+1];
      }

      s->child[0] = r->child[c_i]->child[r->t];
       i = r->n-1;
      while(i>=c_i){
            r->key[i+1] = r->key[i];
            r->child[i+2] = r->child[i+1];
            i--;
      }

      r->key[c_i] = r->child[c_i]->key[r->t-1];
      r->n++;
      r->child[c_i]->n = r->t -1;
      r->child[c_i+1] = s;
      return;
}

void insert_non_full(b_tree &T, b_tree_node *r, int key){
      if(r->leaf == true){
            int i = r->n-1;
            while(i>=0 && r->key[i] > key){
                  r->key[i+1] = r->key[i];
                  i--;
            }
            r->key[i+1] = key;
            r->n++;
      }
      else{
            int i  = 0;
            while(i<r->n && r->key[i]<key) i++;
            if(r->child[i]->n == 2*(T.t) - 1){
                  split_child(r, i);
                  if(r->key[i]<key) i++;
            }
            insert_non_full(T, r->child[i], key);
      }

}

void insert(b_tree &T, int key){
      if(T.root == nullptr){
            T.root = new b_tree_node(true);
            T.root->key[0] = key;
            T.root->n = 1;
            return;
      }

      if(T.root->n == 2*(T.t) - 1){
            b_tree_node *s = new b_tree_node(false);
            s->child[0] = T.root;
            T.root = s;
            split_child(T.root, 0);
            int i = 0;
            if(T.root->key[0] < key) i++;
            insert_non_full(T, T.root->child[i], key);
      }
      else{
            insert_non_full(T, T.root, key);
      }
      return;
}

int main(){
      int n;
      cin>>n;
      int k;
      b_tree T = b_tree(3);

      for(int i = 0; i<n; i++){
            cin>>k;
            cout<<"Inserting "<<k<<endl;
            if(search(T.root,k) == -1){
                  insert(T, k);
                  cout<<"------------Tree--------------\n";
                  print(T.root, 0);
                  cout<<"-----------------------------\n";
            }
            else cout<<"Key already exists\n";
      }

      cin>>k;
      while(k!=-1){
            int tmp = search(T.root, k);
            if(tmp!=-1) cout<<" <--root";
            else cout<<"Not Found";
            cout<<endl;
            cin>>k;
      }
}
