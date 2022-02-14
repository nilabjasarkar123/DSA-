#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define LINE_SIZE 12
#define Ls 12

//----------------------------------
//this portiont is for
//queue implementation
//enque dequeue and isempty queue
//-----------------------------------
typedef struct QNode {
    int key;
    struct QNode* next;
}QNode;

typedef struct Queue {
    QNode *front, *rear;
    int size;
}Queue;
QNode* newNode(int k){
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}
Queue* createQueue(){
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}
void enQueue(Queue* q, int k){
    QNode* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->size++;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}

int deQueue(Queue* q){
    
    if (q->front == NULL)
        return 0;

    QNode* temp = q->front;
    int val = q->front->key;
    q->front = q->front->next;
 
    if (q->front == NULL)
        q->rear = NULL;

    q->size--;
    free(temp);

    return val;
}
bool isEmpty(Queue *q){
    return q->size == 0;
}

//--------------------------------------
//this porstion for 
// graph implementation 
// structure add edge and construct
//-------------------------------------
typedef struct edgeNode{
    int v;
    struct edgeNode *next;
}edgeNode;

typedef struct graph{
    int v;
    edgeNode *List;
}graph;

edgeNode* createEdgeNode(int v){
    edgeNode *e = (edgeNode*)malloc(sizeof(edgeNode));
    e->v = v;
    e->next = NULL;
    return e;
}

graph *createGraph(int v){
    graph *g = (graph*)malloc(sizeof(graph));
    g->v = v;
    g->List = (edgeNode*)malloc(v*sizeof(edgeNode));

    for(int i = 0; i < v; i++){
        g->List[i].v = i;
        g->List[i].next = NULL;
    }
    return g;
}
//connect u to v 
void addEdge(graph *g, int u, int v){
    edgeNode *t = &(g->List[u]);
    while(t->next!=NULL){
        t = t->next;
    }
    t->next = createEdgeNode(v);
}


// a function to find minimum among 2 values
int min(int a, int b){
    if(a<=b) return a;
    else return b;
}

//-------------------MAZE-----------------------------------
//here we are creating a 12 * 12 matrix 
/*
here we are finding char '.' and counting
the position after finding it adding edge 
up/down/left/right where we find the next char
*/
graph *createMaze(char *arr[]){
    graph * g = createGraph(Ls*Ls);
//     for(int i = 0; i<12;i++){
//        for(int j = 0; j<12;j++){
//            printf("%c",arr[i][j]);
//        }
//        printf("\n");
//    }
    for(int i = 0; i < Ls; i++){
        for(int j = 0; j < Ls; j++){
            if(arr[i][j] == '.'){
                int pos = (i*Ls) + j;
                // UP 
                if(arr[i-1][j] == '.' && i != 0){
                    addEdge(g, pos, pos-Ls);
                }
                // DOWN
                 if(arr[i+1][j] == '.' && i != 11){
                    addEdge(g, pos, pos+12);
                }
                // LEFT
                 if(arr[i][j-1] == '.' && j != 0){
                    addEdge(g, pos, pos-1);
                }
                // RIGHT
                 if(arr[i][j+1] == '.' && j != 11){
                    addEdge(g, pos, pos+1);
                }
            }
        }
    }
    return g;
}

// free the graph
void destroyGraph(graph *g) {
    int i;
	for(i = 0; i < g->v; i++) {
		edgeNode *v = g->List[i].next;
		
		while(v!=NULL) {
			edgeNode *tmp = v;
			v = v->next;
			free(tmp);
			}
		}
        free(g);
}
//return the minimum distance obtained
int minDist(graph *g, int u){
  //  int n = g->v;
    int visited[g->v], dist[g->v], d = -1,v;
    for(int i = 0; i < g->v; i++){
        //inititalize the visited array as 0
        //puting max value for each distance
        visited[i] = 0;
        dist[i] = INT_MAX;
    }
    Queue *q = createQueue();
    enQueue(q, u);
    visited[u] = 1;
    dist[u] = 0;
    while(!isEmpty(q)){
        v = deQueue(q);
        if(v%12 == 11){
            d = v;
        }
        edgeNode* tempNode = g->List[v].next;
        while(tempNode){
            if(visited[tempNode->v]==0){
                visited[tempNode->v] = 1;
                dist[tempNode->v] = min(dist[v]+1,dist[tempNode->v]);
                enQueue(q,tempNode->v);
            }
            tempNode = tempNode->next;
        } 
    }
    if(d == -1 || dist[d] == INT_MAX){
        return -1;
    }
    return dist[d];
}


int main(int argc, char const *argv[])
{   
    FILE *in;
    if(argc!=2){
        printf("File name is missing\n");
        exit(1);
    }
    in = fopen(argv[1], "r");
  
    if(in == NULL){
       printf("Unable to read I/P file");
       exit(1);
    }
   
   //dynamically allocating a string
   char **s = (char**)malloc(12*sizeof(char*));
   int i = 0;
   //reading the file
   while(i < 12 && feof(in)==false){
       s[i] = (char*)malloc(sizeof(char)*12);      
       fscanf(in,"%s",s[i]);
       i++;
   }
   //finding start position
   int start = 0;
   for(int j = 0; j < 12; j++){
       if(s[j][0]=='.'){
           start = j*12;
           break;
       }
       else start = -1;
   }

//    printf("\n %d\n",start);
   if(start > -1){
       graph * g = createMaze(s);
       int distance = minDist(g,start);
       printf("%d",distance);
      destroyGraph(g);
   }
   else printf("-1");
   fclose(in);
    return 0;
}

