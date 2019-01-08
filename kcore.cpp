#include"graph.hpp"
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<map>
int main(int argc, char const *argv[])
{
    std::string fname = "data/out.txt";
    Graph<int,int> g;

    if( not g.load(fname))
    {
        std::cout<<"load error\n";
        return 1;
    }
    g.finalized();

    for(size_t i = 0; i < g.num_vertices(); i++)
    {           
        g.vertices[i]=g.in_edges(i).size()+g.out_edges(i).size();
    }
    size_t sum = 0;
    for(auto& e : g.vertices)
    {
        std::cout<<e<<"\t";
        sum += e;
    }
    std::cout<<sum/2<<std::endl;
    std::cout<<g.num_vertices()<<"\t"<<g.num_edges()<<std::endl;    
    int k = 4;
    bool breakflag;
    while(true)
    {
        breakflag=true;
        for(size_t i = 0; i < g.num_vertices(); i++)
        {
            if( g.vertices[i] > 0)
            {
                if( g.vertices[i] < k)
                {
                    for(auto e: g.in_edges(i))
                    {
                        vid_type s = e.first;
                        eid_type eid = e.second;
                        g.vertices[s]--;
                        g.edge_buffer.edata[eid]=-1;
                    }
                    for(auto e: g.out_edges(i))
                    {
                        vid_type t = e.first;
                        eid_type eid = e.second;
                        g.vertices[t]--;
                        g.edge_buffer.edata[eid]=-1;
                    }
                    g.vertices[i]=-1;
                    breakflag=false;
                }
            }
        }
        if(breakflag)break;
    }
    size_t cnt = 0;
    for(size_t i = 0; i < g.num_edges(); i++)
    {
        if( g.edge_buffer.edata[i] != -1)
        {
            std::cout<<g.edge_buffer.source[i]<<", "<<g.edge_buffer.target[i]<<"\n";
            cnt++;
        }
    }
    std::cout<<cnt<<std::endl;
    return 0;
}
