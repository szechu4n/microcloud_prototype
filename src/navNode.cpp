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

char map[SIZE][SIZE];
struct destination start;
struct destination finish;
struct caravan car1;

/*int main(int argc, char* argv[])
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
            else 
            {
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


void navMsgCallback(char * message)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; i < SIZE; i++)
        {
            map[i][j] = message[i + j];
        }
    }
    start.x_pos = message[SIZE * 2];
    start.y_pos = message[SIZE * 2 + 1];
    finish.x_pos = message[SIZE * 2 + 2];
    finish.y_pos = message[SIZE * 2 + 3];    
}

void navMapPlan()
{
    map[start.y_pos][start.x_pos] = 3;    // start point    // pix_map[i][j]
    map[finish.y_pos][finish.x_pos] = 2;    // stop point     // pix_map[y][x]
    //update_temp_map(pix_map, temp_map);
    printf("Is there a path from start[%d][%d] to destination[%d][%d]?: ", car1.y_pos, car1.x_pos, dest.y_pos, dest.x_pos);
    findPath(map) ? cout << "Yes\n"       // sets path elements =0,so need to set map = to temp_map
                        : cout << "No" << endl;
    //update_temp_map(temp_map, pix_map);
    car1 = changeDirection(car1.x_pos, car1.y_pos, dest.x_pos , dest.y_pos , car1);
    while(map[dest.y_pos][dest.x_pos] != 4)
    {
        bool boundsSuccess = checkBounds();
        bool directionSuccess = checkDirection();
        if (boundsSuccess && directionSuccess)
        {
            move_direction();
        }
        else if (!boundsSuccess)
        {
            direction = (direction + 2) % 4;
        }
        else if (!directionSuccess)
        {
            direction = (direction + 1) % 4;
        }
        
        
        
        changeDirection(&car1, finish);
        car1 = move_direction(car1, pix_map, temp_map);            
    }
    cout << "Navigation Complete!!\n";
}

void navStepSend()
{

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

void move_direction(caravan * car, int a[SIZE][SIZE], int a_temp[SIZE][SIZE]){   // moves one elemenent then reprints map
    if (car->direction == North){
        if(a[car->y_pos - 1][car->x_pos] == 1){
            a[car->y_pos][car->x_pos] = 1;//a_temp[car->y_pos][car->x_pos];    // replace current element (car1 position) with 1
            car->y_pos = car->y_pos - 1;      // sets car->y_pos to 1 element above curent location
            a[car->y_pos][car->x_pos] = 3;
            return;
        }
        if(a[car->y_pos - 1][car->x_pos] == 0){
            car->direction = South;
        }
        if(a[car->y_pos - 1][car->x_pos] == 2){
            a[car->y_pos][car->x_pos] = 1;
            car->y_pos = car->y_pos - 1;      
            a[car->y_pos][car->x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }    
    if (car->direction == true){
        if(a[car->y_pos + 1][car->x_pos] == 1){
            a[car->y_pos][car->x_pos] = 1;//a_temp[car->y_pos][car->x_pos];    // replace current element (car1 position) with 1
            car->y_pos = car->y_pos + 1;      // sets car->y_pos to 1 element above curent location
            a[car->y_pos][car->x_pos] = 3;
            return;
        }

        else if(a[car->y_pos + 1][car->x_pos] == 0){
            car->direction = false;
        }
        if(a[car->y_pos + 1][car->x_pos] == 2){
            a[car->y_pos][car->x_pos] = 1;
            car->y_pos = car->y_pos + 1;      
            a[car->y_pos][car->x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    if (car->direction == true){
        if(a[car->y_pos][car->x_pos + 1] == 1){
            a[car->y_pos][car->x_pos] = 1;//a_temp[car->y_pos][car->x_pos];    // replace current element (car1 position) with 1
            car->y_pos = car->x_pos + 1;      // sets car->y_pos to 1 element above curent location
            a[car->y_pos][car->x_pos] = 3;
            return;
        }

        if(a[car->y_pos][car->x_pos + 1] == 0){
            car->direction = false;
        }
        if(a[car->y_pos][car->x_pos + 1] == 2){
            a[car->y_pos][car->x_pos] = 1;
            car->x_pos = car->x_pos + 1;      
            a[car->y_pos][car->x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    if (car->direction == true){
        if(a[car->y_pos][car->x_pos - 1] == 1){
            a[car->y_pos][car->x_pos] = 1;//a_temp[car->y_pos][car->x_pos];    // replace current element (car1 position) with 1
            car->y_pos = car->x_pos - 1;      // sets car->y_pos to 1 element above curent location
            a[car->y_pos][car->x_pos] = 3;
            return;
        }

        if(a[car->y_pos][car->x_pos -1] == 0){
            changeDirection(&car, dest);
        }
        if(a[car->y_pos][car->x_pos - 1] == 2){
            a[car->y_pos][car->x_pos] = 1;
            car->x_pos = car->x_pos - 1;      
            a[car->y_pos][car->x_pos] = 4;    // element value of 4 means caravan has reached destination.
        }
    }
    printMap(a);
    update_temp_map(a,a_temp);
    return car;                                             
}


void changeDirection(caravan * car, const destination & dest){
    int horiz_dist = dest.x_pos - car->x_pos;
    int vert_dist = dest.y_pos - car->y_pos;
    if (horiz_dist > 0)
    {
        car->direction = East;
    }
    else if (horiz_dist < 0)
    {
        car->direction = West;
    }
    else if (vert_dist < 0)
    {
        car->direction = South;
    }
    else if (vert_dist > 0)
    {
        car->direction = North;
    }
    else
    {
        car->direction = Done;
    }
}

 
bool findPath(char M[SIZE][SIZE])
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
}*/
 