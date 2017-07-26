//
//  main.cpp
//  TestCode
//
//  Created by Marissa Loving on 7/23/17.
//  Copyright © 2017 Marissa Loving. All rights reserved.
//

#include<iostream>
#include <fstream>
#include<list>
#include<vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;


// Graph class represents a directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    vector<pair<int,pair<vector<int>,char>>> *adj2;
    void DFSUtil(int v, bool visited[], list<int>& tree, list<int>& pre);  // A function used by DFS
    void DFS(int v, list<int>& tree, list<int>& pre);    // DFS traversal of the vertices reachable from v
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w, vector<int> M, char type); // function to add an edge to graph
    void cycle(int v);
    int find(vector<int> arr, int len, int seek);
    void printlist(list<int> A);
    int getNumOfVertices();
    
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    adj2 = new vector<pair<int,pair<vector<int>, char>>>[V];
}

void Graph::addEdge(int v, int w, vector<int> M, char type)
{
    adj[v].push_back(w);
    adj2[v].push_back(make_pair(w, make_pair(M,type)));
    
}

int Graph::find(vector<int> arr, int len, int seek)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == seek) return i;
    }
    return -1;
}


//finds cycles using depth first traversal from vertex v
//currently does not store or print cycles because we need
//a way to only store unique cycles and weed out cyclic shifts
void Graph::cycle(int v)
{
    
    list<int> tree;
    list<int> pre;
    DFS(v, tree, pre);
    
    vector<int> Tree;
    list<int>::const_iterator Li;
    for (Li = tree.begin(); Li != tree.end(); ++Li)
    {
        Tree.push_back(*Li);
       
    }
    
    vector<int> Pre;
    list<int>::const_iterator Li1;
    for (Li1 = pre.begin(); Li1 != pre.end(); ++Li1)
    {
        Pre.push_back(*Li1);
        
    }
    /*
    cout<<"\n print the tree \n";
    
    for(int i =0;i<Tree.size();i++)
        cout<<Tree[i]<<'\t';
    cout<<"\n print the pre \n";
    
    for(int i =0;i<Pre.size();i++)
        cout<<Pre[i]<<'\t';
    */

    for(int j = 2;j<tree.size();j++)
    {
        int l =j;
        int count = 0;
        list<int> path;
        for (auto i = adj[Tree[j]].begin(); i != adj[Tree[j]].end(); ++i)
        {
            for(int k=0;k<j;k++)
                if(Tree[k]==*i)
                {
                    path.push_front(Tree[l]);
                   // cout<<"\n index : "<< j << "\n";
                    while(l>k){
                        path.push_front(Pre[l]);
                        l = find(Tree,l,Pre[l]);
                        
                    }
                    
                    //cout<<"print cycle: \n";
                    //printlist(path);
                }
            
            count++;
            
        }
        
    }
    
    
    
    
    
}

void Graph::DFSUtil(int v, bool visited[], list<int>& tree, list<int>& pre)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    tree.push_back(v);
    
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            pre.push_back(v);
            DFSUtil(*i, visited, tree, pre);
            
        }
    }
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v, list<int>& tree, list<int>& pre)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // Call the recursive helper function to print DFS traversal
    pre.push_back(v);
    DFSUtil(v, visited, tree, pre);
    
}

void Graph::printlist(list<int> A) {
    list<int>::const_iterator Li;
    for ( Li = A.begin(); Li != A.end(); Li++) {
        cout << *Li << "  ";
    }
    cout << endl;
}

int Graph::getNumOfVertices(){
    return V;
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
    
    infile.open("/Users/marissaloving/Downloads/scratchcomplete.txt");
    
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
    
    infile.open("/Users/marissaloving/Downloads/scratchcomplete.txt");
    
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
            char edgeType = 'B';
            
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
                if (adjacentMatrix[i] == 'A'){
                    edgeType = 'A';
                    
                }
            }
            
            
            infile >> firstVertex;
            infile >> adjacentVertex;
            getline(infile, adjacentMatrix);
            
            
            scratchGraph.addEdge(iV, tV, M, edgeType);
            
        }
    }
    

    infile.close();
    
    for(int i = 0; i < scratchGraph.getNumOfVertices(); i++){
        scratchGraph.cycle(i);
    }

    
    return 0;
}