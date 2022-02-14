#include<stdio.h>
#include<stdlib.h>
//stack structure 
struct stack{
    int size, top;
    char *arr;
};
//queue structur
struct queue{
    int size, f, r; // f: front , r : rare
    char *arr;
};

/*start of stack operation */

int isEmpty(struct stack *sp){
    return sp->top == -1;
}
int isFull(struct stack *sp){
    return (sp->top == sp->size - 1);
}

void push(struct stack *sp, char val){
    if(isFull(sp)) return;
    sp -> top++;
    sp->arr[sp->top] = val;
}

char pop(struct stack *sp){
    if(isEmpty(sp)) return -1;
    char val = sp -> arr[sp->top];
    sp->top--;
    return val;
}
/*end of stack operation */

/*start of queue operation */
int isFullq(struct queue *q){
    if(q->r == q->size-1) return 1;
    return 0;
}
int isEmptyq(struct queue *q){
    if(q->f == q->r) return 1;
    return 0;
}
void enqueue(struct queue *q, char val){
    if(isFullq(q)) return;
    else{
        q->r++;
        q->arr[q->r] = val;
    }
}
char dequeue(struct queue *q){
    int a = -1;
    if(isEmptyq(q)) return -1;
    else{
        q->f++;
        a = q->arr[q->f];
    }
    return a;
}
/*end of queue operation */
int Palindron(char *arr){
    //create and initialize stack 
    struct stack *sp = (struct stack*)malloc(sizeof(struct stack));
    sp->size = 100;
    sp -> top = -1;
    sp -> arr = (char*)malloc(sp->size * sizeof(char));
    
    //create and initialize stack 
    struct queue q  ;
    q.size = 100;
    q.f = q.r = -1;
    q.arr = (char*)malloc(q.size * sizeof(char));
    
    
    for(int i = 0; arr[i]!='\0'; i++){
      push(sp, arr[i]);
      enqueue(&q, arr[i]);
    }
    int flag = 1;
    for(int i = 0; arr[i]!='\0'; i++){
      if(pop(sp) == dequeue(&q)){
          flag = 1;
      }
      else flag = 0;
    }
    
    if(isEmpty(sp) && isEmptyq(&q) && flag == 1) return 1;
    else return 0;
}

int main(){
    char arr[100];
    fgets(arr,100, stdin);
    arr[strcspn(arr,"\n")] = 0; 
    //scanf("%s", arr);
    if(Palindron(arr)) printf("1");
    else printf("0");
    
    return 0;
}