#!/bin/bash
> growingNodes.csv
i=0
nodes=()
echo Testing Growing Nodes
printf "Start Nodes, Start Edges, Start Colours, Nodes, Edges, Colours" | paste -sd ',' >> growingNodes.csv
for filename in ./growingNodes/*-nodes.col
do
    nodes[i]=$(../src/circularreduction Test < $filename | sed -n 2p)
    printf "%s" "${nodes[i]}" | paste -sd ',' >> growingNodes.csv
    i=$(($i + 1))
done

> growingEdges.csv
i=0
nodes=()
echo Testing Growing Edges
printf "Start Nodes, Start Edges, Start Colours, Nodes, Edges, Colours" | paste -sd ',' >> growingEdges.csv
for filename in ./growingEdges/*-edges.col
do
    nodes[i]=$(../src/circularreduction Test < $filename | sed -n 2p)
    printf "%s" "${nodes[i]}" | paste -sd ',' >> growingEdges.csv
    i=$(($i + 1))
done

> growingBoth.csv
i=0
nodes=()
echo Testing Growing Nodes and Edges
printf "Start Nodes, Start Edges, Start Colours, Nodes, Edges, Colours" | paste -sd ',' >> growingBoth.csv
for filename in ./growingBoth/*-nodes-and-edges.col
do
    nodes[i]=$(../src/circularreduction Test < $filename | sed -n 2p)
    printf "%s" "${nodes[i]}" | paste -sd ',' >> growingBoth.csv
    i=$(($i + 1))
done
