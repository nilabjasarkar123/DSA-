#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct node {
    int row;
    int col;
    int val;
    struct node *next;
};
typedef struct node node;

bool less(node *a, node* b){
    if (a->row < b->row) return true;
    if (a->row > b->row) return false;
    return (a->col < b->col);
}

void insert(node **sm, int row, int col, int val){
    node *n = (node*) malloc(sizeof(*n));

    n->row = row;
    n->col = col;
    n->val = val;
    n->next = NULL;

    while(*sm && less(*sm, n)){
        sm = &(*sm)->next;
    }
     if (*sm == NULL || less(n, *sm)) {
        n->next = *sm;
        *sm = n;
    } else {
        (*sm)->val += val;
        free(n);
    }

}

node *add(node * a, node *b){

    node *ans = NULL;

    
    while (a && b) {
        if (less(a, b)) {
            insert(&ans, a->row, a->col, a->val);
            a = a->next;
        } else if (less(b, a)) {
            insert(&ans, b->row, b->col, b->val);
            b = b->next;
        } else {
            insert(&ans, b->row, b->col, a->val + b->val);
            a = a->next;
            b = b->next;
        }
    }

    while (a) {
        insert(&ans, a->row, a->col, a->val);
        a = a->next;
    }

    while (b) {
        insert(&ans, b->row, b->col, b->val);
        b = b->next;
    }

    return ans;
}
void print(node *sp, int m, int n)
{
        int arr[m][n];
        for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            arr[i][j] = 0;
        }
    while (sp) {
        arr[sp->row][sp->col] = sp->val;
        sp = sp->next;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",arr[i][j]);
        }
            printf("\n");
    }
}
void destroy(node *p)
{
    while (p) {
        node *next = p->next;

        free(p);
        p = next;
    }

}
int main(){
    node *a =NULL;
    node *b =NULL;
    node *ans =NULL;

    int m, n;
    int r = m, c = n;
    scanf("%d%d",&m, &n);
    int t1 = 0, t2 = 0;
    int n1, n2, row,col,val;
    scanf("%d%d",&n1, &n2); 
    int f1 = 0, f2 = 0;
    int ele = m*n;
    while(t1<n1){
        scanf("%d%d%d",&row,&col,&val);
        if((ele>=n1 && ele>=n2)&&(row >=0 && row <= m-1) && (col >=0 && col <= n-1)){
           insert(&a,row,col,val);
           t1++;
        }
        else{
           f1 = 1;
           break;
        } 
    }
    
    while(t2<n2){
        scanf("%d%d%d",&row,&col,&val);
        if((ele>=n1 && ele>=n2)&&(row >=0 && row <= m-1) && (col >=0 && col <= n-1)){
          insert(&b,row,col,val);
           t2++;
        }
        else{
            f2 = 1;
            break;
        } 
    } 
    if(f1==1 || f2 ==1){
        printf("INVALID INPUT");
    }
    else{
        ans = add(a, b);
        print(ans, m, n);
    }
    destroy(a);
    destroy(b);
    destroy(ans);
}