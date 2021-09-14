#include<bits/stdc++.h>
#include <conio.h>
#include <unistd.h>

using namespace std;

struct pos{
    int x;
    int y;

    pos(int a, int b){
        x=a;
        y=b;
    }
};

int SIZE_X;
int SIZE_Y;
int SPEED;

queue<pos> snake;

void ask(string s){
    cout << s << '\n';
}

void clear(){
    //cout << "\033[2J\033[1;1H"; esto es en linux
    system("CLS");
}

vector<string> mapa;

char WALL_CHAR='#';
char SNAKE_CHAR='S';
char APPLE_CHAR='O';

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int dir_ac=KEY_RIGHT;

bool alive=false;

pos position(0,0);

int SCORE=0;

///////////////

void title(){ //esto podría mostrar uns imagen de serpiente o algo así xd

} 

void setup(){ //ask the user things, to be displayed after entering the game
    string answer;
    ask("Do you want to play with recommended settings? (y/n)");
    while(cin >> answer){
        //clear();
        if (answer[0]=='Y' || answer[0]=='y') break;
        else if (answer[0]=='N' || answer[0]=='n') break;
        ask("I don't understand your answer. Please write yes or no.");
    }
    if (answer[0]=='Y' || answer[0]=='y'){
        SIZE_X=10;
        SIZE_Y=10;
        SPEED=10;
    }
    else{
        clear();
        ask("What do you want the height to be?");
        while (cin >> SIZE_Y){
            //clear();
            if (SIZE_Y<2 || SIZE_Y>100) ask( "Please specify a height between 2 and 100");
            else break;
        }
        clear();
        ask("What do you want the width to be?");
        while (cin >> SIZE_X){
            //clear();
            if (SIZE_X<2 || SIZE_X>100) ask("Please specify a width between 2 and 100");
            else break;
        }
        clear();
        ask("What do you want the speed to be?");
        while (cin >> SPEED){
            //clear();
            if (SPEED<1 || SPEED>50) ask("Please specify a speed between 1 and 50");
            else break;
        }
    }
}

void draw(){

    clear();

    cout << " Score: " << SCORE*100 << "           Speed: " << SPEED << '\n' << '\n';

    cout << string(2*(SIZE_X+2),WALL_CHAR) << '\n';

    for (int i=SIZE_Y-1;i>=0;i--){
        cout << WALL_CHAR << WALL_CHAR;
        for (int j=0;j<SIZE_X;j++){
            cout << mapa[i][j] << mapa[i][j];
        }
        cout << WALL_CHAR << WALL_CHAR << '\n';
    }
    
    cout << string(2*(SIZE_X+2),WALL_CHAR) << '\n';
}

void input(){ 
    if (_kbhit()){
        int c;

        switch((c=_getch())) {
        case KEY_UP:
            if (dir_ac!=KEY_DOWN) dir_ac=KEY_UP;
            break;
        case KEY_DOWN:
            if (dir_ac!=KEY_UP) dir_ac=KEY_DOWN;
            break;
        case KEY_LEFT:
            if (dir_ac!=KEY_RIGHT) dir_ac=KEY_LEFT;
            break;
        case KEY_RIGHT:
            if (dir_ac!=KEY_LEFT) dir_ac=KEY_RIGHT;
            break;
        case (int) 'x':
            alive=false;
            break;
        }
    }
}

void generate_apple(){
    pos where(rand()%SIZE_X,rand()%SIZE_Y);
    while (mapa[where.y][where.x]!=' '){
        where=pos(rand()%SIZE_X,rand()%SIZE_Y);
    }
    mapa[where.y][where.x]=APPLE_CHAR;
}

bool run(){

    mapa=vector<string>(SIZE_Y, string(SIZE_X,' '));
    mapa[0][0]=SNAKE_CHAR;
    snake=queue<pos>();
    snake.push(pos(0,0));
    SCORE=0;
    position=pos(0,0);
    dir_ac=KEY_RIGHT;

    alive=true;
    clock_t start=clock();
    int turn=1;

    generate_apple();

    while (alive){
        input();
        double time=SPEED*(clock()-start)/(((double) CLOCKS_PER_SEC));
        if (time>turn){
            sleep(0.01); //100 frames per second
            turn++;
            
            if (dir_ac==KEY_RIGHT) position.x++;
            if (dir_ac==KEY_LEFT) position.x--;
            if (dir_ac==KEY_UP) position.y++;
            if (dir_ac==KEY_DOWN) position.y--;

            if (position.x<0 || position.x>=SIZE_X || position.y>=SIZE_Y || position.y<0 || mapa[position.y][position.x]==SNAKE_CHAR){
                sleep(2);
                alive=false;
                break;
            }

            if(mapa[position.y][position.x]==APPLE_CHAR){
                SCORE++;
                generate_apple();
            }
            else{
                mapa[snake.front().y][snake.front().x]=' ';
                snake.pop();
            }
            snake.push(position);
            mapa[position.y][position.x]=SNAKE_CHAR;

            clear();
            draw();
        }
    }
    clear();
    cout << " Score: " << SCORE*100 << "           Speed: " << SPEED << '\n' << '\n';   // Score: XXXX           Speed: XX
    cout << "           GAME OVER"<< '\n';                                              //            GAME OVER
    sleep(1);
    clear();
    
    cout << " Score: " << SCORE*100 << "           Speed: " << SPEED << '\n' << '\n'; 
    cout << "           GAME OVER"<< '\n';                                        
    cout << '\n' << '\n' << '\n';
    string answer;
    ask("Do you want to play again? (y/n)");
    while(cin >> answer){
        if (answer[0]=='Y' || answer[0]=='y') return 1;
        else if (answer[0]=='N' || answer[0]=='n') return 0;
        ask("I don't understand your answer. Please write yes or no.");
    }
    
}


int main(){ 
    srand(time(0));

    clear();
    title();
    setup();
    while (run()){}
    
}
