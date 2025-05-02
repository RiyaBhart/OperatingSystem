#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define size 10
int arr[10]={1,5,3,6,0,9,2,4,8,7};

typedef struct {
int start;
int end;
} SortArgs;

void* sort_half(void* args){
SortArgs* sa = (SortArgs*)args;
int start = sa->start;
int end =  sa->end;

for (int i = start; i < end; ++i) {
for (int j = start; j < end - (i - start) - 1; ++j) {
if (arr[j] > arr[j + 1]) {
int temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
            }
        }
    }
pthread_exit(NULL);
}

void merge(){
int temp[size];
int i =0;
int j = size/2;
int k=0;
while(i<size/2&& j<size){
if(arr[i]<arr[j]){
temp[k++]=arr[i++];
}else{
temp[k++]=arr[j++];
}
}
while(i<size/2 )temp[k++]=arr[i++];
while(j<size)temp[k++]=arr[j++];

for(int i=0;i<size;i++){
arr[i]=temp[i];
}
}

int main() {
    pthread_t t1, t2;
    SortArgs arg1 = {0, size / 2};
    SortArgs arg2 = {size / 2, size};

    printf("Original array: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    pthread_create(&t1, NULL, sort_half, &arg1);
    pthread_create(&t2, NULL, sort_half, &arg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    merge();

    printf("Sorted array:   ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

