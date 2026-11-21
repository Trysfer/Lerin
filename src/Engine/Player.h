#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        int x = 1;
        int y = 1;
    public:
        int get_x() const {return x;}
        int get_y() const {return y;}
        void set_position(int new_x, int new_y){
            x = new_x;
            y = new_y;
        }
};


#endif