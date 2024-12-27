#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>

using namespace std;

// This function checks for the compatibility of each vertex for forming an edge between 2 vertex
bool compatibility(const string& word1, const string& word2) {
    for (size_t i = 0 ; i < word1.size() ; i++) {
        if (word1[i] != 'X' && word2[i] != 'X' && word1[i] != word2[i]) {
            return false;
        }
    }
    return true;
}

//This function checks for the presence of cliques in the string. A representation.
string cliques_acq(const set<int>& cliq, const vector<string>& full_word) {
    string string_clique = full_word[*cliq.begin()]; 
    for (size_t i = 0 ; i < string_clique.size() ; i++) {
        bool equal_mat = true;
        char curr_character = string_clique[i]; 
        for (int index_num : cliq) {
            if (full_word[index_num][i] != curr_character && full_word[index_num][i] != 'X') {
                equal_mat = false;
                break;
            }
        }
        if (equal_mat) {
            string_clique[i] = curr_character;
        } else {
            string_clique[i] = 'X';
        }
    }
    return string_clique;
}

// Function to find maximal clique without vertex repeating.
vector<set<int>> max_cliqeu(const vector<vector<bool>>& resutant_graph) {
    vector<set<int>> cliq_mul;  
    set<int> v_avail_multi; 

    for (size_t i = 0; i < resutant_graph.size(); ++i) {
        v_avail_multi.insert(i);
    }

    while (!v_avail_multi.empty()) {
        set<int> cliq;       
        int vert_1 = *v_avail_multi.begin();
        cliq.insert(vert_1);

        v_avail_multi.erase(vert_1);

        for (int v : v_avail_multi) {

            bool additional_possible = true;
            for (int c : cliq) {
                if (!resutant_graph[v][c]) {
                    additional_possible = false;
                    break;
                }
            }
            if (additional_possible) {
                cliq.insert(v);
            }
        }

        for (int v : cliq) {
            v_avail_multi.erase(v);
        }

        cliq_mul.push_back(cliq);
    }

    return cliq_mul;
}

int main(int total_args, char** argument_indv) {
    if (total_args != 5) {
        cerr << "Incorrect number of arguments" << endl;
        return 1;
    }

//This reads word from file
    string file_path = argument_indv[1];
    size_t number_entres = stoi(argument_indv[2]); 
    string output_file = argument_indv[4];

    ifstream input_file(file_path);
    if (!input_file) {
        cerr << "Wrong file name" << endl;
        return 1;
    }

    vector<string> full_word;
    string w;
    while (input_file >> w) {
        full_word.push_back(w);
    }
    input_file.close();

    size_t n = full_word.size(); 


//generates adjacency matrix
    vector<vector<bool>> resutant_graph(n, vector<bool>(n, false));

// construction of graph
    for (size_t i = 0 ; i < n ; i++) {
        for (size_t j = i + 1 ; j < n ; j++) {
            if (compatibility(full_word[i], full_word[j])) {
                resutant_graph[i][j] = true;
                resutant_graph[j][i] = true; 
            }
        }
    }

//Finad maximal with non-repeating vertices
    vector<set<int>> cliq_mul = max_cliqeu(resutant_graph);

    ofstream output(output_file);

    size_t w_cliq = min(number_entres, cliq_mul.size());
    for (size_t i = 0; i < w_cliq; i++) {
        string string_clique = cliques_acq(cliq_mul[i], full_word);
        output << string_clique << endl;
    }

    if (number_entres > cliq_mul.size()) {
        cerr << "Only " << cliq_mul.size() << " dictionary entries are possible" << endl;
    }
    return 0;
}

