#include"graph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<queue>
typedef char vertex_data_type;
typedef int edge_data_type;
typedef Graph<vertex_data_type, edge_data_type> graph_type;
typedef typename graph_type::Vertex vertex_type;
int main(int argc, char const *argv[])
{
    std::string fname = "data.txt";
    graph_type g;
    if( not g.load(fname))
    return 1;
    g.finalized();
    std::cout<<"graph info:"<<std::endl<<g.num_vertices()<<"\t"<<g.num_edges()<<std::endl;
    for(auto& e : g.vertices)
    {
        e='0';
    }
    std::queue<vid_type> q;
    q.push(0);
    while( not q.empty())
    {
        vid_type  top = q.front();
        vertex_type v = g.get_vertex(top);        
        if( g.vertices[top] == '0')
            std::cout<<v.invid<<"#"<<v.vid<<std::endl;
        for(auto e : g.out_edges(v.vid))
        {
            if( g.vertices[e.first] == '0')
                q.push(e.first);
        }
        for(auto e : g.in_edges(v.vid))
        {
            if( g.vertices[e.first] == '0')
                q.push(e.first);
        }    
        g.vertices[top]='1';
        q.pop();
    }

    
    return 0;
}