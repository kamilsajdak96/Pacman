#include <allegro.h>
#include <cstdlib>
#include <winalleg.h>
#define MAX_WIERSZ 20
#define MAX_KOL 31

BITMAP *bufor;
BITMAP *bitmaptxt;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *coin;
BITMAP *bite;


int antyerrorpx, antyerrorpy;
int dir=4;
int px=30*14, py=30*17;

char mapa[MAX_WIERSZ][MAX_KOL]={
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "X|ooooooooo|XXXXX|ooooooooo|X",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "XoXXXoooooo|ooooo|ooooooXXXoX",
  "XoXXX XX XXXXXXXXXXX XX XXXoX",
  "XoXXX|XX    |XXX|    XX|XXXoX",
  "XoXXX XXXXXX XXX XXXXXX XXXoX",
  "XoXXX                   XXXoX",
  " o   |XX XXXXXXXXXXX XX|   o ",
  " o   |XX XXXXXXXXXXX XX|   o ",
  "XoXXX                   XXXoX",
  "XoXXX XXXXXX XXX XXXXXX XXXoX",
  "XoXXX XX     XXX     XX XXXoX",
  "XoXXX XX XXXXXXXXXXX XX XXXoX",
  "XoXXX|oo|ooooooooooo|oo|XXXoX",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "XoXXX XXXXX       XXXXX XXXoX",
  "XoooooooooooXXXXXoooooooooooX",
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};


 void draw_mapa(){
    int wiersze, kol;

    for(wiersze = 0; wiersze< MAX_WIERSZ ; wiersze++)
    {
        for(kol =  0; kol < MAX_KOL; kol++){
            if(mapa[wiersze][kol] == 'X')
            {
                draw_sprite(bufor, bitmaptxt, kol*880, wiersze*600);
            }
            else if(mapa[wiersze][kol] == 'o'){
                draw_sprite(bufor, coin, kol*30, wiersze*30);
                if(py/30==wiersze && px/30==kol)
                mapa[wiersze][kol] = ' ';
            }
        }
    }
 }


void ekran()
{
    blit(bufor, screen, 0,0,0,0,880, 600);
    load_bitmap("bitmaptxt.bmp",NULL);
}

void draw_pacman()
{
    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(bufor, pacman, px, py);

}


class duszek{
BITMAP *ghost;
BITMAP *ghostbmp;
int fdir;
int _x, _y;
public:
    duszek(int x, int y); //konstruktor
    void draw_duszek() const;
    void move_duszek();
    void choke_pacman();
};
duszek::duszek(int x, int y){
_x=x;
_y=y;
fdir=rand()%4;
ghost = create_bitmap(30,30);
ghostbmp = load_bitmap("ghost.bmp", NULL);
}
void duszek::draw_duszek() const{
 blit(ghostbmp,ghost,0,0,0,0,30,30);
    draw_sprite(bufor, ghost, _x, _y);
}
void duszek::choke_pacman(){
    if((py == _y && px == _x) || (_y==antyerrorpy && _x == antyerrorpx)){

        for(int j= 0; j<=5; j++){
           clear(pacman);
           clear(bufor);
           draw_mapa();

           blit(bite, pacman,j*33,0,0,0,33,33);
           draw_sprite(bufor, pacman, px, py);

           ekran();
           rest(60);

        }
        px=30*14;
        py=30*17;
        dir = 4;

    }
}

void duszek::move_duszek(){

draw_duszek();
    choke_pacman();

    if(mapa[_y/30][_x/30]=='|'){
        fdir=rand()%4;
    }

    if(fdir == 0){
        if(mapa[_y/30][(_x-30)/30] != 'X')_x-=30;
        else fdir=rand()%3;
    }
    if(fdir == 1){
        if(mapa[_y/30][(_x+30)/30] != 'X')_x+=30;
        else fdir=rand()%3;
    }
     if(fdir == 2){
        if(mapa[(_y-30)/30][(_x)/30] != 'X')_y-=30;
        else fdir=rand()%3;
    }
     if(fdir == 3){
        if(mapa[(_y+30)/30][_x/30] != 'X')_y+=30;
        else fdir=rand()%3;
    }
    //duszek przez dziury
    if(_x<= -30) _x = 870;
    else if(_x>=870) _x= -30;
}


bool game_over(){
    int wiersze, kol;

    for(wiersze = 0; wiersze< MAX_WIERSZ ; wiersze++)
    {
        for(kol =  0; kol < MAX_KOL; kol++){
            if(mapa[wiersze][kol] == 'o')
            {
                return true;

            }
                                            }
}
}

class menuu{
BITMAP *menu_con;
BITMAP *menu_con1;
BITMAP *menu_kon;
BITMAP *menu_kon1;
BITMAP *menu_m;
BITMAP *menu_m1;
BITMAP *menu_exit;
BITMAP *menu_exit1;
public:
    menuu(); //konstruktor
    void exitowa();
    void menu_continue();
    void menu();
    void koniec();
};

menuu::menuu(){

    menu_con=load_bitmap("menu_con.bmp", NULL);
    menu_con1=load_bitmap("menu_con1.bmp", NULL);
    menu_kon=load_bitmap("menu_kon.bmp", NULL);
    menu_kon1=load_bitmap("menu_kon1.bmp", NULL);
    menu_m=load_bitmap("menu_m.bmp", NULL);
    menu_m1=load_bitmap("menu_m1.bmp", NULL);
    menu_exit=load_bitmap("menu_exit.bmp", NULL);
    menu_exit1=load_bitmap("menu_exit1.bmp", NULL);

}



void menuu::menu(){

    int selection = 1;
    bool selected = false;
    while(!selected){
            if(selection == 1){
                               draw_sprite(screen, menu_m,0,0);
            } else if(selection ==  2){
                draw_sprite(screen, menu_m1,0,0);
            }

        if(key[KEY_UP]){
            selection = 1;
        }

        if(key[KEY_DOWN]){
            selection = 2;
        }

        if(key[KEY_ENTER] && selection == 1){
            selected = true;

            draw_sprite(screen, menu_m,0,0);
        } else if(key[KEY_ENTER] && selection == 2){
            selected = false;
            draw_sprite(screen, menu_m1,0,0);
            Sleep(350);
           exitowa();

        }

        clear_bitmap(bufor);

    }

}

void menuu::koniec()
{
    int timer = 0;
    int selection = 1;
    bool selected = false;

    while(!selected){


                if(timer <= 0){
                    draw_sprite(screen, menu_kon,0,0);
                  rest(100);
                    timer = 1;
                } else {
                    draw_sprite(screen, menu_kon1,0,0);
                    rest(100);
                    timer--;
                }



            if(selection == 1){

    draw_sprite(screen, menu_kon,0,0);
            }

        if(key[KEY_ENTER] && selection == 1){
            selected = true;
   }

        clear_bitmap(bufor);

    }

}


void menuu::exitowa(){

 int selection = 1;
    bool selected = false;
    while(!selected){

            if(selection == 1){
                               draw_sprite(screen, menu_exit,0,0);
                        } else if(selection ==  2){
                draw_sprite(screen, menu_exit1,0,0);
            }

        if(key[KEY_LEFT]){
            selection = 2;
        }

        if(key[KEY_RIGHT]){
            selection = 1;
        }

        if(key[KEY_ENTER] && selection == 1){
                Sleep(300);
            selected = true;

            draw_sprite(screen, menu_exit,0,0);
        } else if(key[KEY_ENTER] && selection == 2){
            Sleep(300);
            selected = true;
            exit(0);

        }

        clear_bitmap(bufor);
    }


}
void menuu::menu_continue(){


 int selection = 1;
    bool selected=false;
    while(!selected){

            if(selection == 1){
                               draw_sprite(screen, menu_con,0,0);
            } else if(selection ==  2){
                draw_sprite(screen, menu_con1,0,0);
            }

        if(key[KEY_LEFT]){
            selection = 1;
        }

        if(key[KEY_RIGHT]){
            selection = 2;
        }

        if(key[KEY_ENTER] && selection == 1){
            selected = true;

            draw_sprite(screen, menu_con,0,0);
        } else if(key[KEY_ENTER] && selection == 2){

            Sleep(350);
 exitowa();
selected = false;

        }
        clear_bitmap(bufor);
    }
}

class graa{
public:
    graa(); //konstruktor

};
graa::graa(){

    menuu *menu1 = new menuu();
    menu1->menu();
    duszek A(30*2,30*3);
    duszek B(30*15, 30*15);
    duszek C(30*2,30*3);
    duszek D(30*15, 30*15);

    while(game_over()){
    antyerrorpx = px;
    antyerrorpy = py;
    if(key[KEY_ESC]){
       // menuu *menu1 = new menuu();
        menu1->menu_continue();
       // menu_continue();
    }
    if(key[KEY_RIGHT]) dir = 1;
    else if(key[KEY_LEFT]) dir = 0;
    else if(key[KEY_UP]) dir = 2;
    else if(key[KEY_DOWN]) dir = 3;

    if(dir==0){
        if(mapa[(py)/30][(px-30)/30]!='X')
            px -=30;
            else dir = 4;

    }
    if(dir==1) {
        if(mapa[(py)/30][(px+30)/30]!='X')
            px +=30;
            else dir = 4;
    }
    if(dir==2) {
            if(mapa[(py-30)/30][(px)/30]!='X')
            py -=30;
            else dir = 4;
    }
    if(dir==3){
             if(mapa[(py+30)/30][px/30]!='X')
            py +=30;
            else dir = 4;
    }
    if(px<= -30) px = 870;
    else if(px>=870) px= -30;

    clear(bufor);
    draw_mapa();
    draw_pacman();

    A.move_duszek();
    B.move_duszek();
    C.move_duszek();
    D.move_duszek();

    ekran();
    rest(70);

    clear(pacman);
    blit(pacbmp,pacman,4*33,0,0,0,33,33);
    draw_sprite(bufor, pacman, px, py);
    ekran();
    rest(90);

}
    if(!game_over()){
        menu1->koniec();
    }
}



int main(){

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 880 , 600, 0, 0);
    bufor= create_bitmap(880, 600);
    bitmaptxt=load_bitmap("bitmaptxt.bmp",NULL);
    pacbmp = load_bitmap("pacman.bmp", NULL);
    pacman = create_bitmap(33,33);
    coin = load_bitmap("coin.bmp",NULL);
    bite = load_bitmap("bite.bmp", NULL);
    //menuu();
    graa();
 //   koniec();
    return 0;
    }

END_OF_MAIN();
