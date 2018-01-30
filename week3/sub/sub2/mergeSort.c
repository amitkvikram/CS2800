/*
	Name: Amit Vikram Singh
	Roll No: 111601001
	Date: 16/01/2018
	Problem Name: Merge Sort(bottom-up) on binary file
*/
#include<stdio.h>
#include<stdlib.h>

//Function to calculate minimum of two numbers a and b
int min(int a,int b){
	if(a>=b) return b;
	else return a;
}

//Merging two blocks
void merge(FILE *fp3, FILE *fp4, int l, int r, int end){
	//printf("%d %d %d\n",l, r, end);
	FILE *f_temp = fopen("temp.bin","r+");			//Opening file for storing the merged elements
	FILE *fp1 = fopen("input.bin","r+");			//Opening file for storing the merged elements
	FILE *fp2 = fopen("input.bin","r+");			//Opening file for storing the merged elements

	int i = l, j = r;
	fseek(fp1, l*sizeof(long), SEEK_SET);
	fseek(fp2, r*sizeof(long), SEEK_SET);
	long tmp1, tmp2;
	while(i<r && j<end){
		// fseek(fp, i*sizeof(long), SEEK_SET);
		fread(&tmp1, sizeof(tmp1), 1, fp1);
		// fseek(fp, j*sizeof(long), SEEK_SET);
		fread(&tmp2, sizeof(tmp2), 1, fp2);
		if(tmp1<tmp2){
			fwrite(&tmp1, sizeof(tmp1), 1, f_temp);		//writing tmp1 to file pointed by f_temp
			fseek(fp2, -1*sizeof(long), SEEK_CUR);
			i++;
		}
		else{
			fwrite(&tmp2, sizeof(tmp2), 1, f_temp);		//writing tmp2 to file pointed by f_temp
			fseek(fp1, -1*sizeof(long), SEEK_CUR);
			j++;
		}
	}

	//Writing remaining elements in the file pointed by f_temp
	fseek(fp1, i*sizeof(long), SEEK_SET);
	while(i<r){
		fread(&tmp1, sizeof(tmp1),1, fp1);
		fwrite(&tmp1, sizeof(tmp1), 1, f_temp);
		i++;
	}

	fseek(fp2, j*sizeof(long), SEEK_SET);
	while(j<end){
		fread(&tmp1, sizeof(tmp1),1, fp2);
		fwrite(&tmp1, sizeof(tmp1), 1, f_temp);
		j++;
	}

	fseek(f_temp, 0, SEEK_SET);
	fseek(fp1, l*sizeof(long), SEEK_SET);
	//replacing elements from position l to pos end in fp by the elements in f_temp
	for(i = l; i<end; i++){
		fread(&tmp1, sizeof(tmp1), 1, f_temp);
		fwrite(&tmp1, sizeof(tmp1),1, fp1);
	}
	fclose(f_temp);	//closing file pointer
	fclose(fp1);
	fclose(fp2);
}

//Function takes file pointer and sorts the elements of file pointed by the file pointer
void merge_sort(FILE *fp1, FILE *fp2, int sz){
	for(int blk_sz = 1; blk_sz< sz; blk_sz = 2*blk_sz){
		for(int i =0; i< sz; i+=2*blk_sz){
			merge(fp1, fp2, i, min(i+blk_sz, sz), min(i+2*blk_sz, sz));	//calling function to merge
		}
	}
}

//main begins here
int main(){
	char FileName[32];											//Name of input file
	printf("Enter FileName: ");
	scanf("%s", FileName);
	FILE *fp1 = fopen(FileName, "r+");				//Opening Input File.
	FILE *fp2 = fopen(FileName, "r+");				//Opening Input File.
	if(fp1 == NULL || fp2 == NULL){													//Checking if file is opened successfully
		printf("Error in Opening File");
		return 0;
	}

	/*------------Counting numbers of elements in the file---------------------*/
	fseek(fp1, 0, SEEK_END);							//fp now points to the end of file
	long sz = ftell(fp1)/sizeof(long);		//sz store the total number of element in file
	printf("\nSize = %ld\n", sz);				//Printing total no of elements in the file

	long num;
	fseek(fp1,0,SEEK_SET);								//fp now points to the beginning of file
	merge_sort(fp1,fp2, sz);									//Calling merge_sort function which takes the fp and sz as input
																			// and sorts the elemnts in the file pointed by fp

	/*--------------------Printing elements of sorted file-----------------*/
	FILE *fp3 = fopen("output_decimal.txt","w");

	fseek(fp1,0,SEEK_SET);								//File now points to the beginning of file

	FILE *fp4 = fopen(FileName, "r+");
	printf("----------------Sorted-----------------\n");
	while(fread(&num, sizeof(num),1, fp4)>0){
		fprintf(fp3, "%ld\n",num);		//saving decimal equivalent of binary number
		// printf("%ld\n",num);
	}

	fclose(fp3);	//closing file pointer
	fclose(fp1); //closing file pointer
	fclose(fp2); //closing file pointer
	return 0;
}
//main ends here
