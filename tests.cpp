#include <iostream>
#include <fstream>
#include <list>
#include "Graphe.hpp"
#include <time.h>

using std::cout;
using std::endl;

void test_graph_constructors(){
    // Testing empty graph constructors
    
    Graphe G_empty(0);
    cout << G_empty.N << endl;
    cout << G_empty.ListA.size() << endl;
    Graphe G_default;
    cout << G_default.N << endl;
    cout << G_default.ListA.size() << endl;
}
void test_Adj(Graphe G){
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    std::vector<int> neighbours = G.Adj(0);

    cout << "The neighbours of node 0 are:\n";
    for (int i : neighbours) cout << i << "\t";
    cout << endl << endl;
}
void test_cols(Graphe G){
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);

    std::vector<std::pair<int, std::vector<int>>> col (G.N);


    cout << "Number of colours for the graph coloration:\nK = " << K << "\ncols = "; 

    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        G.cols(i, K, col, assigned_colours);
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "\nAvailable colours for node 0:\n";
    for (int i : col[0].second) cout << i << "\t";
    cout << endl;

    // test si son voisin a pris une couleur
    cout << "\nAfter assigning color 1 to node 4\ncols = ";
    assigned_colours[4] = 1;
    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        G.cols(i, K, col, assigned_colours);
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "\nAvailable colours for node 0:\n";
    for (int i : col[0].second) cout << i << "\t";
    cout << endl;

    // test si la couleur est déjà attribuée au noeud 0 
    cout << "\nAfter assigning color 1 to node 0\n";
    cout << "(we're expecting an empty vector here)\ncols = ";
    assigned_colours[4] = 0;
    assigned_colours[0] = 1;
    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        G.cols(i, K, col, assigned_colours);
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "\nAvailable colours for node 0:\n";
    for (int i : col[0].second) cout << i << "\t";
    cout << endl << endl;
}
void test_Init(Graphe G){
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);
    //std::unordered_map<int, std::pair<int, std::vector<int>>> col;
    std::vector<std::pair<int, std::vector<int>>> col (G.N);

    cout << "Number of colours for the graph coloration:\nK = " << K << endl;
    
    cout << "No pre-assigned colours check\n";
    G.Init(K, col, assigned_colours);

    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "\nAvailable colours for node 0:\n";
    for (int i : col[0].second) cout << i << "\t";
    cout << endl;

    cout << "\nAfter assigning color 1 to node 1 and color 2 to node 4:\n";
    assigned_colours[1] = 1;
    assigned_colours[4] = 2;
    G.Init(K, col, assigned_colours);

    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "\nAvailable colours for node 0:\n";
    for (int i : col[0].second) cout << i << "\t";
    cout << endl << endl;
}
void test_sort_by_available_colours(Graphe G){
    cout << "Graph parameters:\nnumber of nodes: " 
         << G.N << "\nnumber of arcs: " << G.ListA.size() 
         << "\nArcs:\n";

    for (Arc arc : G.ListA) cout << arc << "\t";
    cout << endl;

    int K = 3;
    std::vector<int> assigned_colours(G.N,0);
    std::vector<std::pair<int, std::vector<int>>> col (G.N);

    cout << "Number of colours for the graph coloration:\nK = " << K << endl;
    std::vector<int> nodes(G.N);
    for (int i = 0; i < G.N; i++) nodes[i] = i;

    cout << "With no pre-assigned colours\n";
    G.sort_by_available_colours(K, nodes, col, assigned_colours);
    cout << "nodes to pick from =\t";
    for (int node : nodes) cout << node << "\t";
    cout << endl;

    cout << "\nAfter assigning color 1 to node 1 and color 2 to node 4:\n";
    assigned_colours[1] = 1;
    assigned_colours[4] = 2;

    G.Init(K, col, assigned_colours);

    cout << "Number of available colours for all nodes:\ncols =\t";
    for (int i = 0; i < G.N; i ++){
        cout << col[i].first << "\t"; 
    }
    cout << endl;

    cout << "nodes to pick from =\t";
    G.sort_by_available_colours(K, nodes, col, assigned_colours);
    for (int node : nodes) cout << node << "\t";
    cout << endl << endl; 
}

void test_class_methods(){

    Graphe G2("G2.txt");
    Graphe G("G.txt");

    cout << "\n//-------------------- Test for Adj --------------------//:\n\n";
    cout << "\nAdj is a class method with the following signature:\n" <<
            "std::vector<int> Adj(int node)\n" <<
            "that returns a vector of the neighbours of node given in argument.\n\n";
    
    cout <<"Graphe 1:\n\n";
    test_Adj(G);
    cout <<"Graphe 2:\n\n";
    test_Adj(G2);

    cout << "\n//------------------- Test for cols ---------------------//\n\n";
    cout << "\ncols is a class method with the following signature:\n" <<
            "void cols(int node, int K, std::vector<std::pair<int, std::vector<int>>> &col, std::vector<int> &assigned_colors)\n" <<
            "that returns a vector containing the available colours (out of K possible colours) for node,\n" <<
            "based on the pre-assigned colours, which are in the vector assigned_colours.\n\n";
    
    cout <<"Graphe 1:\n\n";
    test_cols(G2);
    cout <<"Graphe 2:\n\n";    
    test_cols(G);

    cout << "\n//------------------- Test for Init ---------------------//\n\n";
    cout << "\nInit is a class method with the folowing signature:\n" <<
            "void Init(int K, std::vector<std::pair<int, std::vector<int>>> &col, std::vector<int> &assigned_colors)\n" <<
            "that initializes the vector col of size N, that contains a pair\n" <<
            "of the number of colours available for node followed by the vector of available colors\n" << 
            "based on the pre-assigned colours, which are in the vector assigned_colours.\n\n";
    
    cout <<"Graphe 1:\n\n";
    test_Init(G2);
    cout <<"Graphe 2:\n\n";
    test_Init(G);

    cout << "\n//------------------- Test sort_by_available_colours ---------------------//\n\n";
    cout << "\nsort_by_available_colours is a class method with the following signature:\n" << 
            "void sort_by_available_colours(int K, std::vector<int> &nodes, \nstd::vector<std::pair<int, std::vector<int>>> &col, std::vector<int> &assigned_colors)\n" <<
            "that updates the vectors col and nodes, the latter containing the\n" <<
            "following nodes to take, ordered by the number of available colours for them, in an ascending order\n\n";
    
    cout <<"Graphe 1:\n\n";
    test_sort_by_available_colours(G2);
    cout <<"Graphe 2:\n\n";
    test_sort_by_available_colours(G);
}

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

void test_sudoku(int size, const char* entries, bool print_solution){
    clock_t t1, t2;
    Sudoku S(size, entries);
    if (print_solution) cout << S << endl;

    int K = sqrt(S.N);
    
    cout << "\nGraph_coloring\n\n";
    t1 = clock();
    S.graph_coloring(K, S.entries);
    t2 = clock();
    cout << "Sudoku solved in: " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
    if (print_solution) cout << S << endl;

    S = Sudoku (size, entries);

    cout << "\nGraph_coloring_BIS\n\n";
    t1 = clock();
    S.graph_coloring_BIS(K, S.entries);
    t2 = clock();
    cout << "Sudoku solved in: " << (float)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
    if (print_solution) cout << S << endl;

}
void test_7_sudokus(bool print_solution){
    cout << "\n\n----------------------- EASY: 38 clues -----------------------\n\n";
    test_sudoku(9, "easy.txt", print_solution); // 38 clues
    cout << "\n\n----------------------- MEDIUM: 30 clues -----------------------\n\n";
    test_sudoku(9, "medium.txt", print_solution); // 30 clues
    cout << "\n\n----------------------- HARD: 25 clues -----------------------\n\n";
    test_sudoku(9, "hard.txt", print_solution); // 25 clues
    cout << "\n\n----------------------- EXPERT: 22 clues -----------------------\n\n";
    test_sudoku(9, "expert.txt", print_solution); // 22 clues
    cout << "\n\n----------------------- SUPER EXPERT: 19 clues -----------------------\n\n";
    test_sudoku(9, "sudoku_9x9_19_two-way_orthogonal_symmetry.txt", print_solution); // 19 clues
    cout << "\n\n----------------------- HYPER EXPERT: 17 clues -----------------------\n\n";
    test_sudoku(9, "sudoku_9x9_17_diagonal_symmetry.txt", print_solution); // 17 clues  
    cout << "\n\n----------------------- ULTRA EXPERT: 17 clues -----------------------\n\n";
    test_sudoku(9, "hyper_expert_des.txt", print_solution); // 17 clues
}

int main(int argc, const char ** argv)
{
    bool noisy = true;
    bool print_solution = true;
    
    Graphe G2("G2.txt");
    Graphe G("G.txt");

    //test_class_methods();
    
    int K = 3;
    cout << "\nExemple de coloration valide du graphe de Petersen, avec K = 3\n\n";
    test_graph_coloring(G2, K, noisy);
    test_graph_coloring_BIS(G2, K, noisy);

    cout << "\nExemple où il n'y a pas de coloration valide du graphe de Petersen, avec K = 2\n\n";
    K = 2;
    test_graph_coloring(G2, K, noisy);
    test_graph_coloring_BIS(G2, K, noisy);

    cout << "\nExemple simple où on voit la différence des deux algorithmes, K = 3\n\n";
    K = 3;
    test_graph_coloring(G, K, noisy);
    test_graph_coloring_BIS(G, K, noisy);

/////////////////////////////////////////////////////////////////////////////////////

// ------------------------------ Bonus: SUDOKU ---------------------------------- //

    //write_arcs_sudoku(2);
    //write_arcs_sudoku(3);

    cout << "Exemple d'un sudoku de taille 4x4\n\n";
    test_sudoku(4, "sudoku_4x4_test_entries.txt", print_solution);
    cout << "Exemple d'un sudoku de taille 9x9\n\n";
    test_sudoku(9, "sudoku_9x9_test_entries.txt", print_solution);

    //test_7_sudokus(false);

    cout << "end prog" << endl;

    return 0;
}
