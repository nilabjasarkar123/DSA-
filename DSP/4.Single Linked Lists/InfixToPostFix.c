#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct node{
    char data;
    struct node *next;
}*top = NULL;
typedef struct node node;

int isEmpty(node *top){
    return top == NULL;
}

int isFull(node *top){
    node *p = (node*)malloc(sizeof(node));
     
    return p == NULL;
}

node* push(char x){
        //if(isFull(top)) overflow
        node *temp = (node*)malloc(sizeof(node));
        temp->data = x;
        temp->next = top;
        top = temp;
        return top;
}

char pop(node *tp){
       // if(isEmpty(top)) underflow
        node *temp = tp;
        top = tp->next;
        char x = temp->data;
        free(temp);
        return x;
}

int isOperand(char ch){
    return (ch >= 'a' && ch <= 'z') ||  (ch >= 'A' && ch <= 'Z');
}

int Priority(char ch){
    if(ch == '^') return 5;
    else if(ch=='*' || ch== '/' || ch == '%') return 4;
    else if(ch=='+' || ch== '-') return 3;
    return 2;;
}


void I2P(char *input){
    char *token = strtok(input, " ");
    while(token != NULL){
        if(isalnum(*token)){
            printf("%s ", token);
        }
        else if(*token == '(' || isEmpty(top) || Priority(*token) > Priority(top->data)){
            push(*token);
        }
        else if(*token == ')'){
            while(top->data != '('){
                printf("%c ", pop(top));
            }
            pop(top);
        }
        else{
            while(!isEmpty(top) && Priority(*token) <= Priority(top->data)){
                printf("%c ",pop(top));
            }
            push(*token);
        }
        token = strtok(NULL, " ");
    }
    while(top != NULL){
        printf("%c ", pop(top));
    }
}


int main(){
    char input[100];
    fgets(input, 100, stdin);
    strtok(input,"\n");
    I2P(input);
    free(top);
    return 0;
}