#include <stdio.h>

int Factorial(int n){
    int sum = 1;
    if(n==0){
        return 1;
    }
    else{
        for(int i=1;i<n;i++){
            sum*=i;
        }
        return sum;
    }
}

int main(){
    printf("5!= %d\n20!= %d\n",Factorial(5),Factorial(20));
    return 0;
}
