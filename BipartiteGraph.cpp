#include"graph.hpp"
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<queue>
typedef enum{ WHITE,GRAY,BLACK } COLOR;
typedef enum{ RED,BLUE,GREEN } PARTITE;
typedef struct{ COLOR color; PARTITE partite;} vertex_data_type;
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
        ele.color=WHITE;
        ele.partite=GREEN;
    }
    std::queue<vid_type> q;
    size_t vid = 0;
    if( argc >= 3) vid = std::atoi(argv[2]);
    q.push(vid);
    g.vertices[vid].color=GRAY;
    g.vertices[vid].partite=RED;
    for(auto e : g.out_edges(vid))g.vertices[e.first].partite=BLUE;
    for(auto e : g.in_edges(vid))g.vertices[e.first].partite=BLUE;
    size_t cnt = 0;
    while( not q.empty())
    {
        vid_type  top = q.front();
        vertex_type v = g.get_vertex(top);        
        std::cout<<v.invid<<std::endl;        
        ++cnt;            
        for(auto e : g.out_edges(v.vid))
        {
            if( g.vertices[e.first].color == WHITE)
            {
                q.push(e.first);
                g.vertices[e.first].color=GRAY;
            }                
            PARTITE& ep=g.vertices[e.first].partite,tp=g.vertices[top].partite;
            if( ep==GREEN )
                ep=PARTITE(1-tp);
            else if(ep == tp)
                return 1;
        }
        for(auto e : g.in_edges(v.vid))
        {
            if( g.vertices[e.first].color == WHITE)
            {
                q.push(e.first);
                g.vertices[e.first].color=GRAY;
            }
            PARTITE& ep=g.vertices[e.first].partite,tp=g.vertices[top].partite;
            if( ep==GREEN )
                ep=PARTITE(1-tp);
            else if(ep == tp)
                return 1;
        }    
        g.vertices[top].color=BLACK;
        q.pop();     
    }
    std::cout<<cnt<<"\t"<<g.num_vertices()<<std::endl;
    
    return 0;
}