#include <iostream>
#include <fstream>
#include <list>
#include "Graphe.hpp"
#include <time.h>

using std::cout;
using std::endl;


/* TO DO:
        3. Do that for cols, which will be updated every time in the recursive function.
            col should be of type std::unordered_map<int, std::pair<int, std::vector<int>>>
*/ 
/*
void test_graph_constructors(){
    // Testing empty graph constructor
    
    Graphe G_empty(0);
    cout << G_empty.N << endl;
    cout << G_empty.ListA.size() << endl;
    Graphe G_default;
    cout << G_default.N << endl;
    cout << G_default.ListA.size() << endl;
}

void test_Adj(Graphe G){
    cout << "\n//-------------------- Test for Adj --------------------//:\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    std::vector<int> neighbours = G.Adj(0);

    cout << "The neighbours of node 0 are:\n";
    for (int i : neighbours) cout << i << "\t";
    cout << endl;
}
void test_cols(Graphe G){
    // ----------- Test pour cols  --------------- //

    cout << "\n//------------------- Test for cols ---------------------//\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);
    std::unordered_map<int, std::vector<int>> neighbours = G.neighbours();

    cout << "Number of colours for the graph coloration:\nK = " << K << "\ncols = "; 

    std::vector<int> cols = G.cols(0,K, assigned_colours, neighbours);
    for (int i : cols) cout << i << "\t";
    cout << endl;

    // test si son voisin a pris une couleur
    cout << "\nAfter assigning color 1 to node 4\ncols = ";
    assigned_colours[4] = 1;
    cols = G.cols(0,K,assigned_colours, neighbours);
    for (int i : cols) cout << i << "\t";
    cout << endl;

    // test si la couleur est déjà attribuée au noeud 0 
    cout << "\nAfter assigning color 1 to node 0\n";
    cout << "(we're expecting an empty vector here)\ncols = ";
    assigned_colours[4] = 0;
    assigned_colours[0] = 1;
    cols = G.cols(0, K, assigned_colours, neighbours);
    for (int i : cols) cout << i << "\t";
    cout << endl;
}
void test_Init(Graphe G){
    cout << "\n//------------------- Test for Init ---------------------//\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);
    std::unordered_map<int, std::vector<int>> neighbours = G.neighbours();

    cout << "Number of colours for the graph coloration:\nK = " << K << endl;
    
    std::vector<int> col(G.N);

    cout << "No pre-assigned colours check\n";
    G.Init(K, col, assigned_colours, neighbours);

    cout << "col =\t";
    for (int i: col) cout << i << "\t";
    cout << endl;

    cout << "\nAfter assigning color 1 to node 1 and color 2 to node 4:\n";
    assigned_colours[1] = 1;
    assigned_colours[4] = 2;
    G.Init(K, col, assigned_colours, neighbours);

    cout << "col =\t";
    for (int i: col) cout << i << "\t";
    cout << endl;
}
void test_sort_by_available_colours(Graphe G){
    cout << "\n//------------------- Test sort_by_available_colours ---------------------//\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);
    std::unordered_map<int, std::vector<int>> neighbours = G.neighbours();


    cout << "Number of colours for the graph coloration:\nK = " << K << endl;
    std::vector<int> nodes(G.N);
    for (int i = 0; i < G.N; i++) nodes[i] = i;

    std::vector<int> col(G.N);

    cout << "With no pre-assigned colours\n";
    G.sort_by_available_colours(K, nodes, assigned_colours, neighbours);
    cout << "nodes to pick from =\t";
    for (int node : nodes) cout << node << "\t";
    cout << endl;

    cout << "\nAfter assigning color 1 to node 1 and color 2 to node 4:\n";
    assigned_colours[1] = 1;
    assigned_colours[4] = 2;
    G.Init(K, col, assigned_colours, neighbours);

    cout << "col =\t";
    for (int i: col) cout << i << "\t";
    cout << endl;

    cout << "nodes to pick from =\t";
    G.sort_by_available_colours(K, nodes, assigned_colours, neighbours);
    for (int node : nodes) cout << node << "\t";
    cout << endl;
}

void test_functions_and_methods_used(){

    test_graph_constructors();

    Graphe G2("G2.txt");
    Graphe G("G.txt");

    cout << "\nAdj is a function with the following signature:\nstd::vector<int> Adj(int node)\n" <<
            "that returns a vector of the neighbours of node given in argument.\n\n";
    test_Adj(G);
    test_Adj(G2);

    cout << "\ncols is a function with the following signature:\nstd::vector<int> cols(int node, int K, std::vector<int> assigned_colours)\n" <<
            "that returns a vector containing the available colours (out of K possible colours) for node,\nusing " <<
            "the pre-assigned colours, which are in the vector assigned_colours.\n\n";
    test_cols(G2);
    test_cols(G);

    cout << "\nInit is a function with the folowing signature:\n" <<
            "void Graphe:: Init(int K, std::vector<int> &vois, std::vector<int> &col, std::vector<int> assigned_colors)\n" <<
            "that initializes the vectors vois of size N (the total number of nodes in the graph)\n" <<
            "\t- vois:\tnumber of neighbours per node\n" <<
            "\t- col:\tnumber of available colours per node\nusing " <<
            "the pre-assigned colours, which are in the vector assigned_colours.\n\n";
    test_Init(G2);
    test_Init(G);

    cout << "\nblabla à écrire\n";
    test_sort_by_available_colours(G2);
}
//*/

void test_graph_coloring(Graphe G, int K, bool noisy){
    clock_t t1, t2;

    cout << "\n//--------------------------- TEST: graph_coloring -----------------------------//\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    std::vector<int> assigned_colours(G.N,0);

    cout << "Number of colours for the graph coloration:\nK = " << K << endl;


    if (noisy) {
        cout << "\n ----------------------------- ALGORITHM STEPS -----------------------------------\n\n";
        t1 = clock();
        G.graph_coloring_NOISY(K, assigned_colours);
        t2 = clock();
        for (int color : assigned_colours) cout << color << "\t";
        cout<<endl;
        cout << "\n ----------------------------- ALGORITHM END -----------------------------------\n\n";
        cout << "Time elapsed: " << (float)(t2-t1) / CLOCKS_PER_SEC << "s" << endl;
    }
    else {
        t1 = clock();
        G.graph_coloring(K, assigned_colours);
        t2 = clock();
        for (int color : assigned_colours) cout << color << "\t";
        cout<<endl;
        cout << "Time elapsed: " << (float)(t2-t1) / CLOCKS_PER_SEC << "s" << endl;
    }
}
void test_graph_coloring_BIS(Graphe G, int K, bool noisy){
    clock_t t1, t2;

    cout << "\n//--------------------------- TEST: graph_coloring_BIS -----------------------------//\n";
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    std::vector<int> assigned_colours(G.N,0);

    cout << "Number of colours for the graph coloration:\nK = " << K << endl;


    if (noisy) {
        cout << "\n ----------------------------- ALGORITHM STEPS -----------------------------------\n\n";
        t1 = clock();
        G.graph_coloring_BIS_NOISY(K, assigned_colours);
        t2 = clock();
        for (int color : assigned_colours) cout << color << "\t";
        cout<<endl;
        cout << "\n ----------------------------- ALGORITHM END -----------------------------------\n\n";
        cout << "Time elapsed: " << (float)(t2-t1) / CLOCKS_PER_SEC << "s" << endl;
    }
    else {
        t1 = clock();
        G.graph_coloring_BIS(K, assigned_colours);
        t2 = clock();
        for (int color : assigned_colours) cout << color << "\t";
        cout<<endl;
        cout << "Time elapsed: " << (float)(t2-t1) / CLOCKS_PER_SEC << "s" << endl;
    }
}
void test_sudoku(int size, const char* entries){
    clock_t t1, t2;
    Sudoku S(size, entries);

    int K = sqrt(S.N);
    cout << "Sudoku of size: " << K << "x" << K << endl;
    cout << S << endl;
    
    cout << "\nGraph_coloring\n\n";
    t1 = clock();
    S.graph_coloring(K, S.entries);
    t2 = clock();
    cout << "Sudoku solved in: " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
    cout << S << endl;

    S = Sudoku (size, entries);

    cout << "\nGraph_coloring_BIS\n\n";
    t1 = clock();
    S.graph_coloring_BIS(K, S.entries);
    t2 = clock();
    cout << "Sudoku solved in: " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
    cout << S << endl;
}

int main(int argc, const char ** argv)
{
    clock_t t1, t2;

    Graphe G2("G2.txt");
    Graphe G("G.txt");

    for (auto i : G2.vois[0]) cout << i << endl;

    //test_functions_and_methods_used();
    
    int K = 3;
    bool noisy = true;

    //test_graph_coloring(G2, K, noisy);
    //test_graph_coloring_BIS(G2, K, noisy);

/////////////////////////////////////////////////////////////////////////////////////

// ------------------------------ Bonus: SUDOKU ---------------------------------- //

    //write_arcs_sudoku(2);
    //write_arcs_sudoku(3);
    //write_arcs_sudoku(4);


    //test_sudoku(4, "sudoku_4x4_test_entries.txt");
    //test_sudoku(9, "sudoku_9x9_test_entries.txt");
    //test_sudoku(9, "sudoku_9x9_test_entries_2.txt");
    //test_sudoku(9, "medium.txt");
    //test_sudoku(9, "hard.txt");
    //test_sudoku(9, "expert.txt");

    // Difficult grids for the backtracking algorithm
    test_sudoku(9, "sudoku_9x9_19_two-way_orthogonal_symmetry.txt");
    test_sudoku(9, "sudoku_9x9_17_diagonal_symmetry.txt");

 /*   
    Sudoku WOW(16, "sudoku_16x16_test_entries.txt");

    K = sqrt(WOW.N);
    cout << "Sudoku of size: " << K << "x" << K << endl;
    cout << WOW << endl;
    t1 = clock();
    WOW.graph_coloring_BIS(K, WOW.entries);
    t2 = clock();
    cout << "Sudoku solved in: " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
    cout << WOW << endl;
//*/

    std::pair<int,std::vector<int>> test;
    test.first = 3;
    std::vector<int> m(3);
    test.second = m;

    cout << test.first << " " << test.second[0] << endl;

    cout << "end prog" << endl;

    return 0;
}
