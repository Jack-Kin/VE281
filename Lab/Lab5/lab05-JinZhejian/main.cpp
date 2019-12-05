#include <iostream>
#include <fstream>
#include <cstring>
#include "priority_queue.h"
#include "binary_heap.h"
#include "fib_heap.h"
#include "unsorted_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

using namespace std;

struct Cell{
    int x = 0;
    int  y = 0;
    int weight = 0;
    int isReached = 0;
    int index = 0;
    int pathcost = 0;
    int predecessor_index = 0;
};

struct World{
    int width;
    int height;
    Cell Start; //only used for storing the start point of x and y, will not be modified after input
    Cell End;
    vector <Cell> grid;
};

struct compare_t
{
    bool operator()(Cell a, Cell b) const
    {
        if (a.pathcost != b.pathcost) return a.pathcost < b.pathcost;
        else{
            if  (a.x != b.x) return a.x < b.x;
            else return a.y < b.y;
        }
    }
};


void argAnalysis(int argc, char** argv, int &impl_index, bool &vFlag){
    int opt = 0, option_index = 0;
    const char* iArg = "";    //store the implementation argument
    vector<const char*> iName {"BINARY", "UNSORTED", "FIBONACCI"};  //implementation name tag

    const char *optstring = "i:v";
    static struct option long_options[] = {
            {"implementation", required_argument, nullptr, 'i'},
            {"verbose", no_argument, nullptr, 'v'}
    };

    while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
        switch (opt){
            case 'i':
                if (optarg) iArg = optarg;
                break;
            case 'v':
                vFlag = true;
                break;
            case '?':
                cout << "error optopt: " << optopt << endl;
                cout << "error opterr: " << opterr << endl;
                break;
            default:
                break;
        }
    }
    for(int i = 0; i < 3; i++){
        if(strcmp(iArg, iName[i]) == 0) impl_index = i;
    }
}



int main(int argc, char* argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool OutputMode = false; // 0 for brief, 1 for verbose
    int ImplementWay = 0; // 0 for BINARY, 1 for UNSORTED, 2 for FIBONACCI

    argAnalysis(argc, argv, ImplementWay, OutputMode);

    //initialize our priority_queue and the world
    priority_queue<Cell, compare_t> *PQ = nullptr;
    switch (ImplementWay){
        case 0 :
            PQ = new binary_heap<Cell, compare_t>;
            break;
        case 1 :
            PQ = new unsorted_heap<Cell, compare_t>;
            break;
        case 2:
            PQ = new fib_heap<Cell, compare_t>;
            break;
        default :
            cout << "Wrong input for implementation way."<< endl;
            return 0;
    }

    vector <Cell> Path;
    World world = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // input & initialization
    cin >> world.width >>  world.height >> world.Start.x >> world.Start.y >> world.End.x >> world.End.y;

    world.Start.index = world.Start.x + world.width*world.Start.y;
    world.End.index = world.End.x + world.width*world.End.y;

    int size = world.width * world.height;
    Cell cellTmp = {0,0,0,0,0,0,0};

    for (int j = 0; j < world.height; ++j) {
        for (int i = 0; i < world.width; ++i) {
            cellTmp.x = i;
            cellTmp.y = j;
            cellTmp.index = cellTmp.x + world.width*cellTmp.y;
            cin >> cellTmp.weight;
            world.grid.push_back(cellTmp);
        }
    }

    // find the shortest path
    Cell &start_point = world.grid[world.Start.index];
    Cell &end_point = world.grid[world.End.index];

    start_point.pathcost = start_point.weight;
    start_point.isReached = 1;
    PQ->enqueue(world.grid[world.Start.index]);
    int step = 0, isEnd = 0;
    while((!PQ->empty()) && ! isEnd)  {
        Cell C = PQ->dequeue_min();
        Cell *N = nullptr;
        if (OutputMode == 1) {
            cout << "Step "<< step << endl;
            cout << "Choose cell (" << C.x << ", "<< C.y << ") with accumulated length "<< C.pathcost  << "." << endl;
        }
        // for each neighbor N of C that has not been reached
        for (int i = 0; i < 4; ++i) {
            // right
            if (! isEnd && i == 0 && (C.index < size) && (world.grid[C.index + 1].isReached == 0)) {
                N = &world.grid[C.index + 1];
            }
                // down
            else if (! isEnd && i == 1 && (C.y != (world.height - 1)) && (world.grid[C.index + world.width].isReached == 0)) {
                N = &world.grid[C.index + world.width];
            }
                // left
            else if (! isEnd && i == 2 && (C.x != 0) && world.grid[C.index - 1].isReached == 0) {
                N = &world.grid[C.index - 1];
            }
                // up
            else if (! isEnd && i == 3 && (C.y != 0) && (world.grid[C.index - world.width].isReached == 0)) {
                N = &world.grid[C.index - world.width];
            } else N = nullptr;

            if  (N != nullptr) {
                N->pathcost = C.pathcost + N->weight;
                N->isReached = 1;
                N->predecessor_index = C.index;

                if ( end_point.x == N->x && end_point.y == N->y) {
                    isEnd = 1;
//                trace_back_path(): save the path into the Path vector
                    while ((N->x != start_point.x) || (N->y != start_point.y)){
                        Path.push_back(*N);
                        N = &world.grid[N->predecessor_index];
                    }
                }
                //for the output information
                    if (OutputMode == 1&& !isEnd && ((N->x != start_point.x) || (N->y != start_point.y))) {
                        cout << "Cell (" << N->x << ", "<< N->y << ") with accumulated length "<< N->pathcost  << " is added into the queue." << endl;
                    }
                    else if (OutputMode == 1&&  isEnd){
                        cout << "Cell (" << world.End.x << ", "<< world.End.y << ") with accumulated length "<< Path[0].pathcost  << " is the ending point." << endl;
                    }
                if( !isEnd) PQ->enqueue(*N);
            }
        }
        step++;
    }

    //print
    cout << "The shortest path from ("<< start_point.x  << ", " << start_point.y << ") to ("
             << end_point.x <<", " << end_point.y << ") is "<< Path[0].pathcost << "." << endl;
    cout << "Path:" << endl;
    cout << "(" << start_point.x<< ", " << start_point.y<< ")" << endl;

    for (unsigned long  j = Path.size()-1; j >=1 ; --j) {
            cout << "(" << Path[j].x<< ", " << Path[j].y<< ")" << endl;
    }
    cout << "(" << Path[0].x<< ", " << Path[0].y<< ")" << endl;


    //free the memory
    delete PQ;
    vector<Cell>().swap(Path);
    {
        vector <Cell> tmp;
        Path.swap(tmp);
    }

    return 0;
}