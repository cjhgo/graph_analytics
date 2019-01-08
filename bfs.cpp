#include"graph.hpp"
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<queue>
typedef char vertex_data_type;
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
    for(auto& e : g.vertices)
    {
        e='0';
    }
    std::queue<vid_type> q;
    if( argc >= 3)
        q.push(std::atoi(argv[2]));
    else
        q.push(0);
    std::set<vid_type> inserted;
    size_t cnt = 0;
    while( not q.empty())
    {
        vid_type  top = q.front();
        vertex_type v = g.get_vertex(top);        
        if( g.vertices[top] == '0')
        {
            ++cnt;
            //std::cout<<v.invid<<"#"<<v.vid<<std::endl;
            std::cout<<v.invid<<std::endl;
        }            
        for(auto e : g.out_edges(v.vid))
        {
            if( g.vertices[e.first] == '0' and inserted.find(e.first) == inserted.end())
            {
                q.push(e.first);
                inserted.insert(e.first);
            }                
        }
        for(auto e : g.in_edges(v.vid))
        {
            if( g.vertices[e.first] == '0' and inserted.find(e.first) == inserted.end())
            {
                q.push(e.first);
                inserted.insert(e.first);
            }
        }    
        g.vertices[top]='1';
        q.pop();
        //std::cout<<"\n----"<<cnt*1.0/g.num_vertices()<<"----"<<std::endl;        
    }
    std::cout<<cnt<<"\t"<<g.num_vertices()<<std::endl;
    
    return 0;
}