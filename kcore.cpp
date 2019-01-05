#include"graph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>
int main(int argc, char const *argv[])
{
    std::string fname = "data.txt";
    Graph<int,int> g;
    g.load(fname);
    g.finalized();
    std::cout<<g.num_vertices()<<"\t"<<g.num_edges()<<std::endl;
    return 0;
}