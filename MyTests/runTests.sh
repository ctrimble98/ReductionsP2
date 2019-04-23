#!/bin/bash
> growingNodes.csv
i=0
nodes=()
echo Testing Growing Nodes
printf "Start Nodes, Nodes, Edges, Colours" | paste -sd ',' >> growingNodes.csv
for filename in ./growingNodes/*-nodes.col
do
    nodes[i]=$(../src/circularreduction < $filename | sed -n 2p)
    printf "%s,%s" "$filename" "${nodes[i]}" | paste -sd ',' >> growingNodes.csv
    i=$(($i + 1))
done

> growingEdges.csv
i=0
nodes=()
echo Testing Growing Edges
printf "Start Nodes, Nodes, Edges, Colours" | paste -sd ',' >> growingEdges.csv
for filename in ./growingEdges/*-edges.col
do
    nodes[i]=$(../src/circularreduction < $filename | sed -n 2p)
    printf "%s,%s" "$filename" "${nodes[i]}" | paste -sd ',' >> growingEdges.csv
    i=$(($i + 1))
done
