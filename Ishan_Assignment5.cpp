#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>
#include<chrono>

using namespace std;
using namespace chrono;


void merge(vector<int>&arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    vector<int>left(n1),right(n2);
    
    for(int i=0 ;i<n1 ;i++)
    {
        left[i] = arr[low + i];
    }
    for(int i=0;i<n2;i++)
    {
        right[i] = arr[mid + 1 + i];
    }
    
    int i=0;int j=0; int k=low;
    
    while(i<n1 && j<n2)
    {
        if(left[i]<right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i<n1)
    {
        arr[k] = left[i];
        k++;
        i++;
    }
     
    while(j<n2)
    {
        arr[k] = right[j];
        k++;
        j++;
    }
}

void merge_sort(vector<int>&arr, int low, int high)
{
    if(low<high)
    {
        int mid = low + (high-low)/2;
        
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        
        merge(arr,low, mid, high);
    }
}

void Merge(vector<int>&arr, int low, int mid ,int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    vector<int>left(n1),right(n2);
    
    for(int i=0;i<n1;i++)
    {
        left[i] = arr[low+i];
    }
    for(int i=0;i<n2;i++)
    {
        right[i] = arr[mid + 1 +i];
    }
    
    int i=0;int j=0; int k=low;
    
    while(i<n1 && j<n2)
    {
        if(left[i]<right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i<n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    
    while(j<n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallel_merge_sort(vector<int>&arr, int low, int high)
{
    if(low<high)
    {
        int mid = low + (high-low)/2;
        
        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_merge_sort(arr,low,mid);
            
            #pragma omp section
            parallel_merge_sort(arr,mid+1,high);
        }
        
        Merge(arr,low,mid,high);
    }
}
int main()
{
    int n;
    cout<<"Enter number of elements to be generated randomly:";
    cin>>n;
    
    srand(time(0));
    vector<int>arr(n);
    
    for(int i=0;i<n;i++)
    {
        arr[i] = rand()%100+1;
    }
    
    vector<int>arr2 = arr;
    
    cout<<"Original array :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    
    auto start1 = high_resolution_clock::now();
    merge_sort(arr,0,n-1);
    auto stop1 = high_resolution_clock::now();
    
    auto duration1 = duration_cast<milliseconds>(stop1-start1);
    
    cout<<endl<<"Sorted array :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"Duration of normal merge sort is :"<<duration1.count()<<" ms";
    
    
    auto start2 = high_resolution_clock::now();
    parallel_merge_sort(arr2,0,n-1);
    auto stop2 = high_resolution_clock::now();
    
    auto duration2 = duration_cast<milliseconds>(stop2-start2);
    
    cout<<endl<<"Duration of parallel merge sort is :"<<duration2.count()<<" ms";
    
    return 0;
}