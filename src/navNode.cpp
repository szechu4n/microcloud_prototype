/*
Austin Pollard
CPE496/496
File: navNode.cpp   MOST RECENT COPY for Austin 2-3-22
Compiler: g++ 9.3.0 | Compile with: g++ navNode.cpp -o navNode
                       Run with : ./navNode Map.txt"

Functionality: reads in 'Map.txt' and populates 2-d array
                also prints matrix to terminal
                will need to handle pathfinding

Description: *-------NEEDS MORE DISCUSSION---------*
    1. Will need to read in variabele caravan x and y cooridatntes
            read in destincation.x_pos and .y_pos 
    2. change pix_map[destination.x_pos][destination.y_pos] to some int that represents caravan

    x. will need to have algorithm to see if there is path from 
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


//void readMap(char* file , int [SIZE][SIZE]);
//void printMap(int [SIZE][SIZE]);


int main(int argc, char* argv[])
{
     // init structures
    struct caravan car1;
    struct destination dest;
    // Initialize the arrays
    int pix_map[SIZE][SIZE];
    int temp_map[SIZE][SIZE];  // holds pix map while pix_map is updated
    int coord[4];    
    // string init
    char* mapFile = argv[1];
   
    // preset x and y cooridantes for 
    // car1.x_pos = 1;
    // car1.y_pos = 15;
    // dest.x_pos = 4;
    // dest.y_pos = 10;

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
                cout << "[i] |[j]";
                for(int j = 0; j < SIZE; j++) {
                    cout << left << setw(4) << j;
                }
                cout << endl;
                //readMap(mapFile, pix_map);
                readData(mapFile, pix_map, coord);
                //printMap(pix_map);
                update_temp_map(pix_map, temp_map);
                printMap(temp_map);
                // assign start and stop coordinates from .txt file
                car1.x_pos = coord[0];
                car1.y_pos = coord[1];
                dest.x_pos = coord[2];
                dest.y_pos = coord[3];
                pix_map[car1.y_pos][car1.x_pos] = 3;
                pix_map[dest.y_pos][dest.x_pos] = 2;
                printMap(pix_map);

                cout <<"Caravan x-pos: " << car1.x_pos << ".\nCaravan y-pos: "<< car1.y_pos << ".\nDestination x-pos: "<< dest.x_pos << ".\nDestination y-pos: "<< dest.y_pos << ".\n";
                }
            else {
                cout << "WRONG FILE INPUT.\nShould be ./<executbale name> Map.txt\n";
                return -2;
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

// struct readMap(char* file, int map[SIZE][SIZE],int caravan::* car, int destination::* dest){
//     ifstream mapFile;
//     mapFile.open(file);
//     caravan *_caravan = new caravan();
//     destination *_destination = new destination();
//     mapFile >> _caravan->x_pos >> _caravan->y_pos >> _destination->x_pos >> _destination->y_pos;
//     //cout << "x_car = " << x_car << "\ny_car = " << y_car << "\nx_dest = " << x_dest << "\ny_dest = " << y_dest << endl;
//     for(int i = 0; i < SIZE; i++) {
//         for(int j = 0; j < SIZE; j++) {
//             mapFile >> map[i][j];
//         }
//     }
//     return &_caravan;
// }

void readData( char* file, int map[SIZE][SIZE], int coord[4]){//int x_car, int y_car, int x_dest, int y_dest){
    ifstream mapFile;
    mapFile.open(file);
    mapFile >> coord[0] >> coord[1] >> coord[2] >> coord[3];
    //cout << "x_car = " << coord[0] << "\ny_car = " << coord[1] << "\nx_dest = " << coord[2] << "\ny_dest = " << coord[3] << endl;
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            mapFile >> map[i][j];
        }
    }
    
}

// void readMap( char* file, int map[SIZE][SIZE]){
//     ifstream mapFile;
//     mapFile.open(file);
//     mapFile >> x_car >> y_car >> x_dest >> y_dest;
//     cout << "x_car = " << x_car << "\ny_car = " << y_car << "\nx_dest = " << x_dest << "\ny_dest = " << y_dest << endl;
//     for(int i = 0; i < SIZE; i++) {
//         for(int j = 0; j < SIZE; j++) {
//             mapFile >> map[i][j];
//         }
//     }
    
// }


void printMap(int a[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        cout << left << setw(4) << i << "|\t"  ;     // shows row number
        for(int j = 0; j < SIZE; j++) {
            cout << left << setw(4) << a[i][j];
        }
        cout << endl;
    }
}

/*
Will be recursviley called in the update_map function
*/
void update_temp_map(int a[SIZE][SIZE], int a_temp[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            a_temp[i][j] = a[i][j];
            //cout << "a = "<<a[i][j] << " a_temp =" << a_temp[i][j] << endl;
        }
    }
}