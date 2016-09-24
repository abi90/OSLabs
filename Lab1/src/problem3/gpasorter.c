/*
 * File:   gpasorter.c
 * Author: Abisai Ramos
 *
 * Created on August 28, 2016, 2:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define NAME_LENGTH 50

struct student {char name[NAME_LENGTH]; float gpa;};
void Merge(struct student *A,struct student *L,int leftCount,struct student *R,int rightCount);
void MergeSort(struct student *A,int n);

/**
 * GPA student sorter
 */
void main()
{
    struct student students[MAX];
    int length,i;
    printf("Please enter the number of students:\n");
    scanf("%d",&length);
    if(length>0&&length<MAX)
    {
        for (i = 0; i < length; i++)
        {
            printf("Student %d. Please enter the name follow by the GPA:\n", i+1);
            scanf("%s %f",&students[i].name,&students[i].gpa);
        }
        MergeSort(students,length);
        printf("Student\tGPA\n");
        for(i=0;i<length;i++)
        {
            printf("%s\t%.2f\n",students[i].name,students[i].gpa);
        }
    }
    else printf("Error using: %d\nThe max number of students is: %d\n",length,MAX);
    printf("Enter 0 to exit:\n");
    scanf("%d");
}

/**
 * Merges Arrays L and R into A.
 * Based on the merge sort algorithm for sorting arrays.
 * @param A output sorted array of struct students
 * @param L input array of struct students
 * @param leftCount number od elements in L
 * @param R input array of struct students
 * @param rightCount number of elements in R
 */
void Merge(struct student *A,struct student *L,int leftCount,struct student *R,int rightCount) {
    int i,j,k;

    // i index for left array L
    // j index for right array R
    // k index for merged array A
    i = 0; j = 0; k =0;

    while(i<leftCount && j< rightCount) {
        if(L[i].gpa  < R[j].gpa) A[k++] = L[i++];
        else A[k++] = R[j++];
    }
    while(i < leftCount) A[k++] = L[i++];
    while(j < rightCount) A[k++] = R[j++];
}

/**
 * Recursive function to sort an array of struct students by GPA in ascending order.
 * Based on the merge sort algorithm for sorting arrays.
 * @param A Array of struct student.
 * @param n Size of the array.
 */
void MergeSort(struct student *A,int n) {
    int mid,i;
    struct student *L, *R;
    // Base condition:
    if(n < 2) return;

    // Mid index.
    mid = n/2;
    //Divide the array in L and R
    L = (struct student *)malloc(mid*sizeof(struct student));
    R = (struct student *)malloc((n- mid)*sizeof(struct student));

    for(i = 0;i<mid;i++) L[i] = A[i];
    for(i = mid;i<n;i++) R[i-mid] = A[i];

    //Sort L and R
    MergeSort(L,mid);
    MergeSort(R,n-mid);

    //Merge L and R
    Merge(A,L,mid,R,n-mid);
    free(L);
    free(R);
}
