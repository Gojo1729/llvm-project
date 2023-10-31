#include<stdio.h>

int factorial(int inputN){
    int result = 1;
    for(int i = inputN; i> 0; i--){
        result *= i;
    }

    return result;
}

int main(){

    int inputN = 5;
    int fact = factorial(inputN);
    printf("Factorial of %d is %d \n", inputN, fact);

    return 0;
}