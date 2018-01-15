#include<stdio.h>

     struct Student
     {
            int roll;
            char name[25];
            float marks;
     };

     void main()
     {
            FILE *fp;
            char ch;
            struct Student Stu;
            long  num;

            fp = fopen("Student.txt","w");            //Statement   1

            if(fp == NULL)
            {
                   printf("\nCan't open file or file doesn't exist.");
                   return;
            }

            // printf("\n\tRoll\tName\tMarks\n");

            // fread(&num,sizeof(long),1,fp);
            // printf("%ld\n",num);
            fscanf()
            // printf("\n\t%d\t%s\t%f",Stu.roll,Stu.name,Stu.marks);
            // fread(&Stu,sizeof(Stu),1,fp);
            // printf("\n\t%d\t%s\t%f",Stu.roll,Stu.name,Stu.marks);

            fclose(fp);
     }
