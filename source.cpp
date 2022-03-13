#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}


void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}


void heapify(int arr[], int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void countSort(int arr[], int n, int exp)
{
    int* output = new int[1000000]; 
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[500000];
    int* R = new int[500000];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;

    int j = 0;

    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete L;
    delete R;
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

static void bucketSort(int* data, int count) {
    int minValue = data[0];
    int maxValue = data[0];
    for (int i = 1; i < count; i++)
    {
        if (data[i] > maxValue)
            maxValue = data[i];
        if (data[i] < minValue)
            minValue = data[i];
    }
    int bucketLength = maxValue - minValue + 1;
    vector<int>* bucket = new vector<int>[bucketLength];
    for (int i = 0; i < bucketLength; i++)
    {
        bucket[i] = vector<int>();
    }
    for (int i = 0; i < count; i++)
    {
        bucket[data[i] - minValue].push_back(data[i]);
    }
    int k = 0;
    for (int i = 0; i < bucketLength; i++)
    {
        int bucketSize = bucket[i].size();
        if (bucketSize > 0)
        {
            for (int j = 0; j < bucketSize; j++)
            {
                data[k] = bucket[i][j];
                k++;
            }
        }
    }
}

int main()
{
    ifstream input;
    input.open("D:\\C++\\datasort.txt");
    int* arr = new int[10000];

    int size = 0;

    clock_t clkStart;
    clock_t clkFinish;

    while (!input.eof())
    {
        input >> arr[size++];
    }
    clkStart = clock();
    //Uncomment the algorithm you want to use
//    selectionSort(arr, size);
//    mergeSort(arr, 0, size - 1);
//    quickSort(arr, 0, size - 1);
//    heapSort(arr, size);
//    radixsort(arr, size);
//    bucketSort(arr,size);

    clkFinish = clock();

    cout << endl << clkFinish - clkStart << " ms" << endl;
    input.close();
    delete arr;
    return 0;
}
