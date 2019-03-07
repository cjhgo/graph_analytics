#include"graph.hpp"
#include<cstdlib>
#include<limits>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<queue>
typedef enum{ WHITE,GRAY,BLACK } Color;
struct vertex_data 
{
  Color color;
  vertex_data(Color color = WHITE) : color(color) { }
}; // end of vertex data
typedef float distance_type;
struct edge_data
{
  distance_type weight;
  edge_data(distance_type weight = 1) : weight(weight) { }
}; // end of edge data
typedef Graph<vertex_data, edge_data> graph_type;
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
    std::vector<uint64_t> dist(g.num_vertices(), std::numeric_limits<uint64_t>::max());
    vid_type source = 3;    
    std::queue<vid_type> active_v;
    dist[source]=0;
    g.vertices[source].color=GRAY;
    active_v.push(source);

    while(not active_v.empty())
    {
        vid_type  top = active_v.front();
        std::cout<<"processing top!"<<top<<std::endl;
        vertex_type v = g.get_vertex(top);        
        for(auto e : g.out_edges(v.vid))
        {
            vid_type v_out=e.first;
            distance_type new_d = dist[top]+1;
            if( new_d < dist[v_out])
            {                
                dist[v_out]=new_d;
                if(g.vertices[v_out].color!=GRAY)
                {
                    active_v.push(v_out);
                    g.vertices[v_out].color=GRAY;
                }
            }
        }
        for(auto e : g.in_edges(v.vid))
        {
            vid_type in_v=e.first;
            distance_type new_d = dist[top]+1;
            if( new_d < dist[in_v] )            
            {                
                dist[in_v]=new_d;
                if(g.vertices[in_v].color!=GRAY)
                {
                    active_v.push(in_v);
                    g.vertices[in_v].color=GRAY;                    
                }
            }

        }    
        g.vertices[top]=BLACK;
        active_v.pop();     
    }
    
    for(size_t i = 0; i < dist.size();i++)
    {
        std::cout<<dist[i]<<"\t";
        if( i % 5 == 0)
        std::cout<<std::endl;
    }
    return 0;
}