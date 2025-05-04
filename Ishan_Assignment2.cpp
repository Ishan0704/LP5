#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>
#include<set>

using namespace std;

class graph
{
    
    public:
    
    int vertices;
    vector<vector<int>>adjlist;
    vector<bool>visited;
    
    graph(int v)
    {
        vertices = v;
        adjlist.resize(v);
        visited.resize(vertices, false);
    }
   
    void random_edges()
    {
	    srand(time(0));
	    
	    set<pair<int,int>>edges;
	    
	    int e = vertices*(vertices-1)/2;
	    
	    for(int i=0;i<e;i++)
	    {
	        int src = rand() % vertices ;
	        int dest = rand() % vertices;
	        
	        if(src != dest)
	        {
	            pair<int,int> edge = {min(src,dest),max(src,dest)};
	            
	            if(edges.find(edge) == edges.end())
	            {
	                edges.insert(edge);
	                adjlist[src].push_back(dest);
	                adjlist[dest].push_back(src);
	            }
	        }
	    }
    }
    
    void display()
    {
        for(int i=0;i<vertices;i++)
        {
            cout<< i <<"->";
            for(int j : adjlist[i])
            {
                cout<<j<<"->";
            }
            cout<<endl;
        }
    }
    
    void dfs(int start)
    {
        visited[start] = true;
        cout<<start<<"->";
        
        for(int neighbour : adjlist[start])
        {
            if(!visited[neighbour])
            {
                dfs(neighbour);
            }
        }
    }
    
};

int main()
{
    int v;
    cout<<"Enter number of vertices : ";
    cin>>v;
    
    graph g(v);
    g.random_edges();
    g.display();
    cout<<"DFS :";
    g.dfs(0);
    return 0;
}