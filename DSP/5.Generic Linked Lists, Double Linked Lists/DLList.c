#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/* create node */
struct node{
    void* data;
    struct node* prev;
    struct node* next;
}*head = NULL;
typedef struct node node;

// to create a perticuler node 
node *createNode(){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert at the begining of the list
void InsertFirst(int data){
    
    node *newNode = createNode();
    newNode->data = (int*)malloc(sizeof(int));
    *(int*)newNode->data = data;
    newNode->next = head;
    newNode->prev = NULL;
    
    /*If the new node is not first 
    elemet we need to point the head previous*/
    if(head) head->prev = newNode;
    
    head = newNode; /*head pointing to new node*/
}

// Insert at the Ending of the list
void InsertLast(int data){
    //If list is empty
    if(head == NULL){
        InsertFirst(data);
        return;
    }

    node *newNode = createNode();
    newNode->data = (int*)malloc(sizeof(int));
    *(int*)newNode->data = data;
    node *temp = head;
    
    // Traqverser the list till last element
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = NULL;
}

// Insert data at the ith position  
int InsertAtIndex(int position, int data){
    //Insert node at begining i.e 0th position
    if(position == 0){
        InsertFirst(data);
        return 1;
    }

    node *newNode = createNode();
    newNode->data = (int*)malloc(sizeof(int));
    *(int*)newNode->data = data;

    node* temp = head;
    int count = 0;
    // traverse till the node after which we insert the new node 
    while(count < position - 1 && temp->next != NULL){
        temp = temp->next;
        count++;
    }
    // IN case of given position not present
    if(count != position - 1){
        return INT_MIN;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if(temp->next){
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    
}

// delete at the begining of the list
int removeFirst(){
    if(head == NULL){
        //printf("LE ");
        return INT_MIN;
    } 
    node *temp = head;
    int val  = *(int*)head->data;
    head = head->next;
    if(head)
        head->prev = NULL;
        
    free(temp);

    return val;
}

// delete at the end of the list
int removeLast(){
    if(head == NULL){
        return INT_MIN;
    } 
   node* tail = head;
   //Iterate till last node and tail will point to the last node
   while(tail->next != NULL){
       tail = tail->next;
   }
   node* newTail = tail->prev;
   int val = *(int*)tail->data;
   newTail->next = NULL;
   free(tail);
   return val;
}

// delete at the position of the list
int removeAtIndex(int position){
    node *temp = head;
    if(head == NULL){
        return INT_MAX;
    } 
    if(position == 0){
        int val1 = removeFirst();
        return val1;
    }
    int k = 0;
    while(k != position && temp != NULL){
        temp = temp->next;
        k++;
    }
    if(temp == NULL){
        
        return INT_MIN;
    }
    int val = *(int*)temp->data;
    temp->prev->next = temp->next;
    // If node is not last node
    if(temp->next){
        temp->next->prev = temp->prev;
    }
    free(temp);
    return val;
}

// traverse the DLL and print the linled list 
void Print(){
    node *p = head;
    while(p){
        printf("%d ",*(int*)p->data);
        p = p->next;
    }
}

int main(){
   while(1){
       int ch, data, position, val1, val2, v1, v2, flag = 0;
       scanf("%d",&ch);
       if(ch == -1) break;
       /* Manu driven switch case to be performed indivisually
         */
       switch(ch){
           // Insert at the begining of Linked list
           case 1: 
                scanf("%d", &data);
                InsertFirst(data);
                break;
           // Insert at the end of Linked list
           case 2: 
                 scanf("%d", &data);
                 InsertLast(data);
                 break;
           // Insert at the ith pos of Linked list
           case 3: 
                 scanf("%d", &position);
                 scanf("%d", &data);
                 v2 = InsertAtIndex(position, data);
                 if(v2 == INT_MIN){
                     printf("INVALID INPUT");
                     flag = 1;
                 }
                 break;
            // romove  front element of the Linked list 
           case 4:
                 v1 = removeFirst();
                 if(v1 == INT_MIN){
                     printf("LE ");
                     break;
                 } 
                 printf("%d ",v1);
                 break;
           // romove  last element of the Linked list
           case 5:
                  val1 = removeLast();
                 if(val1 == INT_MIN){
                     printf("LE ");
                     break;
                 } 
                 printf("%d ",val1);
                 break;
           // romove  given position element  of the Linked list
           case 6:
                 scanf("%d",&position);
                 val2 = removeAtIndex(position);
                 if( val2 == INT_MIN){
                     printf("INVALID INPUT");
                     flag = 1; break;
                 } 
                 if(val2 == INT_MAX){
                     printf("LE ");
                     break;
                 }
                 printf("%d ", val2);
                 break;
           // display the value 
           case 7: 
                 Print();
                 break;
            default:
                 printf("INVALID INPUT");
                 flag = 1;
                 break;
       }
       // flag variavle use for terminating the invalid cases
       if(flag == 1)break;
   }
   free(head);
}