#include <iostream>
#include <string>
#include <sstream>
#include "Graph.h"

int main() {
    std::string from, to;
    int no_of_lines;
    std::cin >> no_of_lines;
    int power_iterations;
    std::cin >> power_iterations;
    Graph list;

    for(int i = 0; i<no_of_lines; i++){
        std::cin >> from;
        std::cin >> to;
        list.InsertEdge(from, to);
    }

    list.CalcPageRank(power_iterations);
    list.PrintPageRank();
    return 0;
}
