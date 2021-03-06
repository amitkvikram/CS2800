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

char FileName[32];											//Name of input file

//Merging two blocks
void merge(int l, int r, int end){
	FILE *fp1 = fopen(FileName, "r+");				//Opening Input File.
	FILE *fp2 = fopen(FileName, "r+");				//Opening Input File.
	printf("%d %d %d\n",l, r, end);
	FILE *f_temp = fopen("temp.bin","r+");			//Opening file for storing the merged elements

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
void merge_sort( int file_size){
	for(int blk_sz = 1; blk_sz< file_size; blk_sz = 2*blk_sz){
		for(int i =0; i< file_size; i+=2*blk_sz){
			merge( i, min(i+blk_sz, file_size), min(i+2*blk_sz, file_size));	//calling function to merge
		}
	}
}

//main begins here
int main(){

	printf("Enter FileName: ");
	scanf("%s", FileName);
	FILE *fp1 = fopen(FileName, "r+");				//Opening Input File.
	if(fp1 == NULL){													//Checking if file is opened successfully
		printf("Error in Opening File");
		return 0;
	}

	/*------------Counting numbers of elements in the file---------------------*/
	fseek(fp1, 0, SEEK_END);							//fp now points to the end of file
	long file_size = ftell(fp1)/sizeof(long);		//file_size store the total number of element in file
	printf("\nFile Size = %ld\n", file_size);				//Printing total no of elements in the file
	long num;						//fp now points to the beginning of file
	merge_sort( file_size);									//Calling merge_sort function which takes the fp and file_size as input
																	// and sorts the elemnts in the file pointed by fp
	fp1 = fopen(FileName, "r+");				//Opening Input File.
	if(fp1 == NULL){													//Checking if file is opened successfully
		printf("Error in Opening File");
		return 0;
	}

	/*--------------------Printing elements of sorted file-----------------*/
	FILE *fp3 = fopen("output_decimal.txt","w");

	// fseek(fp1,0,SEEK_SET);								//File now points to the beginning of file
	rewind(fp1);

	printf("----------------Sorted-----------------\n");
	while(fread(&num, sizeof(num),1, fp1)>0){
		fprintf(fp3, "%ld\n",num);		//saving decimal equivalent of binary number
		printf("%ld\n",num);
	}
	
	fclose(fp3);	//closing file pointer
	fclose(fp1); //closing file pointer
	return 0;
}
//main ends here
