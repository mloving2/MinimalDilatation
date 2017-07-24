//
//  main.cpp
//  DepthFirstTest
//
//  Created by Marissa Loving on 7/3/17.
//  Copyright © 2017 Marissa Loving. All rights reserved.
//


#include<iostream>
#include <fstream>
#include<list>
#include<vector>
#include <string>
#include <stack>

using namespace std;


// Graph class represents a directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    vector<pair<int,vector<int>>> *adj2;
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w, vector<int>); // function to add an edge to graph
    void iterativeDFS(int v);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    adj2 = new vector<pair<int,vector<int>>>[V];
}

void Graph::addEdge(int v, int w, vector<int> M)
{
    adj[v].push_back(w);
    adj2[v].push_back(make_pair(w, M));
    
}

void Graph::iterativeDFS(int v){
    stack<int> S;
    vector<bool> Visited(V, false);
    
    S.push(v);
    
    while(!S.empty()){
        v = S.top();
        S.pop();
        if(Visited[v] == false){
            cout << v << " ";
            Visited[v] = true;
        }
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!Visited[*i])
                S.push(*i);
    }
}

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
            
            vector<int> M;
            
            for(int j = 0; j < uniqueVertices.size(); j++){
                if(uniqueVertices[j] == adjacentVertex){
                    tV = j;
                }
                if(uniqueVertices[j] == firstVertex){
                    iV = j;
                }
            }
            
            for (int i = 0; i < adjacentMatrix.size();i++){
                if (adjacentMatrix[i] == '1'){
                    M.push_back(1);
                }
                if (adjacentMatrix[i] == '0'){
                    M.push_back(0);
                }
            }

            
            infile >> firstVertex;
            infile >> adjacentVertex;
            getline(infile, adjacentMatrix);
            
            
            scratchGraph.addEdge(iV, tV, M);
            
        }
    }
    
    infile.close();
    
    
    return 0;
}