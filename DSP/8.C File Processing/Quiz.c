#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
gcc Quiz.c 
to run ./a.exe fileName 
./a Question
q1:
give ans 
continue
*/
int main(int argc, char const *argv[])
{
    //file input and output
    FILE *fin, *fout, *fans;
    int count = 0;//sore count 
    char data[80];
    fin = fopen(argv[1], "r");
    fout = fopen("score.txt", "w");//printing the score to a file
    fans = fopen("ans.txt", "w");//creating a text file to write answers
    
    if(fin == NULL) {
        printf("unable read i/p file");
        exit(1);
    }
    if(fout == NULL){
        printf("unable to write i/p file");
        exit(1);
    }
    fgets(data, 80, fin);
    //running till EOF
     while(fgets(data, 80, fin)!= NULL){
         char qus[strlen(data)];
         strcpy(qus, data);
         printf("%s", data);

        char *ans =  fgets(data, 80, fin);
        char newdata[10];
        int i = 0;
        while(data[i] != '\n'){
            newdata[i] = data[i];
            i++;
        }
        newdata[i] = '\0';
         char str[10];
         scanf("%s", str);
         //conpare
         int t = strcasecmp(str, newdata);
         if(t==0) count++;

         else{
             fprintf(fans, "%s", qus);
             fprintf(fans, "%s", ans);
         }

     }
    printf("%d\n", count);//print the score
    fprintf(fout, "%d", count);//store the score in a text file
    printf("---------------------------------\n");
    printf("The correct answers are following\n");
    printf("---------------------------------\n");
    fclose(fin);
    fclose(fout);
    fclose(fans);
    FILE *fansptr;
    char  info[80];
    fansptr = fopen("ans.txt", "r");
    while(fgets(info, 80, fansptr)!= NULL){
        printf("%s", info);
    }
    printf("---------------------------------");
    fclose(fansptr);
    return 0;
}