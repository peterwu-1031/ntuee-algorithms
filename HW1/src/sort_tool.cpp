// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i=1; i<data.size(); i++) {
            int key = data[i];
            int j = i-1;
            while(j>=0 && data[j]>key) {
                data[j+1] = data[j];
                j--;
            }
            data[j+1] = key;
        }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high) {
        int partition = Partition(data, low, high);
        QuickSortSubVector(data, low, partition-1);
        QuickSortSubVector(data, partition+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    srand(time(NULL));
    int r = low+rand()%(high-low+1);
    swap(data[high], data[r]);
    int pivot = data[high];
    int i = low-1;
    for(int j=low; j<high; j++) {
        if(data[j]<=pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    data[high] = data[i+1];
    data[i+1] = pivot;
    return (i+1);
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high) {
        int mid = (low+high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n_left = middle1-low+1;
    int n_right = high-middle2+1;
    int left[n_left+1];
    int right[n_right+1];
    for(int i=0; i<n_left; i++) {
        left[i] = data[low+i];
    }
    for(int i=0; i<n_right; i++) {
        right[i] = data[middle2+i];
    }
    left[n_left] = 1000001;
    right[n_right] = 1000001;
    int i = 0;
    int j = 0;
    for(int k=low; k<=high; k++) {
        if(left[i]<=right[j]) {
            data[k] = left[i];
            i++;
        }
        else {
            data[k] = right[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2*root+1;
    int right = left+1;
    int max_index = root;
    if(left<heapSize && data[left]>data[root]) {
        max_index = left;
    }
    if(right<heapSize && data[right]>data[max_index]) {
        max_index = right;
    }
    if(max_index != root) {
        swap(data[root], data[max_index]);
        MaxHeapify(data, max_index);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=(heapSize-2)/2; i>=0; i--) {
        MaxHeapify(data, i);
    }
}
