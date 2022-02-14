#include<stdio.h>
#include<stdlib.h>

//----- Function to swap the the position of two elements--------------------------------------------
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }


//--------MAX heapify function to put max in root--------------------------------------------
void MAX_HEAPIFY(int arr[], int n, int i){
   // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest-
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      MAX_HEAPIFY(arr, n, largest);
    }
}
// -------------Build max heap-------------------------------------------
void BUILD_MAX_HEAP(int arr[], int  n){
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      MAX_HEAPIFY(arr, n, i);
}

//----------- Main function to do heap sort--------------------------------
  void HEAP_SORT(int arr[], int n) {
    
    BUILD_MAX_HEAP(arr, n);
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
  
      // Heapify root element to get highest element at root again
     MAX_HEAPIFY(arr, i, 0);
    }
  }
  

  // ---------Print an array------------------------
  void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
      printf("%d ", arr[i]);
    printf("\n");
  }
  
//----------- code------------------------
  int main() {

    int n;
    scanf("%d",&n);
    int arr[n];
    if(n <= 0){
        printf("INVALID INPUT");
        return 0;
    }
    for(int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
  
    HEAP_SORT(arr, n);

    printArray(arr, n);
  }