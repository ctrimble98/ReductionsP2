import random

for i in range(1, 51):

    nodes = 5*i
    f = open("growingNodes/" + str(format(nodes, '04d')) + "-nodes.col", "w")
    f.write("p edge " + str(nodes) + " 1\n")
    f.write("colours 3\n")
    f.write("e 1 2\n")

    edges = 25*i
    currentEdges = set()
    f = open("growingEdges/" + str(format(edges, '04d')) + "-edges.col", "w")
    f.write("p edge 50 " + str(edges) + "\n")
    f.write("colours 3\n")
    while len(currentEdges) < edges:
        s = random.randint(1,51)
        e = random.randint(1,51)
        if (s != e):
            cand_edge = (s,e)
            if s > e:
                cand_edge = (e,s)
            if (cand_edge not in currentEdges):
                currentEdges.add(cand_edge)
                f.write("e " + str(cand_edge[0]) + " " + str(cand_edge[1]) + "\n")
