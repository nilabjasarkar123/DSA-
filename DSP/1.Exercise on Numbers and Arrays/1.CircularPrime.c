#include<stdio.h>
#include<math.h>

//Passing the value of n and the number of digis in n
int cPrime(int n, int c){
    int cnt = c;
    if(n < 1) return -1;
    if(n == 1) return 0;
    int newNum = n;
    while(cnt){
        // check if non prime
        for(int i = 2; i*i <= newNum; i++){
            if((newNum % i == 0) ) return 0;
        }
        int last_digit = newNum % 10;
        newNum =  last_digit * pow(10,c-1) + (newNum / 10);

        if(n == newNum) return 1;
        cnt--;
    }
}

int main(){
    
    int n;
    scanf("%d", &n);
    int count = 0; 
    int temp = n;
    
    //count the number of digits in n
    while(temp){
        temp /= 10;
        count++;
    }
    printf("%d",cPrime(n,count));
}