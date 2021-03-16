//
//  directed_graph.cpp
//  directed_graph
//
//  Created by Sumanyu Khemlani on 31/05/2020.
//  Copyright © 2020 Sumanyu Khemlani. All rights reserved.
//


#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<set>
#include<queue>
#include<stack>
// include more libraries here if you need to

using namespace std; // the standard namespace are here just in case.

/*
    the vertex class
*/
template <typename T>
class vertex {

public:
    int id;
    T weight;

    vertex(int x, T y) : id(x), weight(y) {}

    // add more functions here if you need to
};

/*
    the graph class
*/
template <typename T>
class directed_graph {

private:

    //You will need to add some data members here
    //to actually represent the graph internally,
    //and keep track of whatever you need to.

    unordered_map<int, T> vertex_list;
    unordered_map<int, unordered_map<int, T> > adj_list;
    size_t number_edges = 0; //number of edges

public:

    directed_graph(); //A constructor for directed_graph. The graph should start empty.
    ~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.

    bool contains(const int&) const; //Returns true if the graph contains the given vertex_id, false otherwise.
    bool adjacent(const int&, const int&); //Returns true if the first vertex is adjacent to the second, false otherwise.

    void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges).
    void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second.

    void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges.
    void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists.

    int get_edge_weight(const int&,const int&) ;
    size_t in_degree(const int&); //Returns number of edges coming in to a vertex.
    size_t out_degree(const int&) ; //Returns the number of edges leaving a vertex.
    size_t degree(const int&); //Returns the degree of the vertex (both in edges and out edges).

    size_t num_vertices() const; //Returns the total number of vertices in the graph.
    size_t num_edges() const; //Returns the total number of edges in the graph.

    vector<vertex<T> > get_vertices(); //Returns a vector containing all the vertices.
    vector<vertex<T> > get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself.
    vector<vertex<T> > get_second_order_neighbours(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex.
                                                              // A vector cannot be considered a second_order_neighbour of itself.
    bool reachable(const int&, const int&); //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
    bool contain_cycles(); // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.

    vector<vertex<T> > depth_first(const int&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
    vector<vertex<T> > breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.
    double get_vertex_weight(const int );

};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

template <typename T>
directed_graph<T>::directed_graph() {}

template <typename T>
directed_graph<T>::~directed_graph() {}

template <typename T>
bool directed_graph<T>::contains(const int& u_id) const {

    if(vertex_list.find(u_id) != vertex_list.end()) // u_id is found in vertex_weights's keys
    {
     return true;
    }
  return false;
}

template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id){
         
     if(adj_list[u_id].find(v_id) != adj_list[u_id].end()) //check if the edge is in the graph
     {
      return true;
     }
  return false;
}

template <typename T>
void directed_graph<T>::add_vertex(const vertex<T>& u) {
    
    if(!contains(u.id))
    {
     vertex_list.insert({u.id, u.weight}); // step 1: add the new vertex to all_vertices
     adj_list[u.id] = unordered_map<int, T>(); // step 2: add an entry for this vertex in adj_list but add no edge
    }
}

template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& weight) {

    if(contains(u_id) && contains(v_id)) // Step 1: make sure both vertices are in the graph
    {
       if(adj_list[u_id].find(v_id)==adj_list[u_id].end()) // Step 2: make sure the edge is not already in the graph
       {
        adj_list[u_id].insert({v_id, weight}); // Step 3: add this edge to adj_list
        ++number_edges;
       }
    }
}

template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id) {

    // remove the vertex, as well as all the incident edges
    vertex_list.erase(u_id); // step 1: remove the vertex from all_vertices
    adj_list.erase(u_id); // step 2: remove all edges starting from this vertex
     for (auto& x: adj_list) // Step 3: iterate adj_list to remove all edges ending at this vertex
     {
        x.second.erase(u_id);
     }
}

template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) {

     if(contains(u_id) && contains(v_id))
      {
        adj_list[u_id].erase(v_id);
        --number_edges;
      }
}

template <typename T>
int directed_graph<T>::get_edge_weight(const int& u_id, const int& v_id )  {

     int weight = adj_list.at(u_id).at(v_id);
    return weight;
}


template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id)  {
    
    auto num_in_degree = 0;
    for(int i = 0; i<=vertex_list.size();i++)
    {
        if(adj_list[i].find(u_id) != adj_list[i].end())
        {
          ++num_in_degree;
        }
    }

  return num_in_degree;
}

template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) {
    return adj_list.at(u_id).size();
}

template <typename T>
size_t directed_graph<T>::degree(const int& u_id) {
    return in_degree(u_id) + out_degree(u_id);
}

template <typename T>
size_t directed_graph<T>::num_vertices() const {
    return vertex_list.size();
}

template <typename T>
size_t directed_graph<T>::num_edges() const {
    return number_edges;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() {
    
    vector<vertex<T>> vertices;
    for(auto x: vertex_list) // iterate vertex_weight to get all vertex_ids
    {
        vertices.push_back(vertex<T>(x.first, x.second)); // and then build a vertex class for each vertex_id
    }

    return vertices; // return a vector of the vertex classes for all vertex_ids
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_neighbours(const int& u_id) {
    
    vector<vertex<T>> neighbours;
    if(contains(u_id)) // Step 1: make sure the vertex is in the graph
    {
       for (auto x: adj_list[u_id]) // Step 2: find all edges starting from the vertex of u_id
       {
            neighbours.push_back(vertex<T>(x.first, vertex_list[x.first])); // Step 3: add the end_node of each edge to the result
       }
    }

    return neighbours;
 }

template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbours(const int& u_id) {
    
    vector<vertex<T>> first =get_neighbours(u_id);
    vector<vertex<T>> second;
    for(auto x : first ) // iterates through the first neighbours of u
    {
        for(auto y : get_neighbours(x.id)) // iterates through fist neighbour of x, meaning second neighbour of u
        {
            bool has_duplicate = false;
            for (auto z : second)
            {
                    if(z.id == y.id) // check if the vertex is already in the vector
                    {
                        has_duplicate = true;
                        break;
                    }
            }

          if(!has_duplicate)
          {
            second.push_back(vertex<T>(y.id, vertex_list[y.id]));
          }
          if(u_id == y.id) // check if u itself has been added to vector
          {
            second.pop_back();
          }
       }

    }
    return second;
}

template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id) {
    
     vector<vertex<T>> depth_f = depth_first(u_id);
     for(auto i=0; i<depth_f.size(); i++)
     {
         if(depth_f[i].id == v_id)
        {
            return true;
        }
     }

   return false;
}

template <typename T>
bool directed_graph<T>::contain_cycles() {

    vector<vertex<T>> vertices = get_vertices();
    bool contains = false;
    for (auto c : vertices) // iterates through all the vertices
    {
        for(auto n : get_neighbours(c.id)) // iterates through the neighbours of the vertices(to avoid self-loop)
        {
           if(reachable(n.id,c.id)) // check if their is a path from neighbour to vertex
           {
             contains =true;
           }
        }
    }

  return contains;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::depth_first(const int& u_id) {
    
    vector<vertex<T>> dfs;
    stack<int> stack;
    bool visited[num_vertices()];
      for(int i =0;i<num_vertices();i++) // set all vertices not visited
      {
        visited[i] = false;
      }

    stack.push(u_id);

    while(!stack.empty())
    {
        int top = stack.top();
        stack.pop();
        if(!visited[top])  // if in stack and not visited , visit it and add to the vector
        {
            visited[top] =true;
            dfs.push_back(vertex<T>(top,vertex_list[top]));
      
            for(auto n : get_neighbours(top)) // add all the neighbours to stack
            {
                if(!visited[n.id]) // if not already visited
                {
                    stack.push(n.id);
                }
            }
        }
    }

  return dfs ;

}

   
template <typename T>
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) {
    

    vector<vertex<T>> bfs;
    queue<int> queue; // similar to depth_first except queue instead of stack
    bool visited[num_vertices()];
    for(int i =0;i<num_vertices();i++)
    {
        visited[i] = false;
    }

    queue.push(u_id);

    while(!queue.empty())
    {
        int top = queue.front();
        queue.pop();
        if(!visited[top])
        {
            visited[top] =true;
            bfs.push_back(vertex<T>(top,vertex_list[top]));
      
            for(auto n : get_neighbours(top))
            {
               if(!visited[n.id])
               {
                queue.push(n.id);
               }
            }
        }
    }

return bfs;
}
template<typename T>
double directed_graph<T>::get_vertex_weight(const int u_id){

  double weight = vertex_list[u_id];
  return weight;

}

#endif
