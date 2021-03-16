
#include <iostream>
//#include "directed_graph_algo.cpp"
#include "algo.cpp"

using namespace std;


int main(){
   directed_graph<double> g1;

     
     vertex<double> v1(10, 10.41);
     vertex<double> v2(2, 2.32);
     vertex<double> v3(3, 3.66);
     vertex<double> v4(8, 4.12);
     vertex<double> v5(12, 5.32);
     vertex<double> v6(23, 6.87);
     vertex<double> v7(5, 7.45);
    vertex<double> v8(4,4.21);
     

     
     g1.add_vertex(v1);
     g1.add_vertex(v2);
     g1.add_vertex(v3);
     g1.add_vertex(v4);
     g1.add_vertex(v5);
     g1.add_vertex(v6);
     g1.add_vertex(v7);
    g1.add_vertex(v8);

   

     g1.add_edge(10, 2, 10);
     g1.add_edge(10, 3, 20);
     g1.add_edge(10, 8, 30);
     g1.add_edge(2, 10, 40);
     g1.add_edge(10, 12, 50);
     g1.add_edge(8, 5, 70);
     g1.add_edge(12, 8, 10);
     g1.add_edge(12, 23, 20);
     g1.add_edge(23, 12, 50);
     g1.add_edge(23, 5, 10);
     g1.add_edge(5, 10, 20);
     g1.add_edge(4, 2, 60);
    
    directed_graph<double> g;

       
       vertex<double> v11(1, 1.41);
       vertex<double> v21(2, 2.32);
       vertex<double> v31(3, 3.66);
       vertex<double> v41(4, 4.12);
       vertex<double> v51(5, 5.32);
       vertex<double> v61(6, 6.87);
       vertex<double> v71(7, 7.45);
       vertex<double> v81(8, 8.87);
       vertex<double> v91(9, 9.45);
       

       
       g.add_vertex(v11);
       g.add_vertex(v21);
       g.add_vertex(v31);
       g.add_vertex(v41);
       g.add_vertex(v51);
       g.add_vertex(v61);
       g.add_vertex(v71);
       g.add_vertex(v81);
       g.add_vertex(v91);
     

       g.add_edge(1, 2, 8);
       g.add_edge(1, 3, 3);
       g.add_edge(1, 6, 13);
       g.add_edge(2, 3, 2);
       g.add_edge(2, 4, 1);
       g.add_edge(3, 2, 3);
       g.add_edge(3, 4, 9);
       g.add_edge(3, 5, 2);
       g.add_edge(4, 5, 4);
       g.add_edge(4, 7, 6);
       g.add_edge(4, 8, 2);
       g.add_edge(5, 4, 6);
       g.add_edge(5, 6, 5);
       g.add_edge(5, 9, 4);
       g.add_edge(5, 1, 5);
       g.add_edge(6, 9, 7);
       g.add_edge(6, 7, 1);
       g.add_edge(7, 5, 3);
       g.add_edge(7, 8, 4);
       g.add_edge(8, 9, 1);
       g.add_edge(9, 7, 5);
       

   
     cout << "Shortest path "<<endl;
    vector<vertex<double>> sp = shortest_path(g,1,8);
     for (vertex<double> snb : sp) {
         cout << "(" << snb.id << ", " << snb.weight << ") ";
     }
     cout <<  endl;
    
    /*cout << "Strong Components "<<endl;
      vector<vector<vertex<double>>> scc = strongly_connected_components(g1);
    for(auto vec : scc){
        for (vertex<double> sc : vec) {
            cout << "(" << sc.id << ", " << sc.weight << ") ";
            cout <<  endl;
        }
         cout <<  endl;
    }
       
       
    cout << "Topological Sort "<<endl;
       vector<vertex<double>> ts = topological_sort(g1);
        for (vertex<double> tss : ts) {
            cout << "(" << tss.id << ", " << tss.weight << ") ";
        }
        cout <<  endl;*/
       
    
}
