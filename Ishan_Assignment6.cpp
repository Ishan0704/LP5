#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>
#include<chrono>

using namespace std;
using namespace chrono;

int part(vector<int>&arr, int low, int high)
{
    int pivot = arr[high];
    int i=low-1;
    
    for(int j=low ;j<high ;j++)
    {
        if(arr[j]<=pivot)
        {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void quicksort(vector<int>&arr, int low , int high)
{
    if(low<high)
    {
        int partation = part(arr,low,high);
        quicksort(arr,low, partation-1);
        quicksort(arr,partation+1,high);
    }
}

int partition(vector<int>&arr, int low, int high)
{
    int pivot = arr[high];
    int i = low-1;
    
    for(int j=low; j<high ;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void parallelquicksort(vector<int>&arr, int low, int high)
{
    if(low<high)
    {
        int part = partition(arr,low,high);
        #pragma omp parallel section
        {
            #pragma omp section
            parallelquicksort(arr, low, part-1);
            
            #pragma omp section
            parallelquicksort(arr,part+1,high);
        }
        
        
    }
}

int main()
{
    int n;
    cout<<"Enter number of random generation :";
    cin>>n;
    
    srand(time(0));
    
    vector<int> arr(n);
    
    for(int i=0;i<n;i++)
    {
        arr[i] = rand() %100 +1;
    }
    
    vector<int>arr2 = arr;
    
    cout << "Original Array :" <<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    
    auto start1 = high_resolution_clock::now();
    
    quicksort(arr,0,n-1);
    
    auto stop1 = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop1-start1);
    
    cout <<endl<< "Sorted Array :" <<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    
    cout <<endl<<"Duration for normal quick sort :" << duration.count()<<" ms";
    
    auto start2 = high_resolution_clock::now();
    
    parallelquicksort(arr2,0,n-1);
    
    auto stop2 = high_resolution_clock::now();
    
    auto duration2 = duration_cast<milliseconds>(stop2 -stop1);
    
    cout <<endl<<"Duration for parallel quick sort :" << duration2.count()<<" ms";
    return 0;
}