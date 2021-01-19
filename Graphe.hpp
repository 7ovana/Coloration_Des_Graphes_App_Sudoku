#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <vector>
#include <iterator>

#include <cmath>            // sqrt
#include <string>
#include <numeric>          // std::iota
#include <algorithm>        // std::sort, std::stable_sort
#include <unordered_map>    // std::unordered_map

#ifndef GRAPHEHEADERDEF
#define GRAPHEHEADERDEF

class Arc
{
public:
    int a, b;                               // sommets formant cet Arc
    Arc() : a(0.0), b(0.0) {}               // constructeur par defaut
    Arc(int a_, int b_) : a(a_), b(b_) {}   // constructeur avec valeurs

    // méthode pour l'affichage 
    std::string to_str() const {
        std::stringstream ss;
        ss << "(" << a << "," << b << ")" ;
        return ss.str();
    }
    // surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream & out, const Arc &arc){
        return out << arc.to_str();
    }
private:
    void operator=(const Arc&);
};


class Graphe
{
public:
    int N;                              // nb de noeuds
    std::vector<Arc> ListA;             // liste des Arcs
    std::vector<std::vector<int>> vois; // stockage des voisins

    Graphe(const char * filename = "default_graph.txt"); // constructeur a partir d'un fichier
    Graphe(int size); // constructeur pour les sudokus
    std::vector<std::vector<int>> neighbours(); // stocke les voisins des nodes (sommets adjacents) dans vois

    std::vector<int> neighborsArcs(int node); // renvoie la liste des indices des arcs attaches au node
    std::vector<int> Adj(int node); // renvoie les voisins du node (sommets adjacents)
    void cols(int node, int K, std::vector<std::pair<int, std::vector<int>>> &col, std::vector<int> &assigned_colors); // renvoie la liste des couleurs disponibles pour node
    void Init(int K, std::vector<std::pair<int, std::vector<int>>> &col, std::vector<int> &assigned_colors); // initialise col
    void sort_by_available_colours(int K, std::vector<int> &nodes, std::vector<std::pair<int, std::vector<int>>> &col, 
                                   std::vector<int> &assigned_colors); // sort les noeuds par nombre de couleurs disponibles et vire les noeuds déjà colorés

    // Backtracking graph coloring algorithm 
    
    bool good_to_take(int node, int color, int K, std::vector<int> &assigned_colors); // booléan qui est vrai si node peut être coloré par color
    bool try_graph_coloring(int node, int K, std::vector<int> &assigned_colors);     // fonction récursive qui essaye de colorier le graphe
    bool graph_coloring(int K, std::vector<int> &assigned_colours);     // fonction qui appelle try_graph_coloring et affiche si la solution existe et est trouvée ou pas 
    
    // Backtracking coloring algorithm modified 

    bool try_graph_coloring_BIS(int node, int K, std::vector<int> &nodes, std::vector<std::pair<int, std::vector<int>>> &col,
                                std::vector<int> &assigned_colors, int colored_node);
    bool graph_coloring_BIS(int K, std::vector<int> &assigned_colours);

    // Bakctracking coloring algorithms with steps shown
    
    bool try_graph_coloring_NOISY(int node, int K, std::vector<int> &assigned_colors);
    bool graph_coloring_NOISY(int K, std::vector<int> &assigned_colours); 
    bool try_graph_coloring_BIS_NOISY(int node, int K, std::vector<int> &nodes, std::vector<std::pair<int, std::vector<int>>> &col,
                                    std::vector<int> &assigned_colors, int colored_node);
    bool graph_coloring_BIS_NOISY(int K, std::vector<int> &assigned_colours);
};

class Sudoku : public Graphe {
    public:
        // les nombres pré-assignés
        std::vector<int> entries;

        // constructeur des grilles sudoku à partir de deux fichiers
        Sudoku(int size, const char* filename_entries);
        // surcharge de l'opérateur <<
        friend std::ostream& operator<<(std::ostream & out, const Sudoku &S);
 };

// fonction qui écrit les graphes des sudokus dans des fichiers .txt
void write_arcs_sudoku(int n);

#endif
