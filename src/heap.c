#include "heap.h"

int main (int argc, char * argv[]) {
    int keys[20];
    int fArray [20][10];
    readFile(fArray, "f.dat");
    buildMaxHeap(fArray, keys);
    //printf("%d\n", fArray[1][0]);
    for(int i=0; i<20; i++){
        printf("%d ", keys[i]);
    }
    printf("\n");
    return 0;
}

int readFile(int fArray[20][10], char *filename){ //Reads data and validates input
    FILE *fptr = fopen("f.dat", "r");
    if (fptr == NULL) {
        printf("Could not open file \n");
        return -1; // Error
    } else {

        for(int i=0; i<20; i++){
            for(int j=0; j<10; j++){
                fscanf(fptr, "%d", &fArray[i][j]);
            }
        }
    }
    fclose(fptr);
    return 0;
}	

void computeKeys(int arr[20][10], int keys[20]){
    for(int i=0; i<20; i++){
        keys[i] = arr[i][0]+arr[i][1]+arr[i][2];
        //printf("%d ", keys[i]);
    }
    //printf("\n");
}

void buildMaxHeap(int arr[20][10], int keys[20]){ //Performs heapify bottom-up
    computeKeys(arr, keys);
    for(int current = 9; current>=0; current--){
        //if not 9 cause 9 has only one left node 
        int i = current;
        while (2*i + 1 < 20){
            //left leaf
            int left = 2*i + 1;
            int right = 2*i + 2;
            int largest = i;

            if (keys[left] > keys[largest]){
                largest = left;
            }
            if (right < 20 && keys[right] > keys[largest]){
                largest = right;
            }
            if (largest != i) {
                swapRows(arr[i], arr[largest]);
                int tempKey = keys[i];
                keys[i] = keys[largest];
                keys[largest] = tempKey;

                i = largest; 
            } else {
                break; // Heap property satisfied
            }
        }
    
    }
}


void heapify(int arr[20][10], int keys[20], int n, int i){}	//Percolates down node i
void writeFile(int arr[20][10], char *filename){}	//Writes output to file
void swapRows(int a[10], int b[10]){
    int temp[10];
    for (int i = 0; i<10; i++){
        temp[i] = a[i];
        a[i] = b[i];
        b[i] = temp[i];
    }
    
} 

