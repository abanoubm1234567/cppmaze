#include <cstdlib>
#include <ctime>
#include <iostream>

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
    unsigned int size = 10; // maze will be 40x40 
    char maze[size][size];
    srand(time(0));
    initMaze((char*)maze, size );
    printMaze((char*)maze, size);
    generateMaze((char*)maze, size);
    printMaze((char*) maze, size);
    return 0;
}

void initMaze(char* p, int size){
    for (int i = 0; i < size*size; i++) {
        *(p+i) = '.';
    }
    for (int i = 0; i< size; i++){
        *(p+i) = 'X';
    }
    for (int i = size*(size-1); i< size*size; i++){
        *(p+i) = 'X';
    }
    for (int i = 0; i<size*size;i+=size){
        *(p+i) = 'X';
    }
    for(int i = size-1; i<size*size; i+=size){
        *(p+i) = 'X';
    }
}

void printMaze(char *p, int size){
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
    int x_pos = 1+(rand()%(size-2));
    int y_pos = 1+(rand()%(size-2));
    //std::cout<<"x_pos: "<<x_pos<<"\t"<<"y_pos: "<<y_pos<<std::endl;
    p+=((y_pos*size)+(x_pos));
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
    char choice = options[rand()%4];
    *p = ' ';
    bool l_avail = *(get_left(p, size))=='.';
    bool r_avail = *(get_right(p, size))=='.';
    bool d_avail = *(get_down(p, size))=='.';
    bool u_avail = *(get_up(p, size))=='.';
    std::cout<<"x: "<<get_x_pos(start, p, size)<<"\ty: "<<get_y_pos(start, p, size)<<std::endl;
    printMaze(start, size);
    while( l_avail || r_avail || d_avail || u_avail ){
    switch (choice) {
        case 'l':
            if (l_avail){
                l_avail = false;
                if (*(p-size-1) != ' '){
                    (*(p-size-1) = 'X');
                }
                if (*(p+size-1) != ' '){
                    (*(p+size-1) = 'X');
                }
                backtracking(start, p-1, size);
                break;
            }
        case 'r':
            if (r_avail){
                r_avail = false;
                if (*(p-size+1) != ' '){
                    (*(p-size+1) = 'X');
                }
                if (*(p+size+1) != ' '){
                    (*(p+size+1) = 'X');
                }
                backtracking(start, p+1, size);
                break;
            }
        case 'd':
            if (d_avail){
                d_avail = false;
                if (*(p+size-1) != ' '){
                    (*(p+size-1) = 'X');
                }
                if (*(p+size+1) != ' '){
                    (*(p+size+1) = 'X');
                }
                backtracking(start, p+size, size);
                break;
            }
        case 'u':
            if (u_avail){
                u_avail = false;
                if (*(p-size-1) != ' '){
                    (*(p-size-1) = 'X');
                }
                if (*(p-size+1) != ' '){
                    (*(p-size+1) = 'X');
                }
                backtracking(start, p-size, size);
                break;
            }

    }
    
}
}

int get_x_pos(char* start, char* p, int size){
    return (p-start)%size;
}

int get_y_pos(char* start, char* p, int size){
    return (p-start)/size;
}


char* get_left(char* p, int size){
    return p-1;
}

char* get_right(char* p, int size){
    return p+1;
}

char* get_up(char* p, int size){
    return p-size;
}

char* get_down(char* p, int size){
    return p+size;
}
