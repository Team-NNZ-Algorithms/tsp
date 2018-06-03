#include <stdio.h>

#include "src/2-opt.hpp"
#include "src/nearest_neighbor.hpp"
#include "src/utils.hpp"

int main(int argc, char** argv) {
    if( argc < 2 ) {
        printf("Need 1 argument: [input filename]\n");
        return 1;
    }

    char* in_file = argv[1];

    read_problem(in_file);

    return 0;
}