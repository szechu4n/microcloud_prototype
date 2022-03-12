/*
Austin Pollard
CPE496/496
File: navNode.cpp   MOST RECENT COPY for Austin 2-3-22
Compiler: g++ 9.3.0 | Compile with: g++ navNode.cpp navNode.h -o navNode
                       Run with : ./navNode Map.txt"

Functionality: reads in 'Map.txt' and populates 2-d array
                also prints matrix to terminal
                will need to handle pathfinding

*/

//#include <Arduino.h>
//#include "painlessMesh.h"
#include "navNode.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <queue>
#include <stdlib.h>

using namespace std;

#define SIZE  20 // number cols/rows in Grid

int main(int argc, char* argv[])
{
     // init structures
    struct caravan car1;
    struct destination dest;
    //typedef BFSElement;
    // Initialize the arrays
    int pix_map[SIZE][SIZE];
    int temp_map[SIZE][SIZE];  // holds pix map while pix_map is updated
    int coord[4];    
    // string init
    char* mapFile = argv[1];
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
                readData(mapFile, pix_map, coord);
                // assign start and stop coordinates from .txt file
                car1.x_pos = coord[0];
                car1.y_pos = coord[1];
                dest.x_pos = coord[2];
                dest.y_pos = coord[3];
                pix_map[car1.y_pos][car1.x_pos] = 3;    // start point    // pix_map[i][j]
                pix_map[dest.y_pos][dest.x_pos] = 2;    // stop point     // pix_map[y][x]
                update_temp_map(pix_map, temp_map);
                printf("Is there a path from start[%d][%d] to destination[%d][%d]?: ", car1.y_pos, car1.x_pos, dest.y_pos, dest.x_pos);
                (findPath(pix_map) == true) ? cout << "Yes\n"       // sets path elements =0,so need to set map = to temp_map
                                    : cout << "No" << endl;
                update_temp_map(temp_map, pix_map);
                car1 = get_direction(car1.x_pos, car1.y_pos, dest.x_pos , dest.y_pos , car1);
                printMap(pix_map);
                if (car1.north == true){
                    cout << "Destination is North\n";
                    }
                if (car1.south == true){
                    cout << "Destination is South\n";
                    } 
                if (car1.east == true){
                    cout << "Destination is East\n";
                    }
                if (car1.west == true){
                    cout << "Destination is West\n";
                    } 
                }
                else {
                    cout << "WRONG FILE INPUT.\nShould be ./<executbale name> Map.txt\n";
                    return -2;
                }
                while(pix_map[dest.y_pos][dest.x_pos] != 4){
                    car1 = get_direction(car1.x_pos, car1.y_pos, dest.x_pos , dest.y_pos , car1);
                    car1 = move_direction( car1, pix_map, temp_map);            
                }
                cout << "Navigation Complete!!\n";
                return 0;
        
    }

    printf("terminating program\n");


    return 0;
}


void readData( char* file, int map[SIZE][SIZE], int coord[4]){  // used array to read in car and dest cooridanates since they are seperate structs
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


void printMap(int a[SIZE][SIZE]) {
    cout << "\n[i] |[j]";
    for(int j = 0; j < SIZE; j++) {
        cout << left << setw(4) << j;
    }
    cout << endl;
    for(int i = 0; i < SIZE; i++) {
        cout << left << setw(4) << i << "|\t"  ;     // shows row number
        for(int j = 0; j < SIZE; j++) {
            cout << left << setw(4) << a[i][j];
        }
        cout << endl;
    }
}


void update_temp_map(int a[SIZE][SIZE], int a_temp[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            a_temp[i][j] = a[i][j];
        }
    }
}

caravan move_direction(caravan car, int a[SIZE][SIZE], int a_temp[SIZE][SIZE]){   // moves one elemenent then reprints map
    if (car.north == true){
        if(a[car.y_pos - 1][car.x_pos] == 1){
            a[car.y_pos][car.x_pos] = 1;//a_temp[car.y_pos][car.x_pos];    // replace current element (car1 position) with 1
            car.y_pos = car.y_pos - 1;      // sets car.y_pos to 1 element above curent location
            a[car.y_pos][car.x_pos] = 3;
            printMap(a);
            return car;
        }
        if(a[car.y_pos - 1][car.x_pos] == 0){
            car.north == false;
        }
        if(a[car.y_pos - 1][car.x_pos] == 2){
            a[car.y_pos][car.x_pos] = 1;
            car.y_pos = car.y_pos - 1;      
            a[car.y_pos][car.x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }    
    if (car.south == true){
        if(a[car.y_pos + 1][car.x_pos] == 1){
            a[car.y_pos][car.x_pos] = 1;//a_temp[car.y_pos][car.x_pos];
            car.y_pos = car.y_pos + 1;
            a[car.y_pos][car.x_pos] = 3;
            printMap(a);
            return car;

        }
        else if(a[car.y_pos + 1][car.x_pos] == 0){
            car.south = false;
        }
        if(a[car.y_pos + 1][car.x_pos] == 2){
            a[car.y_pos][car.x_pos] = 1;
            car.y_pos = car.y_pos + 1;      
            a[car.y_pos][car.x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    if (car.east == true){
        if(a[car.y_pos][car.x_pos + 1] == 1){
            a[car.y_pos][car.x_pos] = 1;//a_temp[car.y_pos][car.x_pos];
            car.x_pos = car.x_pos + 1;
            a[car.y_pos][car.x_pos] = 3;
            printMap(a);
            return car;

        }
        if(a[car.y_pos][car.x_pos + 1] == 0){
            car.east = false;
        }
        if(a[car.y_pos][car.x_pos + 1] == 2){
            a[car.y_pos][car.x_pos] = 1;
            car.x_pos = car.x_pos + 1;      
            a[car.y_pos][car.x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    if (car.west == true){
        if(a[car.y_pos][car.x_pos - 1] == 1){
            a[car.y_pos][car.x_pos] = 1;//a_temp[car.y_pos][car.x_pos];
            car.x_pos = car.x_pos - 1;
            a[car.y_pos][car.x_pos] = 3;
            printMap(a);
            return car;

        }
        if(a[car.y_pos][car.x_pos -1] == 0){
            car.west = false;
        }
        if(a[car.y_pos][car.x_pos - 1] == 2){
            a[car.y_pos][car.x_pos] = 1;
            car.x_pos = car.x_pos - 1;      
            a[car.y_pos][car.x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    printMap(a);
    update_temp_map(a,a_temp);
    return car;                                             
}


caravan get_direction(int x_start, int y_start, int x_stop ,int y_stop ,caravan car){
    int horiz_dist = x_stop - x_start;
    int vert_dist = y_start - y_stop;
    cout << "horiz_dist: "<<horiz_dist<<" vert_dist: "<< vert_dist<< endl;
    if (horiz_dist > 0){
        car.east = true;
        //cout << car.west << endl;
        car.west = false;
    }
    if (horiz_dist < 0){
        car.east = false;
        car.west = true;
    }
    if (vert_dist < 0){
        car.north = false;
        car.south = true;
    }
    if (vert_dist > 0){
        car.north = true;
        car.south = false;
    }
    else if (horiz_dist == 0){
        car.east = false;
        car.west = false;
    }
    else if (vert_dist == 0){
        car.north = false;
        car.south = false;
    }
    return car;
}

 
bool findPath(int M[SIZE][SIZE])
{
    // 1) Create BFS queue q
    queue<BFSElement> q;
 
    // 2)scan the matrix
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
           
            // if there exists a cell in the matrix such
            // that its value is 3 then push it to q
            if (M[i][j] == 3) {     
                q.push(BFSElement(i, j));
                break;
            }
        }
    }
   
    // 3) run BFS algorithm with q.
    while (!q.empty()) {
        BFSElement x = q.front();
        q.pop();
        int i = x.i;
        int j = x.j;
       
        // skipping cells which are not valid.
        // if outside the matrix bounds
        if (i < 0 || i > SIZE || j < 0 || j > SIZE)
            continue;
       
        // if they are walls (value is 0).
        if (M[i][j] == 0)
            continue;
 
        // 3.1) if in the BFS algorithm process there was a
        // vertex x=(i,j) such that M[i][j] is 2 stop and
        // return true
        if (M[i][j] == 2)
            return true;
       
        // marking as wall upon successful visitation
        M[i][j] = 0;
 
        // pushing to queue u=(i,j+1),u=(i,j-1)
        //                 u=(i+1,j),u=(i-1,j)
        for (int k = -1; k <= 1; k += 2) {
            q.push(BFSElement(i + k, j));
            q.push(BFSElement(i, j + k));
        }
    }
   
    // BFS algorithm terminated without returning true
    // then there was no element M[i][j] which is 2, then
    // return false
    return false;
}
 