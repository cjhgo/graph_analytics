#include"graph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>

typedef int vertex_data_type;
typedef int edge_data_type;
typedef Graph<vertex_data_type, edge_data_type> graph_type;
typedef typename graph_type::Vertex vertex_type;
int main(int argc, char const *argv[])
{
    std::string fname = "data.txt";
    graph_type g;
    g.load(fname);
    g.finalized();
    vertex_type v = g.get_vertex(0);
    std::cout<<v.invid<<"#"<<v.vid<<"\n--->"<<std::endl;
    for(auto e : g.out_edges(v.vid))
    {
        std::cout<<e.first<<"\t";
    }
    std::cout<<std::endl<<v.invid<<"#"<<v.vid<<"\n<---"<<std::endl;    
    for(auto e : g.in_edges(v.vid))
    {
        std::cout<<e.first<<"\t";
    }    
    std::cout<<std::endl<<g.num_vertices()<<"\t"<<g.num_edges()<<std::endl;
    return 0;
}