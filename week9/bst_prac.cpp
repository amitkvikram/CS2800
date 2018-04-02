#include<bits/stdc++.h>
using namespace std;

class node{
    public:
      node *left = nullptr;
      node *right = nullptr;
      node *parent = nullptr;
      int key;
      node(int x){
          key = x;
      }
};

class bst
{
    public:
      node *root = nullptr;
      int sz = 0;
};

void print(node *r, int level){
    if(r == nullptr){
            return;
      }
      print(r->right, level+8);     //print right subtree
      printf("%*s", level, " ");
      printf("%d\n",r->key);     //print current node's key
      print(r->left, level+8);      //print left subtree
}

//search a given key and return pointer to node containing the key
node* search(node *r, int key){
    if(r == nullptr || r->key == key)
        return r;
    if(key<r->key)
        return search(r->left, key);
     else 
        return search(r->right, key);
}

//inorder traversal of bst; First left subree then current node and in last right subtree
void inorder_traverse(node *r)
{
    if(r == nullptr)
        return;
    inorder_traverse(r->left);
    cout << r->key << ' ';
    inorder_traverse(r->right);
}

//preorder traversal of bst; First process node then left subtree and then right subtree
void preorder_traverse(node *r){
    if(r == nullptr)
        return;
    cout << r->key << ' ';
    preorder_traverse(r->left);
    preorder_traverse(r->right);
}

//postorder traversal of bst; First process left subtree then right subtree and then current node
void postorder_traverse(node *r){
    if(r == nullptr)
        return;
    postorder_traverse(r->left);
    postorder_traverse(r->right);
    cout << r->key << ' ';
}

//recursive method for insertion
node *insert(node *r, int key){
    if(r->key == key)
        return r;
    if (r == nullptr)
    {
        return new node(key);
    }

    if(key>key){
        r->right = insert(r->right, key);
    }
    else{
        r->left = insert(r->left, key);
    }
}

//Iterative method for insertion
void insert_iter(bst &T, node *r, int key){
    if(T.root == nullptr){
        T.root = new node(key);
        return;
    }

    while(r->key != key){
        if(key<r->key){
            if(r->left == nullptr){
                r->left = new node(key);
                r->left->parent = r;
            }
            r = r->left;
        }
        else{
            if(r->right == nullptr){
                r->right = new node(key);
                r->right->parent = r;
            }
            r = r->right;
        }
    }
}

//inorder predecessor is max element in left subtree if left subtree is not null
//else backtrack until you get a node which is right child of its parent
node *inorder_predecessor(node *r)
{
    if(r->left == nullptr){
        while(r->parent!=nullptr && r!= r->parent->right){
            r = r->parent;
        }
        r = r->parent;
    }

    else{
        r = r->left;
        while(r->right!=nullptr){
            r = r->right;
        }
    }
    return r;
}

//inorder successor is min element in right subtree if right subtree is not null
//else backtrack until you get a node which is left child of its parent
node *inorder_successor(node *r)
{
    if(r->right == nullptr){
        while(r->parent!=nullptr && r->parent->left!=r){
            r = r->parent;
        }
        r = r->parent;
    }

    else{
        r = r->right;
        while(r->left!=nullptr){
            r = r->left;
        }
    }
    return r;
}

//parent of node: if left child of parent || parent->left == nullptr; else go to left child of parent
//keep going down until a node contains no child, always go to right child if right child is present;
node *preorder_predecessor(node *r)
{
    if(r->parent == nullptr)
        return nullptr;
    else if(r->parent->left == r)
        return r->parent;
    else{
        r = r->parent;
        if(r->left == nullptr)
            return r;
        else
            r = r->left;
        while (r->left != nullptr || r->right != nullptr)
        {
            if(r->right!=nullptr)
                r = r->right;
            else
                r = r->left;
        }
        return r;
    }
}

//left child: if left child in not null; else right child: if right child is not null;
//else backtrack until you find a ancestor whose left child is current and child and it has a right child
node *preorder_successor(node *r)
{
    if(r->left!=nullptr)
        return r->left;
    if(r->right!=nullptr)
        return r->right;
    else
    {
        while (r->parent != nullptr)
        {
            // cout << "Here\n";
            if (r->parent->left == r && r->parent->right != nullptr)
            {
                // cout << "breaking";
                break;
            }
            r = r->parent;
        }
        r = r->parent;
        if(r!=nullptr && r->right!=nullptr)
            r = r->right;
        return r;
    }
}

//
// node *postorder_predecessor(node *r){

// }

//Find minimum element in tree
node* find_min(node *r){
    if( r == nullptr ||r->left == nullptr)
        return r;
    return find_min(r->left);
}

//Find maximum element in    tree
node* find_max(node *r){
    if(r== nullptr || r->right == nullptr)
        return r;
    return find_max(r->right);
}

//Second Largest
node *second_largest(node *r){
    node *tmp = find_max(r);
    if(tmp->parent!=nullptr)
        return tmp->parent;
    find_max(r->left);
}

//kth largest recursive
node *k_largest(node *r, int &c, int k){
    if(r == nullptr  || c>=k)
        return;

    k_largest(r->right, c, k);
    c++;
    if(c >= k){
        return r;
    }
    k_largest(r->left, c, k);
}

int main()
{
    bst T = bst();
    int arr[] = {100, 200, 300, 350, 400, 325, 250, 220, 245, 240, 70, 80, 90, 95, 78, 60, 67, 65};
    for (int i = 0; i < 18; i++){
        insert_iter(T, T.root, arr[i]);
    }
    print(T.root, 0);
    int choice, key;
    do{
        cout << "1. Insertion\t2. Deletion\t3. Inorder Traversal\t4. Preorder Traversal\n";
        cout<<"5. Postorder Traversal\t6. Search Key\t7.Find Min\t8. Find Max\n";
        cout << "9. Inorder Pred\t10. Inorder Succ\t11. Preorder Predecessor\t12. Pre Successor\n";
        cout<< "Enter Choice: ";
        cin >> choice;
        if(choice == 1){
            cout << "Key: ";
            cin >> key;
            insert_iter(T, T.root, key);
            print(T.root, 0);
        }
        else if(choice == 2){
            cout << "Key: ";
            cin >> key;
            print(T.root, 0);
        }
        else if(choice == 3){
            inorder_traverse(T.root);
            cout << endl;
        }
        else if(choice == 4){
            preorder_traverse(T.root);
            cout << endl;
        }
        else if(choice == 5){
            postorder_traverse(T.root);
            cout << endl;
        }
        else if(choice == 6){
            cout << "Key: ";
            cin >> key;
            search(T.root, key);
        }
        else if(choice == 7){

        }
        else if(choice == 8){

        }
        else if(choice == 9){
            cout << "Key: ";
            cin >> key;
            node *tmp = search(T.root, key);
            tmp = inorder_predecessor(tmp);
            cout << "Inorder predecessor: ";
            if(tmp!= nullptr)
                cout << tmp->key << endl;
            else
                cout << "NULL\n";
        }
        else if(choice == 10){
            cout << "Key: ";
            cin >> key;
            node *tmp = search(T.root, key);
            tmp = inorder_successor(tmp);
            cout << "Inorder successor: ";
            if(tmp!= nullptr)
                cout << tmp->key << endl;
            else
                cout << "NULL\n";
        }
        else if(choice == 11){
            cout << "Key: ";
            cin >> key;
            node *tmp = search(T.root, key);
            tmp = preorder_predecessor(tmp);
            cout << "preorder predecessor: ";
            if(tmp!= nullptr)
                cout << tmp->key << endl;
            else
                cout << "NULL\n";
        }
        else if(choice == 12){
            cout << "Key: ";
            cin >> key;
            node *tmp = search(T.root, key);
            tmp = preorder_successor(tmp);
            cout << "preorder successor: ";
            if(tmp!= nullptr)
                cout << tmp->key << endl;
            else
                cout << "NULL\n";
        }
    } while (choice >= 1 && choice <= 12);
}