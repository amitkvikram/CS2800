/*
  Name: Amit Vikram Singh
  Roll No:111601001
*/

#include<stdio.h>
#include<limits.h>
#include<stdlib.h>


int main(int argc, char const *argv[]) {
  long n, num;
  printf("Enter the quantity(number) of numbers you want to generate: ");
  scanf("%ld",&n);
  FILE *fp1 = fopen("input.bin","w");
  FILE *fp2 = fopen("input_decimal.txt","w");

  for(int i =0; i<n; i++){
    num = rand()%n+1;
    fprintf(fp2, "%ld\n", num);
    printf("%ld\n",num);
    fwrite(&num,sizeof(num),1,fp1);
  }
  fclose(fp2);
  fclose(fp1);
}
