//
//  main.cpp
//  DepthFirstTest
//
//  Created by Marissa Loving on 7/3/17.
//  Copyright © 2017 Marissa Loving. All rights reserved.
//


// C++ program to print DFS traversal from a given vertex in a  given graph
#include<iostream>
#include <fstream>
#include<list>
#include<vector>
#include <string>

using namespace std;


// Graph class represents a directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void DFSUtil(int v, bool visited[]);  // A function used by DFS
    bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void DFS(int v);    // DFS traversal of the vertices reachable from v
    //void Cycle(int v);  //cycle based at v
    bool isCyclic();    // returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
    
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}

// This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
        
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
        
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
    
    return false;
}

/*void Graph::Cycle(int v){
    
}*/



int main()
{
    
    string firstVertex;
    string adjacentVertex;
    string adjacentMatrix;
    vector<string> uniqueVertices;
    vector<int> valenceByVertex;
    int numberOfVertices = 0;
    int m = 1;
    int maxValence = 0;
    
    
    
    // open a file in read mode.
    ifstream infile;
    
    infile.open("/Users/marissaloving/Downloads/scratch.txt");
    
    if (!infile.good())
        return 1; // exit if file not found
    
    
    if (infile.is_open()) {
        
        infile >> firstVertex;
        
        infile >> adjacentVertex;
        
        getline(infile, adjacentMatrix);
        
        uniqueVertices.push_back(firstVertex);
        
        while (!infile.eof()) {
            
            infile >> firstVertex;
            
            infile >> adjacentVertex;
            
            getline(infile, adjacentMatrix);
            
            
            if(firstVertex != uniqueVertices[numberOfVertices]){
                
                uniqueVertices.push_back(firstVertex);
                numberOfVertices++;
                valenceByVertex.push_back(m);
                m = 1;
            }
            else{
                m++;
                if(m > maxValence){
                    maxValence = m;
                }
            }
            
        }
        valenceByVertex.push_back((m-1));
    }
    
    numberOfVertices++;
    
    infile.close();
    
    cout << "Number of vertices: " << numberOfVertices << '\n';
    
    cout << "Maximal Valence: " << maxValence << '\n';
    
    Graph scratchGraph(numberOfVertices);
    
    infile.open("/Users/marissaloving/Downloads/scratch.txt");
    
    if (!infile.good())
        return 1; // exit if file not found
    
    int iV;
    int tV;
    
    if (infile.is_open()) {
        
        infile >> firstVertex;
        infile >> adjacentVertex;
        getline(infile, adjacentMatrix);
        
        while (!infile.eof()){
            
            for(int j = 0; j < uniqueVertices.size(); j++){
                if(uniqueVertices[j] == adjacentVertex){
                    tV = j;
                }
                if(uniqueVertices[j] == firstVertex){
                    iV = j;
                }
            }
            
            infile >> firstVertex;
            infile >> adjacentVertex;
            getline(infile, adjacentMatrix);
            
            //cout << "Initial vertex: " << iV << '\n';
            //cout << "Terminal vertex: " << tV << '\n';
            
            
            scratchGraph.addEdge(iV, tV);
            
        }
    }
    
    infile.close();
    
// output
    
    if(scratchGraph.isCyclic()){
        cout << "Graph contains cycle" << '\n';
    }
    else{
        cout << "Graph doesn't contain cycle" << '\n';
    }
    
    return 0;
}