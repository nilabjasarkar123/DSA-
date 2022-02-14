
#include<stdio.h>
#include<stdlib.h>

struct node{
    int vertex;
    struct node *next;
};
typedef struct node node;

struct node *CreateNode(int v);

struct Graph{
    int numVertices;
    int *visited;
    // int** for 2D array
    struct node **adjList;
};
typedef struct Graph Graph;
//------------DFS algorithm---------------------
void DFS(Graph *graph, int vertex){
    node* adjList = graph->adjList[vertex];
    node *temp = adjList;

    graph->visited[vertex] = 1;

    while(temp){
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == 0){
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

//-------Create a node-----------------
struct node *CreateNode(int v){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

//------create Graph-------------
Graph *CreateGraph(int vertex){
    Graph * graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertex;
    graph->adjList = (node**)malloc(vertex*sizeof(node*));
    graph->visited = (int*)malloc(sizeof(int));

    for(int i = 1; i <= vertex; i++){
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

//------add edge-------------------------
void addEdge(Graph *graph, int src, int dest){
    //add edge from source to destination
    node* newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    //add edge from dstination to source
    newNode = CreateNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}



int main(int argc, char const *argv[])
{
   FILE *in, *out;
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "wb");

   if(in == NULL){
       printf("Unable to read I/P file");
       exit(1);
   }
   if(out == NULL){
       printf("Unable to write I/P file");
       exit(1);
   }
   int n;
   fscanf(in, "%d", &n);
   Graph *graph = CreateGraph(n);
   int m;
   fscanf(in, "%d", &m);

   int src, dest;
   for(int i = 0; i < m; i++){
       fscanf(in, "%d %d", &src, &dest);
       addEdge(graph, src, dest);
   }

     //mking initital visited[vertex] = 0 
    for(int j = 1; j <= n; j++){
        graph->visited[j] = 0;
    }

    int cc = 0;// cc == number of connected components
    for(int i = 1; i <= n; i++){
        if(graph->visited[i] == 0){
            DFS(graph, i);
            cc++;
        }
    }

    fprintf(out, "%d", cc);
    fclose(in);
    fclose(out);
    free(&graph);
}
