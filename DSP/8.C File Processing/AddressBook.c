#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void display();
void display2();
/*
student record  structure it contain 
student name email rollno and phone no
*/
typedef struct{
    char name[30], Email[100];
    int rollno, phoneNo;
}student;
student s;
//------------------function to insert records---------------------

/*
Here we are inserting data accoring to the structure 
we are created
 */
void createRecord(){
    FILE *fp;
    fp = fopen("student.dat","ab+");

    if(fp == NULL){
        printf("unable to open\n");
        return;
    }
        
    printf("\n------Recorded data---------\n");
    display();

    printf("\nEnter roll number: ");
    scanf("%d",&s.rollno);
    printf("\nEnter Name: ");
    scanf("%s",&s.name);
    printf("\nEnter Phone number: ");
    scanf("%d",&s.phoneNo);
    printf("\nEnter Email id: ");
    scanf("%s",&s.Email);

    fwrite(&s, sizeof(s),1, fp);
    fclose(fp);
    display();
}


//------------------------------------------------------------------

//function to modify records

void modify(){
    display();
  FILE *fp,*ft;
  int r;
  printf("\nEnter roll no needed to update: ");
  scanf("%d", &r);
  fp = fopen("student.dat","rb");
  ft = fopen("temp.dat","wb");

  while(fread(&s,sizeof(s),1,fp)){
      int st = s.rollno;
      if(st !=r){
          fwrite(&s,sizeof(s),1,ft);
      }
      else{
          printf("\nEnter rollno to update: ");
          scanf("%d",&s.rollno);
          printf("\nEnter Name to update: ");
          scanf("%s",&s.name);
          printf("\nEnter Phone number to update: ");
          scanf("%d",&s.phoneNo);
          printf("\nEnter Email id to update: ");
          scanf("%s",&s.Email);

          fwrite(&s,sizeof(s),1,ft);
      }
  }
  fclose(fp);
  fclose(ft);
  remove("student.dat");
  rename("temp.dat","student.dat");
}
//------------------------------------------------
//search function
void search(){
    display();
    FILE *fp;
    int f = 0;
    char str[30];
    printf("\nEnter the name to search: ");
    scanf("%s",str);
    fp = fopen("student.dat","rb");
    if(fp == NULL){
        printf("Unable to open\n");
        return;
    }
    while(fread(&s,sizeof(s),1,fp)){
        if(strstr(s.name,str)!=NULL){
            f = 1;
            printf("\na match is found\n");
            printf("\nRoll NO\t Name\t PhoneNo\tEmail\n");
            printf("%d\t %s\t %d\t %s\n",s.rollno,s.name,s.phoneNo,s.Email);
            break;
        }
    }
    if(f==0){
        printf("\n cound not find\n");
    }
    fclose(fp);
}
//-------------------------------------------------
//delete function
void delete(){
    display();
    FILE *fp,*ft;
    printf("\nEnter the roll you want to delete: ");
    int r;
    scanf("%d",&r);

    fp = fopen("student.dat","rb");
    ft = fopen("temp.dat","wb");
    FILE *fn = fopen("temp2.dat","wb");
     while(fread(&s,sizeof(s),1,fp)){
         int roll = s.rollno;
         if(roll!=r){
             fwrite(&s,sizeof(s),1,ft);
             fwrite(&s,sizeof(s),1,fn);
         }
         else{
           //  char buffer[10] = "#DELETE#";
             s.rollno = 0; strcpy(s.name,"#DELETE#"); 
             s.phoneNo = 0;strcpy(s.Email,"#DELETE#");
             fwrite(&s,sizeof(s),1,fn);
         }
     }
     fclose(fp);
     fclose(ft);
     fclose(fn);
     display2();
     remove("temp2.dat");
     remove("student.dat");
     rename("temp.dat","student.dat");

}
void display2(){
   FILE *fp;
   fp = fopen("temp2.dat","rb");

    if(fp == NULL){
        printf("unable to open\n");
        return;
    }
    printf("\nRollNO\t Name\t PhoneNo   Email\n");
    while(fread(&s,sizeof(s),1,fp)){
        printf("%d\t %s\t %d\t %s\n",s.rollno,s.name,s.phoneNo,s.Email);
    }
    fclose(fp);
}

void display(){
   FILE *fp;
   fp = fopen("student.dat","rb");

    if(fp == NULL){
        printf("unable to open\n");
        return;
    }
    printf("\nRollNO\t Name\t PhoneNo   Email\n");
    while(fread(&s,sizeof(s),1,fp)){
        printf("%d\t %s\t %d\t %s\n",s.rollno,s.name,s.phoneNo,s.Email);
    }
    fclose(fp);
}

int main(){
    int ch;
    do{
        printf("\n");
        printf("\nPRESS FOLLOWING\n");
        printf("1.APPEND NEW STUDENT RECORD\n");
        printf("2.MODIFY BASED ON ROLL NO\n");
        printf("3.SEARCH STUDENT ADDRESS BASED ON NAME\n");
        printf("4.DELETE STUDENT RECORD\n");
        printf("5.Exit\n");
        printf("------------------------------------------\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        printf("\n");

        switch (ch)
        {
        case 1:
            createRecord();
            break;
        case 2:
            modify();
            break;
        case 3:
            search();
            break;
        case 4:
            delete();
            break;
        case 5:
            exit(1);
            break;
        default:
            printf("\nWrong choice\n");
            break;
        }
    }while(ch != 5);
}

