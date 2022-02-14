#include<stdio.h>
#include<stdlib.h>

struct  node
{
      void* data;
      struct node *next;
} *start = NULL;
typedef struct node node;

int digit_finder(int number, int k){
    int term;
    for(int i = 1; i <= k; i++){
        term = number % 10;
        number /= 10;
    }
    return term;
}
int larger_digit(){
    node* p = start;
    int temp = 0, digit = 0;
    while(p){
        if(*(int*)p->data > temp) temp = *(int*)p->data;
        p = p->next;
    }
    while(temp!=0){
        digit++;
        temp /= 10;
    }
    return digit;
}
void radix_sort(){
    // assign buckets
    node *rear[10], *front[10], *p;
    int least_significant = 1, digit;
    int most_significant = larger_digit();
    
    for(int i = least_significant; i <= most_significant; i++){
        for(int count = 0; count <= 9; count++){
            rear[count] = NULL;
            front[count] = NULL;
        }
        for(p = start; p != NULL; p = p->next){
            digit = digit_finder(*(int*)p->data, i);
            if(front[digit] == NULL){
                front[digit] = p;
            }
            else{
                rear[digit]->next = p;
            }
            rear[digit] = p;
        }
        int c = 0;
        while(front[c] == NULL) c++;
        start = front[c];
        while(c < 9){
            if(rear[c+1]){
                rear[c]->next = front[c+1];
            }
            else{
                rear[c+1] = rear[c];
            }
            c++;
        }
        rear[9]->next = NULL;
    }
}


void Print(){
    node *x = start;
    while(x){
        printf("%d ",*(int*)x->data);
        x = x->next;
    }
}
int main(){
    node *temp, *x;
    int n;
    // Enter the total no of elements
    scanf("%d", &n);
    int flag = 0;
    int ele;
    if(n < 1) flag = 1;
    for(int i = 0; i < n; i++){
          scanf("%d", &ele);
          if(ele < 0){
              flag = 1; 
              break;
          }
          temp = (node*)malloc(sizeof(struct node));
          (temp->data) = (int*)malloc(sizeof(int));
             *(int*)temp->data = ele;
             temp->next = NULL;
             if(start == NULL) start = temp;
             else {
                x = start;
                while(x->next) x = x->next;
                x->next = temp;
             }   

    }
    
    
    if(flag == 0){
        radix_sort();
       // Print the sorted list
        Print();
    }
    else{
        printf("INVALID INPUT");
    }
    free(start);
}