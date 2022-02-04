/*
Austin Pollard
CPE496/496
File: navNode.cpp   MOST RECENT COPY for Austin 2-3-22
Compiler: g++ 9.3.0 | Compile with: g++ navNode.cpp -o navNode
                       Run with : ./navNode Map.txt"

Functionality: reads in 'Map.txt' and populates 2-d array
                also prints matrix to terminal
                will need to handle pathfinding

// Description: *-------NEEDS MORE DISCUSSION---------*
//     1. Need class for car caravan
//         - will include x-cooridanate, y-coordinate, direction, fuel level (maybe), .....
//     2. Need int matrix for map. Gray scale image so each element will be between 0-255
//         - needs to be read in from file (file type will be designated/exported by skidder)
//     3. 
*/

//#include <Arduino.h>
//#include "painlessMesh.h"
#include "navNode.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

#define SIZE  20 // number cols/rows in Grid

void readMap(char* file , int [SIZE][SIZE]);
void printMap(int [SIZE][SIZE]);


int main(int argc, char* argv[])
{
    // Initialize the arrays
    int pix_map[SIZE][SIZE];
    // string init
    char* mapFile = argv[1];

    //cout << "input file is " << argv[1] << endl;

    // open map file
    //ifstream mapFile;
    //mapFile.open(argv[1]);
    if (argc == 1){
        printf("Must enter text file name in command line\n./<executbale name> Map.txt\n");
        return -1;
    }
    if (argc > 2){
        printf("Too many input arguments\n./<executbale name> Map.txt\n");
    }
    else{
        int result = strcmp(argv[1], "Map.txt");
            if (result == 0) {
                cout << "CORRECT FILENAME" << endl;
                readMap(mapFile, pix_map);
                printMap(pix_map);
                }
            else {
                cout << "WRONG FILE INPUT.\nShould be ./<executbale name> Map.txt\n";
                exit(1);
            }
        //printf("argv[1] is ", argv[1], "\n\n");
        
        // 
        // for(int i = 0; i < SIZE; i++) {
        //     for(int j = 0; j < SIZE; j++) {
        //         mapFile >> pix_map[i][j];
        //     }
        // }
        
    }

    printf("terminating program\n");


    return 0;
}

void readMap( char* file, int map[SIZE][SIZE]){
    ifstream mapFile;
    mapFile.open(file);
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            mapFile >> map[i][j];
        }
    }
    
}

void printMap(int a[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cout << left << setw(4) << a[i][j];
        }
        cout << endl;
    }
}