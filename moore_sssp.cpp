#include"graph.hpp"
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<queue>
typedef enum{ WHITE,GRAY,BLACK } vertex_data_type;
typedef int edge_data_type;
typedef Graph<vertex_data_type, edge_data_type> graph_type;
typedef typename graph_type::Vertex vertex_type;
int main(int argc, char const *argv[])
{
    std::string fname = "data.txt";
    if( argc > 1)
    fname =  std::string(argv[1]);
    graph_type g;
    if( not g.load(fname))
    {
        std::cout<<"load error\n";
        return 1;
    }    
    g.finalized();
    std::cout<<"graph info:"<<std::endl<<g.num_vertices()<<"\t"<<g.num_edges()<<std::endl;
    for(auto& ele : g.vertices)
    {
        ele=WHITE;
    }
    std::queue<vid_type> q;
    size_t vid = 0;
    if( argc >= 3) vid = std::atoi(argv[2]);
    q.push(vid);
    g.vertices[vid]=GRAY;
    size_t cnt = 0;
    while( not q.empty())
    {
        vid_type  top = q.front();
        vertex_type v = g.get_vertex(top);        
        std::cout<<v.invid<<std::endl;        
        ++cnt;            
        for(auto e : g.out_edges(v.vid))
        {
            if( g.vertices[e.first] == WHITE)
            {
                q.push(e.first);
                g.vertices[e.first]=GRAY;
            }                
        }
        for(auto e : g.in_edges(v.vid))
        {
            if( g.vertices[e.first] == WHITE)
            {
                q.push(e.first);
                g.vertices[e.first]=GRAY;
            }
        }    
        g.vertices[top]=BLACK;
        q.pop();     
    }
    std::cout<<cnt<<"\t"<<g.num_vertices()<<std::endl;
    
    return 0;
}