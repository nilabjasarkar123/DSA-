#include<stdio.h>
#include<stdlib.h>

#define N 1000
//const int N = 1e5+6;
int parent[N];
int rank[N];
//----------------------------------------------------------------------------------------
// swap a and b
void swap(int *a, int *b){
    int temp = *a;
    *a = *b; *b = temp;
}
//-----------------------------------------------------------------------------------------
// MAKE-SET(x) : Create a set with single tone element x. 
//x will be the representative of the set
void make_set(int v){
    parent[v] = v;
    rank[v] = 1;
}
//-------------------------------------------------------------------------------------------
//  FIND-SET(x): Returns the representative of the set S_x.
int find_set(int v){
    //base case
    if(v == parent[v]) 
        return v;
    //path compression
    return parent[v] = find_set(parent[v]);
}
//---------------------------------------------------------------------------------------------
/*
 UNION(x,y): Unite the sets containing x and y, say S_x and S_y into a new set S_x U S_y. 
 This operation destroys S_x and S_y and adds the union.
Representative of S_x (or S_y) will be the representative of the union.
here I am taking the function as union_Set(int a, int b) because c contains 
inbild union function
*/
void union_Set(int a, int b){
    a = find_set(a);//parent of a
    b = find_set(b);//parent of b

    if(a != b){
        if(rank[a] < rank[b])
            swap(&a,&b);
        //adding small tree to big tree
        parent[b] = a;
        rank[a] += rank[b];
    }
}
//-------------------------------------------------------------------------------------------------

// a structure to represent an edge in graph
typedef struct Edge{
    int src, dest, wt;
}Edge;
Edge edge [N];
int sz = 0;

//sort the edges according to weight 
void sort(){
    Edge t;
    for(int i = 1; i < sz; i++){
        for(int j = 0; j <sz-1; j++){
            //swap in assending order of weight
            if(edge[j].wt > edge[j+1].wt){
                Edge t = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = t;
            }
        }
    }
}

int krushKal(){
    for(int i = 0; i < N; i++){
        make_set(i);
    }
    //sorting according to weight
    sort();

    int cost = 0;//string total cost
    printf("Edges of the MST ");
    printf("{");
    int i;
    for(i = 0; i < sz; i++){
        int w = edge[i].wt;
        int u = edge[i].src;
        int v = edge[i].dest;

        int x = find_set(u);
        int y = find_set(v);
        // If not lie in same set
        if(x != y){
            cost +=  w;
            //pritnting the edges
            printf("(%d %d)", u , v);
            union_Set(u,v);

        }
    }
    printf("}");
    return cost;
}

//------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    /* code */
    FILE *in;
   if(argc!=2){
        printf("File name is missing\n");
        exit(1);
    }
   in = fopen(argv[1], "r");// opening the file
   if(in == NULL){
       printf("Unable to read I/P file");
       exit(1);
   }
   
   int n; // no of vertices 
   fscanf(in, "%d", &n);
   int m; // no of edges
   fscanf(in, "%d", &m);
    

    for(int i = 0; i < m; i++){
        int u, v, w;
        fscanf(in, "%d%d%d", &u, &v, &w);
        edge[i].wt = w;
        edge[i].src = u;
        edge[i].dest = v;
        sz++;
    }

    int cost = krushKal();
    printf(", Total Weight: %d",cost);
    return 0;
}
