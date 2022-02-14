#include<stdio.h>
#include<stdlib.h>

struct stack{
    int size, top;
    char *arr;
};

int isEmpty(struct stack *sp){
    return sp->top == -1;
}
int isFull(struct stack *sp){
    return (sp->top == sp->size - 1);
}

void push(struct stack *sp, char val){
    if(isFull(sp)) return ;
    sp -> top++;
    sp->arr[sp->top] = val;
}

char pop(struct stack *sp){
    if(isEmpty(sp)) return -1;
    char val = sp -> arr[sp->top];
    sp->top--;
    return val;
}

int CheckParenthesis(char *arr){
    //create and initialize stack 
    struct stack *sp = (struct stack*)malloc(sizeof(struct stack)) ;
    sp->size = 100;
    sp -> top = -1;
    sp -> arr = (char*)malloc(sp->size * sizeof(char));
    
    for(int i = 0; arr[i]!='\0';i++){
        if(arr[i] == '{'){
            push(sp, '{');
        }
        else if(arr[i] == '}'){
            if(isEmpty(sp)) return 0;
            pop(sp);
        }
    }
    if(isEmpty(sp)) return 1;
    else return 0;
}

int main(){
    char arr[100];
    
    fgets(arr, 100, stdin);
    if(CheckParenthesis(arr)) printf("1");
    else printf("0");
    
    return 0;
}