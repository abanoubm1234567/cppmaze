#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

void initMaze(char* p, int size);
void printMaze(char* p, int size);
void generateMaze(char* p, int size);
void backtracking(char* start, char* p, int size);
int get_x_pos(char* start, char* p, int size);
int get_y_pos(char* start, char* p, int size);
char* get_left(char* p, int size);
char* get_right(char* p, int size);
char* get_up(char* p, int size);
char* get_down(char* p, int size);

int main(){
    unsigned int size = 51; // maze will be 51x51 
    char maze[size][size];
    srand(time(0));
    initMaze((char*)maze, size );
    printMaze((char*)maze, size);
    generateMaze((char*)maze, size);
    printMaze((char*) maze, size);
    return 0;
}

void initMaze(char* p, int size){
    for (int i = 0; i < size*size; i++) {           // put dots everywhere
        *(p+i) = '.';
    }
    for (int i = 0; i< size; i++){                  // upper boundary
        *(p+i) = 'X';
    }
    for (int i = size*(size-1); i< size*size; i++){ // bottom boundary
        *(p+i) = 'X';
    }
    for (int i = 0; i<size*size;i+=size){           // left boundary
        *(p+i) = 'X';
    }
    for(int i = size-1; i<size*size; i+=size){      // right boundary
        *(p+i) = 'X';
    }
    for (int i = 2; i < size; i+=2) {               // vertical columns
        for (int j = i; j<size*size; j+=size) {
            *(p+j) = 'X'; 
        } 
    }
    for (int i = 2; i< size; i+=2){                 // horizontal columns
        for (int j = (i*size); j<((i*size)+size); j++) {
            *(p+j) = 'X';
        }
    }
}

void printMaze(char *p, int size){
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //std::system("clear");
    std::cout << "\033[2J\033[H";
    std::cout<<std::endl;
    for (int i = 0; i<size*size; i++) {
        std::cout<<*(p+i);
        if ((i+1)%size == 0){
            std::cout<<"\n";
        }
    }
    std::cout<<std::endl;
}

void generateMaze(char *p, int size){
    char *start = p;
    int x_pos;
    int y_pos;
    //std::cout<<"x_pos: "<<x_pos<<"\t"<<"y_pos: "<<y_pos<<std::endl;
    do {
        p = start;
        x_pos = 2+(rand()%(size-2));
        y_pos = 2+(rand()%(size-2));
        p+=((y_pos*size)+(x_pos));
        //std::cout<<"generated x: "<<x_pos<<" y: "<<y_pos<<std::endl;
        //std::cout<<"char at p: "<<*p<<std::endl;
    }while (*(p)!='.');
    //int x = get_x_pos(start, p, size);
    //int y = get_y_pos(start, p, size);
    //std::cout<<"helper function x: "<<x<<"y: "<<y<<std::endl;
    backtracking(start, p ,size);
}

void backtracking(char* start, char *p, int size){
    if ((*p)!='.'){
        return;
    }
    *p = ' '; // represents being visited

    std::vector<char> options = {};


    bool l_avail = ((get_x_pos(start, p, size)>1) && (*(get_left(p, size))=='.')); //dot means unvisited
    bool r_avail = ((get_x_pos(start, p, size)<size-2) && (*(get_right(p, size))=='.')); //dot means unvisited
    bool d_avail = ((get_y_pos(start, p, size)<size-2) && (*(get_down(p, size))=='.')); //dot means unvisited
    bool u_avail = ((get_y_pos(start, p, size)>1) && (*(get_up(p, size))=='.')); //dot means unvisited


    if (l_avail){
        options.push_back('l');
    }
    if (r_avail){
        options.push_back('r');
    }
    if (d_avail){
        options.push_back('d');
    }
    if (u_avail){
        options.push_back('u');
    }

    while(1){
        
        l_avail = ((get_x_pos(start, p, size)>1) && (*(get_left(p, size))=='.')); //dot means unvisited
        r_avail = ((get_x_pos(start, p, size)<size-2) && (*(get_right(p, size))=='.')); //dot means unvisited
        d_avail = ((get_y_pos(start, p, size)<size-2) && (*(get_down(p, size))=='.')); //dot means unvisited
        u_avail = ((get_y_pos(start, p, size)>1) && (*(get_up(p, size))=='.')); //dot means unvisited

        if (!(l_avail || r_avail || d_avail || u_avail)){
            break;
        }

        auto it = options.begin();
        char choice = options[rand()%options.size()];
        switch (choice) {
            case 'l': 
                //std::cout<<"===========================================\n\nleft avail: "<<l_avail<<std::endl;
                //std::cout<<"right avail: "<<r_avail<<std::endl;
                //std::cout<<"down avail: "<<d_avail<<std::endl;
                //std::cout<<"up avail: "<<u_avail<<std::endl;
                printMaze(start, size);
                //std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
                //std::cout<<"Going left"<<std::endl;
                l_avail = false;
                it = std::find(options.begin(), options.end(), 'l');
                if (it != options.end()){
                    options.erase(it);
                }
                *(p-1) = ' ';
                backtracking(start, get_left(p, size), size);
                break;
            case 'r':
               // std::cout<<"===========================================\n\nleft avail: "<<l_avail<<std::endl;
               // std::cout<<"right avail: "<<r_avail<<std::endl;
               // std::cout<<"down avail: "<<d_avail<<std::endl;
               // std::cout<<"up avail: "<<u_avail<<std::endl;
                printMaze(start, size);
               // std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
               // std::cout<<"Going right"<<std::endl;
                r_avail = false;
                it = std::find(options.begin(), options.end(), 'r');
                if (it != options.end()){
                    options.erase(it);
                }
                *(p+1) = ' ';
                backtracking(start, get_right(p, size), size);
                break;
            case 'd':
               // std::cout<<"===========================================\n\nleft avail: "<<l_avail<<std::endl;
               // std::cout<<"right avail: "<<r_avail<<std::endl;
               // std::cout<<"down avail: "<<d_avail<<std::endl;
               // std::cout<<"up avail: "<<u_avail<<std::endl;
                printMaze(start, size);
               // std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
               // std::cout<<"Going down"<<std::endl;
                it = std::find(options.begin(), options.end(), 'd');
                if (it != options.end()){
                    options.erase(it);
                }
                d_avail = false;
                *(p+size) = ' ';
                backtracking(start, get_down(p, size), size);
                break;
            case 'u':
               // std::cout<<"===========================================\n\nleft avail: "<<l_avail<<std::endl;
               // std::cout<<"right avail: "<<r_avail<<std::endl;
               // std::cout<<"down avail: "<<d_avail<<std::endl;
               // std::cout<<"up avail: "<<u_avail<<std::endl;
                printMaze(start, size);
               // std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
               // std::cout<<"Going up"<<std::endl;
                it = std::find(options.begin(), options.end(), 'u');
                if (it != options.end()){
                    options.erase(it);
                }
                u_avail = false;
                *(p-size) = ' ';
                backtracking(start, get_up(p, size), size);
                break;
        }
    }
    return;
}

int get_x_pos(char* start, char* p, int size){
    return (p-start)%size;
}

int get_y_pos(char* start, char* p, int size){
    return (p-start)/size;
}

char* get_left(char* p, int size){
    return p-2;
}

char* get_right(char* p, int size){
    return p+2;
}

char* get_up(char* p, int size){
    return p-(2*size);
}

char* get_down(char* p, int size){
    return p+(2*size);
}
