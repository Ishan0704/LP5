#include<iostream>
#include<vector>
#include<omp.h>
#include<set>
#include<ctime>
#include<queue>

using namespace std;

class graph
{
    int vertices;
    vector<vector<int>> adjlist;
    
    public:
    
        graph(int v)
        {
            vertices = v;
            adjlist.resize(v);
        }
    
        void ramdom_edges()
        {
            srand(time(0));
            
            set<pair<int,int>>edges;
            
            int e = vertices*(vertices-1);
            
            for(int i=0;i<e;i++)
            {
                int src = rand()%vertices;
                int dest = rand()%vertices;
                
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
            for(int i=0 ;i<vertices ;i++)
            {
                cout<< i <<" -> ";
                for(int j: adjlist[i])
                {
                    cout<<j<<" -> ";
                }
                cout<<endl;
            }
        }
        
        void bfs(int start)
        {
            vector<bool>visited(vertices, false);
            queue<int>q;
            
            visited[start] = true;
            q.push(start);
            
            cout<<"BFS : ";
            while(!q.empty())
            {
                int current = q.front();
                q.pop();
                
                cout<<current<<",";
                
                for(int neighbour : adjlist[current])
                {
                    if(!visited[neighbour])
                    {
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }
        }
        
        void bfs_parallel(int start)
        {
            vector<bool>visited(vertices, false);
            queue<int>q;
            
            visited[start] = true;
            q.push(start);
            
            cout<<endl<<"BFS for parallel :";
            while(!q.empty())
            {
                int current = q.front();
                q.pop();
                
                cout<<current<<",";
                
                #pragma omp parallel for
                for(int neighbour : adjlist[current])
                {
                    if(!visited[neighbour])
                    {
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }
            
        }
};

int main()
{
    int v;
    cout<<"Enter number of vertices :";c
    cin>>v;
    
    graph g(v);
    g.ramdom_edges();
    g.display();
    g.bfs(0);
    g.bfs_parallel(0);
}