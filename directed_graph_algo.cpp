
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <limits>
#include <optional>
#include <exception>
#include <stdexcept>

#include "directed_graph.cpp"

using namespace std;


template <typename T>
vector<vertex<T>> shortestpath(directed_graph<T> g, int u_id, int v_id) {
  
    
      // Total cost, stage, weight of previous, vertex
     
      priority_queue<pair<double,int>> q;
  // int *shortest = new int[g.num_vertices()];
    int shortest[g.num_vertices()];
      //vector<vertex<T>> prev;
      vector<vertex<T>> path;
 int parent[2*g.num_vertices()];
    bool visited[g.num_vertices()];
         
   // int *parent = new int[2*g.num_vertices()];
      
     // prev.push_back(u_id);
     // unordered_map<int,vector<vertex<T>>> parent;
    
      for (auto i : g.get_vertices()){
          shortest[i.id] = INT_MAX;
          parent[i.id] = -1;
          visited[i.id] = false;
      }
    
      // Push the source vertex
      q.push( { 0, u_id } );
     visited[u_id] = true;
    
      while (!q.empty()) {
    
          // Take the top element in the queue
          auto FRONT = q.top();
    
          // Remove it from the queue
          q.pop();
    
          
          double weight = FRONT.first;
          int x = FRONT.second;
    
          // Take the minimum cost for the vertex
          //shortest[x] = min(shortest[x], cost);
    
          // If destination vertex has already been visited
          if (shortest[v_id] != INT_MAX) break;
    
          
    
              // Start from last not visited vertex
          for (auto n : g.get_neighbours(x)) {
              if(!visited[n.id] && shortest[n.id] > (g.get_edge_weight(x, n.id) + weight ))
              {
                  shortest[n.id] = (g.get_edge_weight(x, n.id) + weight);
                  
                  q.push({shortest[n.id],n.id});
                  parent[n.id] = x;
                 
              }
                   }
        
                 visited[x] = true;
      }
          
   
     int crawl = v_id;
    path.push_back(vertex<T>(crawl,g.get_vertex_weight(crawl)));
      
    while (parent[crawl] != -1) {
         path.push_back(vertex<T>(parent[crawl],g.get_vertex_weight(parent[crawl])));
         crawl = parent[crawl];
     }
      
    reverse(path.begin(), path.end());
    
      return path;
    
}

template <typename T>
vector<vector<vertex<T>>> strongly_connected_components(directed_graph<T>  g) {
 
 int *disc = new int[g.num_vertices()];
    int *low = new int[g.num_vertices()];
    bool *stackMember = new bool[g.num_vertices()];
    stack<int> *st = new stack<int>();
    vector<vector<vertex<T>>> result;
  
    // Initialize disc and low, and stackMember arrays
    for (auto i : g.get_vertices())
    {
        disc[i.id] = -1;
        low[i.id] = -1;
        stackMember[i.id] = false;
    }
  
    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (auto i : g.get_vertices()){
        if (disc[i.id] == -1){
            SCCUtil(g,i.id, disc, low, st, stackMember,result);
        }
    }

    return result;

}


template <typename T>
void SCCUtil(directed_graph<T> g,int u, int disc[], int low[], stack<int> *st,
             bool stackMember[], vector<vector<vertex<T>>> &result)
{
    // A static variable is used for simplicity, we can avoid use
    // of static variable by passing a pointer.
    static int time = 0;
    vector<vertex<T>> components;
    
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
    
    // Go through all vertices adjacent to this
    for(auto n : g.get_neighbours(u))
    {
        int v = n.id;  // v is current adjacent of 'u'
        
        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(g,v, disc, low, st, stackMember,result);
            
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 (per above discussion on Disc and Low value)
            low[u]  = min(low[u], low[v]);
        }
        
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 (per above discussion on Disc and Low value)
        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }
    
    // head node found, pop the stack and print an SCC
    int w = 0;  // To store stack extracted vertices
   if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
           // cout << components << " ";
        components.push_back(vertex<T>(w,g.get_vertex_weight(w)));
        //result.push_back(components);
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
      //  cout << w << "\n";
         components.push_back(vertex<T>(w,g.get_vertex_weight(w)));
         result.push_back(components);
        stackMember[w] = false;
        st->pop();
    }
    

}




template <typename T>
void topologicalSortUtil( directed_graph<T> g, int u_id, bool visited[], stack<int> &stack)
{
  
    // Mark the current node as visited.
    visited[u_id] = true;
  
    // Recur for all the vertices
// adjacent to this vertex
   
    for (auto n : g.get_neighbours(u_id)) {
        if (!visited[n.id]) {
            topologicalSortUtil(g,n.id,visited,stack);
        }
    }
   
    
    // Push current vertex to stack
// which stores result
  stack.push(u_id);
}

template <typename T>
vector<vertex<T>> topological_sort(directed_graph<T> g) {


vector<vertex<T>> ts;
   stack<int> stack;
    bool visited[g.num_vertices()];
  
    // Mark all the vertices as not visited
    for (int i = 0; i < g.num_vertices(); ++i) {
        visited[i] = false;
    }
    // Call the recursive helper function
// to store Topological
    // Sort starting from all
// vertices one by one
    for (auto j : g.get_vertices()) {
        if (!visited[j.id]) {
            topologicalSortUtil(g,j.id,visited,stack);
      }
    }
    
    // Print contents of stack
    while (!stack.empty())
    {
       int top =stack.top();
       stack.pop();
        ts.push_back(vertex<T>(top, g.get_vertex_weight(top)));
       // cout << Stack.top() << " ";
        
        
    }
  return ts;

}
