from sys import argv
fname="data/out.txt"
if( len(argv) > 1 ):
    fname=argv[1]

import networkx as nx
f=open(fname)

data=[]
for line in f:
    s,t=map(int,line[:-1].split(','))
    data.append((s,t))
G=nx.Graph()
G.add_edges_from(data)
from networkx import k_core
res=k_core(G,4)
print len(res.edges())
print len(res.nodes())
for e in res.edges():
    print str(e)[1:-1]