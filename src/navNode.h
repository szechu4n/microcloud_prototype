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

// Function Declaration------------------------
// void readMap(char* file , int [SIZE][SIZE]);  //DONE
void readData(char* file , int [SIZE][SIZE], int [4]); // Done reads in map and dest and start coordinates
// void readMap(char* file , int [SIZE][SIZE], int caravan::* , int destination::* );
void printMap(int [SIZE][SIZE]);  //DONE


void update_temp_map(int [SIZE][SIZE], int [SIZE][SIZE]); /// in progress

int get_x_pos(int x_pos);       //can get x pos from text file
int get_y_pos(int y_pos);       // can get pos from text file
                                    // call  get_x_pos(caravan.x_pos_car); maybe
bool get_direction(bool direction);
int horiz_dist(int x_start, int x_dest);
int vert_distance(int y_start, int y_dest);
void move_direction(bool direct);   // only moves one direction at a time.
void map_redraw(int map[SIZE][SIZE]); // redraws matrix based off direction value

struct caravan  // could be car if we want multiple seperate vehicles
{
    int x_pos;
    int y_pos;
   int fuel;   //could have certain amount of fuel tofind most effecient way.
    bool on_path;
    struct direction        // for direction we could just
    {                         // horizontal and veritcal and move diaganol
        bool north;            // if map arrays updated horizontally it might
        bool south;             // a little more difficult
        bool west;
        bool east;
    };
};

struct destination
{
    int x_pos;
    int y_pos;
};

#endif // NAVNODE_H