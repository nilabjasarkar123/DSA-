
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node node;

/********create ndoe ********************************/
struct node *createNode(int data){
    node * newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
}

/************Insert data in the node**********/
node* insert(node* root, int key){

    //base case
    if(root == NULL){
        return createNode(key);
    }
    //rec casess
    if(key < root->data){
        root->left = insert(root->left, key);
    }
    else{
        root->right = insert(root->right, key);
    }
    return root;
       
}
// Finding the inorder successor for delete node
node *inOrderSucc(node* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}
/************Delete data in the node**********/
node* deletNode(node* root, int val){
   //base ccase
   if(root == NULL) return NULL;
   //find the node to be deleted
   if(val < root->data){
       root->left = deletNode(root->left, val);
   }
   else if(val > root->data){
       root->right = deletNode(root->right, val);
   }
   //node match with key
   else{
       //case 1 : No childern
       if(root->left == NULL && root->right == NULL){
           free(root);
           root = NULL;
       }
       //case 2 : single child
       else if(root->left == NULL){
           node * temp = root;
           root = root->right;
           free(temp);
       }
       else if(root->right == NULL){
           node * temp = root;
           root = root->left;
           free(temp);
       }
       //case 3 : 2 childern
       else{
           node* temp = inOrderSucc(root->right);
           root->data = temp->data;
           root->right = deletNode(root->right, temp->data);
       }
   }
   return root;
}


// --------------search in a BST---------------------
bool Lookup(node *root, int key){
    if(root == NULL) return 0;
    if(root->data == key) return 1;
    if(root->data > key){
        return Lookup(root->left, key);
    }
    else{
        return Lookup(root->right, key);
    }
}

//------Hight of bst-------------------------------
int getHight(node* root){
    // base case
    if(root == NULL) return -1;

    int h1 = getHight(root->right); //recursivly calculate right subtree;
    int h2 = getHight(root->left); //recursivly calculate left subtree;

    if(h1 > h2) return (1 + h1);
    else return (1 + h2);
}
// ------print Sorted Bst-------------------
void PrintSorted(node *root){
    // Base condition
    if(root == NULL) return;
    // Inorder traversal of Bst is sorted
    PrintSorted(root->left);
    printf("%d ",root->data);
    PrintSorted(root->right);
}
// ---------Code-------------
int main(){
    node* root = NULL;
    int ch, ele, hight, flag = 0;
    while(1){
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            scanf("%d",&ele);
            root = insert(root, ele);
            break;
        case 2:
            scanf("%d",&ele);
            root = deletNode(root, ele);
            break;
        case 3:
            scanf("%d",&ele);
            printf("%d ", Lookup(root, ele));
            break;
        case 4:
            hight = getHight(root);
            printf("%d ",hight);
            break;
        case 5:
            PrintSorted(root);
            break;
        
        case -1:
            flag = 1; 
            break;
        default:
            break;
        }
        if(flag == 1) break;
    }
}