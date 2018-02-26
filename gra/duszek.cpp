#include <allegro.h>
#include <cstdlib>

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
