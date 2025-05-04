#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>
#include<chrono>

using namespace std;
using namespace chrono;

void bubblesort(vector<int>& arr)
{
    
    for(int i=0;i<arr.size();i++)
    {
        #pragma omp parallel for
        for(int j=i+1 ;j<arr.size() ;j++)
        {
            if(arr[i]>arr[j])
            
            {
                swap(arr[i],arr[j]);
            }
        }
    }
}

void bubble_sort(vector<int>& arr)
{
    for(int i=0;i<arr.size();i++)
    {
        for(int j=i; j<arr.size() ;j++)
        {
            if(arr[j]<arr[i])
            {
                swap(arr[i],arr[j]);
            }
        }
    }
}
int main()
{
    int n;
    cout<<"Enter numbers for random generation : ";
    cin>>n;
    
    srand(time(0));
    
    vector<int>arr(n);
    
    for(int i=0;i<n;i++)
    {
        arr[i] = rand() %100 +1;   
    }
    
    cout<<"Original Array :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    
    vector<int> arr2 =arr; 
    
    auto start = high_resolution_clock::now(); 
    
    bubblesort(arr);
    
    auto stop = high_resolution_clock::now();
    
    
    cout<<endl<<"Sorted Array :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    
    auto duration = duration_cast<milliseconds>(stop-start);
    
    cout<<endl<<"Duration :" << duration.count() << " Milliseconds for parallel bubble sort";
    
    auto start2 = high_resolution_clock::now();
    bubble_sort(arr2);
    auto stop2 = high_resolution_clock::now();
    
    auto duration2 = duration_cast<milliseconds>(stop2-start2);
    
    cout<<endl<<"Duration :"<<duration2.count()<< "Milliseconds";
    
    return 0;
}