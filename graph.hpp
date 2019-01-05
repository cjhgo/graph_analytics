#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
typedef size_t vid_type;
typedef size_t eid_type;
typedef std::pair<vid_type, eid_type> value_type;
typedef std::vector<value_type> edge_list_type;

struct csr_storage
{
    std::vector<size_t> values_ptr;
    //std::vector<value_type> values;
    edge_list_type values;
};

template<typename EdgeDataType>
struct Edge_buffer
{
    std::vector<vid_type> source,target;
    std::vector<EdgeDataType> edata;

};
void counting_sort(std::vector<vid_type> input, std::vector<size_t> &permute, 
                    std::vector<vid_type> &prefix_sum, size_t max_value)
{
    if( input.size() < 1) return;
    std::vector<vid_type> counter(max_value);
    for(auto e : input)
    {
        counter[e]++;
    }
    permute.resize(input.size());
    for(int i = input.size()-1; i >= 0; i--)
    {
        vid_type vid = input[i];
        permute[--counter[vid]] = i;
    }
    prefix_sum.resize(counter.size()+1);
    prefix_sum[0]=0;
    for(size_t i = 1; i < prefix_sum.size(); i++)
    {
        vid_type res = prefix_sum[i-1]+counter[i-1];        
        prefix_sum[i]=res;
    }
}
template<typename VertexDataType, typename EdgeDataType>
class Graph 
{
public:   
    
    Graph();
    bool load(std::string fname);
    size_t num_vertices(){return max_vid;};
    size_t num_edges(){return edge_buffer.edata.size();};
    edge_list_type out_edges(vid_type vid);
    edge_list_type in_edges(vid_type vid);


    //template<typename VertexDataType>
    struct Vertex
    {
        Graph& graph_ref;
        vid_type vid, invid;
        Vertex(Graph& graph_ref, vid_type vid):
            graph_ref(graph_ref), vid(vid) 
        { 
            invid=graph_ref.vid_to_invid[vid];
        };
        VertexDataType& data()
        {
            return graph_ref.vertices[vid];
        };
    };
    //template<typename EdgeDataType>
    struct Edge
    {
        eid_type eid;
        EdgeDataType& data();
    };
    Vertex get_vertex(vid_type vid)
    {
        return Vertex(*this, vid);
    };
    Edge get_edge(eid_type eid)
    {
        return Edge();
    };
    void finalized();    
private:
    vid_type transe_vid(vid_type vid);
    bool add_edge(vid_type source, vid_type target, EdgeDataType edata=EdgeDataType() );    
private:
    vid_type max_vid;
    Edge_buffer<EdgeDataType> edge_buffer;
    std::vector<VertexDataType> vertices;
    std::map<vid_type, vid_type> vid_to_invid, invid_to_vid;
    csr_storage csr, csc;
};

template<typename VertexDataType, typename EdgeDataType>
Graph<VertexDataType, EdgeDataType>::Graph():
max_vid(0)
{

}

template<typename VertexDataType, typename EdgeDataType>
bool Graph<VertexDataType, EdgeDataType>::load(std::string fname)
{
    std::ifstream myfile;
    myfile.open(fname);
    std::string line;
    
    vid_type source,target;
    source=target=-1;
    char dot;
    std::stringstream iss;
    //line:23,13
    while(getline(myfile, line))
    {    
        iss<<line;
        if(iss>>source>>dot>>target)
        {
            vid_type _source = transe_vid(source);
            vid_type _target = transe_vid(target);
            add_edge(_source, _target);
        }
        else
            return false;
        iss.str(std::string());
        iss.clear();        
    }
    return true;
}
template<typename VertexDataType, typename EdgeDataType>
vid_type Graph<VertexDataType, EdgeDataType>::transe_vid(vid_type vid)
{
    if(invid_to_vid.find(vid) == invid_to_vid.end())
	{
        invid_to_vid[vid]=max_vid++;		
	}
    return invid_to_vid[vid];
	
}
template<typename VertexDataType, typename EdgeDataType>
bool Graph<VertexDataType, EdgeDataType>::add_edge(vid_type source, vid_type target, EdgeDataType edata)
{
    edge_buffer.source.push_back(source);
    edge_buffer.target.push_back(target);
    edge_buffer.edata.push_back(edata);
}
template<typename VertexDataType, typename EdgeDataType>
void Graph<VertexDataType, EdgeDataType>::finalized()
{
//void counting_sort(std::vector<vid_type> input, std::vector<size_t> &permute, 
//                    std::vector<vid_type> &prefix_sum, size_t max_value)
    std::vector<size_t> permute;
    std::vector<vid_type> prefix_sum;

    counting_sort(edge_buffer.source, permute, prefix_sum, max_vid);

    for(size_t i = 0; i < permute.size(); i++)
    {
        size_t pos = permute[i];
        csr.values.push_back( value_type(
                            edge_buffer.target[pos],pos
                            ));
    }
    csr.values_ptr=prefix_sum;

    counting_sort(edge_buffer.target, permute, prefix_sum, max_vid);
    for(size_t i = 0; i < permute.size(); i++)
    {
        size_t pos = permute[i];
        csc.values.push_back( value_type(
                            edge_buffer.source[pos],pos
                            ));
    }
    csc.values_ptr=prefix_sum;
    for (auto const& x : invid_to_vid)
    {
        vid_type invid=x.first, vid=x.second;
        vid_to_invid[vid]=invid;
    }    
}

template<typename VertexDataType, typename EdgeDataType>
edge_list_type Graph<VertexDataType, EdgeDataType>::out_edges(vid_type vid)
{
    auto begin = csr.values.begin() + csr.values_ptr[vid];
    auto end = csr.values.begin() + csr.values_ptr[vid+1];
    return edge_list_type(begin, end);
}
template<typename VertexDataType, typename EdgeDataType>
edge_list_type Graph<VertexDataType, EdgeDataType>::in_edges(vid_type vid)
{
    auto begin = csc.values.begin() + csc.values_ptr[vid];
    auto end = csc.values.begin() + csc.values_ptr[vid+1];
    return edge_list_type(begin, end);    
}