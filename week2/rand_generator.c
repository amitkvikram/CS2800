/*
  Name: Amit Vikram Singh
  Roll No:111601001
*/

#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

long decimalToBinary(int num){
  int base = 1;
  int remainder = 0;
  long binary = 0;
  while(num>0){
    		remainder = num%2;
    		binary += remainder * base;
    		num = num/2;
    		base = base * 10;
  }
    	printf("%ld\n", binary);
    	return binary;
}

int main(int argc, char const *argv[]) {
  int n, num;
  printf("Enter the quantity(number) of numbers you want to generate: ");
  scanf("%d",&n);
  FILE *fp1 = fopen("input.bin","w");
  FILE *fp2 = fopen("input_decimal.txt","w");
  FILE *fp3 = fopen("input_binary.txt","w");

  for(int i =0; i<n; i++){
    num = rand()%1000+1;
    fprintf(fp2, "%d\n", num);
    long binary = decimalToBinary(num);
    fprintf(fp3,"%ld\n", binary);
    fwrite(&binary,sizeof(binary),1,fp1);
  }
  fclose(fp2);
  fclose(fp1);
  fclose(fp3);
}
