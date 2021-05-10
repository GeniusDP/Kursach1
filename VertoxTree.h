#pragma once
#include <cstdlib>
#include <vector>
#include "Field.h"

using namespace std;

/*typedefs*/
typedef int heuristic_t;
typedef uint64_t hash_t;


struct VertoxTree {
    hash_t hash;
    Field m;
    int currDepth;
    VertoxTree* prev;
    vector<VertoxTree*> next;
    VertoxTree() {
        hash = 0;
        prev = NULL;
        currDepth = 0;
    }
};


