#include<stdio.h>

int main(){
    int row, col;
    scanf("%d%d",&row, &col);
    if(row < 1 || col < 1){
      printf("-2");
      return 0;
    } 
    int arr[row][col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    int flag;
    for(int i = 0; i < row; i++){
        int min_colNum = 0;// minimum col number == min_colNum
        for(int j = 1; j < col; j++){
            if(arr[i][j] < arr[i][min_colNum]){
                min_colNum = j;
            }
        }
        flag = 1;
        for(int k = 0; k < row; k++){
            if(arr[k][min_colNum] > arr[i][min_colNum]){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            printf("%d %d", i, min_colNum);
            return 1;
        }
    }
    printf("%d", -1);
}
