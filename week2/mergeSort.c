/*
	Name: Amit Vikram Singh
	Roll No: 111601001
	Date: 16/01/2018
	Problem Name: Merge Sort(bottom-up) on binary file
*/

#include<stdio.h>
#include<stdlib.h>

//Function to Convert Binary Number into Decimal Number
long binaryToDecimal(long num){
	long decimal_num = 0, base = 1;
	while(num>0){
		decimal_num+=base*(num%10);
		num/=10;
		base*=2;
	}
	return decimal_num;			//returning decimal number
}

//Function to calculate minimum of two numbers a and b
int min(int a,int b){
	if(a>=b) return b;
	else return a;
}

//Merging two blocks
void merge(FILE *fp, int l, int r, int end){
	FILE *f_temp = fopen("temp.bin","r+");			//Opening file for storing the merged elements
	int i = l, j = r;
	long tmp1, tmp2;
	while(i<r && j<end){
		fseek(fp, i*sizeof(long), SEEK_SET);
		fread(&tmp1, sizeof(tmp1), 1, fp);
		fseek(fp, j*sizeof(long), SEEK_SET);
		fread(&tmp2, sizeof(tmp2), 1, fp);
		if(tmp1<tmp2){
			fwrite(&tmp1, sizeof(tmp1), 1, f_temp);		//writing tmp1 to file pointed by f_temp
			i++;
		}
		else{
			fwrite(&tmp2, sizeof(tmp2), 1, f_temp);		//writing tmp2 to file pointed by f_temp
			j++;
		}
	}

	//Writing remaining elements in the file pointed by f_temp
	while(i<r){
		fseek(fp, i*sizeof(long), SEEK_SET);
		fread(&tmp1, sizeof(tmp1),1, fp);
		fwrite(&tmp1, sizeof(tmp1), 1, f_temp);
		i++;
	}
	while(j<end){
		fseek(fp, j*sizeof(long), SEEK_SET);
		fread(&tmp1, sizeof(tmp1),1, fp);
		fwrite(&tmp1, sizeof(tmp1), 1, f_temp);
		j++;
	}

	fseek(f_temp, 0, SEEK_SET);
	fseek(fp, l*sizeof(long), SEEK_SET);
	//replacing elements from position l to pos end in fp by the elements in f_temp
	for(i = l; i<end; i++){
		fread(&tmp1, sizeof(tmp1), 1, f_temp);
		fwrite(&tmp1, sizeof(tmp1),1, fp);
	}
	fclose(f_temp);	//closing file pointer
}

//Function takes file pointer and sorts the elements of file pointed by the file pointer
void merge_sort(FILE *fp, int sz){
	for(int blk_sz = 1; blk_sz< sz; blk_sz = 2*blk_sz){
		for(int i =0; i< sz; i+=2*blk_sz){
			merge(fp, i, min(i+blk_sz, sz), min(i+2*blk_sz, sz));	//calling function to merge
		}
	}
}

//main begins here
int main(){
	char FileName[32];											//Name of input file
	printf("Enter FileName: ");
	scanf("%s", FileName);
	FILE *fp = fopen(FileName, "r+");				//Opening Input File.
	if(fp == NULL){													//Checking if file is opened successfully
		printf("Error in Opening File");
		return 0;
	}

	/*------------Counting numbers of elements in the file---------------------*/
	fseek(fp, 0, SEEK_END);							//fp now points to the end of file
	long sz = ftell(fp)/sizeof(long);		//sz store the total number of element in file
	printf("\nSize = %ld\n", sz);				//Printing total no of elements in the file

	long num;
	fseek(fp,0,SEEK_SET);								//fp now points to the beginning of file
	/*--------------------Printing Original File-------------------*/
	while(fread(&num, sizeof(num),1, fp)>0){
		printf("%ld\n",num);
	}

	fseek(fp,0,SEEK_SET);								//fp now points to the beginning of file
	merge_sort(fp, sz);									//Calling merge_sort function which takes the fp and sz as input
																			// and sorts the elemnts in the file pointed by fp

	/*--------------------Printing elements of sorted file-----------------*/
	FILE *fp1 = fopen("output_binary.txt","w");
	FILE *fp2 = fopen("output_decimal.txt","w");

	fseek(fp,0,SEEK_SET);								//File now points to the beginning of file

	printf("----------------Sorted-----------------\n");
	while(fread(&num, sizeof(num),1, fp)>0){
		fprintf(fp2, "%ld\n",binaryToDecimal(num));		//saving decimal equivalent of binary number
		fprintf(fp1,"%ld\n", num);
		printf("%ld\n",num);
	}

	fclose(fp);	//closing file pointer
	fclose(fp1); //closing file pointer
	fclose(fp2); //closing file pointer
	return 0;
}
//main ends here
