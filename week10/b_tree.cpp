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

bool insert_non_full(b_tree &T, b_tree_node *r, int key){
      if(r->leaf == true){
            cout<<"HERE, insert non full and leaf"<<" "<<"n= "<<r->n<<endl;
            int j = 0;
            while(j<=r->n-1 && r->key[j]<=key){
                  cout<<j<<' ';
                  if(r->key[j] == key) return false;
                  j++;
            }
            int i = r->n-1;
            while(i>=j && r->key[i] > key){
                  r->key[i+1] = r->key[i];
                  i--;
            }
            r->key[i+1] = key;
            r->n++;
            return true;
      }
      else{
            int i  = 0;
            while(i<r->n && r->key[i]<key) i++;
            if(r->child[i]->n == 2*(T.t) - 1){
                  split_child(r, i);
                  if(r->key[i]<key) i++;
                  else if(r->key[i] == key) return false;
            }
            return insert_non_full(T, r->child[i], key);
      }

}

bool insert(b_tree &T, int key){
      if(T.root == nullptr){
            T.root = new b_tree_node(true);
            T.root->key[0] = key;
            T.root->n = 1;
            return true;
      }

      if(T.root->n == 2*(T.t) - 1){
            b_tree_node *s = new b_tree_node(false);
            s->child[0] = T.root;
            T.root = s;
            split_child(T.root, 0);
            int i = 0;
            if(T.root->key[0] < key) i++;
            return insert_non_full(T, T.root->child[i], key);
      }
      else{
            return insert_non_full(T, T.root, key);
      }
}

int get_predecessor(node *r){
      while(!r->leaf){
            r = r->child[r->n-1];
      }
      return r->key[n-1];
}

int get_successor(node *r){
      while(!r->leaf){
            r = r->child[0];
      }
      return r->key[0]  ;
}

void delete_from_leaf(b_tree &T, b_tree_node *r, int ind){
      while(ind<r->n-2){
            r->key[ind] = r->key[ind+1];
            ind++;
      }
      r->n--;
}

void delete_from_nonLeaf(b_tree &T, b_tree_node *r, int ind){
      if(r->child[ind]->n >=t){
            int pred = get_predecessor(r->child[ind]);
            r->key[ind] = pred;
            delete_node(T, r->child[ind], pred);
       }
      else if(r->child[ind+1]->n >= t){
            int succ = get_successor(r->child[ind+1]);
            r->key[ind] = succ;
            delete_node(T, r->child[ind+1], succ);
      }
      else{
            b_tree_node *l_child = r->child[ind];
            b_tree_node *r_child = r->child[ind+1];
            /*________Merge__________*/
            l_child->key[l_child->n] = r->key[ind];
            int i = 0;
            while(i<=r_child->n-1){
                  l_child->key[i+l_child->n+1] = r_child->key[i];
                  l_child->child[i+l_child->n+1] = r_child->child[i];
            }
            l_child[2*t-1] = r_child->child[r_child->n];
            /*_________delete ind_____________*/
            i = ind;

            while(i<r->n-1){
                  r->key[i] = r->key[i+1];
                  r->child[i+1] = r->child[i+2];
            }
            r->n--;
            l_child->n = 2*t - 1;
      }
}

void delete_node(b_tree &T, b_tree_node *r, int key){
      if(r == nullptr) return;

      if(r->leaf == true){
            int i = 0;
            while(i<r->n-1 && r->key[i] <= key){
                  if(key[i] == key){
                        delete_from_leaf(T, T.root, i);
                        return;
                  }
                  i++;
            }
      }
      else{
            int i =0;
            while(i<r->n-1 && r->key[i]<=key){
                  if(key[i] == key){
                        delete_from_nonLeaf(T, r, i);
                        return;
                  }
                  i++;
            }
            //HERE WE HAVE TO MAKE SURE THAT CHILD[I] HAS AT LEAST T KEYS..@PENDING
            if(r->child[i]->n == t-1){
                  if(i>0 && r->child[i-1] >= t){
                        /*SHIFT all key and child of current node to right by one place*/
                        int j = r->child[i]->n-1;
                        r->child[i]->n++;
                        while(j>=0){
                              r->child[i]->key[i+1] = r->child[i]->key[i];
                              r->child[i]->child[i+2] = r->child[i]->child[i+1];
                        }
                        r->child[i]->child[1] = r->child[i]->child[0];
                        /*move an extra key from r to curr child at the 0th index*/
                        r->child[i]->child[0] = r->key[i-1];
                        /*move key from left sibling into r*/
                        r->key[i-1] = r->child[i-1]->key[r->child[i-1]->n-1];
                        /*move appropriate child pointer from sibling to child*/
                        r->child[i]->child[0] = r->child[i-1]->child[r->child[i-1]->n];
                        r->child[i-1]->n--;
                  }
                  else if(i<r->n-1 && r->child[i+1] >= t){
                        
                  }
                  else{

                  }
            }
            delete_node(T, r->child[i], key);
      }
}

int main(){
      int n;
      cin>>n;
      int k;
      b_tree T = b_tree(3);

      for(int i = 0; i<n; i++){
            cin>>k;
            cout<<"Inserting "<<k<<endl;
            if(insert(T, k)){
                  cout<<"------------Tree--------------\n";
                  print(T.root, 0);
            }
            else cout<<"Key already exists\n";
            cout<<"-----------------------------\n";
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
