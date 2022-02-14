
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>
#include<string.h>

struct stack{
    int top; 
    int size;
    int *arr;
};
typedef struct stack stack;

stack *CreateStack(){
    stack * s = (stack*)malloc(sizeof(stack));
    if(!s) return NULL;
    s->size = 4;
    s->top = -1;
    s->arr = (int*)malloc(s->size * sizeof(int));
    if(!s->arr) return NULL;
    return s;
}

int isFull(stack *s){
    return s->top == s->size -1;
}
int isEmpty(stack *s){
    return s->top == -1;
}

void DoubleStack(stack *s){
    int size = s->size;
    s->size *= 2;
    int *temp = (int*) malloc(s->size * sizeof(int));
    for(int i = 0; i < size; i++){
        temp[i] = s->arr[i];
    }
    free(s->arr);
    s->arr = temp;
    s->top = size - 1;
}

void push(stack *s, int data){
    if(isFull(s))DoubleStack(s);
    s->arr[++s->top] = data;
}

int pop(stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top--];
}

void deleteStack(stack* s){
    if(s){
        if(s->arr) free(s->arr);
        free(s);
    }
}
int getTop(stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top];
}

int main(){
    char exp[100] ;
    fgets(exp, 100, stdin);
    
    int flag = 1;
    exp[strcspn(exp,"\n")] = 0;
    stack *s = CreateStack();
    if(!s) return -1;
   
    char* token = strtok(exp, " ");
    
    while(token != NULL){
        
     int i = 0, num = 0;
     char c = *token;
     if(c != '+' && c!='*' && c!='-' && c!='/'){
	    while(*(token+i)){
	      char ch = *(token+i);
	      if(ch-'0'>=0 && ch-'0'<= 9)    
            num = num*10 + (int)(*(token+i) - '0');
            i++;
	    }
	     push(s,num);
	     //printf("%d ", num);

     }
     
        
        else if(c == '+' || c=='*' || c=='-' || c=='/'){
            //printf("%c\n", c);
            int op1 = getTop(s);
            pop(s);
            int op2 = getTop(s);
            pop(s);
            
            switch(c){
                case '+':
                     push(s, op2 + op1);
                     break;
                case '-':
                     push(s, op2 - op1);
                     break;
                case '*':
                     push(s, op2 * op1);
                     break;
                case '/':
                     if(op1 == 0) {
                       printf("DIVBYZERO");
                       flag = 0;
                       break;
                       //exit(0);
                     }
                     else
                      push(s, op2 / op1);
                     break;
            }
        }
        token = strtok(NULL, " ");
    }
    if(flag  == 1)
    printf("%d",getTop(s));
}



/*
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>

struct stack{
    int top; 
    int size;
    int *arr;
};
typedef struct stack stack;

stack *CreateStack(){
    stack * s = (stack*)malloc(sizeof(stack));
    if(!s) return NULL;
    s->size = 4;
    s->top = -1;
    s->arr = (int*)malloc(s->size * sizeof(int));
    if(!s->arr) return NULL;
    return s;
}

int isFull(stack *s){
    return s->top == s->size -1;
}
int isEmpty(stack *s){
    return s->top == -1;
}

void DoubleStack(stack *s){
    int size = s->size;
    s->size *= 2;
    int *temp = (int*) malloc(s->size * sizeof(int));
    for(int i = 0; i < size; i++){
        temp[i] = s->arr[i];
    }
    free(s->arr);
    s->arr = temp;
    s->top = size - 1;
}

void push(stack *s, int data){
    if(isFull(s))DoubleStack(s);
    s->arr[++s->top] = data;
}

int pop(stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top--];
}

void deleteStack(stack* s){
    if(s){
        if(s->arr) free(s->arr);
        free(s);
    }
}
int getTop(stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top];
}

int postfix(char *exp){
    stack *s = CreateStack();
    if(!s) return -1;
    
    for(int i = 0; exp[i] != '\0'; i++){
        if(exp[i] == ' ') continue;
        else if(isdigit(exp[i])){
            int num = 0;
            while(isdigit(exp[i])){
                num = num*10 + (int)(exp[i]-'0');
                i++;
            }
            i--;
            push(s,num);
        }
        
        else{
            int op1 = getTop(s);
            pop(s);
            int op2 = getTop(s);
            pop(s);
            
            switch(exp[i]){
                case '+':
                     push(s, op2 + op1);
                     break;
                case '-':
                     push(s, op2 - op1);
                     break;
                case '*':
                     push(s, op2 * op1);
                     break;
                case '/':
                     if(op1 == 0) {
                       return INT_MAX;
                       break;
                     }
                     else
                      push(s, op2 / op1);
                     break;
            }
        }
    }
    return getTop(s);
}

int main(){
    char arr[100] ;
    fgets(arr, 100, stdin);

    arr[strcspn(arr,"\n")] = 0;
    if(postfix(arr) == INT_MAX){
        printf("DIVBYZERO");
    }
    else
    printf("%d",postfix(arr));
}

*/



