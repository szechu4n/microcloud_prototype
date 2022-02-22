/*
Author: Austin Pollard
CPE496/496
File: navNode.h
Description: 
     
*/
#ifndef NAVNODE_H
#define NAVNODE_H

//#include "node.h"

#define SIZE  20 // number cols/rows in Grid

// Structure Declarations
struct caravan  // could be car if we want multiple seperate vehicles
{
    int x_pos;
    int y_pos;
    //int fuel;   //could have certain amount of fuel tofind most effecient way.PROBS NOT VIABLE
    //bool on_path;
    bool north;
    bool south;
    bool east;
    bool west;
    
};

struct destination
{
    int x_pos;
    int y_pos;
};

typedef struct BFSElement {
    BFSElement(int i, int j)
    {
        this->i = i;
        this->j = j;
    }
    int i;
    int j;
} BFSElement;

// Function Declaration------------------------
void readData(char* file , int [SIZE][SIZE], int [4]); // Done reads in map and dest and start coordinates
void printMap(int [SIZE][SIZE]);  //DONE
bool findPath(int [SIZE][SIZE]);
//caravan move_direction(int x_start, int y_start, caravan , int [SIZE][SIZE], int [SIZE][SIZE]);
caravan move_direction(caravan car1, int [SIZE][SIZE], int [SIZE][SIZE]);

void update_temp_map(int [SIZE][SIZE], int [SIZE][SIZE]); /// in progress


caravan get_direction(int x_start, int y_start, int x_stop , int y_stop, caravan car1);




#endif // NAVNODE_H