#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>

using namespace std;

vector<vector<int>> multiply(vector<vector<int>>&matrix1, vector<vector<int>>&matrix2)
{
    
    int row = matrix1.size();
    int column = matrix1[0].size();
    
    vector<vector<int>>result(row, vector<int>(column));
    
    #pragma omp parallel for collapse(2)
     for(int i=0;i< row; i++)
     {
         for(int j=0;j<column ;j++)
         {
             result[i][j] = 0;
             for(int k=0;k<column;k++)
             {
                 result[i][j] += matrix1[i][k] * matrix2[k][j];
             }
         }
     }
     return result;
}
int main()
{
    int row,column;
    cout<<"Enter Number of rows : ";
    cin>>row;
    cout<<"Enter number of column : ";
    cin>>column;
    
    vector<vector<int>> matrix1(row, vector<int>(column));
    vector<vector<int>> matrix2(row, vector<int>(column));
    
    srand(time(0));
    
    for(int i=0;i<row ;i++)
    {
        for(int j=0;j<column ;j++)
        {
            matrix1[i][j] = rand()%10+1;
            matrix2[i][j] = rand()%10+1;
        }
    }
    
    cout<< "First randomly generated matrix is :"<<endl;
    
    for(int i=0;i<row ;i++)
    {
        for(int j=0;j<column ;j++)
        {
            cout<< matrix1[i][j] << " ";
        }
        cout<<endl;
    }
    
    cout<< "Secondly randomly generated matrix is :"<<endl;
    
    for(int i=0;i<row ;i++)
    {
        for(int j=0;j<column ;j++)
        {
            cout<< matrix2[i][j] << " ";
        }
        cout<<endl;
    }
    
    vector<vector<int>>result = multiply(matrix1, matrix2);
    
    cout<< "Result of matrix multiplication is :"<<endl;
    
    for(int i=0;i<row ;i++)
    {
        for(int j=0;j<column ;j++)
        {
            cout<< result[i][j] << " ";
        }
        cout<<endl;
    }
        
    return 0;
}