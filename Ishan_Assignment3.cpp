#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>

using namespace std;

int parallelsum(vector<int>&arr)
{
    int sum=0;
    #pragma omp parallel for reduction (+:sum)
    for(int i=0;i<arr.size();i++)
    {
        sum += arr[i];   
    }
    return sum;
}


int min_no(vector<int>&arr)
{
    int min_value = arr[0];
    #pragma omp parallel for reduction(min:min_value)
    for(int i=1;i<arr.size();i++)
    {
        if(arr[i]<min_value)
        {
            min_value = arr[i];
        }
    }
    return min_value;
}

int max_no(vector<int>&arr)
{
    int max_value = arr[0];
    
    #pragma omp parallel for reduction (max: max_value)
    for(int i=1;i<arr.size();i++)
    {
        if(arr[i]>max_value)
        {
            max_value = arr[i];
        }
    }
    return max_value;
}

double average(vector<int>&arr)
{
    int sum = 0;
    #pragma omp parallel for reduction (+:sum)
    for(int i=0;i<arr.size();i++)
    {
        sum += arr[i];
    }
    
    return (double)sum/arr.size();
}

int main()
{
    
    int n;
    cout<<"Enter number ofr random generation :";
    cin>>n;
    
    srand(time(0));
    
    vector<int>arr(n);
    for(int i=0 ;i<n;i++)
    {
        arr[i] = rand()%100+1;
    }
    
    cout<<"Original array :";
    
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";   
    }
    
    int sum = parallelsum(arr);
    cout<<endl<<"Parallel sum :" << sum;
    
    int min = min_no(arr);
    cout<<endl<<"Min number is :"<< min;
    
    int max = max_no(arr);
    cout<<endl<<"Max number is :" << max;
    
    double avg = average(arr);
    cout<<endl<<"Average is :"<<avg;
    
    return 0;
}