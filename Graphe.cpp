#include "Graphe.hpp"

Graphe::Graphe(const char * filename) { // constructeur a partir d'un fichier texte
    std::ifstream  f(filename);
    assert( f );

    int n; // nombre de noeuds
    int m; // nombre d'arcs

    f >> n >> m;
    N = n;

    // on donne la bonne taille a la liste d'Arcs
    ListA.resize(m); // il faut un constructeur par defaut pour Arc pour cette ligne pourquoi ?

    for(int i=0; i < m; i++) // remplissage du graphe
    {
        int a, b;
        f >> a >> b;
        a--; b--; // zero based notation

        assert(a < n && a >= 0);
        assert(b < n && b >= 0);

        ListA[i].a = a;  ListA[i].b = b;
    }
    f.close();

    vois = this->neighbours();
}

Graphe::Graphe(int size) {
        switch (size)
        {
        case 4: *this = Graphe("sudoku_4x4_arcs.txt");
            break;
        case 9: *this = Graphe("sudoku_9x9_arcs.txt");
            break;
        case 16: *this = Graphe("sudoku_16x16_arcs.txt");
            break;
        default:
            *this = Graphe("default_graph.txt"); 
            break;
        }
}


///////////////////////////////////////////////////////////////////////////////////////

std::vector<int> Graphe::neighborsArcs(int i) {
    assert( i < N && i >= 0);

    std::vector<int> ret;  // a vector of Arc that will be progressively filled

    // fonction indiquant si l'arc A est voisin du noeud i
    auto is_neighbor = [&](const Arc A) -> bool {
        return (A.a == i) || (A.b == i);
    };

    // std::vector<Arc>::iterator it;
    auto it = ListA.begin();
    while( true )
    {
        it = std::find_if(it, ListA.end(), is_neighbor);
        if( it == ListA.end() )
            break;

        ret.push_back(it - ListA.begin());
        it++;
    }

    return ret;
}

std::vector<int> Graphe::Adj(int node){
    assert(node < N && node >= 0);
    std::vector<int> voisins;

    for (auto arc : ListA){
        if (arc.a == node) voisins.push_back(arc.b);
        if (arc.b == node) voisins.push_back(arc.a);
    }
    return voisins;
}

std::unordered_map<int, std::vector<int>> Graphe:: neighbours(){
    std::unordered_map<int, std::vector<int>> map;
    std::vector<int> neighbours;

    for (int i = 0; i < N; i++) map[i] = Adj(i);
    return map;
}

std::vector<int> Graphe:: cols(int node, int K, std::vector<int> &assigned_colors){
    assert(node < N && node >= 0);

    // vecteur qui contiendra les couleurs disponibles
    std::vector<int> colors_available;

    // si le sommet a déjà une couleur attribuée on renvoie un vecteur vide
    if (assigned_colors[node] != 0) return colors_available;
   
    for (int color = 1; color <= K; color++) {
        bool free_color = true;
        for (int neighbour : vois[node]) {
            // Si un des voisins de node contient color
            if (assigned_colors[neighbour] == color)
                // on marque qu'elle n'est pas disponible
                free_color = false;
        }
        if (free_color) colors_available.push_back(color);    
    }  
    return colors_available;
}

void Graphe:: Init(int K, std::vector<int> &col, std::vector<int> &assigned_colors){
    // col: vecteur qui contient le nb de couleurs dispo pour chaque sommet (de taille N)
    
    for (int i = 0; i < N; i++){
        // on initialise cols à -1 comme si chaque couleur à été déjà attribuée
        col[i] = -1; 
        // puis si le noeud i n'a pas de coueleur attribuée 
        if (assigned_colors[i] == 0){
            // on met dans la case correspondante dans cols le nombre de couleurs disponibles pour i
            col[i] = cols(i, K, assigned_colors).size();
        }
    }  
}

void Graphe::sort_by_available_colours(int K, std::vector<int> &nodes, std::vector<int> &assigned_colors){

    nodes = std::vector<int> (N);
    std::vector<int> vois(N);
    std::vector<int> col(N);
    Init(K, col, assigned_colors);

    //std::cout << "col =\t";
    //for (int i: col) std::cout << i << "\t";
    //std::cout << std::endl; 

    // initialize original index locations
    iota(nodes.begin(), nodes.end(), 0);

    //  sort indexes based on comparing values in col using std::stable_sort 
    //  instead of std::sort to avoid unnecessary index re-orderings 
    //  when col contains elements of equal values 
    std::stable_sort(nodes.begin(), nodes.end(), [&col](int i1, int i2) {return col[i1] < col[i2];});
    std::stable_sort(col.begin(), col.end());

    auto it_col = col.begin();
    auto it_nodes = nodes.begin();
    while (*it_col == -1){
        nodes.erase(it_nodes);
        it_col++;
    }

    //std::cout << "nodes =\t";
    //for (int i: nodes) std::cout << i << "\t";
    //std::cout << std::endl; 
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

bool Graphe:: good_to_take(int node, int color, int K, std::vector<int> &assigned_colors){
    assert(node < N && node >= 0);
    assert(color <= K && color > 0);

    for (int neighbour : vois[node]) {
        if (assigned_colors[neighbour] == color) {
            //std::cout<<"\t\tcolor taken by neighbours\n";
            return false;
        }
    }  
    //std::cout<<"\t\tok, color good to take\n";
    return true;
}

bool Graphe:: try_graph_coloring(int node, int K, std::vector<int> &assigned_colors){
    // si tout est déjà attribué c'est bon, on sort de la récursion 
    if (node == N) return true;

    // si une couleur est déjà atttribuée on fait le backtracking directement
    if (assigned_colors[node] != 0){
        return try_graph_coloring(node + 1, K, assigned_colors);
    }

    for (int color = 1; color <= K; color++){  
        if (good_to_take(node, color, K, assigned_colors)){
            
            assigned_colors[node] = color;

            // backtracking:
            if (try_graph_coloring(node + 1, K, assigned_colors) == true){
                return true;
            }
            // mais si jamais on ne renvoie pas true il ne faut pas attribuer
            //   cette couleur à ce sommet, et on remet comme c'était avant:
            assigned_colors[node] = 0;
        }
    }
    // si on ne peut attribuer aucune couleur à un sommet on renvoie false
    return false;
}

bool Graphe :: graph_coloring(int K, std::vector<int> &assigned_colours){

    if (try_graph_coloring(0, K, assigned_colours)){
        std::cout << "Solution exists and it's found.\n";
        return true;
    }
    std::cout << "Solution doesn't exist.\n";
    return false;
}

bool Graphe::try_graph_coloring_BIS(int K, std::vector<int> &nodes, std::vector<int> &available_colors,
                                    std::vector<int> &assigned_colors, int colored_node){

    if (colored_node == N) return true;

    for (int color = 1; color <= K; color++){
        if (good_to_take(nodes[0], color, K, assigned_colors)){
            
            assigned_colors[nodes[0]] = color;

            std::vector<int> nodes_bis = nodes;
            sort_by_available_colours(K, nodes, assigned_colors);
            if (nodes.size() == 0) return true;
            
            // backtracking
            if (try_graph_coloring_BIS(K, nodes, available_colors, assigned_colors, colored_node+1) == true){
                return true;
            }        

            // mais si jamais on ne renvoie pas true il ne faut pas attribuer
            // cette couleur à ce sommet, et on remet sa couleur à 0
            assigned_colors[nodes_bis[0]] = 0;
            sort_by_available_colours(K, nodes, assigned_colors);
        }
    }

    // si on ne peut attribuer aucune couleur à un sommet on renvoie false
    return false;
}

bool Graphe :: graph_coloring_BIS(int K, std::vector<int> &assigned_colours){
    
    std::vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i;
    sort_by_available_colours(K, nodes, assigned_colours);

    if (nodes.size() == 0) {
        std::cout << "Sudoku already solved.\n";
        return true;
    }
    if (try_graph_coloring_BIS(K, nodes, assigned_colours, assigned_colours, 0)){
        std::cout << "Solution exists and it's found.\n";
        return true;
    }
    std::cout << "Solution doesn't exist.\n";
    return false;
}


bool Graphe:: try_graph_coloring_NOISY(int node, int K, std::vector<int> &assigned_colors){
    // si tout est déjà attribué c'est bon, on sort de la récursion 
    if (node == N) return true;
    std::cout<< "node = " << node << std::endl;

    for (int color = 1; color <= K; color++){
        std::cout << "\tcolor = " << color << std::endl;
        
        if (good_to_take(node, color, K, assigned_colors)){
            
            assigned_colors[node] = color;
            
            std::cout << "assigned_colours = ";
            for (int i: assigned_colors) std::cout << i << "\t";
            std::cout << std::endl;

            // backtracking:
            if (try_graph_coloring_NOISY(node + 1, K, assigned_colors) == true){
                return true;
            }
            // mais si jamais on ne renvoie pas true il ne faut pas attribuer
            // cette couleur à ce sommet, et on remet comme c'était avant:
            assigned_colors[node] = 0;

            std::cout << "try_graph_coloring didn't work, we go back to the way it was before\n";
            for (int color : assigned_colors) std::cout << color << "\t";
            std::cout<<std::endl;
        }
    }
    // si on ne peut attribuer aucune couleur à un sommet on renvoie false
    return false;
}

bool Graphe :: graph_coloring_NOISY(int K, std::vector<int> &assigned_colours){

    if (try_graph_coloring_NOISY(0, K, assigned_colours)){
        std::cout << "Solution exists and it's found.\n";
        return true;
    }
    std::cout << "Solution doesn't exist.\n";
    return false;
}

bool Graphe::try_graph_coloring_BIS_NOISY(int K, std::vector<int> &nodes, std::vector<int> &available_colors,
                                    std::vector<int> &assigned_colors, int colored_node){

    if (colored_node == N) return true;

    for (int color = 1; color <= K; color++){
        std::cout << "\tcolor = " << color << std::endl;

        if (good_to_take(nodes[0], color, K, assigned_colors)){
            
            assigned_colors[nodes[0]] = color;

            std::vector<int> nodes_bis = nodes;
            sort_by_available_colours(K, nodes, assigned_colors);
            if (nodes.size() == 0) return true;

            std::cout << "assigned_colours = ";
            for (int i: assigned_colors) std::cout << i << "\t";
            std::cout << std::endl;

            std::cout << "nodes = ";
            for (int i: nodes) std::cout << i << "\t";
            std::cout << std::endl;
            
            if (try_graph_coloring_BIS_NOISY(K, nodes, assigned_colors, assigned_colors, colored_node+1) == true){
                return true;
            }        

            // mais si jamais on ne renvoie pas true il ne faut pas attribuer
            // cette couleur à ce sommet, et on remet sa couleur à 0
            assigned_colors[nodes_bis[0]] = 0;
            sort_by_available_colours(K, nodes, assigned_colors);

            std::cout << "nodes_OUT = ";
            for (int i: nodes) std::cout << i << "\t";
            std::cout << std::endl;

            std::cout << "try_graph_coloring_BIS didn't work, we go back to the way it was before\n";
            for (int color : assigned_colors) std::cout << color << "\t";
            std::cout<<std::endl;
        }
    }

    // si on ne peut attribuer aucune couleur à un sommet on renvoie false
    return false;
}

bool Graphe :: graph_coloring_BIS_NOISY(int K, std::vector<int> &assigned_colours){
    std::vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i;
    sort_by_available_colours(K, nodes, assigned_colours);

    if (nodes.size() == 0) {
        std::cout << "Sudoku already solved.\n";
        return true;
    }
    if (try_graph_coloring_BIS_NOISY(K, nodes, assigned_colours, assigned_colours, 0)){
        std::cout << "Solution exists and it's found.\n";
        return true;
    }
    std::cout << "Solution doesn't exist.\n";
    return false;
}

// -------------------------------------------------------------------------------------------------------

Sudoku :: Sudoku (int size, const char* filename_entries) : Graphe(size) {
    std::ifstream  f(filename_entries);
    assert( f );

    int number_of_entries;
    f >> number_of_entries;
    entries = std::vector<int> (N, 0);
 
    for(int i=0; i < number_of_entries; i++)
    {
        int color;
        int node;
        f >> node >> color;
        node--; // zero based notation

        assert(node >= 0 && node < N); 
        assert(color > 0 && color <= sqrt(N));

        entries[node] = color;
    }
    f.close();
}

std::ostream& operator<<(std::ostream & out, const Sudoku &S){

    std::string line(sqrt(S.N)*4, '-');

    out << line << std::endl;
    for (int i = 0; i < S.N; i++){
        if (i%int(sqrt(sqrt(S.N))) == 0) out << "| ";
        
        switch (S.entries[i])
        {
        case 10: out << 'A' << "  ";
            break;
        case 11: out << 'B' << "  ";
            break;
        case 12: out << 'C' << "  ";
            break;
        case 13: out << 'D' << "  ";
            break;
        case 14: out << 'E' << "  ";
            break;
        case 15: out << 'F' << "  ";
            break;
        case 16: out << 'G' << "  ";
            break;    
        
        default:
            out << S.entries[i] << "  ";
            break;
        }

        if ((i+1)%int(sqrt(S.N)) == 0) out << "| " << std::endl;
        
        if ((i+1)%int(sqrt(S.N*sqrt(S.N))) == 0) {
            out << line << std::endl;
        }
    }
    return out;
}

void write_arcs_sudoku(int n){

    std::string line("sudoku_" + std::to_string(n*n) + "x" + std::to_string(n*n) + "_arcs.txt");
    std::ofstream  f(line);
    assert( f );

    int N = n*n*n*n;
    int n_squared = n*n;
    // compute number of arcs
    int m = N * (3*n_squared - 2*n - 1) / 2; 
    f << N << " " << m << std::endl;

    std::vector<int> nodes_in_order_of_squares;
    
    // arcs par petit carré, donc écriture de n_squared*nb_arcs_small_square entrées
    for (int l = 0; l < n_squared; l += n){ // colonne des carrés
        for (int k = 0; k < n_squared; k += n){ // déplace
            for (int j = 0; j < n; j++){ // indice par colonne
                for(int i = 1; i <= n; i++){ // indice par ligne
                    nodes_in_order_of_squares.push_back(i + j*n_squared + k*n_squared + l);
                }
            }
        }
    }
    
    // PER ROWS, 4*N entries
    for (int i = 1; i <= (n_squared - 1)*n_squared + 1; i += n_squared){
        for (int j = i; j < i + n_squared; j++){
            for (int k = j+1; k <= i + n_squared - 1; k++){
                f << j << " " << k << std::endl;
            }
        }
    }

    // PER COLUMNS, 4*N entries
    for (int i = 1; i <= n_squared; i++){
        for (int j = i; j < i + (n_squared - 1)*n_squared; j += n_squared){
            for (int k = j+n_squared; k <= i + (n_squared - 1)*n_squared; k += n_squared){
                f << j << " " << k << std::endl;
            }
        }
    }

    // PER n*n SQUARES, only diagonals left
    for (int l = 0; l < n_squared; l++){ // pour chaque petit carré
        for (int i = l*n_squared; i < (l+1)*n_squared; i++){ // on lit les cases du carré
            for (int k = i+1; k < (l+1)*n_squared; k++){ // on lit les voisins carréïques de la case i
                // on évite les voisins verticaux
                if ((nodes_in_order_of_squares[k]- nodes_in_order_of_squares[i])%n_squared == 0) continue;
                // on évite les voisins horizontaux
                if (std::abs(nodes_in_order_of_squares[k]-nodes_in_order_of_squares[i]) < n) continue;
                // on écrit tout le reste comme arcs
                f << nodes_in_order_of_squares[i] << " " << nodes_in_order_of_squares[k] << std::endl;
            }
        }
    }

    f.close();
}