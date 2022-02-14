#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define TABLE_SIZE 100
#define MAX_EMAIL 100

typedef struct {
    char email[MAX_EMAIL];
}Email;

Email *hash_table[TABLE_SIZE];
//-------------------------------------------------------
unsigned int hash(char *email){
    int length = strnlen(email, MAX_EMAIL);
    const int p = 31;
    //const int m = 1e9 + 9;
    unsigned int hash_value = 0;
    long long p_pow = 1;
    for(int i = 0; i < length; i++){
        hash_value = (hash_value + (email[i] - 'a' + 1) * p_pow) % TABLE_SIZE;
        p_pow = (p_pow * p) % TABLE_SIZE;
    }
    return hash_value;
}

//-----------------------------------------------------------------

void initHashTable(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}
//--------------------------------------------------------------------------
bool hashTableInsert(Email* p){
    if(p == NULL) return false;
    int index = hash(p->email);
    if(hash_table[index] != NULL){
        return false;
    }
    hash_table[index] = p;
    return true;

}
//-------------------------------------------------------------------------
void PrintHT(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf(" %i ---\n", i);
        }
        else{
            printf(" %i--%s", i, hash_table[i]->email);
        }
    }
}
//--------------------------------------------------------------
int main(int argc, char const *argv[])
{
   FILE *fp;
   if(argc == 1){
       printf("nothing is passed\n");
   }
   if(argc >= 2){
       printf("%s", argv[1]);
   }
   fp = fopen("emailList.txt","w");
   if(fp==NULL){
       printf("can't be open");
       exit(0);
   }
   initHashTable();
   char str[MAX_EMAIL];
   while(!feof(fp)){
       fgets(str, MAX_EMAIL, fp);
       Email var = {.email = str};
       hashTableInsert(&var);
   }
   PrintHT();
   fclose(fp);
}
