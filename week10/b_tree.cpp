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

void delete_node(b_tree &T, b_tree_node *r, int key);

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
            int j = 0;
            while(j<=r->n-1 && r->key[j]<=key){
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

int get_predecessor(b_tree_node *r){
      while(!r->leaf){
            r = r->child[r->n-1];
      }
      return r->key[r->n-1];
}

int get_successor(b_tree_node *r){
      while(!r->leaf){
            r = r->child[0];
      }
      return r->key[0]  ;
}

void delete_from_leaf(b_tree &T, b_tree_node *r, int ind){
      while(ind<r->n-1){
            r->key[ind] = r->key[ind+1];
            ind++;
      }
      r->n--;
}

void delete_from_nonLeaf(b_tree &T, b_tree_node *r, int ind){
      if(r->child[ind]->n >=r->t){
            int pred = get_predecessor(r->child[ind]);
            r->key[ind] = pred;
            delete_node(T, r->child[ind], pred);
       }
      else if(r->child[ind+1]->n >= r->t){
            int succ = get_successor(r->child[ind+1]);
            r->key[ind] = succ;
            print(T.root, 0);
            delete_node(T, r->child[ind+1], succ);
      }
      else{
            int key = r->key[ind];
            b_tree_node *l_child = r->child[ind];
            b_tree_node *r_child = r->child[ind+1];
            /*________Merge__________*/
            l_child->key[l_child->n] = r->key[ind];
            int i = 0;
            while(i<=r_child->n-1){
                  l_child->key[i+r->t] = r_child->key[i];
                  l_child->child[i+r->t] = r_child->child[i];
                  i++;
            }
            l_child->n = 2*r->t - 1;
            l_child->child[2*r->t-1] = r_child->child[r_child->n];
            /*_________delete ind_____________*/
            i = ind;
            while(i<r->n-1){
                  r->key[i] = r->key[i+1];
                  r->child[i+1] = r->child[i+2];
                  i++;
            }
            r->n--;
            if(r->n == 0){
                  delete r;
                  T.root = l_child;
            }
            l_child->n = 2*r->t - 1;
            cout<<endl;
            delete_node(T, l_child, key);
      }
}

void delete_node(b_tree &T, b_tree_node *r, int key){
      if(r == nullptr) return;

      if(r->leaf == true){
            // cout<<"leaf\n";
            int i = 0;
            while(i<=r->n-1 && r->key[i] <= key){
                  if(r->key[i] == key){
                        // cout<<"Calling delete from leaf\n";
                        delete_from_leaf(T, r, i);
                        return;
                  }
                  i++;
            }
      }
      else{
            cout<<"Non leaf\n";
            int i =0;
            while(i<r->n && r->key[i]<=key){
                  if(r->key[i] == key){
                        // cout<<"Calling delete from non_leaf";
                        delete_from_nonLeaf(T, r, i);
                        return;
                  }
                  i++;
            }
            //HERE WE HAVE TO MAKE SURE THAT CHILD[I] HAS AT LEAST T KEYS..@PENDING
            if(r->child[i]->n == r->t-1){
                  if(i>0 && r->child[i-1]->n >= r->t){
                        /*SHIFT all key and child of current node to right by one place*/
                        int j = r->child[i]->n-1;
                        r->child[i]->n++;
                        while(j>=0){
                              r->child[i]->key[i+1] = r->child[i]->key[i];
                              r->child[i]->child[i+2] = r->child[i]->child[i+1];
                              j--;
                        }
                        r->child[i]->child[1] = r->child[i]->child[0];
                        /*move an extra key from r to curr child at the 0th index*/
                        r->child[i]->key[0] = r->key[i];
                        /*move key from left sibling into r*/
                        r->key[i] = r->child[i-1]->key[r->child[i]->n-1];
                        /*move appropriate child pointer from sibling to child*/
                        r->child[i]->child[0] = r->child[i-1]->child[r->child[i]->n];
                        r->child[i-1]->n--;
                  }
                  else if(i<r->n && r->child[i+1]->n >= r->t){
                        /*SHIFT all key and child of current node to right by one place*/
                        r->child[i]->n++;
                        /*move an extra key from r to curr child at the 0th index*/
                        r->child[i]->key[r->child[i]->n-1] = r->key[i];
                        /*move key from left sibling into r*/

                        //BUG
                        r->key[i] = r->child[i+1]->key[0];

                        //Move child of right sibling to curr nodes
                        r->child[i]->child[r->child[i]->n] = r->child[i+1]->child[0];
                        //Right Sibling Shift
                        int j = 0;
                        while(j < r->child[i+1]->n-1){
                              r->child[i+1]->key[j] = r->child[i+1]->key[j+1];
                              r->child[i+1]->child[j] = r->child[i+1]->child[j+1];
                              j++;
                        }
                        r->child[i+1]->child[j] = r->child[i+1]->child[j+1];
                        /*move appropriate child pointer from sibling to child*/
                        r->child[i+1]->n--;
                        print(T.root, 0);

                  }
                  else{
                        int ind = i;
                        int key1 = r->key[ind];
                        b_tree_node *l_child = r->child[ind];
                        b_tree_node *r_child = r->child[ind+1];
                        /*________Merge__________*/
                        l_child->key[l_child->n] = r->key[ind];
                        int i1 = 0;
                        while(i1<=r_child->n-1){
                              l_child->key[i1+r->t] = r_child->key[i1];
                              l_child->child[i1+r->t] = r_child->child[i1];
                              i1++;
                        }
                        l_child->n = 2*r->t - 1;
                        l_child->child[2*r->t-1] = r_child->child[r_child->n];
                        /*_________delete ind_____________*/
                        i1 = ind;
                        while(i1<r->n-1){
                              r->key[i1] = r->key[i1+1];
                              r->child[i1+1] = r->child[i1+2];
                              i1++;
                        }
                        r->n--;
                        if(r->n == 0){
                              delete r;
                              T.root = l_child;
                        }
                        l_child->n = 2*r->t - 1;
                        cout<<endl;
                        delete_node(T, l_child, key);
                        return;
                  }
            }
            delete_node(T, r->child[i], key);
      }
}

int main(){
      b_tree T = b_tree(3);

      int choice, k;

      do{
            cout<<"1. Insert\n2. Delete\n3. Search\n4. Exit\n";
            cout<<"Enter Choice: ";
            cin>>choice;
            if(choice == 1){
                  cout<<"Enter Key: ";
                  cin>>k;
                  if(insert(T, k)){
                        cout<<" ------------Tree--------------\n";
                        print(T.root, 0);
                  }
                  else cout<<"Key already exists\n";
                  cout<<" -----------------------------\n";
            }
            else if(choice == 2){
                  cout<<"Enter Key: ";
                  cin>>k;
                  delete_node(T, T.root, k);
                  cout<<" ------------Tree--------------\n";
                  print(T.root, 0);
                  cout<<" -----------------------------\n";
            }
            else if(choice == 3){
                  cout<<"Enter Key: ";
                  cin>>k;
                  int tmp = search(T.root, k);
                  if(tmp!=-1) cout<<" <--root";
                  else cout<<"Not Found";
                  cout<<endl;
            }
            cout<<"___________________________\n";

      }while(choice>=1 && choice <4);
}
