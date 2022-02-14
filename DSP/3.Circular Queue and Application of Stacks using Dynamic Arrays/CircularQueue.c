#include<stdio.h>
#include<stdlib.h>

struct CircularQueue{
    int front, rear, capacity;
    int *arr;
};
typedef struct CircularQueue queue;

queue *createQueue(){
    queue *q = (queue*)malloc(sizeof(queue));
    if(!q) return NULL;
    q->capacity = 4;
    q->front = q->rear = -1;
    q->arr = (int*)malloc (q->capacity * sizeof(int));
    if(!q->arr) return NULL;
    return q;
}

int isEmpty(queue * q){
    return (q->front == -1);
}
int isFull(queue * q){
    return ((q->rear + 1) % q->capacity == q->front);
}

void DoubleQueue(queue *q){
    int *temp;
    int size = q->capacity;
    q->capacity *= 2; 
    temp = (int*)malloc (q->capacity * sizeof(int));
    for(int i = 0; i < size; i++){
        temp[i] = q->arr[(i + q->front)%size];
    }
    free(q->arr);
    q->arr = temp;
    q->front = 0;
    q->rear = q->capacity/2 -1;
}

int enqueue(queue *q, int data){
    if(isFull(q)) DoubleQueue(q);
    
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = data;
    if(q->front == -1) q->front = q->rear;
}

int dequeue(queue *q){
    int data = 0;
    if(isEmpty(q)) return 0;
    
    else{
        data = q->arr[q->front];
        if(q->front == q->rear) q->front = q->rear = -1;
        else q->front = (q->front+1) % q->capacity;
    }
    return data;
}
int deleteQ(queue *q){
    if(q){
        if(q->arr) free(q->arr);
        free(q->arr);
    }
}
    
int getFront(queue *q){
    return q->arr[q->front];
}

int main(){
    queue *q = createQueue();
    int x, i;
    
    do{
        scanf("%d", &i);
        switch(i){
            case 1:
              scanf("%d", &x);
              if(isFull(q)) printf("QF QSD ");
              enqueue(q, x);
              break;
              
            case 2:
              if(isEmpty(q)) printf("QE ");
              else printf("%d ", dequeue(q));
              break;
              
            case 3:
              if(!isEmpty(q)) printf("%d ", getFront(q));
              else printf("QE ");
              break;
              
            case -1: exit(0);
        }
    }while(i != -1);
}
    
    
    
    
    
    

