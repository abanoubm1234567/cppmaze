#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

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
    std::system("clear");
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
        std::cout<<"generated x: "<<x_pos<<" y: "<<y_pos<<std::endl;
        std::cout<<"char at p: "<<*p<<std::endl;
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
    char options[4] = {'l','r','d','u'}; //representing four directions
    *p = ' '; // represents being visited
    bool l_avail = ((get_x_pos(start, p, size)>1) && (*(get_left(p, size))=='.')); //dot means unvisited
    bool r_avail = ((get_x_pos(start, p, size)<size-2) && (*(get_right(p, size))=='.')); //dot means unvisited
    bool d_avail = ((get_y_pos(start, p, size)<size-2) && (*(get_down(p, size))=='.')); //dot means unvisited
    bool u_avail = ((get_y_pos(start, p, size)>1) && (*(get_up(p, size))=='.')); //dot means unvisited
    //std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
    printMaze(start, size);
    while( l_avail || r_avail || d_avail || u_avail ){
        char choice = options[rand()%4];
        switch (choice) {
            case 'l':
                if (l_avail){
                    //std::cout<<"Going left"<<std::endl;
                    l_avail = false;
                    *(p-1) = ' ';
                    backtracking(start, get_left(p, size), size);
                }
                break;
            case 'r':
                if (r_avail){
                    //std::cout<<"Going right"<<std::endl;
                    r_avail = false;
                    *(p+1) = ' ';
                    backtracking(start, get_right(p, size), size);
                }
                break;
            case 'd':
                if (d_avail){
                    //std::cout<<"Going down"<<std::endl;
                    d_avail = false;
                    *(p+size) = ' ';
                    backtracking(start, get_down(p, size), size);
                }
                break;
            case 'u':
                if (u_avail){
                    //std::cout<<"Going up"<<std::endl;
                    u_avail = false;
                    *(p-size) = ' ';
                    backtracking(start, get_up(p, size), size);
                }
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
